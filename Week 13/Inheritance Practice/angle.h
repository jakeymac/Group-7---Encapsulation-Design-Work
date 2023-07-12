/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Module
 *      ANGLE
 * 3. Assignment Description:
 *      A class to represent an angle
 **************************************************************/

#pragma once

#include <iostream>
#include <cassert>
#include <string>
#define TWO_PI 6.28318530718
#define PI_EIGHT (3.1415926 / 8.0)

class TestAngle;
class TestAngleRadian;

using namespace std;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   friend TestAngle;

public:
    // Default constructor
    Angle() : radians(0.0) {}
    Angle(const Angle& rhs) : radians(rhs.radians) {}
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
    virtual Angle& operator = (double degrees) {
        radians = normalize(convertToRadians(degrees));
        return *this;
    }
    
    virtual Angle& operator = (const Angle& rhs)
    {
        radians = rhs.getRadians();
        return *this;
    }
    bool operator == (const Angle& rhs) const
    {
        return this->radians == rhs.getRadians();
    }
    bool operator != (const Angle& rhs) const
    {
        return this->radians != rhs.getRadians();
    }
    Angle operator- () {
        return Angle(360.0 - this->getDegrees());
    }
    inline friend ostream& operator<< (ostream& out, const Angle& rhs) {
        rhs.display(out);
        return out;
    }
    inline friend istream& operator>> (istream& in, Angle& rhs) {
        string input;
        double degrees;

        in >> input;

        try {
            degrees = stod(input);
            rhs.setDegrees(degrees);
        }
        catch (exception e) {
           in.setstate(std::ios_base::failbit);
        }

        return in;
    }

    virtual Angle & operator++()
    {
        this->setDegrees(this->getDegrees() + 1.0);        // return new value
        return *this;
    }

    virtual Angle & operator--()
    {
        this->setDegrees(this->getDegrees() - 1.0);        // return new value
        return *this;
    }

    inline friend Angle operator++(Angle & angle,
        int postfix)
    {
        Angle angleToReturn(angle);
        angle.setDegrees(angle.getDegrees() + 1.0);
        // return old value
        return angleToReturn;
    }

    inline friend Angle operator--(Angle& angle,
        int postfix)
    {
        Angle angleToReturn(angle);
        angle.setDegrees(angle.getDegrees() - 1.0);
        // return old value
        return angleToReturn;
    }

    // Display
    virtual void display(ostream& out) const
    {
        out.precision(1);
        out.setf(ios::fixed | ios::showpoint);
        out << getDegrees();
    }

protected:
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



/************************************
 * ANGLE RADIANS
 ************************************/
class AngleRadians : public Angle
{
   friend TestAngleRadian;
    
    AngleRadians() : Angle(0.0) {}
    AngleRadians(double radians): Angle(radians) {}
    //AngleRadians(const AngleRadians& rhs):
    
    // Display
    virtual void display(ostream& out) const
    {
        out.precision(2);
        out.setf(ios::fixed | ios::showpoint);
        out << getRadians() << "radians";
    }
    
    virtual AngleRadians& operator = (double radians) {
        radians = normalize(radians);
        return *this;
    }
    
    virtual AngleRadians& operator = (const AngleRadians& rhs)
    {
        radians = rhs.getRadians();
        return *this;
    }
    
    virtual AngleRadians& operator -- () {
        this->setRadians(this->getRadians() - PI_EIGHT);
        return *this;
    }
    
    virtual AngleRadians& operator ++ () {
        this->setRadians(this->getRadians() + PI_EIGHT);
        return *this;
    }
};

