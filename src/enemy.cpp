#include "enemy.h"
#include "resourcemanager.h"
#include "config.h"

#include <QTimer>
#include <cmath>

Enemy::Enemy(int enemyType, QObject *parent)
    : GameEntity(ENEMY, parent)
    , enemyType(enemyType)
    , reward(GameConfig::ENEMY_REWARD)
    , speed(GameConfig::ENEMY_SPEED)
    , currentPathIndex(0)
    , reachedEnd(false)
    , currentState(ResourceManager::ENEMY_WALK)
{
    maxHealth = GameConfig::ENEMY_HEALTH;
    currentHealth = maxHealth;

    // 从资源文件加载敌人图片
    ResourceManager &rm = ResourceManager::instance();
    setPixmap(rm.getEnemyPixmap(enemyType, currentState));

    // 移动计时器
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemy::onMoveTimer);
    moveTimer->start(GameConfig::ENEMY_MOVE_INTERVAL);
}

Enemy::~Enemy()
{
    if (moveTimer) moveTimer->stop();
}

void Enemy::update()
{
    moveAlongPath();
}

void Enemy::setPath(const QVector<QPointF>& pathPoints)
{
    this->pathPoints = pathPoints;
    if (!pathPoints.isEmpty()) {
        setPos(pathPoints.first());
        currentPathIndex = 1;
    }
}

QPointF Enemy::getCenterPosition() const
{
    QPointF topLeft = pos();
    QRectF rect = boundingRect();
    return QPointF(topLeft.x() + rect.width() / 2.0,
                   topLeft.y() + rect.height() / 2.0);
}

void Enemy::moveAlongPath()
{
    if (reachedEnd || pathPoints.isEmpty() || currentPathIndex >= pathPoints.size()) {
        reachedEnd = true;
        velocity = QPointF(0,0);
        return;
    }

    QPointF currentPos = pos();
    QPointF targetPos = pathPoints[currentPathIndex];
    QPointF dir = targetPos - currentPos;
    qreal distance = std::sqrt(dir.x()*dir.x() + dir.y()*dir.y());

    if (distance > 0) {
        velocity = dir / distance * speed;
    } else {
        velocity = QPointF(0,0);
    }

    if(distance < speed) {
        setPos(targetPos);
        currentPathIndex++;
        if(currentPathIndex >= pathPoints.size()) {
            reachedEnd = true;
            velocity = QPointF(0,0);
            emit reachedEndPoint();
        }
    } else {
        setPos(currentPos + velocity);
    }
}

void Enemy::onMoveTimer()
{
    moveAlongPath();
}

void Enemy::setState(EnemyState state)
{
    if (currentState == state)
        return;

    currentState = state;

    if (state == ResourceManager::ENEMY_DEAD) {
        if (moveTimer) moveTimer->stop();
    }

    // 更新贴图
    ResourceManager &rm = ResourceManager::instance();
    setPixmap(rm.getEnemyPixmap(enemyType, currentState));
}

void Enemy::takeDamage(int amount)
{
    if (currentState == ResourceManager::ENEMY_DEAD)
        return;

    currentHealth -= amount;
    if (currentHealth <= 0) {
        currentHealth = 0;
        setState(ResourceManager::ENEMY_DEAD);
        emit enemyKilled(reward);
    }
}
