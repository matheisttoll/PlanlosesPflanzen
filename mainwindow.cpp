#include "mainwindow.h"

#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QAction>
#include <QIcon>
#include <QFileDialog>
#include <QSettings>
#include <QVariant>

#include "gameboard.h"
#include "application_constants.h"

const QString MainWindow::iconName{"/app_icon"};

MainWindow::MainWindow(QRect screenRect, bool askForResources, QWidget *parent)
    : QMainWindow(parent)
{
    if(askForResources) {
        askForResourcesFolder();
    }

    QSettings settings;
    resourcesPath = settings.value(keys::resourcesPath).toString();

    setWindowTitle(constant::appName);
    setWindowIcon(QIcon(resourcesPath + iconName + ".png"));
    GameBoard *gameBoard = new GameBoard(screenRect, constant::boardSizes[Large], this);


    QMenu *gameMenu = new QMenu(tr("Spiel"));
    QAction *newGame = new QAction(tr("Neues Spiel"));
    QAction *restartGame = new QAction(tr("Neu starten"));
    gameMenu->addAction(newGame);
    gameMenu->addAction(restartGame);
    QObject::connect(newGame, &QAction::triggered, gameBoard, &GameBoard::resetBoard);
    QObject::connect(restartGame, &QAction::triggered, gameBoard, &GameBoard::restartBoard);
    menuBar()->addMenu(gameMenu);

    QMenu *boardSize = new QMenu(tr("Größe"));
    QAction *small = new QAction(tr("Klein 8x8"));
    QAction *medium = new QAction(tr("Mittel 16x16"));
    QAction *large = new QAction(tr("Groß 30x16"));
    boardSize->addAction(small);
    boardSize->addAction(medium);
    boardSize->addAction(large);
    QObject::connect(small, &QAction::triggered, gameBoard, [gameBoard]{gameBoard->resizeBoard(constant::boardSizes[Small]);});
    QObject::connect(medium, &QAction::triggered, gameBoard, [gameBoard]{gameBoard->resizeBoard(constant::boardSizes[Medium]);});
    QObject::connect(large, &QAction::triggered, gameBoard, [gameBoard]{gameBoard->resizeBoard(constant::boardSizes[Large]);});
    menuBar()->addMenu(boardSize);


    QMenu *settingsMenu = new QMenu(tr("Einstellungen"));
    QAction *resourceAction = new QAction(tr("Resourcen Ordner"));
    settingsMenu->addAction(resourceAction);
    QObject::connect(resourceAction, &QAction::triggered, this, &MainWindow::askForResourcesFolder);
    menuBar()->addMenu(settingsMenu);


    QMenu *aboutMenu = new QMenu(tr("Über"));
    QAction *about = new QAction(tr("Über Muckis Minessweeper"));
    QAction *aboutQt = new QAction(tr("Über Qt"));
    aboutMenu->addAction(aboutQt);
    aboutMenu->addAction(about);
    QObject::connect(about, &QAction::triggered, this, &MainWindow::showAboutDialog);
    QObject::connect(aboutQt, &QAction::triggered, this, [this]{QMessageBox::aboutQt(this);});
    menuBar()->addMenu(aboutMenu);

    setCentralWidget(gameBoard);
}

void MainWindow::askForResourcesFolder() {
    resourcesPath = QFileDialog::getExistingDirectory(this, "Speicherort für Bilder");
}


void MainWindow::showAboutDialog() {
    QMessageBox::about(this, "Über Muckis Blumensweeper", "Ein MineSweeper Spiel ohne Werbung für Muckis Klapprechner.\nProgrammiert von Paul mit Grafiken von Pablo.\n2019");
}

MainWindow::~MainWindow() {
    QSettings settings;
    settings.setValue(keys::resourcesPath, resourcesPath);
}

