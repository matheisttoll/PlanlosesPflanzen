#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "boardsquare.h"
#include "application_constants.h"
#include "flagwidget.h"

#include <QWidget>
#include <QGridLayout>
#include <vector>
#include <QRect>
#include <QSize>

class GameBoard : public QWidget, BoardDims
{
    Q_OBJECT
public:

    explicit GameBoard(QRect screenRect, BoardDims params, QWidget *parent = nullptr);

    void placeMines();
    void resetBoard();
    void resizeBoard(BoardDims params);

    ~GameBoard();
private:

    void populateGrid();
    void findNeighbours();
    QSize calculateSquareSize(QRect screenRect);

    QGridLayout *grid;
    FlagWidget *flagWidget;
    std::vector<BoardSquare*> squares;
    size_t minesFound;
    size_t squaresRevealed;
    QSize squareSize;


    void createLayout();
signals:

public slots:
    void mineExploded();
    void squareFlagged(bool f);
    void squareRevealed();
    void restartBoard();
};

#endif // GAMEBOARD_H
