#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include <QMainWindow>

// 前向声明
class GamePage;
class MainMenuPage;
class LevelSelectPage;
class QStackedWidget;

// 管理三个主页面的主窗口
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 创建主窗口并初始化页面
    MainWindow(QWidget *parent = nullptr);
    // 释放页面与布局资源
    ~MainWindow();

    // 切换到游戏页面并开始游戏
    void switchToGamePage(GameConfig::MapId mapId);
    // 切换回主菜单界面
    void switchToMainMenu();

private slots:
    // 游戏结束回调处理
    void onGameOver();

private:
    QStackedWidget *stackedWidget;
    GamePage *gamePage;
    MainMenuPage *mainMenuPage;
    LevelSelectPage *levelSelectPage;
};

#endif // MAINWINDOW_H
