// camera.h
// Alex Rutan
// 3/31/15

#ifndef CAMERA_EXIST
#define CAMERA_EXIST

#include <vector>
#include "raycast.h"
#include "map.h"

class Camera
{
    private:
        Map * map;
        double posX;
        double posY;
	double dx;
	double dy;
	double direction;
	int raycount;
	double wallHeightTheta;//angle to max height of wall to min height of wall
	int screenHeight;
	double startDraw;
	double endDraw;
	Raycast rays;
	std::vector<double>rayCurrentX;
	std::vector<double>rayCurrentY;
	std::vector<double>rayMyTheta;
	std::vector<double>rayDists;
	std::vector<double>solidRayDists;
	std::vector<bool>rayHitX;
	std::vector<bool>rayHitY;
	std::vector<int>solid;

    public:
	Camera(double, double, double, int, int, Map*);
	~Camera();
	int step;
	void move(int);
	void rotate(double);
	double getLoc(char);
	double getDxdy();
	void update(double, double, double);
	void castRay();
	std::vector<double>xRaysY1;
	std::vector<double>xRaysY2;
	std::vector<double>yRaysY1;
	std::vector<double>yRaysY2;
	std::vector<double>EnemyY1;
	std::vector<double>EnemyY2;
	std::vector<double>PickupY1;
	std::vector<double>PickupY2;
	std::vector<double>GunPickupY1;
	std::vector<double>GunPickupY2;
        std::vector<double>currentX;
        std::vector<double>currentY;
}; //end Camera

#endif //CAMERA_EXISTS
