#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QObject>
#include <QPushButton>
#include <QList>
#include <QMouseEvent>
#include <QBrush>
#include <QSize>

class BoardSquare : public QPushButton
{
    Q_OBJECT
public:
    enum SquareType {Unrevealed, Revealed, Flagged, MineWon, MineLost, MineExploded, MineFlagged};
    static constexpr SquareType allSquareTypes[7] = {Unrevealed, Revealed, Flagged, MineWon, MineLost, MineExploded, MineFlagged};
    static void loadPictures(QSize size);

    static QSize squareSize;
    static QBrush brushes[6];

    BoardSquare();
    ~BoardSquare();


    void addNeighbour(BoardSquare* square);
    bool isMine();
    void setMine(bool m = true);
    void countMines();
    void reveal();
    void unreveal();
    void reset();
    void flag();
    void gameOver(bool won);


private:
    static const QString imageNames[7];
    static const QString colors[7];

    void setBackground(SquareType t);

    QList<BoardSquare*> *neighbours;
    bool isRevealed;
    bool mine;
    bool flagged;
    int mines;

signals:
    void explode();
    void flagSet(bool f);
    void revealed();

private slots:
    void mousePressEvent(QMouseEvent* e);
};

#endif // BOARDSQUARE_H
