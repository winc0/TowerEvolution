#include "include/quadtree.h"

Quadtree::Quadtree(const QRectF& boundary, int capacity)
    : boundary(boundary), capacity(capacity), divided(false),
      northwest(nullptr), northeast(nullptr), southwest(nullptr), southeast(nullptr)
{
}

Quadtree::~Quadtree()
{
    clear();
}

void Quadtree::clear()
{
    if (divided)
    {
        delete northwest;
        delete northeast;
        delete southwest;
        delete southeast;
        northwest = nullptr;
        northeast = nullptr;
        southwest = nullptr;
        southeast = nullptr;
        divided = false;
    }
    enemies.clear();
}

void Quadtree::insert(Enemy* enemy)
{
    if (!enemy) return;
    
    QPointF pos = enemy->pos();
    if (!boundary.contains(pos))
    {
        return;
    }

    if (enemies.size() < capacity && !divided)
    {
        enemies.append(enemy);
    }
    else
    {
        if (!divided)
        {
            subdivide();
        }

        northwest->insert(enemy);
        northeast->insert(enemy);
        southwest->insert(enemy);
        southeast->insert(enemy);
    }
}

void Quadtree::subdivide()
{
    qreal x = boundary.x();
    qreal y = boundary.y();
    qreal w = boundary.width();
    qreal h = boundary.height();

    QRectF nw(x, y, w / 2, h / 2);
    QRectF ne(x + w / 2, y, w / 2, h / 2);
    QRectF sw(x, y + h / 2, w / 2, h / 2);
    QRectF se(x + w / 2, y + h / 2, w / 2, h / 2);

    northwest = new Quadtree(nw, capacity);
    northeast = new Quadtree(ne, capacity);
    southwest = new Quadtree(sw, capacity);
    southeast = new Quadtree(se, capacity);

    divided = true;

    // Move existing enemies to children
    for (Enemy* e : enemies)
    {
        northwest->insert(e);
        northeast->insert(e);
        southwest->insert(e);
        southeast->insert(e);
    }
    enemies.clear();
}

void Quadtree::query(const QRectF& range, QList<Enemy*>& found) const
{
    if (!boundary.intersects(range))
    {
        return;
    }

    if (divided)
    {
        northwest->query(range, found);
        northeast->query(range, found);
        southwest->query(range, found);
        southeast->query(range, found);
    }
    else
    {
        for (Enemy* e : enemies)
        {
            if (range.contains(e->pos()))
            {
                found.append(e);
            }
        }
    }
}
