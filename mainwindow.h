#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QRect screenRect, QWidget *parent = nullptr);
    ~MainWindow();

private:

private slots:
    void showAboutDialog();

};
#endif // MAINWINDOW_H
