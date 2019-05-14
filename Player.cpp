#include "pch.h"
#include "Player.h"
#include "TextureHolder.h"

Player::Player()
{
	m_Speed = START_SPEED;


	// Associate a texture with the sprite
	// !!Watch this space!!
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/player.png"));

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Place the player in the middle of the arena
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 4;

	// Copy the details of the arena to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	// Remember how big the tiles are in this arena
	m_TileSize = tileSize;
	rightstep = true;
	leftstep = false;

	// Strore the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;

}
void Player::initPlayer(Vector2f Position)
{
	rightstep = true;
	leftstep = false;
	moveOneStep = false;
	cptStep = 0;
	m_Position.x = Position.x;
	m_Position.y = Position.y;
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

void Player::getRightFoot()
{	m_RightPressed = true;
	CurrentStep = Right;
	rightstep = true;
	
	if (CurrentStep != PreviousStep) {
		// previous step is diferent thant the current step, move player
		moveOneStep = true;
	}
}

void Player::getLeftFoot()
{   m_LeftPressed = true;
	CurrentStep = Left;
	leftstep = true;

	if (CurrentStep != PreviousStep) {
		// previous step is diferent thant the current step, move player
		moveOneStep = true;
		}	
}

Sprite Player::getSprite()
{
	return m_Sprite;
}



void Player::moveRight()
{
	
	if (moveOneStep) {
		
		m_MoveRight = true;
		moveOneStep = false;
				
	}
	else {
		m_MoveRight = false;
	}
	
}


void Player::stopLeft()
{
	 if (leftstep){
	 	m_LeftPressed = false;
		PreviousStep = Left;
		leftstep =false;
		}
}

void Player::stopRight()
{
	if (rightstep){
		m_RightPressed = false;
		PreviousStep = Right;
		rightstep =false;
		}
}


void Player::update(float elapsedTime, Vector2i mousePosition)
{

	
	if (m_MoveRight)
	{
		m_Position.x += m_Speed * elapsedTime;
	}
	printf("Player position : %f \n", m_Position.x);
	
	m_Sprite.setPosition(m_Position);



	// Keep the player in the arena
	if (m_Position.x > m_Arena.width - m_TileSize)
	{
	//	m_Position.x = m_Arena.width - m_TileSize;
	}

	if (m_Position.x < m_Arena.left + m_TileSize)
	{
	//	m_Position.x = m_Arena.left + m_TileSize;
	}

	if (m_Position.y > m_Arena.height - m_TileSize)
	{
		m_Position.y = m_Arena.height - m_TileSize;
	}

	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = m_Arena.top + m_TileSize;
	}

	
}




