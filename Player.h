﻿#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	// Where is the player
	Vector2f m_Position;

	// The sprite
	Sprite m_Sprite;

	// And a texture
	// !!!! Watch this space � Changes here soon!!
	Texture m_Texture;

	//what is the screen resolution
	Vector2f m_Resolution;

	//What size is the current arena
	IntRect m_Arena;

	//How big us each title of the arena
	int m_TileSize;

	// Which direction(s) the pleyer is moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	// How much health has the player got?
	int m_Health;

	// What is the max' health the player can have
	int m_MaxHealth;

	// When was the player last hit
	Time m_LastHit;

	// Speed in pixels per second
	float m_Speed;

	// All our public functions next
public:
	Player();
	void spawn(IntRect arena, Vector2f resolution, int titleSize);

	// Call this at the end of every game
	void resetPlayerStats();

	//Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	//How long ago was the player last hit.
	Time getLastHitTime();

	//Where is the player
	FloatRect getPosition();

	// Where is the center of the player
	Vector2f getCenter();

	//Where is the center of the player facing
	float getRotation();

	//Send a copy of the sprite to the main function;
	Sprite getSprite();

	// The next four functions move the player
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	// Stop the player moving in a specific direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	// We will call this function once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	// Give the player a speed boost
	void upgradeSpeed();

	//give the playerr some health
	void upgradeHealth();

	void increaseHealthLevel(int amount);

	//How much health has player currently got?
	int getHealth();

};