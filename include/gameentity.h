#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QString>

class ResourceManager;

// 声音播放能力接口
class ISoundPlayable
{
public:
    virtual ~ISoundPlayable() {}
    // 设置资源管理器指针
    virtual void setResourceManager(ResourceManager *manager) = 0;
    // 播放指定音效
    virtual void playSound(const QString &soundId, qreal volume = 1.0, bool loop = false) = 0;
};

// 场景内通用游戏实体
class GameEntity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum EntityType {
        ENEMY,
        TOWER,
        BULLET,
        PATH
    };

    // 构造实体并设置类型
    explicit GameEntity(EntityType type, QObject *parent = nullptr);
    // 虚析构保证多态销毁
    virtual ~GameEntity() = default;

    // 获取实体类型枚举
    EntityType getType() const { return type; }
    // 获取当前生命值
    int getHealth() const { return health; }
    // 设置当前生命值
    void setHealth(int newHealth);
    // 设置最大生命值
    void setMaxHealth(int newMaxHealth);
    // 抽象更新接口由子类实现
    virtual void update() = 0;

protected:
    EntityType type;
    int health;
    int maxHealth;
    QPointF velocity;
};

#endif // GAMEENTITY_H
