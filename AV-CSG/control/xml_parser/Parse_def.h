#ifndef STATE_PARSE_DEF
#define STATE_PARSE_DEF

#define STAGE_ROOT_GAME "gamestage"
#define PLANE_ROOT_GAME "gameplane"
#define BULLET_ROOT_GAME "gamebullet"
#define BLAST_ROOT_GAME "gameblast"
#define WEAPON_ROOT_GAME "gameweapon"
#define EMITTER_ROOT_GAME "gameemitter"

#define TRUE_GAME "true"
#define FALSE_GAME "false"

#define ID_OBJECT "id"
#define TYPE_OBJECT "type"
#define NAME_OBJECT "name"
#define POSX_OBJECT "posx"
#define POSY_OBJECT "posy"
#define WIDTH_OBJCET "width"
#define HEIGHT_OBJECT "height"
#define FRAMECOUNT_OBJECT "framecount"

///> stage
#define ITEM_GAME "item"
#define ENEMY_GAME "enemy"
#define STAGE_GAME "stage"

///> enemy
#define ENEMY_APPEAR_OBJECT "appear"
#define ENEMY_BIND_OBJECT "bind"

///> stage
#define STAGE_DIFFICULTY_OBJECT "difficulty"
#define STAGE_MAP_OBJECT "map"

///> item
#define ITEM_WAY_OBJECT "way"
#define ITEM_NUMBER_OBJECT "number"

///> enemyplane
#define PLANE_GAME "plane"
#define PLANE_ENEMY_GAME "enemyplane"
#define PLANE_SELF_GAME "selfplane"
#define PLANE_HP_OBJECT "hp"
#define PLANE_SKIN_OBJECT "skin"
#define PLANE_WEAPON_OBJECT "weapon"
#define PLANE_SPEED_OBJECT "speed"

///> bullet
#define BULLET_GAME "bullet"
#define BULLET_SPEED_GAME "speed"
#define BULLET_POWER_GAME "power"

///> blast
#define BLAST_GAME "blast"
#define BLAST_SKIN_OBJECT "skin"

///> emitter
#define EMITTER_GAME "emitter"

///> weapon
#define WEAPON_GAME "weapon"
#define WEAPON_BULLETTYPE_OBJECT "bullettype"
#define WEAPON_EMITTER_OBJCET "emitter"

///> xmllist
#define XMLLIST_ROOT "xmllist"
#define XMLLIST_PATH "path"
#define XMLLIST_XML "xml"

#endif