/***********************************************************************
 * Header File:
 *    Moon Lander : Takes care of the fuel and physics of the moon lander's
 *    movement
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#include "moonlander.h"
#include "point.h"

 /******************************************
  * POINT : CONSTRUCTOR WITH X,Y
  * Initialize the point to the passed position
  *****************************************/
MoonLander::MoonLander(Point location) {
    this->location = location;
    angle = 0.0;
    leftThrusterActive = false;
    rightThrusterActive = false;
    downThrusterActive = false;
    dx = 10.0;
    dy = 0.0;
    fuel = 1030.0;
    landerMass = 14073.0;
    alive = true;
}


/******************************************
  * POINT : CONSTRUCTOR WITH X,Y
  * Initialize the point to the passed position
  *****************************************/
void MoonLander::move(int framesPerSecond)
{
    if (fuel > 0) {
        if (leftThrusterActive) {
            addAngle(0.1);
            dx = dx - 0.05;
            burnFuel(0.1);
        }
        if (rightThrusterActive) {
            addAngle(-0.1);
            dx = dx + 0.05;
            burnFuel(0.1);
        }
        if (downThrusterActive) {
            double acceleration = 45000 / (landerMass + fuel);
            dx = dx + Trigonometry::computeHorizontalComponent(angle, acceleration);
            dy = dy + Trigonometry::computeVerticalComponent(angle, acceleration);
            burnFuel(1.0);
        }
    }
    

    dy = dy - 1.625; // gravity of the moon

    location.addX(-dx / framesPerSecond);
    location.addY(dy / framesPerSecond);
        
}

/******************************************
  * POINT : CONSTRUCTOR WITH X,Y
  * Initialize the point to the passed position
  *****************************************/
void MoonLander::die()
{
    alive = false;
    dx = 0.0;
    dy = 0.0;
    leftThrusterActive = false;
    rightThrusterActive = false;
    downThrusterActive = false;
}