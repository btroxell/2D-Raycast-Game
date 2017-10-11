#ifndef MOVEMENTENGINE_H_DEFINED
#define MOVEMENTENGINE_H_DEFINED

#include <cmath>
#include <vector>
#include "raycast.h"
#include "map.h"

class MovementEngine
{
  private:
    double blockedx;
    double blockedy;
    double direction;
    Map m;
    vector<double> aix;
    vector<double> aiy;
    vector<double> path;
    int oldWall;
    void setDirection(double);
  public:
    MovementEngine();
    MovementEngine(Map&);
    ~MovementEngine();
    bool atDest(double, double, double, double);
    bool blocked(double, double, double, double);
    void aiPath(double, double, double, double, double);
    double getBlockedX(double, double, double, double);
    double getBlockedY(double, double, double, double);
};

#endif // MOVEMENTENGINE_H_DEFINED
