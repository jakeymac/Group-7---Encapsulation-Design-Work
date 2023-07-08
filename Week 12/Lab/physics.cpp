/***********************************************************************
 * Source File:
 *    Class : brief discription
 * Author:
 *    add author
 * Summary:
 *    add summary
 ************************************************************************/

#include <cassert>
#include <cmath>
#include <iterator>
#include "physics.h"

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

Physics::Physics(double radians, Position p, Ground *pGround) {
    this->radians = radians;
    this->pGround = pGround;
    x = p.getMetersX();
    y = p.getMetersY();
    t = 0.5;
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

    thinkAhead();
}

void Physics::thinkAhead()
{
    for (int i = 0; i < 2; i++) {
        advance();
        if (hitGround()) {
            return;
        }
    }
}

bool Physics::hitGround()
{          // We hit the ground...                          or      // We shot through the green square above the ground
    return pGround->getElevationMeters(Position(x, y)) >= y || computeDistance(pGround->getTarget(), Position(x, y)) < 250.0;
}

bool Physics::hitTarget() {
    return abs(pGround->getTarget().getPixelsX() - x) < 10;
}

void Physics::advance() {
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

    if (hitGround()) {
        finalize();
    }
    else {
        distanceToAltitude.push_back(Position(x, y));
    }
}

void Physics::finalize()
{
    y = pGround->getElevationMeters(Position(x, y));
    distanceToAltitude.push_back(Position(x, y));
}

double Physics::interpolation(double inputMiddle, map<double, double> m) {
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

void Physics::setRo(double altitude) {
    if (altitudeToDensity.find(altitude) != altitudeToDensity.end())
        ro = altitudeToDensity[altitude];
    else
        ro = interpolation(altitude, altitudeToDensity);
}

void Physics::setGravity(double altitude) {
    if (altitudeToGravity.find(altitude) != altitudeToGravity.end())
        gravity = altitudeToGravity[altitude];
    else
        gravity = interpolation(altitude, altitudeToGravity);
}

void Physics::setSpeedOfSound(double altitude) {
    if (altitudeToSound.find(altitude) != altitudeToSound.end())
        speedOfSound = altitudeToSound[altitude];
    else
        speedOfSound = interpolation(altitude, altitudeToSound);
}

void Physics:: setMach() {
    mach = v / speedOfSound;
}

void Physics::setC() {
    if (machToC.find(mach) != machToC.end())
        c = machToC[mach];
    else
        c = interpolation(mach, machToC);
}

void Physics::setDrag() {
    dragForce = 0.5 * c * ro * v * v * area;
}

void Physics::setAcceleration() {
    acceleration = dragForce / mass;
}

void Physics::setAngle() {
    radians = atan2(dx, dy);
}

void Physics::setDdx() {
    ddx = -sin(radians) * acceleration;
}

void Physics::setDdy(){
    ddy = -gravity - cos(radians) * acceleration;
}
