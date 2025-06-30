#include "Player.h"

Player::Player()
	: m_Speed(START_SPEED), 
	m_Health(START_HEALTH), 
	m_MaxHealth(START_HEALTH), 
	m_Texture(), 
	m_Sprite()
{
	// Associate a texture with the sprite
	// !!Watch this space!!
	m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setTexture(m_Texture);

	// Set the origin of the sprite to the center,
	// for smooth rotation
	m_Sprite.setOrigin(25, 25);
}