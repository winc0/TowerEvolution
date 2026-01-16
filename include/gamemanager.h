#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "enemy.h"
#include "tower.h"
#include "bullet.h"
#include "config.h"
#include "gameentity.h"
#include "resourcemanager.h"
#include <QObject>
#include <QList>
#include <QPointer>
#include <QTimer>
#include <QVector>
#include <QPointF>

// 管理整体关卡与战斗状态
class GameManager : public QObject, public ISoundPlayable
{
    Q_OBJECT

public:
    // 构造游戏管理器实例
    explicit GameManager(QObject *parent = nullptr);

    // 初始化地图路径与终点
    void initialize(GameConfig::MapId mapId,
                    const QVector<QPointF> &pathPoints,
                    const QVector<GameConfig::EndPointConfig> &endPoints);

    // 开始或继续游戏循环
    void startGame();
    // 暂停整体游戏逻辑
    void pauseGame();
    // 重置关卡与统计数据
    void resetGame();

    // 获取当前金币数量
    int getGold() const { return gold; }
    // 获取剩余生命数量
    int getLives() const { return lives; }
    // 获取当前波次编号
    int getCurrentWave() const { return currentWave; }
    // 获取累计击杀数量
    int getKillCount() const { return killCount; }
    // 查询游戏是否运行中
    bool isGameRunning() const { return gameRunning; }
    // 查询游戏是否处于暂停
    bool isPaused() const { return paused; }

    // 获取当前所有敌人列表
    const QList<QPointer<Enemy>> &getEnemies() const { return enemies; }
    // 获取当前所有防御塔列表
    const QList<QPointer<Tower>> &getTowers() const { return towers; }
    // 获取当前所有子弹列表
    const QList<QPointer<Bullet>> &getBullets() const { return bullets; }

    // 建造指定类型防御塔
    QPointer<Tower> buildTower(Tower::TowerType type, const QPointF &position, QObject *parentForTower);
    // 升级指定防御塔实例
    QPointer<Tower> upgradeTower(QPointer<Tower> tower);
    // 拆除指定防御塔并退款
    bool demolishTower(QPointer<Tower> tower);

signals:
    void goldChanged(int gold);
    void livesChanged(int lives);
    void waveChanged(int currentWave);
    void killCountChanged(int killCount);
    void gameStateChanged(bool running, bool paused);
    void gameOver();
    void levelCompleted(GameConfig::MapId mapId, int wave);

    void enemySpawnRequested(QPointer<Enemy> enemy);
    void enemyReachedEnd(QPointer<Enemy> enemy);
    void enemyDied(QPointer<Enemy> enemy);
    void towerBuilt(QPointer<Tower> tower);
    void towerUpgraded(QPointer<Tower> oldTower, QPointer<Tower> newTower);
    void towerDemolished(QPointer<Tower> tower);

public slots:
    // 定时生成下一只敌人
    void spawnEnemy();
    // 驱动一帧游戏更新
    void updateGame();

    // 注入资源管理器用于音效
    void setResourceManager(ResourceManager *manager) override;
    // 播放全局管理相关音效
    void playSound(const QString &soundId, qreal volume = 1.0, bool loop = false) override;

private:
    // 更新所有敌人列表状态
    void updateEnemies();
    // 更新所有防御塔状态
    void updateTowers();
    // 清理已死亡实体对象
    void removeDeadEntities();
    // 检查并触发下一波敌人
    void checkNextWave();
    // 计算当前波次刷怪间隔
    int getWaveSpawnInterval() const;
    // 判断敌人是否到任一终点
    bool isEnemyAtAnyEndPoint(QPointer<Enemy> enemy) const;

    // 根据类型计算塔造价
    int getTowerCost(Tower::TowerType type) const;
    // 计算当前波次敌人血量
    int calculateWaveHealth() const;
    // 计算当前波次敌人速度
    float calculateWaveSpeed() const;

private:
    QList<QPointer<Enemy>> enemies;
    QList<QPointer<Tower>> towers;
    QList<QPointer<Bullet>> bullets;

    int gold;
    int lives;
    int currentWave;
    int enemiesSpawnedThisWave;
    bool waveSpawnComplete;
    bool gameRunning;
    bool paused;
    int killCount;

    GameConfig::MapId currentMapId;
    QVector<QPointF> pathPoints;
    QVector<GameConfig::EndPointConfig> endPointAreas;

    QTimer *gameTimer;
    QTimer *enemySpawnTimer;
    ResourceManager *resourceManager;
};

#endif // GAMEMANAGER_H
