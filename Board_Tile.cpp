#include "Board_Tile.h"

Board_Tile Board_Tile::goalConfig;

std::list<Board_Tile> Board_Tile::nextConfigs() {
  std::list<Board_Tile> possibleConfigs; //a list of the possible next configurations for the current puzzle
  Board_Tile temp; //temporary Board_Tile used to copy the current tile and move it in one of the possible directions.
  updateMoves(); //make sure that the current moves vector is properly udated to the currentConfig
  for(unsigned int i = 0; i < currentMoves.size(); ++i){
    temp = *this;
    temp.move(currentMoves[i]);
    possibleConfigs.push_back(temp);
  }
  return possibleConfigs;
}

int Board_Tile::Manhattan_Distance(const Board_Tile& goalconfig) const {
  std::string goal = goalconfig.getConfig();
  int heuristic = 0;
  //below are nine different const char* that represent each position that a tile can be, represented by 0
  //and then each other character is the distance from that position
  //topL is the top left, topM is the top middle, etc.
  const char* topL = "012123234", *topM = "101212323", *topR = "210321432";
  const char* midL = "123012123", *midM = "212101212", *midR = "321210321";
  const char* botL = "234123012", *botM = "323212101", *botR = "432321210";
  if(goal == "")
    return 0;

  //here the Manhattan_Distance distance is calculated by summing up the distance from where the tile is in relation
  //to where it should be using the above const char*
  std::string temp = "";
  temp = topL[goal.find(currentConfig[0], 0)]; heuristic += std::stoi(temp);
  temp = topM[goal.find(currentConfig[1], 0)]; heuristic += std::stoi(temp);
  temp = topR[goal.find(currentConfig[2], 0)]; heuristic += std::stoi(temp);
  temp = midL[goal.find(currentConfig[3], 0)]; heuristic += std::stoi(temp);
  temp = midM[goal.find(currentConfig[4], 0)]; heuristic += std::stoi(temp);
  temp = midR[goal.find(currentConfig[5], 0)]; heuristic += std::stoi(temp);
  temp = botL[goal.find(currentConfig[6], 0)]; heuristic += std::stoi(temp);
  temp = botM[goal.find(currentConfig[7], 0)]; heuristic += std::stoi(temp);
  temp = botR[goal.find(currentConfig[8], 0)]; heuristic += std::stoi(temp);

  return heuristic;
}

void Board_Tile::move(DIRECTION dir) {
  std::string temp = currentConfig;
  direction += getChar(dir);
  int index = temp.find('0', 0);

  //moves the hole (represented by 0) in the direction specified,
  //as long as it is possible for it to move in that direction
  if(dir == Up && index >= 3) {
    std::swap(temp[index], temp[index - 3]);
  } else if(dir == Right && index != 2 && index != 5 && index != 8) {
    std::swap(temp[index], temp[index + 1]);
  } else if(dir == Down && index <= 5) {
    std::swap(temp[index], temp[index + 3]);
  } else if(dir == Left && index != 0 && index != 3 && index != 6) {
    std::swap(temp[index], temp[index - 1]);
    }
  currentConfig = temp;
  updateMoves();

  //update the number of moves every time the hole is moved
  ++numOfMoves;
}

void Board_Tile::updateMoves() {
  //get rid of the past possible moves
  currentMoves.clear();
  int hole = currentConfig.find('0', 0);
  //push the possible moves onto the currentMoves vector
  if(hole > 2) {
    currentMoves.push_back(Up);
  } if(hole != 2 && hole != 5 && hole != 8) {
    currentMoves.push_back(Right);
  } if(hole < 6) {
    currentMoves.push_back(Down);
  } if(hole != 0 && hole != 3 && hole != 6) {
    currentMoves.push_back(Left);
  }
}

const char* Board_Tile::getChar(DIRECTION dir) {
  if(dir == Up) {
    return "U";
  } else if(dir == Down) {
    return "D";
  } else if(dir == Left) {
    return "L";
  } else if(dir == Right) {
    return "R";
  } else {
    return "";
  }
}
