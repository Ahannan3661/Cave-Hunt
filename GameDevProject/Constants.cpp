#pragma once
#include "Constants.h"

////
// ALL THE GAME CONSTANTS ARE INITIALIZED IN THIS CLASS
////

//Screen dimension constants
 int SCREEN_WIDTH = 640;
 int SCREEN_HEIGHT = 480;
 int PLATFORM_HEIGHT = 380;

//number of items in menu
 int NUM_MENU_ITEMS = 2;

//menu item colors
 SDL_Color colors[2] = { {0,0,0}, {0,255,0} };

 int BOSS_ARRIVAL_SCORE = 0;
 int bossWarningTimer = 160;

//Frame rate
 int FPS = 60;

 int FONT_SIZE = 28;

//Time between each frame
 int frameDelay = 1000 / FPS;

//friction in game
 float friction = 0.95f;

//player constants
 int totalSpellCount = 10;
 int totalCastingCooldown = 40;
 int totalSpellReloadTime = 120;

//Game Object state constants
 int IDLE = 0;
 int RUNNING = 1;
 int ATTACKING = 2;
 int HIT = 3;
 int DEATH = 4;

//Sprite change time
 int totalSpriteTime = 5;
 int totalSpellSpriteTime = 10;

//delete after death time
 int totalPlayerDeathTime = 120;
 int totalEnemyDeathTime = 120;
 int totalProjectileDeathTime = 0;

//attck constants
 int totalAttackTime = 120;
 int totalEnemyAttackTime = 200;

//player constants
 int jumpVel = -25;
 int playerHealth = 50;
 int playerSourceW = 231;
 int playerSourceH = 190;
 int playerScale = 1;
 int playerProjDamage = 10;
 int playerSpeed = 5;

//the offset of player's sprites actual location
 int playerSpriteOffsetX = 85;
 int playerSpriteOffsetY = 50;
 int playerSpriteW = 65;
 int playerSpriteH = 90;

//monster Constants
 int monsterSpriteOffsetX = 55;
 int monsterSpriteOffsetY = 50;
 int monsterSpriteW = 35;
 int monsterSpriteH = 50;
 float monsterScale = 1.5;
 int monsterSourceW = 150;
 int monsterSourceH = 150;
 int skeletonAttackRange = 120;
 int skeletonGuardRange = 200;
 int totalGuardDuration = 60;
 int meeleMonsterDamage = 5;
 int eyeAttackRange = 500;
 int mushroomAttackRange = 200;
 int goblinAttackRange = 80;

 int enemyMoveSpeed = 2;
 int monsterHealth = 20;

//DarkWiz constants
 int darkWizSpriteOffsetX = 100;
 int darkWizSpriteOffsetY = 100;
 int darkWizSpriteW = 55;
 int darkWizSpriteH = 65;
 int darkWizSourceW = 250;
 int darkWizSourceH = 250;
 int darWizAttackRange = 300;

//Worm constants
 int wormSpriteOffsetX = 15;
 int wormSpriteOffsetY = 15;
 int wormSpriteW = 60;
 int wormSpriteH = 50;
 int wormSourceW = 90;
 int wormSourceH = 90;
 int wormAttackRange = 350;

//boss constants
 int bossAttackTime = 1000;
 int bossHealth = 40;
 int bossSourceW = 160;
 int bossSourceH = 128;
 int bossAttackRange = 380;

//the offset of boss sprites actual location
 int bossSpriteOffsetX = 55;
 int bossSpriteOffsetY = 60;
 int bossSpriteW = 50;
 int bossSpriteH = 60;

//player movement limts
 int playerLimit = 150;

//background constants
 int backgroundWidth = 1137;
 int l1MoveSpeed = 20;
 int l2MoveSpeed = 15;
 int l3MoveSpeed = 10;
 int l4MoveSpeed = 5;
 int l5MoveSpeed = 0;

//projectile constants
 int projMoveSpeed = 6;
 int projHealth = 1;
 int hostileProjDamage = 5;
 int projDamage = 10;
 int projW = 32;
 int projH = 32;
 int projScale = 1;

//HealthBar constants
 float barToFillRatio = 0.21;

//button sprite constants
 int buttonSpriteW = 32;
 int buttonSpriteH = 32;

//cloud constants
 int cloudW = 32;
 int cloudH = 32;
 float cloudScale = 3.0f;

//thunder bolt constants
 int boltW = 32;
 int boltH = 32;
 float boltScale = 1.0f;
 float boltAngle = 90.0f;

//sprite paths
 const char* POISONBALL = "assets/monsters/mushroom/poisonBall.png";
 const char* EYE = "assets/monsters/eye";
 const char* SKELETON = "assets/monsters/skeleton";
 const char* SKELETON_SHIELD = "assets/monsters/skeleton/shield.png";
 const char* WORM = "assets/monsters/worm";
 const char* TUNDERCLOUD = "assets/monsters/darkWiz/thunderCloud.png";
 const char* THUNDERBOLT = "assets/monsters/darkWiz/bolt.png";
 const char* EYESPELL = "assets/monsters/eye/eyeSpell.png";
 const char* FIREBALL = "assets/monsters/worm/fireBall.png";
 const char* BOSS = "assets/monsters/boss";
 const char* MUSHROOM = "assets/monsters/mushroom";
 const char* GOBLIN = "assets/monsters/darkWiz";
 const char* DARKWIZ = "assets/monsters/goblin";
 const char* PLAYER = "assets/player";
 const char* PLAYERSPELL = "assets/player/playerSpell1.png";
 const char* SKULL = "assets/skull.png";
 const char* HEALTHBAR = "assets/healthBar.png";
 const char* HEALTHFILL = "assets/healthFill.png";
 const char* MENUMUSIC = "sounds/menu.mp3";
 const char* BUTTONSOUND = "sounds/button.wav";
 const char* GAMEMUSIC = "sounds/game.mp3";
 const char* SKY = "assets/BackGround/sky.png";
 const char* DOWNLAYER = "assets/BackGround/downLayer.png";
 const  char* MIDDLELAYER = "assets/BackGround/middleLayer.png";
 const char* LIGHT = "assets/BackGround/light.png";
 const char* TOPLAYER = "assets/BackGround/topLayer.png";
 const char* BOSSARRIVALSOUND = "sounds/bossArrival.wav";
 const char* YOUWINSOUND = "sounds/youWin.wav";
 const char* YOULOSESOUND = "sounds/youLose.wav";
 const char* PLAYERSPELLSOUND = "sounds/lightning.wav";
 const char* BUTTONCORNER = "assets/buttonCorner.png";
 const char* BUTTONEDGE = "assets/buttonEdge.png";
 const char* BUTTONMIDDLE = "assets/buttonMiddle.png";
 const char* FONT = "assets/timesNewrRman.ttf";
 const char* PLAYERJUMPSOUND = "sounds/jump.wav";
 const char* HITSOUND = "sounds/hit.wav";
 const char* MEELEATTACKSOUND = "sounds/meeleAttack.wav";
 const char* SPELLSOUND = "sounds/spellFire.wav";
 const char* BOSSATTACKSOUND = "sounds/bossAttack.wav";

//enemy spawn locations
 int MONSTER_SPAWNX = SCREEN_WIDTH - 100;
 int MONSTER_SPAWNY = PLATFORM_HEIGHT - ((monsterSpriteOffsetY + monsterSpriteH) * monsterScale);
 int WORM_SPAWNY = PLATFORM_HEIGHT - ((wormSpriteOffsetY + wormSpriteH) * monsterScale) + 15;
 int CLOUD_SPAWNY = 50;
 int EYE_SPAWNX = -50;
 int EYE_SPAWNY = -50;
 int BOSS_SPAWNY = PLATFORM_HEIGHT - ((bossSpriteOffsetY + bossSpriteH) * monsterScale);
 int DARKWIZ_SPAWNY = PLATFORM_HEIGHT - ((darkWizSpriteOffsetY + darkWizSpriteH) * monsterScale);
 int PLAYER_SPAWNX = 100;
 int PLAYER_SPAWNY = PLATFORM_HEIGHT - playerSpriteOffsetY - playerSpriteH;