// map.h
// Alex Rutan
// 3/26/15

#ifndef MAP_EXIST
#define MAP_EXIST

#include <vector>
#include <string>
#include "tile.h"
#include "enemy.h"

class Enemy;
class Map
{
  private:
    int gridX;
    int gridY;
    int tileX[625];
    int tileY[625];
    int tileTag[625];

  public:
	Map();
	~Map();
	std::vector<int>mapData;
	std::vector<Tile>tile;
	std::vector<Enemy>enemies;
	void loadMap();
	int getTileX(int);
	int getTileY(int);
	double initPlayerX;
	double initPlayerY;
	int getTileTag(int, int);
	void setTileTag(int, int, int);
	bool isWall(double, double);
	bool isSolid(double, double);
	void setEnemyMap(Map*);
	double getInitPlayerX();
	double getInitPlayerY();
}; //end Map

#endif //MAP_EXISTS
