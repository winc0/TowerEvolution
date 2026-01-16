#ifndef BULLET_H
#define BULLET_H

#include "gameentity.h"
#include "enemy.h"
#include "config.h"
#include <QTimer>
#include <QPointer>

// 投射物子弹实体
class Bullet : public GameEntity, public ISoundPlayable
{
    Q_OBJECT
public:
    // 子弹类型枚举
    enum BulletType
    {
        BULLET_ARROW = 0,
        BULLET_CANNON = 1,
        BULLET_MAGIC = 2
    };

    // 创建带初始方向的子弹
    explicit Bullet(BulletType type, QPointF startPos, const QPointF &initialDirection, QPointer<Enemy> target, int damage, QObject *parent = nullptr);
    // 析构子弹并停止计时
    ~Bullet();

    // 刷新子弹位置与命中
    void update() override;
    // 获取当前追踪目标
    Enemy* getTarget() const { return target; }
    
    // 暂停子弹移动计时器
    void pauseMovement() { if (moveTimer) moveTimer->stop(); }
    // 恢复子弹移动计时器
    void resumeMovement() { if (moveTimer && !moveTimer->isActive()) moveTimer->start(GameConfig::BULLET_MOVE_INTERVAL); }

    // 注入资源管理器用于音效
    void setResourceManager(ResourceManager *manager) override { resourceManager = manager; }
    // 播放子弹相关音效
    void playSound(const QString &soundId, qreal volume = 1.0, bool loop = false) override;

signals:
    // 命中敌人并附带伤害
    void hit(Enemy* enemy, int damage);

private:
    // 根据方向更新朝向角度
    void updateRotation();

private slots:
    // 子弹移动计时器回调
    void onMoveTimer();

private:
    BulletType bulletType; // 子弹类型
    QPointer<Enemy> target;  // 使用QPointer自动跟踪target的生命周期
    int damage; // 伤害
    float speed; // 速度
    QTimer* moveTimer;
    QPointF direction; // 方向
    QPointF startPosition; // 发射位置
    float travelledDistance;
    int lostTargetTimeMs;
    ResourceManager *resourceManager;
};

#endif
