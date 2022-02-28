#include "gameboard.h"
#include "boardsquare.h"
#include "application_constants.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>
#include <QRandomGenerator>

#include <random>
#include <set>

GameBoard::GameBoard(QRect screenRect, BoardDims dims, QWidget *parent) : QWidget(parent), BoardDims(dims)
{
    squareSize = calculateSquareSize(screenRect);
    BoardSquare::loadPictures(squareSize);
    squares = std::vector<BoardSquare*>();
    grid = new QGridLayout();
    flagWidget = new FlagWidget(mines, squareSize, this);
    resizeBoard(dims);
    createLayout();
}

GameBoard::~GameBoard() {
    delete flagWidget;
    delete grid;
}

void GameBoard::createLayout() {
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QHBoxLayout *infobar = new QHBoxLayout();
    QHBoxLayout *gridHolder = new QHBoxLayout();
    vlayout->addLayout(infobar);
    vlayout->addLayout(gridHolder);

    infobar->addStretch(1);
    infobar->addWidget(flagWidget);
    infobar->addStretch(1);

    gridHolder->addStretch(1);
    gridHolder->addLayout(grid);
    gridHolder->addStretch(1);
}

QSize GameBoard::calculateSquareSize(QRect screenRect) {
    int w = screenRect.width();
    int h = screenRect.height();
    int squareSize = static_cast<int>(std::min((0.85*w)/constant::board_max_width, (0.7*h)/constant::board_max_height));
    return QSize(squareSize, squareSize);
}

void GameBoard::resizeBoard(BoardDims dims) {
    setDims(dims);
    populateGrid();
    findNeighbours();
    resetBoard();
    flagWidget->setMines(mines);
    adjustSize();
    parentWidget()->adjustSize();
}

void GameBoard::populateGrid() {
    for(auto square : squares) {
        grid->removeWidget(square);
        delete square;
    }

    squares.clear();

    for(size_t y = 0; y < board_height; y++) {
        for(size_t x = 0; x < board_width; x++) {
            BoardSquare *newSquare = new BoardSquare();
            squares.push_back(newSquare);
            grid->addWidget(newSquare, static_cast<int> (y), static_cast<int>(x));
            QObject::connect(newSquare, &BoardSquare::explode, this, &GameBoard::mineExploded);
            QObject::connect(newSquare, &BoardSquare::flagSet, this, &GameBoard::squareFlagged);
            QObject::connect(newSquare, &BoardSquare::revealed, this, &GameBoard::squareRevealed);
        }
    }

}

void GameBoard::mineExploded() {
    for(auto square : squares) {
        square->gameOver(false);
    }
}

void GameBoard::squareFlagged(bool f) {
    flagWidget->incFlagCount(f);
}

void GameBoard::squareRevealed() {
    squaresRevealed++;
    if(board_width * board_height - squaresRevealed == mines) {
        // Das Spiel wurde gewonnen
        for(auto square : squares) {
            square->gameOver(true);
        }
    }
}

void GameBoard::findNeighbours() {
    for(size_t x = 0; x < board_width; x++) {
        for(size_t y = 0; y < board_height; y++) {
            BoardSquare *curSquare = squares.at(y * board_width + x);
            if(y > 0) {
                curSquare->addNeighbour(squares.at((y-1) * board_width + x));
            }
            if(y < board_height-1) {
                curSquare->addNeighbour(squares.at((y+1) * board_width + x));
            }
            if(x > 0) {
                curSquare->addNeighbour(squares.at(y * board_width + x-1));
                if(y > 0) {
                    curSquare->addNeighbour(squares.at((y-1) * board_width + x-1));
                }
                if(y < board_height-1) {
                    curSquare->addNeighbour(squares.at((y+1) * board_width + x-1));
                }
            }
            if(x < board_width-1) {
                curSquare->addNeighbour(squares.at(y * board_width + x+1));
                if(y > 0) {
                    curSquare->addNeighbour(squares.at((y-1) * board_width + x+1));
                }
                if(y < board_height-1) {
                    curSquare->addNeighbour(squares.at((y+1) * board_width + x+1));
                }
            }
        }
    }
}


void GameBoard::resetBoard() {
    flagWidget->resetFlagCount();
    for(auto square : squares) {
        square->reset();
    }
    placeMines();
    squaresRevealed = 0;
}

void GameBoard::restartBoard() {
    flagWidget->resetFlagCount();
    squaresRevealed = 0;
    for(auto square : squares) {
        square->unreveal();
    }
}

void GameBoard::placeMines() {
    std::uniform_int_distribution<size_t> dist(0, board_width * board_height - 1);
    std::set<size_t> minePos;

    while(minePos.size() < mines) {
        minePos.insert(dist(*QRandomGenerator::global()));
    }
    for(auto m : minePos) {
        squares.at(m)->setMine();
    }

    for(auto square : squares) {
        square->countMines();
    }
}
