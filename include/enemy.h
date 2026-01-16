#ifndef ENEMY_H
#define ENEMY_H

#include "gameentity.h"
#include "resourcemanager.h"
#include "config.h"
#include <QTimer>
#include <QVector>
#include <QElapsedTimer>

// 敌人单位图元实体
class Enemy : public GameEntity
{
    Q_OBJECT
public:
    // 使用ResourceManager中定义的EnemyState
    typedef ResourceManager::EnemyState EnemyState;

    // 创建指定类型敌人
    explicit Enemy(int enemyType = 0, QObject *parent = nullptr);
    // 析构敌人并释放资源
    ~Enemy();

    // 刷新敌人逻辑与移动
    void update() override;
    // 设置敌人路径点序列
    void setPath(const QVector<QPointF>& pathPoints);
    // 沿当前路径移动一帧
    void moveAlongPath();

    // 获取被击杀奖励金币
    int getReward() const { return reward; }
    // 判定是否到达终点
    bool isAtEnd() const { return reachedEnd; }
    // 获取敌人类型编号
    int getEnemyType() const { return enemyType; }
    // 获取当前动画状态
    EnemyState getState() const { return currentState; }
    // 切换敌人动画状态
    void setState(EnemyState state);
    // 获取敌人中心坐标
    QPointF getCenterPosition() const;
    // 获取当前移动速度
    float getSpeed() const { return speed; }
    // 设置当前移动速度
    void setSpeed(float newSpeed) { speed = newSpeed; }
    
    // 暂停敌人移动计时器
    void pauseMovement() { if (moveTimer) moveTimer->stop(); }
    // 恢复敌人移动计时器
    void resumeMovement() { if (moveTimer && currentState != ResourceManager::ENEMY_DEAD) moveTimer->start(GameConfig::ENEMY_MOVE_INTERVAL); }

    // 设置高亮显示状态
    void setHighlighted(bool highlighted) { isHighlighted = highlighted; }
    // 查询当前高亮状态
    bool getHighlighted() const { return isHighlighted; }

protected:
    // 自定义绘制包含高亮效果
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    // 返回扩展后的包围矩形
    QRectF boundingRect() const override;

private slots:
    // 敌人移动计时器回调
    void onMoveTimer();
signals:
    // 敌人到达终点信号
    void reachedEndPoint();
    // 敌人死亡携带奖励
    void enemyKilled(int reward);
private:
    int enemyType;
    int reward;
    float speed;
    EnemyState currentState;
    QVector<QPointF> pathPoints;
    int currentPathIndex;
    QTimer *moveTimer;
    bool reachedEnd;
    bool isHighlighted;
};

#endif
