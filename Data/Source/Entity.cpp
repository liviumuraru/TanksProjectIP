#include "Entity.h"

sf::Vector2f Entity::getPos() const {
	return mSprite->getPosition();
}

void Entity::setPos(const sf::Vector2f& pos) {
	mSprite->setPosition(pos);
}

Entity::Entity(const sf::Vector2f& pos, sf::Sprite* sprite)
: mSprite(sprite){
	setPos(mSprite->getPosition());
}