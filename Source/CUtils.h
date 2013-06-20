#ifndef UTILS_H
#define UTILS_H

#include "CGraphics.h"
#include "CCollisions.h"

#define uint unsigned int

/* GP2X button mapping */
enum MAP_KEY
{
	VK_UP         , // 0
	VK_UP_LEFT    , // 1
	VK_LEFT       , // 2
	VK_DOWN_LEFT  , // 3
	VK_DOWN       , // 4
	VK_DOWN_RIGHT , // 5
	VK_RIGHT      , // 6
	VK_UP_RIGHT   , // 7
	VK_START      , // 8
	VK_SELECT     , // 9
	VK_FL         , // 10
	VK_FR         , // 11
	VK_FA         , // 12
	VK_FB         , // 13
	VK_FX         , // 14
	VK_FY         , // 15
	VK_VOL_UP     , // 16
	VK_VOL_DOWN   , // 17
	VK_TAT          // 18
};

static const int CAANOO_JOYSTICK_MIN = -32768;
static const int CAANOO_JOYSTICK_MAX = 32767;

enum CaanooAxes {
CAANOO_AXIS_X = 0,
CAANOO_AXIS_Y = 1
};

enum CaanooButtons {
CAANOO_BUTTON_A = 0,
CAANOO_BUTTON_X = 1,
CAANOO_BUTTON_B = 2,
CAANOO_BUTTON_Y = 3,
CAANOO_BUTTON_L = 4,
CAANOO_BUTTON_R = 5,
CAANOO_BUTTON_HOME = 6,
CAANOO_BUTTON_HOLD = 7,
CAANOO_HELP_1 = 8,
CAANOO_HELP_2 = 9,
CAANOO_BUTTON_JOY = 10
};

/* The attributes of the screen*/
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
const int SCREEN_BPP = 16;


//
// Structures
//

struct Rect{

	public:
		int x, y;
		int width, height;
	public:
		Rect() : x(0), y(0), width(0), height(0) {}
		Rect(int X, int Y, int W, int H) : x(X), y(Y), width(W), height(H){}
		Rect percent(const float param) const { return Rect( (int)(x + (width - x)*(param/100.0)), (int)(y - (y - height)*(param/100.0)), (int)(width - (width - x)*(param/100.0)), (int)(height + (y - height)*(param/100.0)));}

};

struct Vector2{

	public:
		int x, y;
	public:
		Vector2() : x(0), y(0) {}
		Vector2(int X, int Y) : x(X), y(Y){}
		Vector2 operator+(const Vector2 &param) const { return Vector2( x + param.x, y + param.y);}
		Vector2 operator-(const Vector2 &param) const { return Vector2( x - param.x, y - param.y);}
		Vector2 operator*(const float param) const { return Vector2((int)(x * param), (int)(y * param));}
		Vector2 operator/(const float param) const { return Vector2((int)(x / param), (int)(y / param));}
		bool operator==(const Vector2 &param) const { return (x == param.x && y == param.y);}
		bool operator!=(const Vector2 &param) const { return (x != param.x && y != param.y);}
};

#endif //UTILS_H
