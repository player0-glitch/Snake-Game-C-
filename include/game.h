#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>
#include <string>
// error codes
enum ERR { MUSIC = 0, BOUND };
enum DIRECTION { STOP = 0, UP, RIGHT, DOWN, LEFT };
// Globals
static const int CELL_COUNT = 25;
static const int CELL_SIZE = 30;
static const sf::Color DARK_GREEN = {43, 57, 24, 255};
static const sf::Color GREEN = {173, 204, 96, 255};

class Game {
public:
  Game(int width, int height);
  ~Game();
  void createFood();
  void moveInDirection();
  void run(sf::Int32 &elapsedTime);
  void createSnake();
  sf::RectangleShape getFood() { return _food; }
  std::deque<sf::RectangleShape> getSnake() { return _snake; };
  sf::Vector2f getNewDirection() { return _newDirection; }
  void setDirection(const DIRECTION &);

private:
  void eat(); // AABB Box Collision
  sf::Vector2f randLocation();
  void setUp();
  sf::RectangleShape makeNewRectangle(sf::Vector2f);
  void wallWarping();
  void loadMusic(std::string musicFile);
  void selfCollision();
  int _width, _height;
  sf::RectangleShape _food;
  std::deque<sf::RectangleShape> _snake;
  sf::Music _eatSound;
  int _score;
  float _updateTime;
  float _fixedTimeStep;
  DIRECTION _eDirection;
  sf::Vector2f _newDirection;
  sf::Vector2f _currentDirection;
};
