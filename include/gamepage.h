#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QTimer>
#include <QElapsedTimer>
#include <QColor>

#include "enemy.h"
#include "tower.h"
#include "bullet.h"
#include "config.h"
#include "gamemanager.h"

class QLabel;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGraphicsRectItem;
class PlacementValidator;
class QGraphicsOpacityEffect;

namespace Ui
{
class GamePage;
}

// 承载主游戏场景与UI
class GamePage : public QWidget
{
    Q_OBJECT

public:
    // 创建游戏页面并初始化
    explicit GamePage(QWidget *parent = nullptr);
    // 释放场景与管理器资源
    ~GamePage();

    // 启动游戏并进入战斗
    void startGame();
    // 暂停当前游戏进程
    void pauseGame();
    // 重置游戏到初始状态
    void resetGame();
    // 切换当前关卡地图
    void setMap(GameConfig::MapId mapId);

signals:
    // 游戏结束返回结果信号
    void gameOver();
    // 请求回到主菜单界面
    void returnToMainMenu();

public slots:
protected:
    // 处理鼠标移动更新高亮
    void mouseMoveEvent(QMouseEvent *event) override;
    // 拦截子控件相关事件
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    // 初始化场景对象与视图
    void initGameScene();
    // 初始化界面控件布局
    void initUI();
    // 按路径点创建敌人路径
    void createPath();
    // 弹出游戏失败结果面板
    void showGameOverDialog();
    // 弹出关卡完成结果面板
    void showLevelCompleteDialog();
    // 显示暂停菜单遮罩
    void showPauseMenu();
    // 隐藏暂停菜单遮罩
    void hidePauseMenu();
    // 保存关卡进度与评分
    void saveLevelProgress(bool levelCompleted);

    // 绘制地图背景贴图
    void drawBackground();
    // 绘制调试用网格线
    void drawGrid();

    // 更新鼠标悬停高亮格
    void updateHoverHighlight(const QPointF &scenePos);
    // 初始化建塔位置校验器
    void initPlacementValidator();
    // 刷新面板上的游戏统计
    void updateGameStats();
    // 绘制可建塔区域高亮
    void drawPlacementAreas();
    // 显示短暂悬浮提示文字
    void showFloatingTip(const QString &text, const QPointF &scenePos, const QColor &color);
    // 播放升级特效动画
    void showUpgradeEffect(const QPointF &scenePos);
    
    // 暂停所有敌人移动
    void pauseAllEnemies();
    // 恢复所有敌人移动
    void resumeAllEnemies();
    
    // 暂停所有塔与子弹逻辑
    void pauseAllTowersAndBullets();
    // 恢复所有塔与子弹逻辑
    void resumeAllTowersAndBullets();

    struct ResultViewContext
    {
        QWidget *overlay;
        QWidget *panel;
        QVBoxLayout *layout;
        QGraphicsOpacityEffect *opacityEffect;
    };

    // 创建结算界面包装容器
    ResultViewContext createResultWrapper(const QString &panelStyle, const QColor &shadowColor);
    // 播放结算面板淡入动画
    void playResultAnimation(const ResultViewContext &ctx);

    // 处理鼠标点击建塔等操作
    void mousePressEvent(QMouseEvent *event) override;

    Ui::GamePage *ui;

    QGraphicsScene *gameScene;
    QGraphicsView *gameView;
    QGraphicsPixmapItem *userItem;
    PlacementValidator *placementValidator;
    GameManager *gameManager;

    QWidget *controlPanel;
    QLabel *goldLabel;
    QLabel *livesLabel;
    QLabel *waveLabel;
    QPushButton *pauseButton;
    QPushButton *returnButton;
    QWidget *resultOverlay;
    QWidget *resultPanel;
    QWidget *pauseOverlay;
    QWidget *pausePanel;

    QVBoxLayout *mainLayout;
    QHBoxLayout *infoLayout;
    QHBoxLayout *buttonLayout;

    QVector<QPointF> pathPoints;

    GameConfig::MapId currentMapId;
    QVector<GameConfig::EndPointConfig> endPointAreas;
    QElapsedTimer elapsedTimer;
    QList<QGraphicsRectItem *> placementAreaItems;
};

#endif
