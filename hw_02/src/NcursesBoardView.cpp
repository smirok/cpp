#include "NcursesBoardView.h"
#include "ncurses.h"
#include "Board.h"
#include <vector>
#include <cstdlib>

namespace NC {
    const char *const MESSAGE_HIDER = "          ";
    constexpr int NUMBER_ROUTS = 8;
    constexpr int VIEW_ROUTS = 4;
}

NcursesBoardView::NcursesBoardView() {
    initscr();
    clear();
    noecho();
    cbreak();
    raw();
    title = newwin(3, 21, 1, 4);
    win = newwin(/*_board->getHeight()*/10, /*_board->getWidth()*/10, 5, 9);
    message = newwin(10, 30, 7 + /*_board->getHeight()*/10, 0);
    keypad(win, TRUE);
    keypad(message, TRUE);
    wattron(win, A_BOLD);
    wattron(message, A_BOLD);
    wattron(title, A_BOLD);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    mvwprintw(title, 1, 5, "Tic Tac Toe");
    box(title, '|', '-');
    wrefresh(title);
    box(message, '|', '-');
}

NcursesBoardView::~NcursesBoardView() {
    screenClear();
}

void NcursesBoardView::showBoard(const vector<vector<FieldState>> &field, int height, int width) const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mvwaddch(win, i, j, (char) field[i][j]);
        }
    }
    mvwprintw(message, 5, 10, NC::MESSAGE_HIDER);
    wrefresh(message);
}

void NcursesBoardView::showResultMessage(GameState state) const {
    wattron(message, A_BOLD);
    wattron(message, COLOR_PAIR(2));
    mvwprintw(message, 3, 10, NC::MESSAGE_HIDER);
    if (state == O_WIN) {
        mvwprintw(message, 3, 10, "O wins!");
    } else if (state == X_WIN) {
        mvwprintw(message, 3, 10, "X wins!");
    } else {
        mvwprintw(message, 3, 10, "Draw.");
    }
    wattron(message, A_BLINK);
    wattroff(message, A_BOLD);
    mvwprintw(message, 5, 2, "Press any key to exit...");
    wattroff(message, COLOR_PAIR(2));
    wattroff(message, A_BLINK);
    wrefresh(message);
    wgetch(message);
}

void NcursesBoardView::showMoveNext(Players player) const {
    mvwprintw(message, 3, 10, player == Players::O ? "O move: " : "X move: ");
    wrefresh(message);
}

void NcursesBoardView::showWinLine(int &x, int &y, const vector<vector<FieldState>> &field,
                                   int height, int width, int winlen) const {
    int dx[NC::NUMBER_ROUTS] = {1, 1, 1, 0, -1, -1, -1, 0};
    int dy[NC::NUMBER_ROUTS] = {-1, 1, 0, 1, 1, -1, 0, -1};
    std::vector<std::pair<int, int>> route[NC::VIEW_ROUTS];
    for (int i = 0; i < NC::VIEW_ROUTS; i++)
        route[i].emplace_back(x, y);
    for (int j = 0; j < NC::NUMBER_ROUTS; j++) {
        int i = 1;
        while (i < winlen) {
            int curX = x + i * dx[j];
            int curY = y + i * dy[j];
            if (curX < height && curX >= 0 && curY < width && curY >= 0
                && field[x][y] == field[curX][curY]) {
                route[j % NC::VIEW_ROUTS].emplace_back(curX, curY);
            }
            i++;
        }
    }
    for (int i = 0; i < NC::VIEW_ROUTS; i++) {
        if (route[i].size() >= winlen) {
            start_color();
            init_pair(4, COLOR_CYAN, COLOR_BLACK);
            wattron(win, COLOR_PAIR(4));
            int j = 0;
            while (j < winlen) {
                mvwaddch(win, route[i][j].first, route[i][j].second, (char) field[x][y]);
                j++;
            }
            wrefresh(win);
            break;
        }
    }
}

void NcursesBoardView::showBadMove() const {
    mvwprintw(message, 5, 10, "Bad Move");
    wrefresh(message);
}

bool NcursesBoardView::enterCorrectTurn(int &x, int &y, const vector<vector<FieldState>> &field,
                                        int height, int width, Players player) const {
    int ch = 0;
    do {
        char prev;
        if (field[x][y] == FieldState::O)
            prev = 'O';
        else if (field[x][y] == FieldState::X)
            prev = 'X';
        else
            prev = '.';
        wmove(win, x, y);
        ch = wgetch(win);
        if ((ch == 's' || ch == KEY_DOWN) && x < height - 1) {
            x++;
        }
        if ((ch == 'w' || ch == KEY_UP) && x > 0) {
            x--;
        }
        if ((ch == 'a' || ch == KEY_LEFT) && y > 0) {
            y--;
        }
        if ((ch == 'd' || ch == KEY_RIGHT) && y < width - 1) {
            y++;
        }
        if (ch == 'x') {
            screenClear();
            exit(0);
        }
        wattron(win, COLOR_PAIR(1));
        waddch(win, prev);
        wattroff(win, COLOR_PAIR(1));
        if (field[x][y] == FieldState::NONE) {
            wattron(win, COLOR_PAIR(2));
            mvwaddch(win, x, y, (char) player);
        } else {
            wattron(win, COLOR_PAIR(3));
            mvwaddch(win, x, y, (char) player);
        }
        wmove(win, x, y);
        wattroff(win, COLOR_PAIR(2));
        wattroff(win, COLOR_PAIR(3));
    } while (ch != ' ');
    return true;
}

void NcursesBoardView::screenClear() const {
    clear();
    delwin(title);
    delwin(message);
    delwin(win);
    endwin();
}
