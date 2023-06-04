#pragma once
#include "position.h"
#include "trigonometry.h"
#include <list>

class Physics {
public:
    Physics(double v, double radians)
    {
        
        t = .01;
        this->radians = radians;
        gravity = 9.8;
        dv = 0.0;
        ddx = 0.0;
        ddy = 0.0;
        this->v = v;
        dx = Trigonometry::computeHorizontalComponent(radians, v);
        dy = Trigonometry::computeVerticalComponent(radians, v);
    }

    void compute_physics(double radius, double mass)
    {
        //double force = getDragForce(v, radius);
        //compute_acceleration(force, mass);
        compute_velocity();
        //radians = Trigonometry::getAngle(dx, dy);
    }

    double getGravity() { return gravity * t; }
    void applyGravity() { dy = dy - getGravity(); }

    void compute_acceleration(double force, double mass)
    {
        dv = force / mass;
        ddx = Trigonometry::computeHorizontalComponent(radians, dv) * -1;
        ddy = Trigonometry::computeVerticalComponent(radians, dv) * -1;
    }

    void compute_velocity() 
    {
        dx = dx - (ddx * t);
        dy = dy + (ddy * t);

        applyGravity();

        v = Trigonometry::computeTotalComponent(dx, dy);
    }

    Position compute_location(Position pt)
    {
        pt.addMetersX(dx * t);
        pt.addMetersY(dy * t);
        return pt;
    }

    double get_velocity() { return v; }
    
    double interpolation(double startX, double startY, double endX, double endY, double middleX) {
        return startY + ((middleX -startX)  * (endY - startY)) / (endX - middleX);
    }
    
    
    //Function to calculate density, speed of sound, gravity,
    
    double findDensity(double altitude) {
        double altitudeList[20] = {0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,15000,20000,25000,30000,40000,50000,60000,70000,80000};
        double densityList[20] = {1.225,1.112,1.007,0.9093,0.8194,0.7364,0.6601,0.59,0.5258,0.4671,0.4135,0.1948,0.08891,0.04008,0.184100,0.0039960,0.0010270,0.0003097,0.0000828,0.0000185};
        for (int index = 0; index < 20; index++) {
            if (altitude <= altitudeList[index]) {
                return interpolation(altitudeList[index-1],densityList[index-1],altitudeList[index],densityList[index],altitude);
            }
        }
        return 0.0;
    }
        
    double findGravity(double altitude) {
        double altitudeList[14] = {0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,150000,20000,25000};
        double gravityList[14] = {9.807,9.804,9.801,9.797,9.794,9.791,9.788,9.785,9.782,9.779,9.776,9.761,9.745,9.730};
        for (int index = 0; index < 14; index++) {
            if (altitude <= altitudeList[index]) {
                return interpolation(altitudeList[index-1],gravityList[index-1],altitudeList[index],gravityList[index],altitude);
            }
        }
        return 0.0;
    }
    
    double speedOfSound(double altitude) {
        double altitudesList[16] = {0,1000, 2000, 3000, 4000, 5000, 6000,7000,8000,9000,1000,15000,20000,25000,30000,40000};
        double speedOfSoundList[16] = {340,336,332,328,324,320,316,312,308,303,299,295,295,295,305,324};
        for (int index = 0; index < 16; index++) {
            if (altitude <= altitudesList[index]) {
                return interpolation(altitudesList[index-1],speedOfSoundList[index-1], altitudesList[index],speedOfSoundList[index],altitude);
            }
        }
        return 0.0;
    }
    
    double getDragCoefficient(double v, double speedOfSound) {
        double start;
        double machSpeeds[16] = {0.3, 0.5, 0.7, 0.89, 0.92, 0.96, 0.98, 1.0, 1.02, 1.06, 1.24, 1.53,1.99,2.87,2.89,5.0};
        double dragCoefficient[16] = {0.1629, 0.1659, 0.2031,0.2597,0.3010,0.3287,0.4002,0.4258,0.4335,0.4483,0.4064,0.3663,0.2897,0.2297,0.2306,0.2656};
        for (int index = 0; index < 16; index++) {
            if ((v/speedOfSound) <= machSpeeds[index]) {
                return interpolation(machSpeeds[index-1],dragCoefficient[index-1],machSpeeds[index],dragCoefficient[index],v/speedOfSound);
            }
        }
        return 0.0;
    }

    double getDragForce(double v, double r)
        {
                   //drag co   density
                  //    |      |
                  //    V      V
            return 0.5 * 0.3 * 0.6 * v * v * Trigonometry::areaOfCircle(r);
        }
private:
    double t;
    double radians;
    double gravity;
    double dv;          // Delta Velocity a.k.a. Total Acceleration
    double ddx;         // Horizontal Acceleration
    double ddy;         // Vertical Acceleration
    double v;           // Total Velocity
    double dx;          // Horizontal Velocity
    double dy;          // Vertical Velocity
};
