#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"
#include "TextureHolder.h" //
#include "Bullet.h"
#include "Pickup.h"

using namespace sf;


int main()
{
    // Here is the instance of TextureHolder
    TextureHolder holder;
    ///

    /// The game will always be in one of four states
    /// Igrica ima cetri stanja ///
    enum class State {
        PAUSED,
        LEVELING_UP,
        GAME_OVER,
        PLAYING
    };

    // Start with the GAME_OVER state
    State state = State::GAME_OVER;
    // Get the screen resolution and
    // create an SFML window
    Vector2f resolution;
    resolution.x =
        VideoMode::getDesktopMode().width;
    resolution.y =
        VideoMode::getDesktopMode().height;

    RenderWindow window(
        VideoMode(resolution.x, resolution.y), "Zombie Arena ", Style::Fullscreen
    );

    // Create a an SFML View for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    // Here is our clock for timing everything
    Clock clock;

    // How long has the PLAYING state been active
    Time gameTimeTotal;

    // Where is the mouse in
    // relation to world coordinates
    Vector2f mouseWorldPosition;

    // Where is the mouse in
    // relation to screen coordinates
    Vector2i mouseScreenPosition;

    // Create an instance of the Player class
    Player player;

    // The boundaries of the arena
    IntRect arena;

    // Create the background
    VertexArray background;

    // Load the texture for our background vertex array
    //Texture textureBackground;
    //textureBackground.loadFromFile("graphics/background_sheet.png");
    Texture textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png");


    ///// NAuci dobro /////
    // Prepare for a horde of zombies
    int numZombies;
    int numZombiesAlive;
    Zombie* zombies = nullptr;
    // 100 bullets 
    Bullet bullets[100];
    int currentBullet  = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSide = 6;
    float fireRate = 2;

    //Where was the fire button pressed?
    Time lastPressed;
    
    // Hide the mouse pointer and replace it with crosshair
    window.setMouseCursorVisible(false);
    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    spriteCrosshair.setOrigin(25, 25);

    // Create a couple of pickups
    Pickup healthPickup(1);
    Pickup ammoPickup(2);

    // About the game
    int score = 0;
    int hiScore = 0;

    ////

    // The main game loop // /// // /// ///
    while (window.isOpen())
    {
        Time dt = clock.restart();

        // Update the total game time
        gameTimeTotal += dt;

        float dtAsSeconds = dt.asSeconds();

        /*
        ************
        Handle input
        ************
        */
        // Handle events by polling
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                //Pause a game while playing
                if (event.key.code == Keyboard::Return && state == State::PLAYING)
                {
                    state = State::PAUSED;
                }
                // Restart while paused
                else if (event.key.code == Keyboard::Return && state == State::PAUSED)
                {
                    state = State::PLAYING;
                    // Reset the clock so there isn't a frame jump
                    clock.restart();
                }
                // Start a new game while in GAME_OVER state
                else if (event.key.code == Keyboard::Return &&
                    state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }
                if (state == State::PLAYING)
                {
                    // Reloading
                    if (event.key.code == Keyboard::R)
                    {
                        if (bulletsSpare >= clipSide)
                        {
                            // Plenty of bullets. Realod.
                            bulletsInClip = clipSide;
                            bulletsSpare -= clipSide;
                        }
                        else if (bulletsSpare > 0)
                        {
                            // Only few bullets left
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                        }
                        else
                        {
                            ///
                        }
                    }
                }

            }
        } // End event polling

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        // Handle WASD while playing
        if (state == State::PLAYING)
        {
            // Handle the pressing and releasing of WASD keys
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }

            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }
            if (Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0)
                {
                    // Pass the centre of the player
                    // and the centre of the cross-hair
                    // to the shoot function
                    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
                    currentBullet ++;
                    if (currentBullet  > 99)
                    {
                        currentBullet  = 0;
                        std::cout << "Fired bullet #" << currentBullet << std::endl;
                    }
                    lastPressed = gameTimeTotal;
                    bulletsInClip--;
                }
                std::cout << "Mouse clicked!" << std::endl;
            }// End fire a bullet*******

        }// End WASD while playing

        // Handle the LEVELING up state
        if (state == State::LEVELING_UP)
        {
            // Handle the player LEVELING up
            if (event.key.code == Keyboard::Num1)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num2)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num3)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num4)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num5)
            {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num6)
            {
                state = State::PLAYING;
            }

            if (state == State::PLAYING)
            {
                // Prepare the level
                // We will modify the next two lines later
                arena.width = 1000;
                arena.height = 1000;
                arena.left = 0;
                arena.top = 0;
                // Pass the vertex array by reference
                // to the createBackground function
                int tileSize = createBackground(background, arena);
                // We will modify this line of code later
                //int tileSize = 50;
                // Spawn the player in middle of the arena
                player.spawn(arena, resolution, tileSize);
                
                ////***////

                // Configure the pick-ups
                healthPickup.setArena(arena);
                ammoPickup.setArena(arena);

                
                // Create a horde of zombies
                numZombies = 10;
                // Delete the previously allocated memory (if it exists)
                delete[] zombies;
                zombies = createHorde(numZombies, arena);
                numZombiesAlive = numZombies;

                ////***////

                // Reset clock so there isn't a frame jump
                clock.restart();
            }

        } // End LEVELING up


        /*
        ****************
        UPDATE THE FRAME
        ****************
        */
        if (state == State::PLAYING)
        {
            
            //// GORE SAM PREBACIO JER ONDA RADI /////
            // Update the delta time
            //Time dt = clock.restart();

            //// Update the total game time
            //gameTimeTotal += dt;

            //float dtAsSeconds = dt.asSeconds();

            ////////

            //// Make a decimal fraction of 1 from the delta time
            //float dtAsSeconds = dt.asSeconds();

            // Where is the mouse pointer
            mouseScreenPosition = Mouse::getPosition();

            // Convert mouse position to world
            // based coordinates of mainView
            mouseWorldPosition = window.mapPixelToCoords(
                Mouse::getPosition(), mainView);

            // Set the crosshair to the mouse world location
            spriteCrosshair.setPosition(mouseWorldPosition);

            // Update the player
            player.update(dtAsSeconds, Mouse::getPosition());

            // Make a note of the players new position
            Vector2f playerPosition(player.getCenter());

            // Make the view centre
            // the around player
            mainView.setCenter(player.getCenter());

            ////****////

            // Loop through each Zombie and update them
            for (int i = 0; i < numZombies; i++)
            {
                if (zombies[i].isAlive())
                {
                    zombies[i].update(dt.asSeconds(), playerPosition);
                }
            }
            // Update any bullets that are in-flight
            for (int i = 0; i < 100; i++)
            {
                if (bullets[i].isInFlight())
                {
                    bullets[i].update(dtAsSeconds);
                }
            }

            // Update the pickups
            healthPickup.update(dtAsSeconds);
            ammoPickup.update(dtAsSeconds);

            // Collision detection
            // Have any zombies been shot?

            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < numZombies; j++)
                {
                    if (bullets[i].isInFlight() && zombies[j].isAlive())
                    {
                        if (bullets[i].getPosition().intersects(zombies[j].getPosition()))
                        {
                            // Stop the bullet
                            bullets[i].stop();
                            // Register the hit and see if it was a kill
                            if (zombies[j].hit())
                            {
                                // Not just a hit but a kill too
                                score += 10;
                                if (score >= hiScore)
                                {
                                    hiScore = score;
                                }

                                numZombiesAlive--;
                                // When all the zombies are dead (again)
                                if (numZombiesAlive == 0)
                                {
                                    state = State::LEVELING_UP;
                                }
                            }
                        }
                    }
                }
            } // End of zombie being shot

            // Have any zombies touched the player
            for (int i = 0; i < numZombies; i++)
            {
                if (player.getPosition().intersects(zombies[i].getPosition()) && zombies[i].isAlive())
                {
                    if (player.hit(gameTimeTotal))
                    {
                        ///
                    }
                    if (player.getHealth() <= 0)
                    {
                        state = State::GAME_OVER;
                    }
                }
            }

            // Has the player touched health pickup
            if (player.getPosition().intersects(healthPickup.getPosition()) && healthPickup.isSpawned())
            {
                player.increaseHealthLevel(healthPickup.gotIt());
            }

            // Has the player touched ammo pickup
            if (player.getPosition().intersects(ammoPickup.getPosition()) && ammoPickup.isSpawned())
            {
                bulletsSpare += ammoPickup.gotIt();
            }

            ////****////

        }// End updating the scene

        /*
        **************
        Draw the scene
        **************
        */
        //std::cout << "Stete";
        if (state == State::PLAYING)
        {
            //std::cout << "test from Stete::Playing";

            window.clear();
            // set the mainView to be displayed in the window
            // And draw everything related to it
            window.setView(mainView);
            // Draw the background
            window.draw(background, &textureBackground);

            ////****////
            // Draw the zombies
            for (int i = 0; i < numZombies; i++)
            {
                window.draw(zombies[i].getSprite());
            }
            for (int i = 0; i < 100; i++)
            {
                if (bullets[i].isInFlight())
                {
                    window.draw(bullets[i].getShape());
                }
            }
            ////****////

            // Draw the player
            window.draw(player.getSprite());

            // Draw the pick-ups, if currently spawned
            if (ammoPickup.isSpawned())
            {
                window.draw(ammoPickup.getSprite());
            }
            if (healthPickup.isSpawned())
            {
                window.draw(healthPickup.getSprite());
            }

            //Draw the crosshair
            window.draw(spriteCrosshair);
        }
        if (state == State::LEVELING_UP)
        {
            //std::cout << "test from Stete::LEVELING_UP";
        }
        if (state == State::PAUSED)
        {
            //std::cout << "test from Stete::PAUSED";
        }
        if (state == State::GAME_OVER)
        {
            //std::cout << "test from Stete::LEVELING_UP";
        }
        window.display();

    } // End game loop

    ///****////

    // Delete the previously allocated memory (if it exists)
    delete[] zombies;

    ////****////

    return 0;
}