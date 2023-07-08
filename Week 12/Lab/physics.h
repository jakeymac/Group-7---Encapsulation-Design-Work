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

#include <map>
#include <list>
#include "position.h"
#include "ground.h"

using namespace std;

/*********************************************
 * Class
 * brief definition
 *********************************************/
class Physics {
public:
    Physics(double radians, Position p, Ground *pGround);
    void advance();
    bool hitGround();
    bool hitTarget();
    Position getPosition() { return Position(x, y); }
    list<Position> distanceToAltitude;

private:
    double x;
    double y;
    double t;           // This is delta time, the time interval between calculations
    double hangTime;    // This is total time in the air
    double radians;
    double gravity;
    double ddx;         // Horizontal Acceleration
    double ddy;         // Vertical Acceleration
    double v;           // Total Velocity
    double dx;          // Horizontal Velocity
    double dy;          // Vertical Velocity
    double mass;        // how much does bullet weighs
    double radius;      // the size of the bullet
    double area;        // determined by radius, used for drag
    double ro;          // air density, determined by altitude
    double c;           // drag coefficient 
    double speedOfSound;
    double mach;
    double dragForce;
    double acceleration;
    map<double, double> hangTimeToAltitude;
    map<double, double> hangTimeToDistance;
    Ground *pGround;

    void thinkAhead();

    void finalize();

    double interpolation(double inputMiddle, map<double, double> m);

    void setRo(double altitude);

    void setGravity(double altitude);

    void setSpeedOfSound(double altitude);

    void setMach();

    void setC();

    void setDrag();

    void setAcceleration();

    void setAngle();

    void setDdx();

    void setDdy();
};
