#include "Player.h"
#include <iostream>
#include "TextureHolder.h"

Player::Player()
	: m_Speed(START_SPEED),
	m_Health(START_HEALTH),
	m_MaxHealth(START_HEALTH),
	m_Texture(),
	m_Sprite()
{
	// Associate a texture with the sprite
	// !!Watch this space!!
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/player.png"));
	// ***
	//m_Texture.loadFromFile("graphics/player.png");
	//m_Sprite.setTexture(m_Texture);
	// ***
	// Set the origin of the sprite to the center,
	// for smooth rotation
	m_Sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Place the player of te middel of the area
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	// Copy the details of the arena
	// to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	// Remember how big the tiles are in this arena ( only small one title)
	m_TileSize = tileSize;

	// Store the resolution for the future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

Time Player::getLastHitTime()
{
	return m_LastHit;
}

bool Player::hit(Time timehit)
{
	if (timehit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
	{
		m_LastHit = timehit;
		m_Health -= 10;
		return true;
	}
	else
	{
		return false;
	}
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

int Player::getHealth()
{
	return m_Health;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}
void Player::moveUp()
{
	m_UpPressed = true;
}
void Player::moveDown()
{
	m_DownPressed = true;
}
void Player::stopLeft()
{
	m_LeftPressed = false;
}
void Player::stopRight()
{
	m_RightPressed = false;
}
void Player::stopUp()
{
	m_UpPressed = false;
}
void Player::stopDown()
{
	m_DownPressed = false;
}

// Update //
void Player::update(float elapsedTime, Vector2i mousePostion)
{
	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}
	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}
	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);
	// keep the player in the arena
	if (m_Position.x > m_Arena.width - m_TileSize)
	{
		m_Position.x = m_Arena.width - m_TileSize;
	}
	if (m_Position.x < m_Arena.left + m_TileSize)
	{
		m_Position.x = m_Arena.left + m_TileSize;
	}
	if (m_Position.y > m_Arena.height - m_TileSize)
	{
		m_Position.y = m_Arena.height - m_TileSize;
	}
	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = m_Arena.top + m_TileSize;
	}

	// Calculate the angle the player is facing VAZNO Treba oBJASNOTI!!!
	float angle = (atan2(mousePostion.y - m_Resolution.y / 2,
		mousePostion.x - m_Resolution.x / 2) * 180) / 3.141;
	m_Sprite.setRotation(angle);
	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///
}

void Player::upgradeSpeed()
{
	//20% speed upgrade
	m_Speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
	// 20% max health upgrade
	m_MaxHealth += (START_HEALTH * .2);
}

void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;
	//But not beyond the maximum
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}