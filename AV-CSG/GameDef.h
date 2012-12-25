#pragma once

#define SCREEN_WIDTH        500
#define SCREEN_HEIGHT       700
#define MSPERFRAME          30

#define XML_ROOT_ELEMENT_NAME   "root"
#define XML_PIC_ELEMENT_ID      "id"
#define XML_PIC_ELEMENT_R       "r"
#define XML_PIC_ELEMENT_G       "g"
#define XML_PIC_ELEMENT_B       "b"
#define XML_PIC_ELEMENT_PATH    "path"

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
    FIREALL
};

//敌机类型
enum EnemyType
{
    emEnemyTypeENEMY0 = 0,
    emEnemyTypeENEMY1,
    emEnemyTypeENEMY2,
    emEnemyTypeENEMY3,
    emEnemyTypeENEMY4,

    emEnemyTypeMax
};

//爆炸效果类型
enum BlastType
{
    emBlastTypeBullet = 0,
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
};

// 图片类型
enum PictureType
{
    emPicTypeBullet = 0,
    emPicTypeExplosion,
    emPicTypePlane,
};