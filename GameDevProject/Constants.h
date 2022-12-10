#pragma once

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PLATFORM_HEIGHT = 380;

const int BOSS_ARRIVAL_SCORE = 10;
const int bossWarningTimer = 160;

//Frame rate
const int FPS = 60;

//Time between each frame
const int frameDelay = 1000 / FPS;

//friction in game
const float friction = 0.95f;

//value of pi
const double pi = 3.14159265358979323846;

//player constants
const int totalSpellCount = 10;
const int totalCastingCooldown = 40;
const int totalSpellReloadTime = 120;

//Game Object state constants
const int IDLE = 0;
const int RUNNING = 1;
const int ATTACKING = 2;
const int HIT = 3;
const int DEATH = 4;

//Sprite change time
const int totalSpriteTime = 5;
const int totalSpellSpriteTime = 10;

//delete after death time
const int totalPlayerDeathTime = 120;
const int totalEnemyDeathTime = 120;
const int totalProjectileDeathTime = 0;

//attck constants
const int totalAttackTime = 120;
const int totalEnemyAttackTime = 200;

//player jump velocity
const int jumpVel = -25;

//the offset of player's sprites actual location
const int playerSpriteOffsetX = 85;
const int playerSpriteOffsetY = 50;
const int playerSpriteW = 65;
const int playerSpriteH = 90;

//the offset of monsters' sprites actual location
const int monsterSpriteOffsetX = 55;
const int monsterSpriteOffsetY = 50;
const int monsterSpriteW = 35;
const int monsterSpriteH = 50;

//the offset of DarkWiz sprites actual location
const int darkWizSpriteOffsetX = 100;
const int darkWizSpriteOffsetY = 100;
const int darkWizSpriteW = 55;
const int darkWizSpriteH = 65;

//the offset of worm sprites actual location
const int wormSpriteOffsetX = 15;
const int wormSpriteOffsetY = 15;
const int wormSpriteW = 60;
const int wormSpriteH = 50;

//the offset of boss sprites actual location
const int bossSpriteOffsetX = 55;
const int bossSpriteOffsetY = 60;
const int bossSpriteW = 50;
const int bossSpriteH = 60;

//boss constants
const int bossAttackTime = 1000;

//skeleton guard duration
const int totalGuardDuration = 120;

//player movement limts
const int playerLimit = 150;

//background image dimensions
const int backgroundWidth = 1137;