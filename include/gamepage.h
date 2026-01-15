#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QTimer>
#include <QElapsedTimer>

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

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();

    void startGame();
    void pauseGame();
    void resetGame();

signals:
    void gameOver();
    void returnToMainMenu();

public slots:

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    // UI & 游戏逻辑
    void initGameScene();
    void initUI();
    void createPath();
    void showGameOverDialog();

    // 绘制
    void drawBackground();
    void drawGrid();
    void updateHoverHighlight(const QPointF &scenePos);
    void initPlacementValidator();
    void drawPlacementAreas();
    void showFloatingTip(const QString &text, const QPointF &scenePos, const QColor &color);

    // 敌人管理
    void pauseAllEnemies();
    void resumeAllEnemies();

    // 塔和子弹管理
    void pauseAllTowersAndBullets();
    void resumeAllTowersAndBullets();

    // 暂停菜单
    void showPauseMenu();
    void hidePauseMenu();
    QWidget *pauseOverlay = nullptr;
    QWidget *pausePanel = nullptr;


    // 游戏状态
    QGraphicsScene *gameScene;
    QGraphicsView *gameView;
    PlacementValidator *placementValidator;
    GameManager *gameManager;

    // UI元素
    QWidget *controlPanel;
    QLabel *goldLabel;
    QLabel *livesLabel;
    QLabel *waveLabel;
    QPushButton *pauseButton;
    QPushButton *returnButton;
    QWidget *resultOverlay;
    QWidget *resultPanel;

    // 布局
    QVBoxLayout *mainLayout;
    QHBoxLayout *infoLayout;
    QHBoxLayout *buttonLayout;

    // 路径点
    QVector<QPointF> pathPoints;

    GameConfig::MapId currentMapId;
    QVector<GameConfig::EndPointConfig> endPointAreas;
    QElapsedTimer elapsedTimer;
    QList<QGraphicsRectItem *> placementAreaItems;
};

#endif
