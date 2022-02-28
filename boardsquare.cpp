#include "boardsquare.h"

#include <QBrush>
#include <QSize>
#include <QSettings>
#include "application_constants.h"

constexpr BoardSquare::SquareType BoardSquare::allSquareTypes[7];
const QString BoardSquare::imageNames[7] = {"unrevealed", "revealed", "flagged", "mine_won", "mine_lost", "mine_exploded", "mine_flagged"};
const QString BoardSquare::colors[7] = {"black", "midnightblue", "darkblue", "blue", "darkred", "firebrick", "red"};
QBrush BoardSquare::brushes[6] = {};
QSize BoardSquare::squareSize;

void BoardSquare::loadPictures(QSize size) {
    squareSize = size;
    for(auto type : allSquareTypes) {
        brushes[type] = QBrush(QPixmap(":/resources/square_" + imageNames[type] + ".png", "png").scaled(size));
    }
}

BoardSquare::BoardSquare() : QPushButton() {
    setFlat(true);
    setAutoFillBackground(true);
    setBackground(Unrevealed);
    neighbours = new QList<BoardSquare*>();
    reset();
}

BoardSquare::~BoardSquare() {
    delete neighbours;
}

void BoardSquare::setBackground(SquareType t) {
    setFixedSize(squareSize);
    QPalette pal = palette();
    pal.setBrush(backgroundRole(), brushes[t]);
    setPalette(pal);
}


void BoardSquare::gameOver(bool won) {
    if(!isRevealed) {
        isRevealed = true;
        if(won) {
            if(mine) {
                setBackground(MineWon);
            }
        } else {
            if(mine) {
                if(flagged) {
                    setBackground(MineFlagged);
                } else {
                    setBackground(MineLost);
                }
            } else {
                reveal();
            }
        }
    }
    setDisabled(true);
}

void BoardSquare::reveal() {
    if(!isRevealed && !flagged) {
        isRevealed = true;
        if(mine) {
            setBackground(MineExploded);
            emit explode();
        } else {
            setBackground(Revealed);
            if(mines == 0) {
                for(auto square : *neighbours) {
                    square->reveal();
                }
            } else {
                setText(QString::number(mines));
            }
            emit revealed();
        }
    }
}

void BoardSquare::mousePressEvent(QMouseEvent *e) {
    if(e->button()==Qt::RightButton) {
        flag();
    } else if(e->button()==Qt::LeftButton) {
        if(!isRevealed) {
            reveal();
        } else {
            int neighbourFlags = 0;
            for(auto square : *neighbours) {
                if(square->flagged) {
                    neighbourFlags++;
                }
            }
            if(neighbourFlags == mines) {
                for(auto square : *neighbours) {
                    square->reveal();
                }
            }
        }
    }
}

void BoardSquare::flag() {
    if(isRevealed)
        return;
    flagged = !flagged;
    if(flagged) {
        setBackground(Flagged);
        emit flagSet(true);
    } else {
        setBackground(Unrevealed);
        emit flagSet(false);
    }
}

void BoardSquare::addNeighbour(BoardSquare* square) {
    neighbours->append(square);
}

void BoardSquare::countMines() {
    mines = 0;
    for(auto square : *neighbours) {
        if(square->isMine()) {
            mines++;
        }
    }
    setStyleSheet(QString("font: bold 22px; color: ") + colors[mines] + QString(";"));
}

void BoardSquare::unreveal() {
    setEnabled(true);
    isRevealed = false;
    flagged = false;
    setBackground(Unrevealed);
    setText("");
}

void BoardSquare::reset() {
    mines = 0;
    mine = false;
    unreveal();
}

void BoardSquare::setMine(bool m) {
    mine = m;
}

bool BoardSquare::isMine() {
    return mine;
}
