#pragma once

#define SCREEN_WIDTH        500
#define SCREEN_HEIGHT       650

///> 帧数定为60，这是一个非常合理的数字，飞机子弹的速度将根据这个固定的帧数来计算
#define MSPERFRAME          16.666666f // 1000/60

#define ElapsedTime         0.0166666f

#define PI                  3.141592f

typedef std::string BulletType;
typedef std::string BlastType;

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
    FIREALL,
};

//游戏状态
enum GameStatus
{
    emGameStatusNone,       ///> 什么都不干
    emGameStatusReady,
    emGameStatusOver,
    emGameStatusRuning,
    emGameStatusPause,  ///> 暂停
};

//控制器类型
enum GameStagePlayType
{
    emGameStagePlayTime,
    emGameStagePlayEnemy,
    emGameStagePlayEnemyBoss,
};

//控制器状态
enum GameStagePlayStatus
{
    emGameStagePlayStatusNone,
    emGameStagePlayStatusRuning
};

// 图片类型
enum PictureType
{
    emPicTypeBullet = 0,
    emPicTypeExplosion,
    emPicTypePlane,
};

typedef int32_t   int32;
typedef uint32_t  uint32;
typedef int16_t   int16;
typedef uint16_t  uint16;
typedef int8_t    int8;
typedef uint8_t   uint8;
