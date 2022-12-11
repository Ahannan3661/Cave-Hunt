#pragma once
#include <SDL.h>

//Screen dimension constants
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int PLATFORM_HEIGHT;

//number of items in menu
extern int NUM_MENU_ITEMS;

//font size
extern int FONT_SIZE;

//menu item colors
extern SDL_Color colors[2];

extern int BOSS_ARRIVAL_SCORE;
extern int bossWarningTimer;

//Frame rate
extern int FPS;

//Time between each frame
extern int frameDelay;

//friction in game
extern float friction;

//player constants
extern int totalSpellCount;
extern int totalCastingCooldown;
extern int totalSpellReloadTime;

//Game Object state constants
extern int IDLE;
extern int RUNNING;
extern int ATTACKING;
extern int HIT;
extern int DEATH;

//Sprite change time
extern int totalSpriteTime;
extern int totalSpellSpriteTime;

//delete after death time
extern int totalPlayerDeathTime;
extern int totalEnemyDeathTime;
extern int totalProjectileDeathTime;

//attck constants
extern int totalAttackTime;
extern int totalEnemyAttackTime;

//player constants
extern int jumpVel;
extern int playerHealth;
extern int playerSourceW;
extern int playerSourceH;
extern int playerScale;
extern int playerProjDamage ;
extern int playerSpeed;

//the offset of player's sprites actual location
extern int playerSpriteOffsetX;
extern int playerSpriteOffsetY;
extern int playerSpriteW;
extern int playerSpriteH;

//monster Constants
extern int monsterSpriteOffsetX;
extern int monsterSpriteOffsetY;
extern int monsterSpriteW;
extern int monsterSpriteH;
extern float monsterScale;
extern int monsterSourceW;
extern int monsterSourceH;
extern int skeletonAttackRange;
extern int skeletonGuardRange;
extern int totalGuardDuration;
extern int meeleMonsterDamage;
extern int eyeAttackRange;
extern int mushroomAttackRange;
extern int goblinAttackRange;

extern int enemyMoveSpeed;
extern int monsterHealth;

//DarkWiz constants
extern int darkWizSpriteOffsetX;
extern int darkWizSpriteOffsetY;
extern int darkWizSpriteW;
extern int darkWizSpriteH;
extern int darkWizSourceW;
extern int darkWizSourceH;
extern int darWizAttackRange;

//Worm constants
extern int wormSpriteOffsetX;
extern int wormSpriteOffsetY;
extern int wormSpriteW;
extern int wormSpriteH;
extern int wormSourceW;
extern int wormSourceH;
extern int wormAttackRange;

//boss constants
extern int bossAttackTime;
extern int bossHealth;
extern int bossSourceW;
extern int bossSourceH;
extern int bossAttackRange;

//the offset of boss sprites actual location
extern int bossSpriteOffsetX;
extern int bossSpriteOffsetY;
extern int bossSpriteW;
extern int bossSpriteH;

//player movement limts
extern int playerLimit;

//background constants
extern int backgroundWidth;
extern int l1MoveSpeed;
extern int l2MoveSpeed;
extern int l3MoveSpeed;
extern int l4MoveSpeed;
extern int l5MoveSpeed;

//projectile constants
extern int projMoveSpeed;
extern int projHealth;
extern int hostileProjDamage;
extern int projDamage;
extern int projW;
extern int projH;
extern int projScale;

//HealthBar constants
extern float barToFillRatio;

//button sprite constants
extern int buttonSpriteW;
extern int buttonSpriteH;

//cloud constants
extern int cloudW;
extern int cloudH;
extern float cloudScale;

//thunder bolt constants
extern int boltW;
extern int boltH;
extern float boltScale;
extern float boltAngle;

// sprite/sound/font paths
extern const char* POISONBALL;
extern const char* EYE;
extern const char* SKELETON;
extern const char* SKELETON_SHIELD;
extern const char* WORM;
extern const char* TUNDERCLOUD;
extern const char* THUNDERBOLT;
extern const char* EYESPELL;
extern const char* FIREBALL;
extern const char* BOSS;
extern const char* MUSHROOM;
extern const char* GOBLIN;
extern const char* DARKWIZ;
extern const char* PLAYER;
extern const char* PLAYERSPELL;
extern const char* SKULL;
extern const char* HEALTHBAR;
extern const char* HEALTHFILL;
extern const char* MENUMUSIC;
extern const char* BUTTONSOUND;
extern const char* GAMEMUSIC;
extern const char* SKY;
extern const char* DOWNLAYER;
extern const char* MIDDLELAYER;
extern const char* LIGHT;
extern const char* TOPLAYER;
extern const char* BOSSARRIVALSOUND;
extern const char* YOUWINSOUND;
extern const char* YOULOSESOUND;
extern const char* PLAYERSPELLSOUND;
extern const char* PLAYERJUMPSOUND;
extern const char* BOSSATTACKSOUND;
extern const char* HITSOUND;
extern const char* MEELEATTACKSOUND;
extern const char* SPELLSOUND;
extern const char* BUTTONCORNER;
extern const char* BUTTONEDGE;
extern const char* BUTTONMIDDLE;
extern const char* FONT;

//enemy spawn locations
extern int MONSTER_SPAWNX;
extern int MONSTER_SPAWNY;
extern int WORM_SPAWNY;
extern int CLOUD_SPAWNY;
extern int EYE_SPAWNX;
extern int EYE_SPAWNY;
extern int BOSS_SPAWNY;
extern int DARKWIZ_SPAWNY;
extern int PLAYER_SPAWNX;
extern int PLAYER_SPAWNY;