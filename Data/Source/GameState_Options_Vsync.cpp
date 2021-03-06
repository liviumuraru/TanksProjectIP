#include "GameState_Options_Vsync.h"

GameState_Options_Vsync::GameState_Options_Vsync()
	: game(Game::get())
	, mSelector(game->mTextures.get(Texture::button_Selector), sf::Vector2f(20.0f, game->mWindow.getSize().y - 220.0f), 50.0f, mButtons)
{
	buildGUI();
	mSelector.mNumberOfButtons = mButtons.size();
	mSelector.mButtons = mButtons;
	mSelector.mSelectedButton = &mButtons[0];
	mSelector.mSelectedButton->getText().setFillColor(sf::Color::Red);
}

GameState_Options_Vsync::~GameState_Options_Vsync()
{

}

void GameState_Options_Vsync::buildGUI()
{
	VSyncButton activate(sf::Vector2f(75.0f, game->mWindow.getSize().y - 200.0f), "Activate Vertical Synchronization", 20, VSyncButton::Action::changeVSync, 1);
	VSyncButton deactivate(sf::Vector2f(75.0f, game->mWindow.getSize().y - 150.0f), "De-activate Vertical Synchronization", 20, VSyncButton::Action::changeVSync, 0);
	VSyncButton back(sf::Vector2f(75.0f, game->mWindow.getSize().y - 100.0f), "Back", 20, VSyncButton::Action::back, 0);

	mButtons.push_back(activate);
	mButtons.push_back(deactivate);
	mButtons.push_back(back);
}

void GameState_Options_Vsync::update(sf::Time deltaTime)
{
	handleInput();
}

void GameState_Options_Vsync::draw()
{
	game->mWindow.draw(game->mBackground);
	//game->mWindow.draw(mSelector.mSprite);
	for each (VSyncButton button in mButtons)
	{
		game->mWindow.draw(button.getText());
	}
}

void GameState_Options_Vsync::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_Options_Vsync::handleEvents()
{
	sf::Event eventToBeHandled;

	while (game->mWindow.pollEvent(eventToBeHandled))
	{
		switch (eventToBeHandled.type)
		{
			case sf::Event::Closed:
			{
				game->mWindow.close();
				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				switch (eventToBeHandled.mouseButton.button)
				{
					case sf::Mouse::Left:
					{
						if (mSelector.mSelectedButton->isSpriteSelected())
						{
							mSelector.mSelectedButton->triggerAction();
							sf::Clock timer;
							while (timer.getElapsedTime() < sf::seconds(0.15f))
							{

							}
						}

						break;
					}

				default:break;
				}

			}


			case sf::Event::KeyPressed:
			{
				switch (eventToBeHandled.key.code)
				{
					case sf::Keyboard::Return:
					{
						mSelector.mSelectedButton->triggerAction();
						break;
					}

					case sf::Keyboard::Down:
					{
						mSelector.mSelectedButton->getText().setFillColor(sf::Color::White);
						mSelector.move(Movement::down);
						mSelector.mSelectedButton->getText().setFillColor(sf::Color::Red);
						break;
					}

					case sf::Keyboard::Up:
					{
						mSelector.mSelectedButton->getText().setFillColor(sf::Color::White);
						mSelector.move(Movement::up);
						mSelector.mSelectedButton->getText().setFillColor(sf::Color::Red);
						break;
					}
				}
			}
		}
	}
}

void GameState_Options_Vsync::handleRealTimeInput()
{
	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		if (mButtons[i].getText().getFillColor() == sf::Color::White)
			if (mButtons[i].isSpriteSelected())
			{
				mSelector.mSelectedButton->getText().setFillColor(sf::Color::White);
				mButtons[i].getText().setFillColor(sf::Color::Red);
				mSelector.mSelectedButton = &mButtons[i];
			}
	}
}

void GameState_Options_Vsync::rePositionButtons(sf::Vector2u & currentPosition, sf::Vector2u & newPosition)
{
}
