#include "bullet.h"
#include "enemy.h"         // ✅ 在 cpp 文件里包含完整 Enemy
#include "config.h"
#include "resourcemanager.h"

#include <QGraphicsScene>
#include <cmath>
#include <QDebug>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Bullet::Bullet(QPointF startPos, QPointer<Enemy> target, int damage, QObject *parent)
    : GameEntity(BULLET, parent),
    target(target),
    damage(damage),
    speed(GameConfig::BULLET_SPEED)
{
    setPos(startPos);

    // 载入子弹图片
    QPixmap pixmap = ResourceManager::instance().getBulletPixmap();
    setPixmap(pixmap);
    setTransformOriginPoint(pixmap.width()/2.0, pixmap.height()/2.0);
    setOffset(-pixmap.width()/2.0, -pixmap.height()/2.0);

    // 计算方向向量，如果有目标则朝目标中心，否则默认向上
    if(target && !target.isNull()) {
        QPointF delta = target->getCenterPosition() - startPos;
        qreal len = std::sqrt(delta.x()*delta.x() + delta.y()*delta.y());
        direction = (len > 0) ? (delta / len) : QPointF(0, -1);
    } else {
        direction = QPointF(0, -1);
    }

    updateRotation();

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Bullet::onMoveTimer);
    moveTimer->start(GameConfig::BULLET_MOVE_INTERVAL);
}

Bullet::~Bullet()
{
    if(moveTimer) moveTimer->stop();
}

void Bullet::update()
{
    onMoveTimer();
}

void Bullet::onMoveTimer()
{
    QPointF nextPos = pos() + direction * speed;
    setPos(nextPos);

    if(target && !target.isNull()) {
        QPointF targetCenter = target->getCenterPosition();
        qreal distance = QLineF(nextPos, targetCenter).length();
        if(distance <= GameConfig::ENEMY_COLLISION_RADIUS + GameConfig::BULLET_COLLISION_RADIUS) {
            target->setHealth(target->getHealth() - damage); // 伤害生效
            if(scene()) scene()->removeItem(this);
            deleteLater();
            return;
        }
    }

    // 超出屏幕也删除
    if(nextPos.x() < -GameConfig::BULLET_SIZE || nextPos.x() > GameConfig::WINDOW_WIDTH + GameConfig::BULLET_SIZE ||
        nextPos.y() < -GameConfig::BULLET_SIZE || nextPos.y() > GameConfig::WINDOW_HEIGHT + GameConfig::BULLET_SIZE)
    {
        if(scene()) scene()->removeItem(this);
        deleteLater();
        return;
    }
}


void Bullet::updateRotation()
{
    qreal angle = std::atan2(direction.y(), direction.x()) * 180.0 / M_PI + 90.0;
    setRotation(angle);
}
