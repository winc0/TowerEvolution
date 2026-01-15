#ifndef BULLET_H
#define BULLET_H

#include "gameentity.h"
#include <QPointer>
#include <QTimer>
#include <QPointF>
#include "config.h"

class Enemy; // 前置声明，头文件里只用指针或引用

class Bullet : public GameEntity
{
    Q_OBJECT
public:
    Bullet(QPointF startPos, QPointer<Enemy> target, int damage, QObject *parent = nullptr);
    ~Bullet();

    void update() override;
    void pauseMovement() { if(moveTimer) moveTimer->stop(); }
    void resumeMovement() { if(moveTimer) moveTimer->start(GameConfig::BULLET_MOVE_INTERVAL); }


signals:
    void hit(QPointer<Enemy> enemy, int damage);

private slots:
    void onMoveTimer();

private:
    void updateRotation();

private:
    QPointer<Enemy> target;
    QPointF targetPos;
    QPointF direction;
    int damage;
    float speed;
    QTimer *moveTimer;
};

#endif // BULLET_H
