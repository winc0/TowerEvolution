#ifndef LEVELSELECTPAGE_H
#define LEVELSELECTPAGE_H

#include "config.h"
#include <QWidget>

class QPushButton;
class QLabel;
class QVBoxLayout;

namespace Ui
{
class LevelSelectPage;
}

// 选择关卡与显示进度页面
class LevelSelectPage : public QWidget
{
    Q_OBJECT

public:
    // 创建关卡选择页面
    explicit LevelSelectPage(QWidget *parent = nullptr);
    // 释放UI资源与控件
    ~LevelSelectPage();

signals:
    // 请求开始指定地图的游戏
    void startGameRequested(GameConfig::MapId mapId);
    // 请求返回主菜单界面
    void returnToMainMenuRequested();

private slots:
    // 地图一按钮点击响应
    void onMap1Clicked();
    // 地图二按钮点击响应
    void onMap2Clicked();
    // 取消返回主菜单响应
    void onCancelClicked();

private:
    // 初始化关卡选择界面布局
    void initUI();
    // 从存档加载关卡进度
    void loadProgress();

    Ui::LevelSelectPage *ui;

    GameConfig::MapId mapId;
    QLabel *map1StatusLabel;
    QLabel *map2StatusLabel;
    QLabel *map1WaveLabel;
    QLabel *map2WaveLabel;
    QPushButton *map2Button;
};

#endif
