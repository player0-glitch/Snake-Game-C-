#include "../include/game.h"
#include "../include/boxcollision.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;
Game::Game(int width, int height) {
  _width = width;
  _height = height;

  setUp();
}
Game::~Game() {}
void Game::setUp() {
  loadMusic("../resource/sound/eat.wav");
  createFood();
  createSnake();
  _newDirection = _snake.front().getPosition();
  _eDirection = RIGHT;
  _currentDirection = {1, 0};
  _score = 0;
  _updateTime = 500.0f;
  _fixedTimeStep = 1.0f / 60.0f; // 60FPS
}

sf::Vector2f Game::randLocation() {
  int x = rand() % CELL_COUNT * CELL_SIZE;
  int y = rand() % CELL_COUNT * CELL_SIZE;
  return sf::Vector2f(x, y);
}
void Game::createFood() {
  sf::Vector2f pos = randLocation();
  _food.setPosition(pos);
  _food.setFillColor(DARK_GREEN);
  _food.setSize({25, 25}); // the size is based on the size of the cells.
  // I couldn't be bothered to not hardcode these
}
void Game::loadMusic(std::string musicFIle) {
  if (!_eatSound.openFromFile(musicFIle))
    exit(ERR::MUSIC);
}
void Game::createSnake() {
  // these indeces aren't going to influence the snake queue
  sf::Vector2f pos = randLocation();
  /*pos.x = x;*/
  /*pos.y = y;*/
  _snake = {sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape()};
  for (std::size_t i = 0; i < _snake.size(); i++) {
    // Customise the snake body and stuff
    _snake.at(i).setFillColor(DARK_GREEN);
    _snake.at(i).setPosition(pos);
    _snake.at(i).setSize({25, 25});
    /*pos.x += 25;*/
    /*pos.y += 25;*/
  }
}

void Game::moveInDirection() {
  switch (_eDirection) {
  case UP:
    if (_currentDirection.y != -1) // snake is NOT going down
    {
      _newDirection.y -= 25;
      // reset the current direction to the new current direction
      _currentDirection = {0, 1};
      sf::RectangleShape front = _snake.front();
      _snake.pop_back();
      /*_snake.emplace_front(front);*/
      _snake.emplace_front(makeNewRectangle(_newDirection));
    }
    break;
  case DOWN:
    if (_currentDirection.y != 1) // snake is NOT goin up
    {
      _newDirection.y += 25;
      _currentDirection = {0, -1};
      sf::RectangleShape front = _snake.front();
      _snake.pop_back();
      /*_snake.emplace_front(front);*/
      _snake.emplace_front(makeNewRectangle(_newDirection));
    }
    break;
  case LEFT:
    if (_currentDirection.x != 1) // snake is NOT going right
    {
      _newDirection.x -= 25;
      _currentDirection = {-1, 0};
      sf::RectangleShape front = _snake.front();
      _snake.pop_back();
      /*_snake.emplace_front(front);*/
      _snake.emplace_front(makeNewRectangle(_newDirection));
    }
    break;
  case RIGHT:
    if (_currentDirection.x != -1) // snake if NOT going left
    {
      _newDirection.x += 25;
      _currentDirection = {1, 0};
      sf::RectangleShape front = _snake.front();
      _snake.pop_back();
      /*_snake.emplace_front(front);*/
      _snake.emplace_front(makeNewRectangle(_newDirection));
    }
    break;
  default:
    break;
  }
  // Do Bounds Checking right here
}
sf::RectangleShape Game::makeNewRectangle(sf::Vector2f pos) {
  sf::RectangleShape rect;
  rect.setPosition(pos);
  rect.setFillColor(DARK_GREEN);
  rect.setSize({25, 25});
  return rect;
}
void Game::setDirection(const DIRECTION &direction) { _eDirection = direction; }
void Game::run(sf::Int32 &elapsedTime) {

  if (elapsedTime >= _updateTime) {
    elapsedTime = 0.0;
    moveInDirection();

    wallWarping();
  }

  eat();
}
void Game::wallWarping() {
  sf::RectangleShape head = _snake.front();
  // wallWarping up or down
  if (head.getPosition().y < 0) {
    _newDirection.y = _height;
    _newDirection.x = head.getPosition().x;
    _snake.pop_back();
    _snake.emplace_front(makeNewRectangle(_newDirection));
  }
  if (head.getPosition().y >= _height) {
    _newDirection.y = 0;
    _snake.pop_back();
    _snake.emplace_front(makeNewRectangle(_newDirection));
  }

  // wallwarping left or right
  if (head.getPosition().x <= 0) {
    _newDirection.x = _width;
    _newDirection.y = head.getPosition().y;
    _snake.pop_back();
    _snake.emplace_front(makeNewRectangle(_newDirection));
  }
  if (head.getPosition().x >= _width) {
    _newDirection.x = 0;
    _snake.pop_back();
    _snake.emplace_front(makeNewRectangle(_newDirection));
  }
}
void Game::eat() {
  /* Box boundaries for both food and snake
   *      B
   *   --------
   *  A|      |C
   *   |______|
   *      D
   * (B,A)-> min
   * (D,C)-> max
   */
  // variable declartions are just for easier typing and readability
  AABB foodBox(_food.getPosition().x, _food.getPosition().x + _food.getSize().x,
               _food.getPosition().y,
               _food.getPosition().y + _food.getSize().y);
  AABB snakeHeadBox(_snake.front().getPosition().x,
                    _snake.front().getPosition().x + _snake.front().getSize().x,
                    _snake.front().getPosition().y,
                    _snake.front().getPosition().y +
                        _snake.front().getSize().y);

  if (snakeHeadBox.checkCollision(foodBox)) {
    _eatSound.play();
    createFood();
    // grow the snake
    sf::Vector2f tail = _snake.back().getPosition();
    _snake.emplace_back(makeNewRectangle(tail));
    _score++;

    _updateTime -= 25.0f;
    // make sure the update time is never lower than 0.05 seconds
  }
  /*if (_score > 1 && _score % 5 == 0) {*/
  /*  _updateTime = _updateTime - (float)50.0f;*/
  /*}*/
  if (_updateTime <= 0.05f)
    _updateTime = 0.05f;
}

void Game::selfCollision() {}
