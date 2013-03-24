#pragma once

#define SCREEN_WIDTH        500
#define SCREEN_HEIGHT       650

///> ֡����Ϊ60������һ���ǳ���������֣��ɻ��ӵ����ٶȽ���������̶���֡��������
#define MSPERFRAME          16.666666f // 1000/60

#define ElapsedTime         0.0166666f

#define PI                  3.141592f

typedef std::string BulletType;
typedef std::string BlastType;

//���嶯������
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

//��Ϸ״̬
enum GameStatus
{
    emGameStatusNone,       ///> ʲô������
    emGameStatusReady,
    emGameStatusOver,
    emGameStatusRuning,
    emGameStatusPause,  ///> ��ͣ
};

//����������
enum GameStagePlayType
{
    emGameStagePlayTime,
    emGameStagePlayEnemy,
    emGameStagePlayEnemyBoss,
};

//������״̬
enum GameStagePlayStatus
{
    emGameStagePlayStatusNone,
    emGameStagePlayStatusRuning
};

// ͼƬ����
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
