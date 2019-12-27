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
    QCoreApplication::setOrganizationName("Fuhrmann");
    QCoreApplication::setOrganizationDomain("paulfuhrmann.de");
    QCoreApplication::setApplicationName("BlumenSweeper");

    QSettings settings;
    QString resourcesPath;
    QVariant posVal = settings.value(keys::resourcesPath);
    bool askForResources = false;
    if(posVal.isNull()) {
        askForResources = true;
    } else {
        resourcesPath = posVal.toString();
    }

    QFile styleFile = QFile(resourcesPath + "/styleSheet.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    a.setStyleSheet(styleSheet);
    QRect screenRect = a.primaryScreen()->geometry();

    MainWindow w(screenRect, askForResources);
    w.show();
    return a.exec();
}
