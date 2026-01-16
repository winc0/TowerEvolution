#ifndef CONFIG_H
#define CONFIG_H

#include <QHash>
#include <QVector>
#include <QPointF>

// 全局配置入口：
// - 所有与游戏规则、数值平衡、窗口尺寸等相关的常量均集中在此
// - 页面内部纯绘制用的“像素偏移”“控件间距”等局部魔法数保留在各自页面中
namespace GameConfig
{
    // ======================== 应用信息配置 ========================
    const char* const APP_NAME = "TowerEvolutionGame";
    const char* const ORG_NAME = "TowerEvolutionStudio";
    const char *const APP_VER = "1.0.0";

    // ======================== 窗口与网格配置 ========================

    // 游戏主窗口宽度（像素），决定渲染区域和地图宽度
    const int WINDOW_WIDTH = 800;

    // 游戏主窗口高度（像素），决定渲染区域和地图高度
    const int WINDOW_HEIGHT = 600;

    // 逻辑网格大小（像素），用于路径、建塔、碰撞等坐标换算
    const int GRID_SIZE = 40;

    // ======================== 游戏基础数值配置 ========================

    // 每局游戏初始生命值（被敌人到达终点时扣减）
    const int INITIAL_LIVES = 20;

    // 每局游戏初始金币，用于建造与升级防御塔
    const int INITIAL_GOLD = 300;

    // 敌人被击杀时基础金币奖励
    const int ENEMY_REWARD = 15;

    // 游戏逻辑更新的帧间隔（毫秒），控制主循环刷新频率
    const int GAME_TICK_INTERVAL_MS = 16;

    // 每击杀一个敌人获得的得分
    const int SCORE_PER_KILL = 10;

    // 每通过一波获得的得分
    const int SCORE_PER_WAVE = 50;

    // 评级阈值（总得分不小于该值触发对应等级）
    const int SCORE_GRADE_S_MIN = 1200;
    const int SCORE_GRADE_A_MIN = 800;
    const int SCORE_GRADE_B_MIN = 400;

    // 拆除防御塔时返还的百分比（0-100）
    const int TOWER_SELL_REFUND_PERCENT = 70;

    // ======================== 敌人基础配置 ========================

    // 可用敌人类型的数量（用于随机类型选择与边界检查）
    const int ENEMY_TYPE_NUMBER = 4;

    // 第一波敌人的基础血量，后续波次在此基础上按公式递增
    const int ENEMY_HEALTH = 100;

    // 敌人逻辑尺寸（像素），用于渲染与碰撞检测
    const int ENEMY_SIZE = 30;

    // 敌人移动计时器触发间隔（毫秒）
    const int ENEMY_MOVE_INTERVAL = 50;

    // 敌人基础移动速度（每次移动的单位距离，配合计时器使用）
    const float ENEMY_SPEED = 1.0f;

    // 敌人死亡后在场景中保留的时间（毫秒）
    const int ENEMY_DEAD_KEEP_TIME = 500;

    // ======================== 子弹基础配置 ========================

    // 子弹逻辑尺寸（像素），用于渲染与碰撞检测
    const int BULLET_SIZE = 10;

    // 子弹移动计时器触发间隔（毫秒）
    const int BULLET_MOVE_INTERVAL = 30;

    // 子弹基础移动速度（每次移动的单位距离）
    const float BULLET_SPEED = 5.0f;

    // ======================== 防御塔数值配置 ========================

    namespace TowerStats
    {
        // -------- 箭塔（基础型防御塔） --------

        // 箭塔单次攻击造成的基础伤害
        const int ARROW_DAMAGE = 20;

        // 箭塔攻击范围半径（像素）
        const int ARROW_RANGE = 150;

        // 建造箭塔所需金币
        const int ARROW_COST = 100;

        // 箭塔攻击间隔（毫秒），两次开火之间的最小时间
        const int ARROW_FIRE_RATE = 1000;

        // -------- 炮塔（范围伤害防御塔） --------

        // 炮塔单次攻击基础伤害
        const int CANNON_DAMAGE = 30;

        // 炮塔攻击范围半径（像素）
        const int CANNON_RANGE = 100;

        // 建造炮塔所需金币
        const int CANNON_COST = 150;

        // 炮塔攻击间隔（毫秒）
        const int CANNON_FIRE_RATE = 1500;

        // -------- 魔法塔（高伤高价防御塔） --------

        // 魔法塔单次攻击基础伤害
        const int MAGIC_DAMAGE = 50;

        // 魔法塔攻击范围半径（像素）
        const int MAGIC_RANGE = 150;

        // 建造魔法塔所需金币
        const int MAGIC_COST = 200;

        // 魔法塔攻击间隔（毫秒）
        const int MAGIC_FIRE_RATE = 2000;
    }

    // ======================== 波次与刷怪节奏配置 ========================

    // 每波固定刷新的敌人数量
    const int WAVE_ENEMY_COUNT = 10;

    // 单关卡最大波次数量
    const int WAVE_COUNT_MAX = 5;

    // 第一波刷怪的初始间隔（毫秒）
    const int WAVE_SPAWN_INTERVAL_MAX = 2000;

    // 后期刷怪间隔下限（毫秒）
    const int WAVE_SPAWN_INTERVAL_MIN = 500;

    // 每增加一波时刷怪间隔递减量（毫秒）
    const int WAVE_SPAWN_INTERVAL_EACH = 200;

    // 每波敌人血量相对上一波的线性增长系数
    const qreal ENEMY_HEALTH_GROWTH_PER_WAVE = 0.5;

    // 每波敌人速度相对上一波的线性增长系数
    const float ENEMY_SPEED_GROWTH_PER_WAVE = 0.1f;

    // ======================== 碰撞检测配置 ========================

    // 敌人碰撞半径（像素），用于与子弹的碰撞判断
    const float ENEMY_COLLISION_RADIUS = ENEMY_SIZE / 2.0f;

    // 子弹碰撞半径（像素）
    const float BULLET_COLLISION_RADIUS = BULLET_SIZE / 2.0f;

    // ======================== 旋转与目标锁定配置 ========================

    // 防御塔单帧最大旋转角度（度），控制转向速度
    const float TOWER_ROTATION_MAX_STEP = 5.0f;

    // 防御塔旋转速度（度/秒），用于计算每帧插值步长
    const float TOWER_ROTATION_SPEED_DEG_PER_SEC = 45.0f;

    // 塔在锁定目标时保持目标不变的时间（毫秒）
    const int TOWER_TARGET_LOCK_MS = 400;

    // 子弹最大飞行距离（像素），超过则自动销毁
    const float BULLET_MAX_DISTANCE = 600.0f;

    // 失去目标后维持追踪的最大时间（毫秒）
    const int BULLET_TARGET_LOST_TIMEOUT_MS = 400;

    // ======================== 地图与路径配置 ========================

    // 终点区域配置，用于判断敌人是否到达萝卜
    struct EndPointConfig
    {
        qreal x;
        qreal y;
        qreal radius;
    };

    // 关卡枚举 ID，对应不同地图与资源
    enum MapId
    {
        MAP1 = 0,
        MAP2 = 1
    };

    // 网格坐标结构，统一描述路径点与建塔点位置
    struct GridPoint
    {
        int gridX;
        int gridY;
    };

    namespace MapPaths
    {
        // 地图 1 的敌人行进路径（网格坐标序列）
        const QVector<GridPoint> MAP1_PATH = {
            {16, 6},
            {16, 7},
            {11, 7},
            {11, 6},
            {4, 6},
            {4, 7},
            {7, 7},
            {7, 11},
            {9, 11},
            {9, 9},
            {16, 9},
        };

        // 地图 2 的敌人行进路径（网格坐标序列）
        const QVector<GridPoint> MAP2_PATH = {
            {2, 12},
            {5, 12},
            {5, 8},
            {6, 8},
            {6, 7},
            {10, 7},
            {10, 10},
            {9, 10},
            {9, 13},
            {15, 13},
            {15, 10},
            {18, 10},
            {18, 8},
        };

        // 根据地图 ID 查找对应路径配置的映射表
        const QHash<MapId, QVector<GridPoint>> PATH_MAP = {
            {MAP1, MAP1_PATH},
            {MAP2, MAP2_PATH},
        };
    }

    // ======================== 建塔可放置区域配置 ========================

    namespace Placement
    {
        // 地图 1 中允许建塔的网格列表
        const QVector<GridPoint> MAP1_BUILDABLE_GRIDS = {
            {13, 6},
            {14, 6},
            {15, 6},

            {8, 7},
            {9, 7},
            {10, 7},
            {8, 8},
            {9, 8},

            {4, 8},
            {5, 8},
            {6, 8},
            {6, 9},
            {6, 10},

            {11, 8},
            {12, 8},
            {13, 8},
            {14, 8},
            {15, 8},
            {16, 8},

            {10, 10},
            {11, 10},
            {12, 10},

            {14, 10},
            {15, 10},
            {16, 10},
        };

        // 地图 2 中允许建塔的网格列表
        const QVector<GridPoint> MAP2_BUILDABLE_GRIDS = {
            {2, 10},
            {3, 10},
            {3, 8},
            {3, 7},
            {4, 6},
            {12, 7},
            {12, 8},
            {12, 9},
            {12, 11},
            {13, 11},
            {13, 10},
            {13, 9},
            {13, 7},
            {14, 7},
            {14, 8},
            {15, 8},
            {16, 8},
            {16, 7},
            {7, 11},
            {7, 13},
        };

        // 地图 ID 到可建塔网格列表的映射
        const QHash<MapId, QVector<GridPoint>> BUILDABLE_MAP = {
            {MAP1, MAP1_BUILDABLE_GRIDS},
            {MAP2, MAP2_BUILDABLE_GRIDS},
        };
    }

    // ======================== UI 提示与特效配置 ========================

    // 悬浮提示文字的显示时长（毫秒）
    const int TIP_DURATION_MS = 2000;

    // 升级特效（光圈等）的持续时间（毫秒）
    const int UPGRADE_EFFECT_DURATION_MS = 300;

    // 建塔时高亮方格的持续时间（毫秒）
    const int HIGHLIGHT_EFFECT_DURATION_MS = 500;

    // 结算面板淡入和缩放动画时长（毫秒）
    const int RESULT_PANEL_ANIM_DURATION_MS = 300;
}

#endif // CONFIG_H
