/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 03: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

#pragma once

#define TWO_PI 6.28318530718

#include <math.h>    // for floor()
#include <iostream>  // for cout
#include <cassert>   // for assert()
using namespace std;

class TestAngle;

/************************************
 * ANGLE
 ************************************/
class Angle
{
    friend TestAngle;

public:
    /***************************************************
    * GET DEGREES
    * Takes no parameters and returns the angle in degrees.
    *
    * INPUT
    *     None
    * OUTPUT
    *     angle : in degrees
    **************************************************/
    double getDegrees() { return convertToDegrees(radians); }

    /***************************************************
    * GET RADIANS
    * Takes no parameters and returns the angle in radians.
    *
    * INPUT
    *     None
    * OUTPUT
    *     angle : in radians
    **************************************************/
    double getRadians() { return radians; }

    /***************************************************
    * SET DEGREES
    * Takes a degrees as a parameter and updates the
    * attribute with the passed parameter. If the parameter
    * is above 360 or below zero, then it will "unwrap" so
    * the radians is between 0 and 2pi.
    *
    * INPUT
    *     degrees
    * OUTPUT
    *     None
    **************************************************/
    void setDegrees(double degrees) { radians = normalize(convertToRadians(degrees)); }

    /***************************************************
    * SET RADIANS
    * Takes a radian as a parameter and updates the
    * attribute with the passed parameter. If the parameter
    * is above 360 or below zero, then it will "unwrap" so
    * the radians is between 0 and 2pi.
    *
    * INPUT
    *     radians
    * OUTPUT
    *     None
    **************************************************/
    void setRadians(double radians) { this->radians = normalize(radians); }

    /***************************************************
    * DISPLAY
    * Takes a ostream & out as a parameter display the value,
    * in degrees, to 1 decimal place of accuracy. This out
    * parameter can be treated exactly the same as cout.
    * You can use it with a.display(cout) if a is the name
    * of your object.
    *
    * INPUT
    *     ostream & out
    * OUTPUT
    *     None, prints to screen
    **************************************************/
    void display(ostream& out);

private:
    double radians;

    /***************************************************
    * CONVERT TO DEGREES
    * Takes a radians as a parameter and returns degrees.
    * Does not utilize the class's attribute.
    *
    * INPUT
    *     radians
    * OUTPUT
    *     angle : in degrees
    **************************************************/
    double convertToDegrees(double radians) { return normalize(radians) * 360.0 / TWO_PI; }

    /***************************************************
        * CONVERT TO RADIANS
        * Takes a degrees as a parameter and returns radians.
        * Does not utilize the class's attribute.
        *
        * INPUT
        *     degrees
        * OUTPUT
        *     angle : in radians
        **************************************************/
    double convertToRadians(double degrees) { return normalize(degrees * TWO_PI / 360.0); }

    /***************************************************
        * NORMALIZE
        * Takes a radian as a parameter and reduce it to
        * between 0 and 2pi. For example, 3pi will become pi,
        * 362° will become 2°, -5° will become 355°, and
        * -7pi will become pi.
        *
        * INPUT
        *     radians
        * OUTPUT
        *     angle : in radians
        **************************************************/
    double normalize(double radians) { return radians - floor(radians / TWO_PI) * TWO_PI; }

};


