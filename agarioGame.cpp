#pragma once
#include "pch.h"
#include "agarioGame.h"
#include "boxsize.h"
#include "playerOrb.h"
#include "gamecamera.h"
#include "agarioGameMap.h"
#include "gameEngine.h"
#include "box.h"
#include <string>
#include <Windows.h>

void agarioGame::Game()
{
	boxsize cameraSize(0,0,60,60);
	int framebuffersize = cameraSize.characters();
	char* framebuffer = (char*)alloca(sizeof(char) * framebuffersize);
	box gamecamerab(cameraSize, framebuffer, framebuffersize, false);
	gamecamera* cam = (gamecamera*)alloca(sizeof(gamecamera));
	CHAR_INFO* charinfoframebuffer = (CHAR_INFO*)alloca(sizeof(CHAR_INFO) * framebuffersize);
	playerOrb* players = (playerOrb*)alloca(sizeof(playerOrb) * 2);
	*cam = gamecamera(gamecamerab, players[0], *(agarioGameMap*)(void*)nullptr);
	agarioGameMap map(100);
	agarioGame game(cam, charinfoframebuffer, players, 2, &map);
	game.Start();
}

agarioGame::agarioGame(gamecamera* gamecamerad, CHAR_INFO* fb, playerOrb* players, int numberOfPlayers, agarioGameMap* map) : 
gameEngine(gamecamerad->screen, GetConsoleWindow(), fb, false)/*,
gameMap(100),
gameCamera(*gamecamera, gamePlayers[0], gameMap)*/
{
	SetTargetTicksPerSecond(20);
	this->gameCamera = gamecamerad;
	this->gamePlayers = players;
	this->numberOfPlayers = numberOfPlayers;
	this->gameMap = map;
	consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleIn = GetStdHandle(STD_INPUT_HANDLE);
	ConstructConsole(gamecamerad->screen->sizeX, gamecamerad->screen->sizeY, 8, 8, (wchar_t*)L"Raster");
	//SetConsoleActiveScreenBuffer(consoleOut = CreateBuffer());
	doClear = true;
}

bool agarioGame::OnUpdate(float elapsedtime)
{
	if (keys[VK_ESCAPE].bReleased) {
		Close();
	}
	/*if (mouse[0].bReleased) {
		mousePos.SetCalcPos(getMouseX(), getMouseY());
	}
	else {
		mousePos.UpdatePos(getMouseX(), getMouseY());
	}*/
	mousePos.UpdatePos(getMouseX(), getMouseY());
	gamePlayers[0].degChangeAngle(mousePos.Degrees());
	gamePlayers[0].update(0.200f);
	//gamePlayers[1].update(0.020f);
	return false;
}

void agarioGame::OnClose()
{
	
}

bool agarioGame::OnCreate()
{
	gamePlayers[0] = playerOrb(*gameCamera, *gameMap, *this);
	gamePlayers[1] = playerOrb(*gameCamera, *gameMap, *this);
	*gameMap = agarioGameMap(100);
	*gameCamera = gamecamera(*gameCamera->screen, gamePlayers[0], *gameMap);
	gameCamera->updateView();
	mousePos.SetCalcPos(gameCamera->screen->getscaleX(0.5f, 1), gameCamera->screen->getscaleY(0.5f, 1));
	return false;
}

bool agarioGame::OnFrame()
{
	gameCamera->screen->clear();
	gameCamera->updateView();
	gamePlayers[0].drawToCamera();
	//gamePlayers[1].drawToCamera();
	//Position
	gameCamera->screen->set((char*)&"Position: ", 11, 0, 0);
	gameCamera->screen->set(gamePlayers[0].getPositionX(), 6, 0, 1);
	gameCamera->screen->set(gamePlayers[0].getPositionY(), 6, 6, 1);
	gameCamera->screen->set((char*)&"Camera:   ", 11, 0, 2);
	gameCamera->screen->set(gameCamera->minX(), 6, 0, 3);
	gameCamera->screen->set(gameCamera->minY(), 6, 6, 3);

	return true;
}


agarioGame::~agarioGame()
{
}
