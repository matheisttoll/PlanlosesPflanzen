#ifndef FLAGWIDGET_H
#define FLAGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QSize>

class FlagWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlagWidget(size_t mines, QSize size, QWidget *parent = nullptr);

    void setMines(size_t m);
    void resetFlagCount();

    ~FlagWidget();
private:
    static const QString flagIcon;
    QLabel *flagIconLabel;
    QLabel *flagCountLabel;
    size_t flagCount;
    size_t mines;

    void updateFlagLabel();

signals:

public slots:
    void incFlagCount(bool flagSet);
};

#endif // FLAGWIDGET_H
