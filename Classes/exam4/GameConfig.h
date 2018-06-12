#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

#define PTM_RATIO 32  // 定义32像素代表1米
#define BALL_SCALE 0.7
#define BALL_RADIO 32*BALL_SCALE
#define LEFT_BALL_X 560
#define LEFT_BALL_Y 320
#define BALL_ANGEL CC_DEGREES_TO_RADIANS(30.0f)

static const int SLIDER_BG_TAG = 1000;
static const int SLIDER_TAG = 1001;
static const int DASH_LINE_TAG = 1002;
static const int MAIN_BILLIARDS_TAG = 1003;
static const int AIM_ICON_TAG = 1004;
static const int AIM_GAN_TAG = 1005;

static const int MAX_SPEED = 2600;

static const std::string ball[15] = {
	"exam4/Ball/0.png",
	"exam4/Ball/3.png",
	"exam4/Ball/1.png",
	"exam4/Ball/10.png",
	"exam4/Ball/6.png",
	"exam4/Ball/1.png",
	"exam4/Ball/5.png",
	"exam4/Ball/2.png",
	"exam4/Ball/5.png",
	"exam4/Ball/2.png",
	"exam4/Ball/9.png",  //黑球
	"exam4/Ball/0.png",
	"exam4/Ball/3.png",
	"exam4/Ball/10.png",
	"exam4/Ball/6.png"
};

/*5球*/
/*
static const Vec2 ballPos[] = {
	Vec2(300,500),
	Vec2(500,300),
	Vec2(100,500),
	Vec2(600,100),
	Vec2(800,500)
};*/
static const char* ballName[15]
{
	"ball1",
	"ball2",
	"ball3",
	"ball4",
	"ball5",
	"ball6",
	"ball7",
	"ball8",
	"ball9",
	"ball10",
	"ball11",
	"ball12",
	"ball13",
	"ball14",
	"ball15"
};

//场上16个球以及两个记分板的label所设置的tag
static const int lableTag[18] = {
	1010,1011,1012,1013,1014,1015,1016,1017,1018,1019,1020,1021,1022,1023,1024,1025,1026,1027
};

//15个球的位置
static const Vec2 ballPos[] = {
	Vec2(LEFT_BALL_X + 8 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y + 8 * (BALL_RADIO + 1)*sin(BALL_ANGEL)),
	Vec2(LEFT_BALL_X + 8 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y + 8 * (BALL_RADIO + 1)*sin(BALL_ANGEL) - 2 * (BALL_RADIO + 1)),
	Vec2(LEFT_BALL_X + 8 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y),
	Vec2(LEFT_BALL_X + 8 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y - 8 * (BALL_RADIO + 1)*sin(BALL_ANGEL) + 2 * (BALL_RADIO + 1)),
	Vec2(LEFT_BALL_X + 8 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y - 8 * (BALL_RADIO + 1)*sin(BALL_ANGEL)),
	Vec2(LEFT_BALL_X + 6 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y + 6 * (BALL_RADIO + 1)*sin(BALL_ANGEL)),
	Vec2(LEFT_BALL_X + 6 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y + 6 * (BALL_RADIO + 1)*sin(BALL_ANGEL) - 2 * (BALL_RADIO + 1)),
	Vec2(LEFT_BALL_X + 6 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y - 6 * (BALL_RADIO + 1)*sin(BALL_ANGEL) + 2 * (BALL_RADIO + 1)),
	Vec2(LEFT_BALL_X + 6 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y - 6 * (BALL_RADIO + 1)*sin(BALL_ANGEL)),
	Vec2(LEFT_BALL_X + 4 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y + 4 * (BALL_RADIO + 1)*sin(BALL_ANGEL)),
	Vec2(LEFT_BALL_X + 4 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y),
	Vec2(LEFT_BALL_X + 4 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y - 4 * (BALL_RADIO + 1)*sin(BALL_ANGEL)),
	Vec2(LEFT_BALL_X + 2 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y + 2 * (BALL_RADIO + 1)*sin(BALL_ANGEL)),
	Vec2(LEFT_BALL_X + 2 * (BALL_RADIO + 1)*cos(BALL_ANGEL),LEFT_BALL_Y - 2 * (BALL_RADIO + 1)*sin(BALL_ANGEL)),
	Vec2(LEFT_BALL_X,LEFT_BALL_Y),
};

#endif