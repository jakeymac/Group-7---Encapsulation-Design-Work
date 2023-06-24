

#define _USE_MATH_DEFINES

#include <iostream>  // for CIN and COUT
#include <string>
#include <cmath>
#include <numbers>
#include<list>
#include <cmath>
#include <map>
#include <iterator>
#include <cassert>

using namespace std;

map<double, double> altitudeToDensity = {
    {0,	    1.225},
    {1000,	1.112},
    {2000,	1.007},
    {3000,	0.9093},
    {4000,	0.8194},
    {5000,	0.7364},
    {6000,	0.6601},
    {7000,	0.59},
    {8000,	0.5258},
    {9000,	0.4671},
    {10000,	0.4135},
    {15000,	0.1948},
    {20000,	0.08891},
    {25000,	0.04008},
    {30000,	0.01841},
    {40000,	0.003996},
    {50000,	0.001027},
    {60000,	0.0003097},
    {70000,	0.0000828},
    {80000,	0.0000185}
};

map<double, double> altitudeToGravity = {
    {0,	    9.807},
    {1000,	9.804},
    {2000,	9.801},
    {3000,	9.797},
    {4000,	9.794},
    {5000,	9.791},
    {6000,	9.788},
    {7000,	9.785},
    {8000,	9.782},
    {9000,	9.779},
    {10000,	9.776},
    {15000,	9.761},
    {20000,	9.745},
    {25000,	9.73}
};

map<double, double> altitudeToSound{
    {0,	    340},
    {1000,	336},
    {2000,	332},
    {3000,	328},
    {4000,	324},
    {5000,	320},
    {6000,	316},
    {7000,	312},
    {8000,	308},
    {9000,	303},
    {10000,	299},
    {15000,	295},
    {20000,	295},
    {25000,	295},
    {30000,	305},
    {40000,	324}
};

map<double, double> machToC = {
    {0.3,	0.1629},
    {0.5,	0.1659},
    {0.7,	0.2031},
    {0.89,	0.2597},
    {0.92,	0.301},
    {0.96,	0.3287},
    {0.98,	0.4002},
    {1,	    0.4258},
    {1.02,	0.4335},
    {1.06,	0.4483},
    {1.24,	0.4064},
    {1.53,	0.3663},
    {1.99,	0.2897},
    {2.87,	0.2297},
    {2.89,	0.2306},
    {5,	    0.2656}
};



class Physics {
    //friend Tester;
public:
    Physics(double radians, double x, double y) {
        this->radians = radians;
        this->x = x;
        this->y = y;
        t = 0.01;
        hangTime = 0.0;
        v = 827;
        dx = sin(radians) * v;
        dy = cos(radians) * v;
        mass = 46.7;
        radius = 0.077445;
        area = 0.018842418;
        setRo(y);
        setGravity(y);
        setSpeedOfSound(y);
        setMach();
        setC();
        setDrag();
        setAcceleration();
        setDdx();
        setDdy();
    }

    double getAltitude() {
        return y;
    }

    //This method has no unit tests
    void fire() {

        while (y > 0.0) {
            advance();
        }

        double impactAltitude = 0.0;
        y = impactAltitude;

        hangTime = interpolation_reversed(impactAltitude, hangTimeToAltitude);
        
        double impactDistance = interpolation(hangTime, hangTimeToDistance);
        x = impactDistance;

        assert(hangTimeToAltitude.size() == hangTimeToDistance.size());

        map<double, double>::iterator itA = hangTimeToAltitude.begin();
        map<double, double>::iterator itD = hangTimeToDistance.begin();

        while (itA != hangTimeToAltitude.end() && itD != hangTimeToDistance.end()) {
            if (itA->second > 0.0) {
                distanceToAltitude.insert({ itD->second, itA->second });
            }
            else {
                distanceToAltitude.insert({ impactDistance, impactAltitude });
            }
            itA++;
            itD++;
        }

    }

    void display() {
        cout << "Distance: " << x << " Altitude: " << y << " Hang time: " << hangTime << endl;
    }

//private:
    double x;
    double y;
    double t;
    double hangTime;
    double radians;
    double gravity;
    double ddx;         // Horizontal Acceleration
    double ddy;         // Vertical Acceleration
    double v;           // Total Velocity
    double dx;          // Horizontal Velocity
    double dy;          // Vertical Velocity
    double mass;
    double radius;
    double area;
    double ro;
    double c;
    double speedOfSound;
    double mach;
    double dragForce;
    double acceleration;
    map<double, double> hangTimeToAltitude;
    map<double, double> hangTimeToDistance;
    map<double, double> distanceToAltitude;

    //This method doesn't have any unit tests
    void advance() {
        x = x + dx * t;
        y = y + dy * t;

        hangTime = hangTime + t;

        dx = dx + ddx * t;
        dy = dy + ddy * t;

        v = sqrt(dx * dx + dy * dy);

        setRo(y);
        setGravity(y);
        setSpeedOfSound(y);
        setMach();
        setC();
        setDrag();
        setAcceleration();
        setAngle();
        setDdx();
        setDdy();
        hangTimeToAltitude.insert({ hangTime,y });
        hangTimeToDistance.insert({ hangTime,x });

        assert(hangTimeToAltitude.size() == hangTimeToDistance.size());
    }

    double interpolation(double inputMiddle, map<double, double> m) {

        map<double, double>::iterator it = m.begin();

        if (inputMiddle <= it->first)
            return it->second;

        double inputBegin = 0.0;
        double inputEnd = 0.0;
        double outputBegin = 0.0;
        double outputEnd = 0.0;

        while (it != m.end()) {
            if (it->first > inputMiddle)
            {
                inputEnd = it->first;
                outputEnd = it->second;
                it--;
                inputBegin = it->first;
                outputBegin = it->second;
                break;
            }
            it++;
        }

        if (it == m.end()) {
            it--;
            return it->second;
        }

        return outputBegin + (inputMiddle - inputBegin) * (outputEnd - outputBegin) / (inputEnd - inputBegin);
    }

    //This method doesn't have any unit tests
    double interpolation_reversed(double outputMiddle, map<double, double> m) {

        map<double, double>::iterator it = m.end();
        it--;

        double inputEnd = it->first;
        double outputEnd = it->second;

        it--; 

        double inputBegin = it->first;
        double outputBegin = it->second;

        return inputBegin + (outputMiddle - outputBegin) * (inputEnd - inputBegin) / (outputEnd - outputBegin);
    }

    void setRo(double altitude) {
        if (altitudeToDensity.find(altitude) != altitudeToDensity.end())
            ro = altitudeToDensity[altitude];
        else
            ro = interpolation(altitude, altitudeToDensity);
    }

    void setGravity(double altitude) {
        if (altitudeToGravity.find(altitude) != altitudeToGravity.end())
            gravity = altitudeToGravity[altitude];
        else
            gravity = interpolation(altitude, altitudeToGravity);
    }

    void setSpeedOfSound(double altitude) {
        if (altitudeToSound.find(altitude) != altitudeToSound.end())
            speedOfSound = altitudeToSound[altitude];
        else
            speedOfSound = interpolation(altitude, altitudeToSound);
    }

    void setMach() {
        mach = v / speedOfSound;
    }

    void setC() {
        if (machToC.find(mach) != machToC.end())
            c = machToC[mach];
        else
            c = interpolation(mach, machToC);
    }

    void setDrag() {
        dragForce = 0.5 * c * ro * v * v * area;
    }

    void setAcceleration() {
        acceleration = dragForce / mass;
    }

    void setAngle() {
        radians = atan2(dx, dy);
    }

    void setDdx() {
        ddx = -sin(radians) * acceleration;
    }

    void setDdy() {
        ddy = -gravity -cos(radians) * acceleration;
    }
};

class Tester {
public:
    void run() {
        test_interpolation();
        test_constructor();
        cout << "all tests passed" << endl;
    }

private:
    void test_interpolation() {
        Physics physics = Physics(0.523599, 0, 0);
        //First entry in table
        assert(physics.interpolation(0, altitudeToDensity) == 1.225);
        //Lower than altitude 0
        assert(physics.interpolation(-1, altitudeToDensity) == 1.225);
        //Last entry in table
        assert(physics.interpolation(80000, altitudeToDensity) == 0.0000185);
        //Higher than altitude 80,000
        assert(physics.interpolation(100000, altitudeToDensity) == 0.0000185);
        //altitude between 0 and 1000
        double value = physics.interpolation(500, altitudeToDensity);
        assert(value > 1.112 && value < 1.225);
        //altitude between 1000 and 2000
        value = physics.interpolation(1500, altitudeToDensity);
        assert(value > 1.007 && value < 1.112);
        //altitude between 2000 and 3000
        value = physics.interpolation(2500, altitudeToDensity);
        assert(value > 0.9093 && value < 1.007);
        //altitude between 3000 and 4000
        value = physics.interpolation(3500, altitudeToDensity);
        assert(value > 0.8194 && value < 0.9093);
        //compare two different altitudes between 3000 and 4000
        double v1 = physics.interpolation(3400, altitudeToDensity);
        double v2 = physics.interpolation(3600, altitudeToDensity);
        assert(v1 > v2);



    }
    void test_constructor() {
        //Whiteboard demo
        Physics physics = Physics(0.523599, 0, 0);
        assert(physics.v == 827);
        assert(physics.dx > 413.4 && physics.dx < 413.6);
        assert(physics.dy > 716.202 && physics.dy < 716.204);
        assert(physics.ro == 1.225);
        assert(physics.gravity == 9.807);
        assert(physics.speedOfSound == 340.0);
        assert(physics.mach > 2.43234 && physics.mach < 2.43236);
        assert(physics.c > 0.25953 && physics.c < 0.25955);
        assert(physics.dragForce > 2048.5 && physics.dragForce < 2048.7);
        assert(physics.acceleration > 43.8672 && physics.acceleration < 43.8674);
        assert(physics.ddx > -21.9337 && physics.ddx < - 21.9335);
        assert(physics.ddy > -47.7973 && physics.ddy < - 47.7971);

        //Altitude in data tables 
        physics = Physics(0.523599, 0, 1000);
        assert(physics.v == 827);
        assert(physics.dx > 413.4 && physics.dx < 413.6);
        assert(physics.dy > 716.202 && physics.dy < 716.204);
        assert(physics.ro == 1.112);
        assert(physics.gravity == 9.804);
        assert(physics.speedOfSound == 336.0);
        assert(physics.mach > 2.46130 && physics.mach < 2.46132);
        assert(physics.c > 0.257564 && physics.c < 0.257566);
        assert(physics.dragForce > 1845.47 && physics.dragForce < 1845.49);
        assert(physics.acceleration > 39.5177 && physics.acceleration < 39.5179);
        assert(physics.ddx > -19.7590 && physics.ddx < -19.7588);
        assert(physics.ddy > -44.0275 && physics.ddy < -44.0273);

        //Interpolation needed
        physics = Physics(0.523599, 0, 1500);
        assert(physics.v == 827);
        assert(physics.dx > 413.4 && physics.dx < 413.6);
        assert(physics.dy > 716.202 && physics.dy < 716.204);
        assert(physics.ro > 1.0594 && physics.ro < 1.0596);
        assert(physics.gravity > 9.8024 && physics.gravity < 9.8026);
        assert(physics.speedOfSound == 334.0);
        assert(physics.mach > 2.47604 && physics.mach < 2.47606);
        assert(physics.c > 0.25655 && physics.c < 0.25657);
        assert(physics.dragForce > 1751.48 && physics.dragForce < 1751.50);
        assert(physics.acceleration > 37.5051 && physics.acceleration < 37.5053);
        assert(physics.ddx > -18.7527 && physics.ddx < -18.7525);
        assert(physics.ddy > -42.2830 && physics.ddy < -42.2828);

        //Input zeros 
        physics = Physics(0.0, 0, 0);
        assert(physics.v == 827);
        assert(physics.dx == 0.0);
        assert(physics.dy == 827);
        assert(physics.ro == 1.225);
        assert(physics.gravity == 9.807);
        assert(physics.speedOfSound == 340.0);
        assert(physics.mach > 2.43234 && physics.mach < 2.43236);
        assert(physics.c > 0.25953 && physics.c < 0.25955);
        assert(physics.dragForce > 2048.5 && physics.dragForce < 2048.7);
        assert(physics.acceleration > 43.8672 && physics.acceleration < 43.8674);
        assert(physics.ddx == 0);
        assert(physics.ddy > -53.6744 && physics.ddy < -53.6742);

        //Max Altitude
        physics = Physics(0.523599, 0, 80000);
        assert(physics.v == 827);
        assert(physics.dx > 413.4 && physics.dx < 413.6);
        assert(physics.dy > 716.202 && physics.dy < 716.204);
        assert(physics.ro > 1.84e-05 && physics.ro < 1.86e-05);
        assert(physics.gravity > 9.72 && physics.gravity < 9.74);
        assert(physics.speedOfSound == 324.0);
        assert(physics.mach > 2.55246 && physics.mach < 2.55248);
        assert(physics.c > 0.25134 && physics.c < 0.25136);
        assert(physics.dragForce > 0.0299617 && physics.dragForce < 0.0299619);
        assert(physics.acceleration > 0.00064157 && physics.acceleration < 0.00064159);
        assert(physics.ddx > -0.00032080 && physics.ddx < -0.00032078);
        assert(physics.ddy > -9.73057 && physics.ddy < -9.73055);

        //Side shot
        physics = Physics(1.570796, 0, 0);
        assert(physics.v == 827);
        assert(physics.dx > 826.9 && physics.dx < 827.1);
        assert(physics.dy > -0.1 && physics.dy < 0.1);
        assert(physics.ro == 1.225);
        assert(physics.gravity == 9.807);
        assert(physics.speedOfSound == 340.0);
        assert(physics.mach > 2.43234 && physics.mach < 2.43236);
        assert(physics.c > 0.25953 && physics.c < 0.25955);
        assert(physics.dragForce > 2048.5 && physics.dragForce < 2048.7);
        assert(physics.acceleration > 43.8672 && physics.acceleration < 43.8674);
        assert(physics.ddx > -43.8674 && physics.ddx < -43.8672);
        assert(physics.ddy > -9.808 && physics.ddy < -9.806);
    }
};

int main()
{
    //This code is for the prototype exercise that has a hang time of 33.5 seconds
    //double radians = 75.0 * M_PI / 180.0;
    //Physics physics = Physics(radians, 0, 0.000001);
    //physics.fire();
    //physics.display();

    Tester t = Tester();
    t.run();
    
    

    return 0;
}
