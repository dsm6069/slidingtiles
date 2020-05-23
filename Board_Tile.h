#ifndef BOARD_TILE_H
#define BOARD_TILE_H

#include "directions.h"
#include <vector>
#include <string>
#include <list>
#include <memory>

void updateMoves();

class Board_Tile {
public:
  //default constructor that just assigns an empty string to the current configuration
  Board_Tile(): currentConfig{""} {};

  //constructor taking a string representing the current config of the puzzle and assigns it to the private member currentConfig
  Board_Tile(const std::string& config): currentConfig{config} {};

  //function that returns a list of the next possible configurations of the board
  std::list<Board_Tile> nextConfigs();

  //function that returns the number of moves that have been taken to get to the current
  //configuration from the initial configuration
  int numMoves() const { return numOfMoves;}

  //function that takes a Board_Tile and returns an int representing the Manhattan Distance of that configuration
  int Manhattan_Distance(const Board_Tile& goalconfig) const;

  //gets the current configuration of the board
  std::string getConfig() const {return currentConfig; }

  //function that sets the configuration of a previously created Board_Tile
  void setConfig(std::string config) {currentConfig = config; }

  //moves the hole in the direction specified
  void move(DIRECTION dir);

  //returns a vector of the possible moves of the current board
  std::vector<DIRECTION> possibleMoves() { return currentMoves; }

  //returns a string representing the moves used to get to this configuration from the starting configuration
  std::string getDirection() const { return direction; }

  //static Board_Tile representing the goal configuration of the current puzzle. Assigned by the Solve_Puzzle function in Sliding_Solver
  static Board_Tile goalConfig;

private:
  //function that takes a DIRECTION and returns a const char* representing that direction for the final output.
  //used to add to the direction string
  const char* getChar(DIRECTION dir);

  //function that updates the currentMove vector for use in nextConfigs
  void updateMoves();

  //string representing the current configuration of the Board
  std::string currentConfig;

  //vector representing the popssible moves from the current configuration for use in nextConfigs
  std::vector<DIRECTION> currentMoves;

  //integer representing the number of moves taken to get to this configuration from the initial configuration
  int numOfMoves = 0;

  //string representing the moves taken to get to the current configuration from the initial configuration
  std::string direction;


};
#endif
