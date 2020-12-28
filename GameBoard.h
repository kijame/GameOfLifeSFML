#include <vector>
#include <SFML/Graphics.hpp>
#include <set>
#include <unordered_set>
#include <utility>

#ifndef BOARDGAME_H
#define BOARDGAME_H

class GameBoard
{
private:
  int height = 600;
  int width = 800;
  std::vector<std::vector<sf::RectangleShape>> boardState;
  std::set<std::pair<int, int>> alive;

public:
  GameBoard(); // Default Constructor
  void click(int x, int y);
  std::vector<std::vector<sf::RectangleShape>> *getState();
  void iterate();
  void draw(sf::RenderWindow *window);
  void reset();
};

#endif
