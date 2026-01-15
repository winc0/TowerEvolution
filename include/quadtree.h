#ifndef QUADTREE_H
#define QUADTREE_H

#include "enemy.h"
#include <QRectF>
#include <QList>
#include <QPointer>

class Quadtree
{
public:
    Quadtree(const QRectF& boundary, int capacity);
    ~Quadtree();

    void insert(Enemy* enemy);
    void query(const QRectF& range, QList<Enemy*>& found) const;
    void clear();

private:
    QRectF boundary;
    int capacity;
    QList<Enemy*> enemies;
    bool divided;

    Quadtree* northwest;
    Quadtree* northeast;
    Quadtree* southwest;
    Quadtree* southeast;

    void subdivide();
};

#endif // QUADTREE_H
