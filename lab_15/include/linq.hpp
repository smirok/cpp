#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
    namespace impl {

        template<typename T, typename Iter>
        class range_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T>
        class take_enumerator;

        template<typename T, typename U, typename F>
        class select_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        template<typename T>
        class enumerator {
        public:
            virtual const T &operator*() const = 0; // Получает текущий элемент.
            virtual enumerator<T> &operator++() = 0;  // Переход к следующему элементу
            virtual explicit operator bool() const = 0;  // Возвращает true, если есть текущий элемент

            auto drop(int count) {
                return drop_enumerator<T>(*this, count);
            }

            auto take(int count) {
                return take_enumerator<T>(*this, count);
            }

            template<typename U = T, typename F>
            auto select(F functor) {
                return select_enumerator<U, T, F>(*this, std::move(functor));
            }

            template<typename F>
            auto until(F functor) {
                return until_enumerator<T, F>(*this, std::move(functor));
            }

            auto until_eq(const T &stop_item) {
                return until([&stop_item](T current_item) { return (stop_item == current_item); });
            }

            template<typename F>
            auto where(F functor) {
                return where_enumerator<T, F>(*this, std::move(functor));
            }

            auto where_neq(const T &wrong_item) {
                return where([&wrong_item](T current_item) { return (wrong_item != current_item); });
            };

            std::vector<T> to_vector() {
                std::vector<T> vec;
                for (; *this; ++*this) {
                    vec.push_back(**this);
                }
                return vec;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                for (; *this; ++*this) {
                    *it = **this;
                    ++it;
                }
            }
        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {
            }

            const T &operator*() const override {
                return *begin_;
            }

            enumerator<T> &operator++() override {
                ++begin_;
                return *this;
            }

            explicit operator bool() const override {
                return begin_ != end_;
            }

        private:
            Iter begin_, end_;
        };

        template<typename T>
        class drop_enumerator : public enumerator<T> {
        public:
            drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
                while (count && parent_) {
                    --count;
                    ++parent_;
                }
            }

            const T &operator*() const override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                return *this;
            }

            explicit operator bool() const override {
                return static_cast<bool>(parent_);
            }

        private:
            enumerator<T> &parent_;
        };

        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {
            }

            const T &operator*() const override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                --count_;
                return *this;
            }

            explicit operator bool() const override {
                return (parent_ && count_);
            }

        private:
            enumerator<T> &parent_;
            int count_;
        };

        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<T> {
        public:
            select_enumerator(enumerator<U> &parent, F&& functor) : parent_(parent), functor_(std::move(functor)) {
                take_item();
            }

            const T &operator*() const override {
                return current_item_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                take_item();
                return *this;
            }

            explicit operator bool() const override {
                return static_cast<bool>(parent_);
            }

        private:
            T current_item_;
            enumerator<U> &parent_;
            F functor_;

            void take_item() {
                if (parent_)
                    current_item_ = functor_(*parent_);
            }
        };

        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator(enumerator<T> &parent, F&& functor) : parent_(parent), functor_(std::move(functor)) {
            }

            const T &operator*() const override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                return *this;
            }

            explicit operator bool() const override {
                return (parent_ && !functor_(*parent_));
            }

        private:
            enumerator<T> &parent_;
            F functor_;
        };

        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F&& functor) : parent_(parent), functor_(std::move(functor)) {
                to_correct_item();
            }

            const T &operator*() const override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                to_correct_item();
                return *this;
            }

            explicit operator bool() const override {
                return static_cast<bool>(parent_);
            }

        private:
            enumerator<T> &parent_;
            F functor_;

            void to_correct_item() {
                while (parent_ && !functor_(*parent_))
                    ++parent_;
            }
        };

    } // namespace impl

    template<typename Iter>
    auto from(Iter begin, Iter end) {
        return impl::range_enumerator<typename std::iterator_traits<Iter>::value_type, Iter>(begin, end);
    }

} // namespace linq

#endif