#include "Bullet.h"

// The Constructor
Bullet::Bullet()
{
	// Making a size of bullet 2x2
	// Pravimo metak veličine 2x2 piksela
	m_BulletShape.setSize(sf::Vector2f(5, 5));
}

// start X and Y are position of a player
// target X and Y are position of a target
// startX i startY su pozicija igrača, targetX i targetY su pozicija mete
void Bullet::shoot(float startX, float startY, float targetX, float targetY)
{
	m_InFlight = true; // Bullet is now flying !!!
	m_Position.x = startX;
	m_Position.y = startY;

	// Calculate the gradient of the flight path
	// Izračunavanje nagiba putanje (vektorski pravac)
	// Trigometrija !!!
	float gradient = (startX - targetX) / (startY - targetY);

	// Any gradient less than 0 needs to be positive
	// Ako je nagib negativan, pretvaramo ga u pozitivan (radimo s pravcem kasnije)
	if (gradient < 0)
	{
		gradient *= -1;
	}

	// Calculate the ratio between x and y
	// Računamo koliko ide po Y a koliko po X da ukupna brzina bude ista
	float ratioXY = m_BulletSpeeds / (1 + gradient);

	// Set the "speed" horizontally and vertically
	// Postavljamo brzinu po X i Y osama
	m_BulletDistanceY = ratioXY;
	m_BulletDistanceX = ratioXY * gradient;

	// Point the bullet in the right direction
	// Ako meta levo/gore, menjamo smer brzine
	if (targetX < startX)
	{
		m_BulletDistanceX *= -1;
	}
	if (targetY < startY)
	{
		m_BulletDistanceY *= -1;
	}

	// Set a max range of 1000 pixels ( Domet metka )
	// Bullet will disappear after traveling 1000px in any direction
	float range = 1000;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;

	// Position the bullet ready to be drawn
	// Postavljamo grafički oblik metka na trenutnu poziciju
	m_BulletShape.setPosition(m_Position);
}

// Stop the bullet
// Zaustavi metak – više nije u letu
void Bullet::stop()
{
	m_InFlight = false;
}

// Return if bullet is flying
// Da li je metak trenutno u letu (true ili false)
bool Bullet::isInFlight()
{
	return m_InFlight;
}

// Get the position (bounding box) of the bullet
// Vraća poziciju metka kao pravougaonik – koristi se za koliziju
FloatRect Bullet::getPosition()
{
	return m_BulletShape.getGlobalBounds();
}

// Get the shape of the bullet for drawing
// Vraća oblik metka (pravougaonik) da se nacrta na ekranu
RectangleShape Bullet::getShape()
{
	return m_BulletShape;
}

void Bullet::update(float elapsedTime)
{
	// Add velocity to position — real-time motion
	// Dodaj brzinu na poziciju — kretanje kroz vreme
	m_Position.x += m_BulletDistanceX * elapsedTime;
	m_Position.y += m_BulletDistanceY * elapsedTime;

	// Move the bullet
	// Pomera metak !!!!!!!!
	m_BulletShape.setPosition(m_Position);

	// Has the bullet gone out of range?
	// da li je metak izaso iz "dozvoljene zone"
	if (m_Position.x < m_MinX ||
		m_Position.x > m_MaxX ||
		m_Position.y < m_MinY ||
		m_Position.y > m_MaxY
		)
	{
		m_InFlight = false;
	}
}

