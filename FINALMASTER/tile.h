// tile.h
// Alex Rutan
// 3/28/15

#ifndef TILE_EXIST
#define TILE_EXIST

class Tile
{
  private:
    int ID;
	int tag;
	int Xcoord;
	int Ycoord;

  public:
	Tile();
	~Tile();
	void setInfo(int, int, int, int);
	int getX();
	int getY();
	int getTag();
}; //end Tile

#endif //TILE_EXISTS
