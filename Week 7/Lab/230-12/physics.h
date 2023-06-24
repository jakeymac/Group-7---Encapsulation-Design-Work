#pragma once
#include "position.h"
#include "trigonometry.h"
#include <list>
using namespace std;

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

    void compute_physics(double radius, double mass,double density,double dragCoefficient)
    {
        double force = getDragForce(v, radius, density,dragCoefficient);
        compute_acceleration(force, mass);
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
        return startY + ((middleX -startX)  * (endY - startY)) / (endX - startX);
    }
    
    
    double interpolationForX(double startX, double startY, double endX, double endY, double middleY) {
        return startX + (((middleY - startY) * (endX - startX)) / (endY - startY));
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
    
    double getDragCoefficient(double speedOfSound) {
        double machSpeeds[16] = {0.3, 0.5, 0.7, 0.89, 0.92, 0.96, 0.98, 1.0, 1.02, 1.06, 1.24, 1.53,1.99,2.87,2.89,5.0};
        double dragCoefficient[16] = {0.1629, 0.1659, 0.2031,0.2597,0.3010,0.3287,0.4002,0.4258,0.4335,0.4483,0.4064,0.3663,0.2897,0.2297,0.2306,0.2656};
        for (int index = 0; index < 16; index++) {
            if ((v/speedOfSound) <= machSpeeds[index]) {
                return interpolation(machSpeeds[index-1],dragCoefficient[index-1],machSpeeds[index],dragCoefficient[index],v/speedOfSound);
            }
        }
        return 0.0;
    }

    double physicsInterpolation(std::string target, double xValue) {
        std::map<double, double>* targetMap;
        
        std::map<std::string,int> mapList = {
            {"density",0},
            {"gravity",1},
            {"sound",2},
            {"mach",3}
        };
        
        switch (mapList[target]) {
            case 0 :
                targetMap = &altitudeToDensity;
            case 1:
                targetMap = &altitudeToGravity;
            case 2:
                targetMap = &altitudeToSound;
            case 3:
                targetMap = &machToC;
        }
        
        for (targetMap::iterator i = targetMap.begin(); i != targetMap.end(); ++i) {
            if (xValue <= targetMap.first) {
                double secondX = targetMap.first;
                double secondY = targetMap.second;
                i--;
                double firstX = targetMap.first;
                double firstY = targetMap.second;
                return interpolation(firstX,firstY,secondX,secondY,xValue);
            }
        }
    }
    
    std::map<double, double> altitudeToDensity = {
        {0,    1.225},
        {1000,    1.112},
        {2000,    1.007},
        {3000,    0.9093},
        {4000,    0.8194},
        {5000,    0.7364},
        {6000,    0.6601},
        {7000,    0.59},
        {8000,    0.5258},
        {9000,    0.4671},
        {10000,    0.4135},
        {15000,    0.1948},
        {20000,    0.08891},
        {25000,    0.04008},
        {30000,    0.01841},
        {40000,    0.003996},
        {50000,    0.001027},
        {60000,    0.0003097},
        {70000,    0.0000828},
        {80000,    0.0000185}
        };

    std::map<double, double> altitudeToGravity = {
        {0,    9.807},
        {1000,    9.804},
        {2000,    9.801},
        {3000,    9.797},
        {4000,    9.794},
        {5000,    9.791},
        {6000,    9.788},
        {7000,    9.785},
        {8000,    9.782},
        {9000,    9.779},
        {10000,    9.776},
        {15000,    9.761},
        {20000,    9.745},
        {25000,    9.73}
        };

   std:: map<double, double> altitudeToSound{
        {0,    340},
        {1000,    336},
        {2000,    332},
        {3000,    328},
        {4000,    324},
        {5000,    320},
        {6000,    316},
        {7000,    312},
        {8000,    308},
        {9000,    303},
        {10000,    299},
        {15000,    295},
        {20000,    295},
        {25000,    295},
        {30000,    305},
        {40000,    324},
        };

    std::map<double, double> machToC = {
        {0.3,    0.1629},
        {0.5,    0.1659},
        {0.7,    0.2031},
        {0.89,    0.2597},
        {0.92,    0.301},
        {0.96,    0.3287},
        {0.98,    0.4002},
        {1,    0.4258},
        {1.02,    0.4335},
        {1.06,    0.4483},
        {1.24,    0.4064},
        {1.53,    0.3663},
        {1.99,    0.2897},
        {2.87,    0.2297},
        {2.89,    0.2306},
        {5,    0.2656}
    };
    
    double getDragForce(double v, double r,double density, double dragCoefficient)
        {
                   //drag co   density
                  //    |      |
                  //    V      V
            return 0.5 * dragCoefficient * density * v * v * Trigonometry::areaOfCircle(r);
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


