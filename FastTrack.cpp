#include "pch.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include "FastTrack.h"
#include "Player.h"
#include "TextureHolder.h"


using namespace sf;

int main()
{
	// Here is the instance of TextureHolder
	TextureHolder holder;

	// The game will always be in one of four states
	enum class State { PAUSED, GAME_OVER, PLAYING };
	// Start with the GAME_OVER state
	State state = State::GAME_OVER;


	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = 800;
	resolution.y = 600;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"FastTrack", Style::Resize);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Here is our clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	Vector2f InitPlayerCoordinates;
	InitPlayerCoordinates.x = 0.0;
	InitPlayerCoordinates.y = 0.0;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;
	Player player2;

	// The boundaries of the arena
	IntRect arena;

	// Create the background
	VertexArray background;
	Sprite spriteBackground;
	// Load the texture for our background vertex array
	Texture textureBackground = TextureHolder::GetTexture("graphics/Track.png");
	

	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(-(resolution.x/2), -(resolution.y/2));


	// When was the fire button last pressed?
	Time lastPressed;


	// About the game
	int score = 0;
	int hiScore = 0;

	// For the home/game over screen
	Sprite spriteGameOver;
	Texture textureGameOver = TextureHolder::GetTexture("graphics/background.png");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);



	// Create a view for the HUD
	View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));


	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;

	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;

	//init Player
	InitPlayerCoordinates.x = 0;
	InitPlayerCoordinates.y = resolution.y /2 - 250;
	player.initPlayer(InitPlayerCoordinates);
	InitPlayerCoordinates.y += 100;
	player2.initPlayer(InitPlayerCoordinates);

	// The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handle input
		************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}

				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					//init Player
					//player.initPlayerSteps();
					clock.restart();
				}

				if (state == State::PLAYING)
				{
					// Reloading
					if (event.key.code == Keyboard::R)
					{
						
						
					}
				}

			}
		}// End event polling


		 // Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle controls while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys
			

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				 // left foot
				player.getLeftFoot();
			}
			else
			{
				player.stopLeft();
			}

		
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				// right foot
				player.getRightFoot();
			}
			else
			{
				player.stopRight();
			}

			

			if (Keyboard::isKeyPressed(Keyboard::G))
			{
				 // left foot
				player2.getLeftFoot();
			}
			else
			{
				player2.stopLeft();
			}

		
			if (Keyboard::isKeyPressed(Keyboard::H))
			{
				// right foot
				player2.getRightFoot();
			}
			else
			{
				player2.stopRight();
			}
			player.moveRight();
			player2.moveRight();

		}// End WASD while playing

		 

		 /*
		 ****************
		 UPDATE THE FRAME
		 ****************
		 */
		if (state == State::PLAYING)
		{
			// Update the delta time
			Time dt = clock.restart();
			// Update the total game time
			gameTimeTotal += dt;
			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			

			// Update the player
			player.update(dtAsSeconds);
			player2.update(dtAsSeconds);

			// Make a note of the players new position
			Vector2f player1Position(player.getCenter());
			Vector2f player2Position(player2.getCenter());
			Vector2f viewPosition;
			viewPosition.y = 0 ;

			// Make the view centre around the fastest player
			if (player1Position.x > player2Position.x )
			{
				viewPosition.x = player1Position.x;
			}			
			else
			{
				viewPosition.x = player2Position.x;	
			}
			mainView.setCenter(viewPosition);

			// Increment the number of frames since the last HUD calculation
			framesSinceLastHUDUpdate++;
			// Calculate FPS every fpsMeasurementFrameInterval frames
			if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
			{

					
			
				

			

				framesSinceLastHUDUpdate = 0;
			}// End HUD update

		}// End updating the scene

		 /*
		 **************
		 Draw the scene
		 **************
		 */

		if (state == State::PLAYING)
		{
			window.clear();

			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);

			// Draw the background
			window.draw(spriteBackground);
			

			
			// Draw the player
			window.draw(player.getSprite());
			window.draw(player2.getSprite());
			

			
		
			// Switch to the HUD view
			window.setView(hudView);

		
		}

		

		if (state == State::PAUSED)
		{
			
		}

		if (state == State::GAME_OVER)
		{
			window.draw(spriteGameOver);

		}

		window.display();

	}// End game loop

	return 0;
}
