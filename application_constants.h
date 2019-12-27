#ifndef APPLICATION_CONSTANTS_H
#define APPLICATION_CONSTANTS_H


#include <QString>
#include <array>

struct BoardDims {
    size_t board_width;
    size_t board_height;
    size_t mines;
    BoardDims(size_t w, size_t h, size_t m) {
        board_width = w;
        board_height = h;
        mines = m;
    }

    void setDims(BoardDims dims) {
        board_width = dims.board_width;
        board_height = dims.board_height;
        mines = dims.mines;
    }
};

namespace constant {
    inline const QString appName{"Muckis BlumenSweeper"};
    inline constexpr size_t board_max_width = 30;
    inline constexpr size_t board_max_height = 16;

    inline const std::array<BoardDims, 3> boardSizes{BoardDims{8, 8, 10}, BoardDims{16, 16, 40}, BoardDims{30, 16, 99}};
}

namespace keys {
    inline const QString resourcesPath{"resourcesPath"};
}

enum BoardSize {Small, Medium, Large};

#endif // APPLICATION_CONSTANTS_H
