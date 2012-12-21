#pragma once

#define SCREEN_WIDTH        600
#define SCREEN_HEIGHT       800
#define MSPERFRAME          30

#define PI                  3.141592f

//定义子弹类型
enum BulletType
{
    AMMO0 = 0,
    AMMO1,
    AMMO2,
    AMMO3,
    AMMO4,
    AMMO5,
    AMMO6,
    WHOLEFRIED
};

//定义动作类型
enum ActionType
{
    LEFT,
    DOWN,
    RIGHT,
    UP,
    LEFT_UP,
    LEFT_DOWN,
    RIGHT_UP,
    RIGHT_DOWN,
    STOP_MOVE,
    FIRE,
    STOP_FIRE,
    FIREALL
};

//敌机类型
enum EnemyType
{
    ENEMY0 = 0,
    ENEMY1,
    ENEMY2,
    ENEMY3,
    ENEMY4
};

//爆炸效果类型
enum BlastType
{
    BULLETBLAST = 0,
    PLANEBLAST
};

//游戏状态
enum GameStatus
{
    emGameStatusNone,       ///> 什么都不干
    emGameStatusReady,
    emGameStatusOver,
    emGameStatusPlaying,
};

// 图片类型
enum PictureType
{
    emPicTypeBullet = 0,
    emPicTypeExplosion,
    emPicTypePlane,
};