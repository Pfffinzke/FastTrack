#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
class Player
{
private:
	const float START_SPEED = 20;
	enum Steps {Left, Right};

	// Where is the player
	Vector2f m_Position;
	// Of course we will need a sprite
	Sprite m_Sprite;
	// And a texture
	// !!Watch this space!!
	Texture m_Texture;
	// What is the screen resolution
	Vector2f m_Resolution;
	// What size is the current arena
	IntRect m_Arena;
	// How big is each tile of the arena
	int m_TileSize;
	// Which directions is the player currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_MoveRight;
	bool rightstep;
	bool leftstep;
	bool moveOneStep;
	int cptStep;
	Steps CurrentStep;
	Steps PreviousStep;
	float m_Speed;
	// All our public functions will come next
public:
	Player();
	void spawn(IntRect arena, Vector2f resolution, int tileSize);
	// Call this at the end of every game
		void initPlayer(Vector2f Position);
	// Handle the player getting hit by a zombie
	FloatRect getPosition();
	// Where is the center of the player
	Vector2f getCenter();
	// Which angle is the player facing
	Sprite getSprite();
	// The next four functions move the player
	void moveLeft();
	void moveRight();
	// read step inputs
	void getRightFoot();
	void getLeftFoot();
	// Stop the player moving in a specific direction
	void stopLeft();
	void stopRight();
	// We will call this function once every frame
	void update(float elapsedTime);
	// Chose color of player
	void setColor(sf::Color Color);
	

};
