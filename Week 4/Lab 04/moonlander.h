/***********************************************************************
 * Header File:
 *    Moon Lander : Takes care of the fuel and physics of the moon lander's 
 *    movement
 * Author:
 *    
 * Summary:
 *    
 ************************************************************************/

#pragma once

#include "point.h"
#include "trigonometry.h"
 /*********************************************
  * MOON LANDER
  * our lunar module that player must land
  *********************************************/
class MoonLander
{
public:
    MoonLander(Point location);
    double getAngle() { return angle; }
    Point getLocation() { return location; }
    void setAngle(double angle) { this->angle = angle; }
    void addAngle(double ammount) { angle += ammount; }
    bool getLeftThruster() { return (leftThrusterActive && fuel > 0.0); }
    bool getRightThruster() { return (rightThrusterActive && fuel > 0.0); }
    bool getDownThruster() { return (downThrusterActive && fuel > 0.0); }
    void setLeftThruster(bool state) { leftThrusterActive = state; }
    void setRightThruster(bool state) { rightThrusterActive = state; }
    void setDownThruster(bool state) { downThrusterActive = state; }
    void move(int framesPerSecond);
    double getVelocity() { return Trigonometry::computeTotalComponent(dx,dy); }
    bool isAlive() { return alive; }
    double getFuel() { return fuel; }
    void die();

private:
    double angle;
    Point location;
    bool leftThrusterActive;
    bool rightThrusterActive;
    bool downThrusterActive;
    double dx;
    double dy;
    double fuel;
    double landerMass;
    bool alive;

    void burnFuel(double ammount) { fuel = fuel - ammount; }
};