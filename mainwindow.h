#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QRect screenRect, bool askForResources, QWidget *parent = nullptr);
    ~MainWindow();

private:
    static const QString iconName;
    QString resourcesPath;

private slots:
    void showAboutDialog();
    void askForResourcesFolder();

};
#endif // MAINWINDOW_H
