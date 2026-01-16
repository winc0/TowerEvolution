#ifndef MAINMENUPAGE_H
#define MAINMENUPAGE_H

#include "config.h"
#include <QWidget>
#include <QPixmap>

class QPushButton;
class QLabel;
class QVBoxLayout;

namespace Ui
{
class MainMenuPage;
}

// 游戏主菜单与入口页面
class MainMenuPage : public QWidget
{
    Q_OBJECT

public:
    // 创建主菜单页面
    explicit MainMenuPage(QWidget *parent = nullptr);
    // 析构并释放UI资源
    ~MainMenuPage();

signals:
    // 请求直接开始某个地图
    void startGameRequested(GameConfig::MapId mapId);
    // 请求退出整个游戏
    void exitGameRequested();
    // 请求打开关卡选择界面
    void openLevelSelectRequested();

private slots:
    // 开始按钮点击响应
    void onStartButtonClicked();
    // 退出按钮点击响应
    void onExitButtonClicked();

private:
    // 初始化主菜单界面布局
    void initUI();
    // 加载背景与按钮资源
    void loadResources();

    Ui::MainMenuPage *ui;

    QLabel *titleLabel;
    QLabel *backgroundLabel;
    QPushButton *startButton;
    QPushButton *exitButton;
    QVBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;

    QPixmap backgroundImage;
};

#endif
