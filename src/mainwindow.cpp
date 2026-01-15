#include "include/config.h"
#include "include/mainwindow.h"
#include "include/gamepage.h"
#include "include/mainmenupage.h"

#include <ui_mainwindow.h>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QSettings>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gamePage(nullptr), mainMenuPage(nullptr)
{
    // 设置全局的 QSettings 组织名和应用名
    QApplication::setApplicationName("TowerDefenseGame");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("TowerDefenseStudio");

    ui->setupUi(this);

    // 移除UI中stackedWidget的默认页面（如果有）
    while (ui->stackedWidget->count() > 0)
    {
        QWidget *widget = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }

    // 创建页面
    mainMenuPage = new MainMenuPage(this);
    gamePage = new GamePage(this);

    // 添加到 stackedWidget
    ui->stackedWidget->addWidget(mainMenuPage);
    ui->stackedWidget->addWidget(gamePage);
    ui->stackedWidget->setCurrentWidget(mainMenuPage);

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
    delete ui;
}

void MainWindow::switchToGamePage(GameConfig::MapId mapId)
{
    ui->stackedWidget->setCurrentIndex(1);
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
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onGameOver()
{
    switchToMainMenu();
}
