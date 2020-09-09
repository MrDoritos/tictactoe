#pragma once
//#include "gamecamera.h"
//#include "agarioGameMap.h"
//#include "agarioGame.h"
#include "box.h"
#include "boxsize.h"
//#include "agarioGame.h"
class agarioGame;
class gamecamera;
class agarioGameMap;
class playerOrb
{
public:
	playerOrb(gamecamera& gamecamera, agarioGameMap& gameMap, agarioGame& game);
	playerOrb();
	~playerOrb();
	float getScore() { return score; }
	float getPositionX() { return positionX; }
	float getPositionY() { return positionY; }
	//1.0f to return the normal radius, no intent to draw
	float getRadius(float scale);
	float getRadius();
	//1.0f to return the normal diameter, no intent to draw
	float getDiameter(float scale);
	float getDiameter();
	float centerX();
	float centerY();
	float centerX(float scale);
	float centerY(float scale);
	float maxX();
	float maxY();
	float minX();
	float minY();
	float getDrawScale();
	void setCenter(float x, float y);
	void setCenter(int x, int y);
	void setCenterX(int x);
	void setCenterX(float x);
	void setCenterY(int y);
	void setCenterY(float y);
	void update(float elapsedTime);
	void degChangeAngle(float degrees) {
		this->angle = degrees;
	}
	void updateAngle(float degrees);
	bool inBounds(float centerX, float centerY);
	bool needToDraw();
	void drawToCamera();
	void drawTo(gamecamera& gameCamera);
	
protected:
	float positionX;
	float positionY;
	float score;
	float angle;

	gamecamera* gameCamera;
	agarioGameMap* gameMap;
	agarioGame* game;
};

