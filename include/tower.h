#ifndef TOWER_H
#define TOWER_H

#include "gameentity.h"
#include <QTimer>
#include <QList>
#include <QGraphicsPixmapItem>
#include <QPointer>
#include <QElapsedTimer>

class Enemy;
class QGraphicsScene;

// 防御塔图元与攻击逻辑
class Tower : public GameEntity, public ISoundPlayable
{
    Q_OBJECT
public:
    // 防御塔种类枚举
    enum TowerType
    {
        ARROW_TOWER,
        CANNON_TOWER,
        MAGIC_TOWER
    };

    // 创建指定类型防御塔
    explicit Tower(TowerType type, QPointF position, QObject *parent = nullptr);
    // 析构塔并清理底座
    ~Tower();

    // 刷新塔目标与旋转
    void update() override;
    // 手动设置当前攻击目标
    void setTarget(QPointer<Enemy> target);
    // 对当前目标发射子弹
    void fire();
    // 注入所属场景指针
    void setGameScene(QGraphicsScene *scene) { gameScene = scene; }

    // 获取单次伤害数值
    int getDamage() const { return damage; }
    // 获取攻击范围半径
    int getRange() const { return range; }
    // 获取建塔或升级消耗
    int getCost() const { return cost; }
    // 获取当前塔类型
    TowerType getTowerType() const { return towerType; }

    // 更新范围内可攻击敌人
    void setEnemiesInRange(const QList<QPointer<Enemy>> &enemies);

    // 暂停攻击计时器
    void pauseAttack()
    {
        if (attackTimer)
            attackTimer->stop();
    }
    // 恢复攻击计时器
    void resumeAttack()
    {
        if (attackTimer && !attackTimer->isActive())
            attackTimer->start(fireRate);
    }

    // 获取底座图形项指针
    QGraphicsPixmapItem *getBaseItem() const { return baseItem; }

    // 注入资源管理器用于音效
    void setResourceManager(ResourceManager *manager) override { resourceManager = manager; }
    // 播放塔相关音效
    void playSound(const QString &soundId, qreal volume = 1.0, bool loop = false) override;

private slots:
    // 攻击计时器回调入口
    void onAttackTimer();
signals:
    // 每次成功开火发射信号
    void fired();
    // 当前锁定目标被消灭
    void targetDestroyed();

private:
    TowerType towerType;
    int damage;
    int range;
    int fireRate; // 毫秒
    int cost;
    QPointer<Enemy> currentTarget; // 当前攻击目标
    QTimer *attackTimer;
    QList<QPointer<Enemy>> enemiesInRange;
    QMap<Enemy*, qint64> enemyEntryTimes; // 记录敌人进入范围的时间
    qint64 targetLostTime; // 目标丢失的时间戳
    QGraphicsScene *gameScene;

    QGraphicsPixmapItem *baseItem; // 底座图形
    qreal currentRotation;         // 当前旋转角度
    qreal targetRotation;          // 目标旋转角度
    qreal rotationSpeed;           // 旋转速度
    bool targetLocked;
    QElapsedTimer targetLockTimer;

    ResourceManager *resourceManager;

    // 判断敌人是否在射程内
    bool isInRange(QPointer<Enemy> enemy) const;
    // 在范围内选择合适目标
    void findTarget();
    // 根据目标更新塔的旋转角度
    void updateTowerRotation();
    // 管理目标锁定与超时
    void updateTargetLock();
};

#endif
