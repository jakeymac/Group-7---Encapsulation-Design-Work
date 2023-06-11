

#define _USE_MATH_DEFINES

#include <iostream>  // for CIN and COUT
#include <string>
#include <cmath>
#include <numbers>
#include<list>
#include <cmath>
#include <map>
#include <iterator>

using namespace std;

map<double, double> altitudeToDensity = {
    {0,	1.225},
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
    {0,	9.807},
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
    {0,	340},
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
{40000,	324},
};

map<double, double> machToC = {
    {0.3,	0.1629},
{0.5,	0.1659},
{0.7,	0.2031},
{0.89,	0.2597},
{0.92,	0.301},
{0.96,	0.3287},
{0.98,	0.4002},
{1,	0.4258},
{1.02,	0.4335},
{1.06,	0.4483},
{1.24,	0.4064},
{1.53,	0.3663},
{1.99,	0.2897},
{2.87,	0.2297},
{2.89,	0.2306},
{5,	0.2656}
};

class Bullet {
public:
    Bullet(double radians, double x, double y) {
        this->radians = radians;
        this->x = x;
        this->y = y;
        t = 1.0;
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

    void display() {
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
        cout << "radians: " << radians << endl;
        cout << "t: " << t << endl;
        cout << "v: " << v << endl;
        cout << "dx: " << dx << endl;
        cout << "dy: " << dy << endl;
        cout << "mass: " << mass << endl;
        cout << "radius: " << radius << endl;
        cout << "area: " << area << endl;
        cout << "ro: " << ro << endl;
        cout << "gravity: " << gravity << endl;
        cout << "speedSound: " << speedOfSound << endl;
        cout << "mach: " << mach << endl;
        cout << "c: " << c << endl;
        cout << "drag: " << dragForce << endl;
        cout << "acceleration: " << acceleration << endl;
        cout << "ddx: " << ddx << endl;
        cout << "ddy: " << ddy << endl;

    }
private:
    double x;
    double y;
    double t;
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

    double interpolation(double inputMiddle, map<double, double> m) {

        map<double, double>::iterator it = m.begin();
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

    void setDdx() {
        ddx = -sin(radians) * acceleration;
    }

    void setDdy() {
        ddy = -gravity -cos(radians) * acceleration;
    }
};


int main()
{
    // these are the conditions used by the Demo video last week:
    Bullet bullet = Bullet(0.523598776, 0, 0);
    bullet.display();
    // check to see if they match up!!!
    
    return 0;
}
