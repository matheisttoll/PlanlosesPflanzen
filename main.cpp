#include "mainwindow.h"
#include "application_constants.h"
#include "boardsquare.h"

#include <QApplication>
#include <QRect>
#include <QScreen>
#include <QFile>
#include <QSettings>
#include <QString>
#include <QVariant>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QCoreApplication::setOrganizationName("Fuhrmann");
    QCoreApplication::setOrganizationDomain("paulfuhrmann.de");
    QCoreApplication::setApplicationName("BlumenSweeper");

    QFile styleFile = QFile(":/resources/styleSheet.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    a.setStyleSheet(styleSheet);
    QRect screenRect = a.primaryScreen()->geometry();

    MainWindow w(screenRect);
    w.show();
    return a.exec();
}
