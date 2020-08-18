#include "shared_ptr.hpp"
#include <algorithm>

// -------------------STORAGE-------------------

shared_ptr::Storage::Storage(Matrix *mtx) : data_(mtx), ref_count_(1) {}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ++ref_count_;
}

void shared_ptr::Storage::decr() {
    --ref_count_;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix *shared_ptr::Storage::getObject() const {
    return data_;
}

// ----------------SHARED_PTR---------------

shared_ptr::shared_ptr(Matrix *obj) {
    if (obj == nullptr)
        storage_ = nullptr;
    else
        storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr &other) {
    storage_ = other.storage_;
    if (storage_ != nullptr)
        storage_->incr();
}

shared_ptr &shared_ptr::operator=(shared_ptr other) {
    std::swap(storage_, other.storage_);
    return *this;
}

shared_ptr::~shared_ptr() {
    if (storage_ != nullptr) {
        storage_->decr();
        if (storage_->getCounter() == 0) {
            delete storage_;
            storage_ = nullptr;
        }
    }
}

Matrix *shared_ptr::ptr() const {
    if (storage_ == nullptr)
        return nullptr;
    return storage_->getObject();
}

bool shared_ptr::isNull() const {
    return storage_ == nullptr;
}

void shared_ptr::reset(Matrix *obj) {
    storage_->decr();
    if (storage_->getCounter() == 0) {
        delete storage_;
    }

    if (obj == nullptr)
        storage_ = nullptr;
    else
        storage_ = new Storage(obj);
}

Matrix *shared_ptr::operator->() const {
    return ptr();
}

Matrix &shared_ptr::operator*() const {
    return *ptr();
}