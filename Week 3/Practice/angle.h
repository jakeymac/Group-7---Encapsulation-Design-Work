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
    // Getters
    double getDegrees();
    double getRadians();

    // Setters
    void setDegrees(double degrees); // Takes in degrees, but must convert to radians before changing the member variable
    void setRadians(double radians);

    void display(ostream& out);

private:
    double angle; // In radians
    double convertToDegrees(double radians); // Does not affect the member variable "angle"
    double convertToRadians(double degrees); // Does not affect the member variable "angle"
    double normalize(double radians);        // Does not affect the member variable "angle"

};


