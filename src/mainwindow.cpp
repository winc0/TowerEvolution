#include "include/config.h"
#include "include/mainwindow.h"
#include "include/gamepage.h"
#include "include/mainmenupage.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QSettings>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), stackedWidget(nullptr), gamePage(nullptr), mainMenuPage(nullptr)
{
    // 设置全局的 QSettings 组织名和应用名
    QApplication::setApplicationName("TowerDefenseGame");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("TowerDefenseStudio");

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    stackedWidget = new QStackedWidget(central);
    layout->addWidget(stackedWidget);

    setCentralWidget(central);

    mainMenuPage = new MainMenuPage(this);
    gamePage = new GamePage(this);

    stackedWidget->addWidget(mainMenuPage);
    stackedWidget->addWidget(gamePage);
    stackedWidget->setCurrentWidget(mainMenuPage);

    // 连接信号
    connect(mainMenuPage, &MainMenuPage::startGameRequested,
            this, &MainWindow::switchToGamePage);
    connect(mainMenuPage, &MainMenuPage::exitGameRequested,
            this, &QApplication::quit);
    connect(gamePage, &GamePage::returnToMainMenu,
            this, &MainWindow::switchToMainMenu);
    connect(gamePage, &GamePage::gameOver,
            this, &MainWindow::onGameOver);

    setWindowTitle("保卫萝卜 - TD Defense Game");
    resize(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT);
}

MainWindow::~MainWindow()
{
}

void MainWindow::switchToGamePage(GameConfig::MapId mapId)
{
    if (stackedWidget)
        stackedWidget->setCurrentIndex(1);
    if (gamePage)
    {
        gamePage->setMap(mapId);
        gamePage->startGame();
    }
}

void MainWindow::switchToMainMenu()
{
    if (gamePage)
    {
        // 移除任何图形效果以防止 painter 冲突
        gamePage->setGraphicsEffect(nullptr);
        gamePage->resetGame();
    }
    if (stackedWidget)
        stackedWidget->setCurrentIndex(0);
}

void MainWindow::onGameOver()
{
    switchToMainMenu();
}
