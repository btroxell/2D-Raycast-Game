// raycast.h
// Alex Rutan
// 4/10/15

#ifndef RAYCAST_EXIST
#define RAYCAST_EXIST

 class Raycast
 {
    private:
        double tilewidth;
        double currentx;
        double currenty;
        double myTheta;
        double distance;
        int determineQuad(double);
        int side;
        //Map map;
    public:
        Raycast();
        ~Raycast();
        void distanceCalc(double, double, double, double);
        int isSolid(double, double);
        //int isWall(double, double);
        int xOrYSide();
        void setCurrentX(double);
        void setCurrentY(double);
        void setCurrentTheta(double);
        double getCurrentX();
        double getCurrentY();
        double getCurrentTheta();
        double getCurrentDistance();
 };

#endif //RAYCAST_EXISTS
