/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 04: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/


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
   // Default constructor
   Angle() : radians(0.0) {}
   Angle(const Angle & rhs) : radians(rhs.radians) {}
   Angle(double degrees) : radians(0.0)
   {
      setDegrees(degrees);
   }

   // Getters
   double getDegrees() const
   {
      return convertToDegrees(radians);
   }
   double getRadians() const
   {
      return radians;
   }

   // Setters
   void setDegrees(double degrees)
   {
      radians = normalize(convertToRadians(degrees));
   }
   void setRadians(double radians)
   {
      this->radians = normalize(radians);
   }

   // Display
   void display(ostream & out) const
   {
      out.precision(1);
      out.setf(ios::fixed | ios::showpoint);
      out << getDegrees() << "degrees";
   }

private:
   // Convert functions
   double convertToDegrees(double radians) const
   {
      return normalize(radians) / TWO_PI * 360.0;
   }
   double convertToRadians(double degrees) const
   {
      return normalize(degrees / 360.0 * TWO_PI);
   }

   // Normalize
   double normalize(double radians) const
   {
      if (radians >= TWO_PI)
      {
         double multiples = floor(radians / TWO_PI);
         assert(radians - TWO_PI * multiples >= 0.0);
         assert(radians - TWO_PI * multiples <= TWO_PI);
         return radians - (TWO_PI * multiples);
      }
      else if (radians < 0.0)
      {
         double multiples = ceil(-radians / TWO_PI);
         assert(TWO_PI * multiples + radians >= 0.0);
         assert(TWO_PI * multiples + radians <= TWO_PI);
         return TWO_PI * multiples + radians;
      }

      assert(0.0 <= radians && radians <= TWO_PI);
      return radians;
   }

   double radians;
};

