
#include <iostream>
#include <fstream>

#include "headers/Bomb.h"
#include "headers/Exceptions.h"
#include "headers/Player.h"
#include "headers/Maze.h"


int main() {
    try {
        Enemies::loadTexture();
        tiles::loadTexture();
        Player::loadTexture();
        Bomb::loadTexture();


        constexpr unsigned int screenWidth = 15;
        constexpr unsigned int screenHeight = 10;

        //Create the maze
        Maze maze(screenWidth, screenHeight);
        sf::RenderWindow window(sf::VideoMode({screenWidth*tiles::getsize().x, screenHeight*tiles::getsize().y}), "Game");
        window.setSize({800,400});

        //Create player
        Player player(0.9f*static_cast<float>(tiles::getsize().x), 2.f*static_cast<float>(tiles::getsize().y));
        constexpr float speed=32.f;
        player.set_speed(speed);

        //Create a bomb that can be deployed by the player
        Bomb bomb;

        //Load the maze
        constexpr std::array loadMaze = { // 0-falseWall, 1-free path, 2-wall, 3-exit
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 3,
            2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2,
            2, 2, 2, 2, 2, 0, 2, 2, 1, 1, 1, 2, 2, 1, 2,
            2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 1, 2,
            2, 2, 2, 2, 2, 0, 2, 2, 1, 2, 2, 2, 2, 1, 2,
            2, 2, 2, 2, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        };
        maze.load(loadMaze.data());

        //add enemies in maze
        maze.add_enemy(10.f*static_cast<float>(tiles::getsize().x), 3.f*static_cast<float>(tiles::getsize().y));
        maze.add_enemy(9.f*static_cast<float>(tiles::getsize().x), 3.f*static_cast<float>(tiles::getsize().y));

        //start clock
        sf::Clock clock;

        //GameLoop
        while (window.isOpen() && !player.getHitBox().contains(maze.get_exit()) && player.get_life_status()){
            float deltaTime = clock.restart().asSeconds();
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            //clear window before drawing
            window.clear(sf::Color::White);


            //draw maze
            maze.drawMaze(window);

            //update bomb and player
            bomb.Update(deltaTime);
            player.Update(deltaTime);

            //if you press space the bomb is deployed
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && player.can_deploy()==true) {
                player.set_deploy_status(false);
                sf::Vector2f playerPosition = player.getPlayerPosition();
                bomb.deploy(playerPosition.x, playerPosition.y);
                //attach the observers to the deployed bomb
                bomb.Attach(&maze);
                bomb.Attach(&player);
            }
            //detach the observers if bomb exploded
            if (bomb.isDeployed() == false && bomb.isExploded() == true) {
                bomb.Detach(&maze);
                bomb.Detach(&player);
            }

            //update maze
            maze.Update(player, deltaTime);
            //draw bomb and player
            bomb.draw(window);
            player.draw(window);
            window.display();
        }
    }catch (const NotInMaze& error) {
        std::cout<<"ERROR: "<< error.what()<<'\n';
    }catch (const InvalidTileNumber& error) {
        std::cout<<"ERROR: "<< error.what()<<'\n';
    }catch (const FileLoadFail& error) {
        std::cout<<"ERROR: "<<error.what()<<'\n';
    }
}
