/***********************************************************************
 * Header File:
 *    Class : brief definition
 * Author:
 *    add author
 * Summary:
 *    add
 *    summary
 ************************************************************************/

#pragma once

#include "position.h"
#include "ground.h"
#include "physics.h"
#include <list>
#include <iterator>

using namespace std;

/*********************************************
 * Class
 * brief definition
 *********************************************/
class Bullet {
public:
    Bullet(Position p, double radians, Ground * ground);
    bool isAlive() const;
    void advance();
    list<Position> getStreakPath() const;
    Position getImpactPosition() { return impactPos; }
    double getAltitude();
    double getSpeed();
    double getDistance();
    double getHangTime();
    bool hitGround();
    
private:
    list<Position> streakPath;
    Physics physics;
    Position impactPos;
    Position startPos;
};
