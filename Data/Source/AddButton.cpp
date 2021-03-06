#include "AddButton.h"
#include "RemoveButton.h"
#include "Team.h"

AddButton::AddButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action)
	: TextButton(initialPosition, text, characterSize, TextButton::Action::none)
	, mAction(action)
{

}

AddButton::AddButton(sf::Vector2f initialPosition, Action action)
	: TextButton(initialPosition, "+", 20, TextButton::Action::none)
	, mAction(action)
{

}

void AddButton::getTextureIDs(const std::string& textureString, Texture& baseTexture, Texture& topTexture)
{
	if (textureString == "tank1") {
		baseTexture = Texture::tank1_body;
		topTexture = Texture::tank1_gun;
	}
	else if (textureString == "tank1b") {
		baseTexture = Texture::tank1b_body;
		topTexture = Texture::tank1b_gun;
	}
	else if (textureString == "tank2") {
		baseTexture = Texture::tank2_body;
		topTexture = Texture::tank2_gun;
	}
	else if (textureString == "tank2b") {
		baseTexture = Texture::tank2b_body;
		topTexture = Texture::tank2b_gun;
	}
	else if (textureString == "tank3") {
		baseTexture = Texture::tank3_body;
		topTexture = Texture::tank3_gun;
	}
	else if (textureString == "tank3b") {
		baseTexture = Texture::tank3b_body;
		topTexture = Texture::tank3b_gun;
	}
	else if (textureString == "tank3c") {
		baseTexture = Texture::tank3c_body;
		topTexture = Texture::tank3c_gun;
	}
	else if (textureString == "tank3d") {
		baseTexture = Texture::tank3d_body;
		topTexture = Texture::tank3d_gun;
	}
	else
		throw std::runtime_error("Map->getTankTextureIds: The specified texture doesn't exist");
}

void AddButton::triggerAction(team& team)
{
	switch (mAction)
	{
		case Action::addPlayer1:
		{
			if (team.numberOfMembers < 18)
			{
				insertPlayerOne("tank1", team.spawnPosition, new sf::Vector2f(100.0f, 100.0f), 100.0f, 15.0f, team, team.mAddPosition);
				//team.spawnPosition->x += 50.0f;
			}
			break;
		}

		case Action::addPlayer2:
		{
			if (team.numberOfMembers < 18)
			{
				insertPlayerTwo("tank1", team.spawnPosition, new sf::Vector2f(100.0f, 100.0f), 100.0f, 15.0f, team, team.mAddPosition);
				//team.spawnPosition->x += 50.0f;
			}
			break;
		}

		case Action::addAI_easy:
		{
			if (team.numberOfMembers < 18)
			{
				insertAI("easy", "tank2", team.spawnPosition, new sf::Vector2f(60.0f, 60.0f), 200.0f, 17.0f, team, team.mAddPosition);
				//team.spawnPosition->x += 50.0f;
			}
			break;
		}

		case Action::addAI_medium:
		{
			if (team.numberOfMembers < 18)
			{
				insertAI("medium", "tank2", team.spawnPosition, new sf::Vector2f(80.0f, 80.0f), 250.0f, 25.0f, team, team.mAddPosition);
				//team.spawnPosition->x += 50.0f;
			}
			break;
		}

		case Action::addAI_hard:
		{
			if (team.numberOfMembers < 18)
			{
				insertAI("hard", "tank2", team.spawnPosition, new sf::Vector2f(100.0f, 100.0f), 350.0f, 30.0f, team, team.mAddPosition);
				//team.spawnPosition->x += 50.0f;
			}
			break;
		}



		default:break;
	}
}

void AddButton::insertPlayerOne(const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage, team& team, sf::Vector2f buttonPosition)
{
	std::vector<sf::Keyboard::Key> keys;
	keys.resize(20);

	keys[(int)Tank::Command::DOWN] = sf::Keyboard::S;
	keys[(int)Tank::Command::UP] = sf::Keyboard::W;
	keys[(int)Tank::Command::LEFT] = sf::Keyboard::A;
	keys[(int)Tank::Command::RIGHT] = sf::Keyboard::D;

	keys[(int)Tank::Command::ROT_LEFT] = sf::Keyboard::Q;
	keys[(int)Tank::Command::ROT_RIGHT] = sf::Keyboard::E;

	keys[(int)Tank::Command::SHOOT] = sf::Keyboard::Space;

	Texture baseTexture, topTexture;
	getTextureIDs(team.player1TankData.mTextureIdentifier, baseTexture, topTexture);
	team.numberOfMembers++;

	

	if (team.teamNumber == 1)
	{
		team.mTeamMembers.push_back(teamRecord(new Player(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
			new sf::Sprite(Game::get()->mTextures.get(topTexture)),
			position,
			new sf::Vector2f(team.player1TankData.mSpeed, team.player1TankData.mSpeed),
			team.player1TankData.mHealth,
			team.player1TankData.mDamage,
			keys,
			team.teamNumber),
			new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
			sf::Text("Player 1", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
			team.numberOfMembers - 1));
	}
	else
	{
		team.mTeamMembers.push_back(teamRecord(new Player(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
			new sf::Sprite(Game::get()->mTextures.get(topTexture)),
			position,
			new sf::Vector2f(team.player1TankData.mSpeed, team.player1TankData.mSpeed),
			team.player1TankData.mHealth,
			team.player1TankData.mDamage,
			keys,
			team.teamNumber),
			new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
			sf::Text("Player 1", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
			team.numberOfMembers - 1));
	}
	
		team.mTeamMembers.back().mRemoveButton->getText().setFillColor(sf::Color(110, 28, 28));
		team.mTeamMembers.back().mText.setFillColor(sf::Color(110, 28, 28));
	
	
		team.mAddPosition.y += 30.0f;
}

void AddButton::insertPlayerTwo(const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage, team& team, sf::Vector2f buttonPosition)
{
	std::vector<sf::Keyboard::Key> keys;
	keys.resize(20);

	keys[(int)Tank::Command::DOWN] = sf::Keyboard::Numpad5;
	keys[(int)Tank::Command::UP] = sf::Keyboard::Numpad8;
	keys[(int)Tank::Command::LEFT] = sf::Keyboard::Numpad4;
	keys[(int)Tank::Command::RIGHT] = sf::Keyboard::Numpad6;

	keys[(int)Tank::Command::ROT_LEFT] = sf::Keyboard::Numpad7;
	keys[(int)Tank::Command::ROT_RIGHT] = sf::Keyboard::Numpad9;

	keys[(int)Tank::Command::SHOOT] = sf::Keyboard::P;

	Texture baseTexture, topTexture;
	getTextureIDs(team.player2TankData.mTextureIdentifier, baseTexture, topTexture);
	team.numberOfMembers++;

	

	if (team.teamNumber == 1)
	{
		team.mTeamMembers.push_back(teamRecord(new Player(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
			new sf::Sprite(Game::get()->mTextures.get(topTexture)),
			position,
			new sf::Vector2f(team.player2TankData.mSpeed, team.player2TankData.mSpeed),
			team.player2TankData.mHealth,
			team.player2TankData.mDamage,
			keys,
			team.teamNumber),
			new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
			sf::Text("Player 2", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
			team.numberOfMembers - 1));
	}
	else
	{
		team.mTeamMembers.push_back(teamRecord(new Player(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
			new sf::Sprite(Game::get()->mTextures.get(topTexture)),
			position,
			new sf::Vector2f(team.player2TankData.mSpeed, team.player2TankData.mSpeed),
			team.player2TankData.mHealth,
			team.player2TankData.mDamage,
			keys,
			team.teamNumber),
			new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
			sf::Text("Player 2", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
			team.numberOfMembers - 1));
	}

		team.mAddPosition.y += 30.0f;

	
		team.mTeamMembers.back().mRemoveButton->getText().setFillColor(sf::Color(110, 28, 28));
		team.mTeamMembers.back().mText.setFillColor(sf::Color(110, 28, 28));
}

void AddButton::insertAI(const std::string& difficulty, const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage, team& team, sf::Vector2f buttonPosition)
{
	Texture baseTexture, topTexture;
	getTextureIDs(tankType, baseTexture, topTexture);
	team.numberOfMembers++;

	if (difficulty == "easy") {
		

		team.mAddPosition.y += 30.0f;

		if (team.teamNumber == 1)
		{
			team.mTeamMembers.push_back(teamRecord(new AI_Easy(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
				new sf::Sprite(Game::get()->mTextures.get(topTexture)),
				position,
				velocity,
				health,
				damage,
				team.teamNumber),
				new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
				sf::Text("AI(easy)", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
				team.numberOfMembers - 1));

			team.mTeamMembers.back().mRemoveButton->getText().setFillColor(sf::Color(0, 0, 153));
			team.mTeamMembers.back().mText.setFillColor(sf::Color(0, 0, 153));
		}
		else if (team.teamNumber == 2)
		{
			team.mTeamMembers.push_back(teamRecord(new AI_Easy(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
				new sf::Sprite(Game::get()->mTextures.get(topTexture)),
				position,
				velocity,
				health,
				damage,
				team.teamNumber),
				new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
				sf::Text("AI(easy)", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
				team.numberOfMembers - 1));

			team.mTeamMembers.back().mRemoveButton->getText().setFillColor(sf::Color(0, 102, 51));
			team.mTeamMembers.back().mText.setFillColor(sf::Color(0, 102, 51));
		}
	}
	else if (difficulty == "medium") {
		team.mAddPosition.y += 30.0f;

		if (team.teamNumber == 1)
		{
			team.mTeamMembers.push_back(teamRecord(new AI_Medium(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
				new sf::Sprite(Game::get()->mTextures.get(topTexture)),
				position,
				velocity,
				health,
				damage,
				team.teamNumber),
				new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
				sf::Text("AI(medium)", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
				team.numberOfMembers - 1));


			team.mTeamMembers.back().mRemoveButton->getText().setFillColor(sf::Color(0, 0, 153));
			team.mTeamMembers.back().mText.setFillColor(sf::Color(0, 0, 153));
		}
		else if (team.teamNumber == 2)
		{

			team.mTeamMembers.push_back(teamRecord(new AI_Medium(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
				new sf::Sprite(Game::get()->mTextures.get(topTexture)),
				position,
				velocity,
				health,
				damage,
				team.teamNumber),
				new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
				sf::Text("AI(medium)", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
				team.numberOfMembers - 1));
			team.mTeamMembers.back().mRemoveButton->getText().setFillColor(sf::Color(0, 102, 51));
			team.mTeamMembers.back().mText.setFillColor(sf::Color(0, 102, 51));
		}
	}
	else if (difficulty == "hard") {
		

		team.mAddPosition.y += 30.0f;

		if (team.teamNumber == 1)
		{
			team.mTeamMembers.push_back(teamRecord(new AI_Hard(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
				new sf::Sprite(Game::get()->mTextures.get(topTexture)),
				position,
				velocity,
				health,
				damage,
				team.teamNumber),
				new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
				sf::Text("AI(hard)", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
				team.numberOfMembers - 1));

			team.mTeamMembers.back().mRemoveButton->getText().setFillColor(sf::Color(0, 0, 153));
			team.mTeamMembers.back().mText.setFillColor(sf::Color(0, 0, 153));
		}
		else if (team.teamNumber == 2)
		{
			team.mTeamMembers.push_back(teamRecord(new AI_Hard(new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
				new sf::Sprite(Game::get()->mTextures.get(topTexture)),
				position,
				velocity,
				health,
				damage,
				team.teamNumber),
				new RemoveButton(buttonPosition + sf::Vector2f(250.0f, 0.0f), "X", 20, RemoveButton::Action::remove),
				sf::Text("AI(hard)", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20),
				team.numberOfMembers - 1));

			team.mTeamMembers.back().mRemoveButton->getText().setFillColor(sf::Color(0, 102, 51));
			team.mTeamMembers.back().mText.setFillColor(sf::Color(0, 102, 51));
		}
	}
}