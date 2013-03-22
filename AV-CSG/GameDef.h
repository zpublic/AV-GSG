#pragma once

#define SCREEN_WIDTH        500
#define SCREEN_HEIGHT       650

///> 帧数定为60，这是一个非常合理的数字，飞机子弹的速度将根据这个固定的帧数来计算
#define MSPERFRAME          16.666666f // 1000/60

#define ElapsedTime         0.0166666f

#define PI                  3.141592f

//定义子弹类型
enum BulletType
{
    emBulletTypeAMMO0 = 0,
    emBulletTypeAMMO1,
    emBulletTypeAMMO2,
    emBulletTypeAMMO3,
    emBulletTypeAMMO4,
    emBulletTypeAMMO5,
    emBulletTypeAMMO6,
    emBulletTypeAmmoAll1,
    emBulletTypeAmmoSB,
    emBulletTypeAmmoSB2,

    emBulletTypeMax
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
    FIREALL,
    WILL,
};

//爆炸效果类型
enum BlastType
{
    emBlastTypeBullet = 16,
    emBlastTypePlane,

    emBlastTypeMax
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