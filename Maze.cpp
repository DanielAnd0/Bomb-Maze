//
// Created by Daniel on 02.11.2025.
//

#include<iostream>
#include "Maze.h"
#include <fstream>
using namespace std;

int Maze::is_in_maze(const int x, const int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= cols) return 0;
    return 1;
}
Maze::Maze() : exit{9,9} {
    rows = 5;
    cols = 10;
    player = new Player;
}
Maze::Maze(const int rows, const int cols, const int x, const int y): exit{x,y}{
    this->rows = rows;
    this->cols = cols;
    player = new Player;
    exit.x = x;
    exit.y = y;
}
Maze::Maze(const Maze& other) : exit{other.exit.x,other.exit.y} {
    rows = other.rows;
    cols = other.cols;
    if (other.player)
        player = new Player(*other.player);
    else
        player = nullptr;
    for (auto i : other.enemies)
        enemies.push_back(i);
}
Maze::~Maze() {
    delete player;
    for(const auto i : enemies) {
        delete i;
    }
    enemies.clear();
}

void Maze::create_maze() {
    ifstream fin("Maze.txt");
    fin >> rows >> cols;
    fin >> exit.x >> exit.y;
    for (int i = 0; i < rows; i++) {
        maze.push_back("");
        for (int j = 0; j < cols; j++) {
            char c;
            fin.get(c);
            if (c == ' ')
                fin.get(c);
            if (c != '\n')
                maze[i].push_back(c);
            else j--;  // sare penste endl
        }
    }
    fin.close();
}

void Maze::replace_player(const int x, const int y) {
    if (is_in_maze(x, y) == 0)
        cout<<"Not in maze"<<endl;
    else{
        if (maze[x][y] == ' ') {
            int pos_x = player->get_position_x();
            int pos_y = player->get_position_y();
            if (is_in_maze(pos_x, pos_y))
                maze[pos_x][pos_y] = ' ';
            player->set_position(x,y);
            maze[x][y] = 'P';
        }
    }
}
int Maze::Move_Player(const int direction) {
    for(int i = 0 ; i < player->get_speed(); i++) {
        const int pos_x = player->get_position_x();
        const int pos_y = player->get_position_y();
        switch (direction) { //verificam daca se poate mutarea
            case 1:
                if (is_in_maze(pos_x-1, pos_y) == 0) return 0;
                if (maze[pos_x-1][pos_y] != ' ' && maze[pos_x-1][pos_y] != 'E') return 0;
                break;
            case 2:
                if (is_in_maze(pos_x, pos_y+1) == 0) return 0;
                if (maze[pos_x][pos_y+1] != ' ' && maze[pos_x][pos_y+1] != 'E') return 0;
                break;
            case 3:
                if (is_in_maze(pos_x+1, pos_y) == 0) return 0;
                if (maze[pos_x+1][pos_y] != ' ' && maze[pos_x+1][pos_y] != 'E') return 0;
                break;
            case 4:
                if (is_in_maze(pos_x,pos_y-1) == 0) return 0;
                if (maze[pos_x][pos_y-1] != ' ' && maze[pos_x][pos_y-1] != 'E') return 0;
                break;
            default:
                cout<<"Select direction in range 1-4"<<endl;
                return 0;
        }
        player->Move(direction);
        int pos_x_new = player->get_position_x();
        int pos_y_new = player->get_position_y();
        if (maze[pos_x_new][pos_y_new] == 'E') { // Inamicul ii ia o viata player-ului, iar acesta se intoarce inapoi
            i = player->get_speed();
            player->life_update();
            player->set_position(pos_x, pos_y);
            if (player->get_lifes() == 0) {
                player->die();
            }
        }
        else { // ' '
            maze[pos_x_new][pos_y_new] = 'P';
            maze[pos_x][pos_y] = ' ';
        }
    }
    return 1;
}
void Maze::Player_Bomb() {
    Bomb b = player->Drop_Bomb();
    int pos_x = b.get_position_x();
    int pos_y = b.get_position_y();
    int range = b.get_radius();
    for (int i = 1; i <= range; i++) { // Nord
        int new_x = pos_x - i;
        int new_y = pos_y;
        if (is_in_maze(new_x, new_y) && (maze[new_x][new_y] == 'o' || maze[new_x][new_y] == 'E')) {
            if (maze[new_x][new_y] == 'E') destroy_enemy(new_x, new_y);
            maze[new_x][new_y] = ' ';
        }
    }
    for (int i = 1; i <= range; i++) { // Est
        int new_x = pos_x;
        int new_y = pos_y + i;
        if (is_in_maze(new_x, new_y) && (maze[new_x][new_y] == 'o' || maze[new_x][new_y] == 'E')) {
            if (maze[new_x][new_y] == 'E') destroy_enemy(new_x, new_y);
            maze[new_x][new_y] = ' ';
        }
    }
    for (int i = 1; i <= range; i++) { // Sud
        int new_x = pos_x + i;
        int new_y = pos_y;
        if (is_in_maze(new_x, new_y) && (maze[new_x][new_y] == 'o' || maze[new_x][new_y] == 'E')) {
            if (maze[new_x][new_y] == 'E') destroy_enemy(new_x, new_y);
            maze[new_x][new_y] = ' ';
        }
    }
    for (int i = 1; i <= range; i++) { // Vest
        int new_x = pos_x;
        int new_y = pos_y - i;
        if (is_in_maze(new_x, new_y) && (maze[new_x][new_y] == 'o' || maze[new_x][new_y] == 'E')) {
            if (maze[new_x][new_y] == 'E') destroy_enemy(new_x, new_y);
            maze[new_x][new_y] = ' ';
        }
    }
}
void Maze::place_enemy(int x, int y){
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        cout<<"Not in maze"<<endl;
    else {
        if (maze[x][y] == ' ') {
            enemies.push_back(new Enemies(x,y));
            maze[x][y] = 'E';
        }
        else cout<<"Enemy can not be placed";
    }
}
void Maze::destroy_enemy(int x, int y) {
    if (maze[x][y] == 'E') {
        maze[x][y] = ' ';
        for(int i = 0; i < static_cast<int>(enemies.size()); i++) {
            if (enemies[i]->get_position_x() == x && enemies[i]->get_position_y() == y) {
                enemies[i]->kill();
                enemies.erase(enemies.begin() + i);
                cout<<"Delete enemy from position ("<<x<<", "<<y<<")"<<endl;
            }
        }
    }
    else cout<<"There is no enemy at position ("<<x<<", "<<y<<")"<<endl;
}
Maze& Maze::operator=(const Maze& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        exit.x = other.exit.x;
        exit.y = other.exit.y;
        player = other.player;
        for (auto i : other.enemies) {
            enemies.clear();
            enemies.push_back(i);
        }
    }
    return *this;
}
ostream& operator<<(ostream& os, const Maze& maze) {
    for (int i = 0; i < maze.rows; i++) {
        for (int j = 0; j < maze.cols; j++) {
            os<<maze.maze[i][j]<<" ";
        }
        os<<endl;
    }
    os << *maze.player;
    if (maze.enemies.size() != 0) {
        for (auto i : maze.enemies) {
            os << *i;
        }
    }
    return os;
}
int Maze::checkGame() const{ //return 0 daca s-a terminat jocul
    int pos_x = player->get_position_x();
    int pos_y = player->get_position_y();
    if (pos_x == exit.x && pos_y == exit.y && enemies.size() == 0) {
        cout<<"----------"<<endl;
        cout<<"GAME WON!"<<endl;
        cout<<"----------"<<endl;
        return 0;
    }
    if (player->get_life_status()==false) {
        cout<<"----------"<<endl;
        cout<<"GAME OVER!"<<endl;
        cout<<"----------"<<endl;
        return 0;
    }
    return 1;
}