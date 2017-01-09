#include "GameState_Play.h"

GameState_Play::GameState_Play(std::string& mapObjectsPath, std::vector<Entity*>& entities)
	: game(Game::get())
	, mMapObjectsPath(mapObjectsPath)
{
	for each (Entity* entity in entities)
	{
		mEntities.push_back(entity);
	}
	buildGUI();
}

void GameState_Play::buildGUI()
{
	mMap = new Map(mMapObjectsPath, mEntities);
}

void GameState_Play::update(sf::Time deltaTime)
{
	mMap->update(deltaTime);
}

void GameState_Play::draw()
{
	mMap->draw(&(game->mWindow));
}

void GameState_Play::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_Play::handleEvents()
{

}


void GameState_Play::handleRealTimeInput()
{

}

void GameState_Play::rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition)
{
	//THIS IS USELESS SHIT, BUT I CAN'T REMOVE IT BCUZ I WOULD HAVE TO REMOVE A **LOT** OF LEFTOVER CODE...
}