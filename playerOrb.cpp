#pragma once
#include "pch.h"
#include "playerOrb.h"
#include "agarioGameMap.h"
#include "box.h"
#include "boxsize.h"
#include "gamecamera.h"
#include "rigidbody.h"
//#include "agarioGame.h"
class agarioGame;

playerOrb::playerOrb(gamecamera& gCamera, agarioGameMap& gameMap, agarioGame& game)
{
	this->gameCamera = &gCamera;
	this->gameMap = &gameMap;
	this->game = &game;
	positionX = 0.0f;
	positionY = 0.0f;	
	score = 10.0f;
	this->angle = 0.0f;
}

playerOrb::playerOrb()
{
}

playerOrb::~playerOrb()
{
}

float playerOrb::getRadius(float scale)
{
	return (getDiameter(scale) / 2);
}

float playerOrb::getRadius()
{
	return (getDiameter() / 2);
}

float playerOrb::getDiameter(float scale)
{
	return (score / PI) / scale;
}

float playerOrb::getDiameter()
{
	return (score / PI);
}

float playerOrb::centerX()
{
	return positionX + getRadius();
}

float playerOrb::centerY()
{
	return positionY + getRadius();
}

float playerOrb::centerX(float scale)
{
	return centerX() / scale;
}

float playerOrb::centerY(float scale)
{
	return centerY() / scale;
}

float playerOrb::maxX()
{
	return positionX + getDiameter();
}

float playerOrb::maxY()
{
	return positionY + getDiameter();
}

float playerOrb::minX()
{
	return positionX;
}

float playerOrb::minY()
{
	return positionY;
}

float playerOrb::getDrawScale()
{
	float minScale = gameCamera->radius();
	return minScale / score;
}

void playerOrb::setCenter(float x, float y)
{
	if (inBounds(x, y)) {
		positionX = x - getRadius();
		positionY = y - getRadius();
	}
}

void playerOrb::setCenter(int x, int y)
{
	if (inBounds(x, y)) {
		positionX = x - getRadius();
		positionY = y - getRadius();
	}
}

void playerOrb::setCenterX(int x)
{
	if (inBounds(x, centerY())) {
		positionX = x - getRadius();
	}
}

void playerOrb::setCenterX(float x)
{
	if (inBounds(x, centerY())) {
		positionX = x - getRadius();
	}
}

void playerOrb::setCenterY(int y)
{
	if (inBounds(centerX(), y)) {
		positionY = y - getRadius();
	}
}

void playerOrb::setCenterY(float y)
{
	if (inBounds(centerX(), y)) {
		positionY = y - getRadius();
	}
}

void playerOrb::update(float elapsedTime)
{
	float centerXf = centerX();
	float centerYf = centerY();
	float nextX = (centerXf + elapsedTime * cos(rigidbody::degtorad(angle)));
	float nextY = (centerYf + elapsedTime * sin(rigidbody::degtorad(angle)));

	if (inBounds(nextX, nextY)) {
		setCenterX(nextX);
		setCenterY(nextY);
	}
	else {
		if (inBounds(nextX, centerY())) {
			setCenterX(nextX);
		}
		else {
			setCenterX(getRadius());
		}

		if (inBounds(centerX(), nextY)) {
			setCenterY(nextY);
		}
		else {
			setCenterY(getRadius());
		}
	}

}

bool playerOrb::inBounds(float centerX, float centerY)
{
	float minX = centerX - getRadius();
	float minY = centerY - getRadius();
	float maxX = getRadius() + centerX;
	float maxY = getRadius() + centerY;

	return (
		minX >= 0.0f &&
		minY >= 0.0f &&
		maxX >= 0.0f &&
		maxY >= 0.0f &&
		minX < gameMap->getMapSize() &&
		minY < gameMap->getMapSize() &&
		maxX < gameMap->getMapSize() &&
		maxY < gameMap->getMapSize());
}

bool playerOrb::needToDraw()
{
	return true;
}

void playerOrb::drawToCamera()
{
	drawTo(*gameCamera);
}

void playerOrb::drawTo(gamecamera & gameCamera)
{
	float scale = gameCamera.scale();
	int radius = getRadius(scale);
	float diameter = getDiameter(scale);
	int fCenterX = minX(), fCenterY = minY();
	int boundsX = gameCamera.screen->sizeX, boundsY = gameCamera.screen->sizeY;
	char* fB = gameCamera.framebuffer();

	//Draw Orb

	float step = 0.03f;
	int x, y;
	for (float theta = 0.0; theta < DOUBLE_PI; theta += step) {
		x = ((fCenterX + radius * cos(theta))) + gameCamera.centerX();
		y = ((fCenterY - radius * sin(theta))) + gameCamera.centerY();
		if (x < boundsX && y < boundsY && y >= 0 && x >= 0) {
			fB[gameCamera.get(x, y)] = '#';
		}
	}

	//Draw Velocity

	for (float cradius = 0.0f; cradius < radius; cradius += step) {
		x = (fCenterX + cradius * cos(rigidbody::degtorad(angle))) + gameCamera.centerX();
		y = (fCenterY + cradius * sin(rigidbody::degtorad(angle))) + gameCamera.centerY();
		if (x < boundsX && y < boundsY && y >= 0 && x >= 0) {
			fB[gameCamera.get(x, y)] = '*';
		}
	}
}
