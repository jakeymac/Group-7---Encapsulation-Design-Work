

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
#include "physics.h"
#include "tester.h"

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

    void PhysicsTester::run() {
        test_interpolation();
        test_constructor();
        cout << "all tests passed" << endl;
    }


    void PhysicsTester::test_interpolation() {
        Bullet b = Bullet(0.523599, 0, 0);
        //First entry in table
        assert(b.interpolation(0, altitudeToDensity) == 1.225);
        //Lower than altitude 0
        assert(b.interpolation(-1, altitudeToDensity) == 1.225);
        //Last entry in table
        assert(b.interpolation(80000, altitudeToDensity) == 0.0000185);
        //Higher than altitude 80,000
        assert(b.interpolation(100000, altitudeToDensity) == 0.0000185);
        //altitude between 0 and 1000
        double value = b.interpolation(500, altitudeToDensity);
        assert(value > 1.112 && value < 1.225);
        //altitude between 1000 and 2000
        value = b.interpolation(1500, altitudeToDensity);
        assert(value > 1.007 && value < 1.112);
        //altitude between 2000 and 3000
        value = b.interpolation(2500, altitudeToDensity);
        assert(value > 0.9093 && value < 1.007);
        //altitude between 3000 and 4000
        value = b.interpolation(3500, altitudeToDensity);
        assert(value > 0.8194 && value < 0.9093);
        //compare two different altitudes between 3000 and 4000
        double v1 = b.interpolation(3400, altitudeToDensity);
        double v2 = b.interpolation(3600, altitudeToDensity);
        assert(v1 > v2);



    }
    void PhysicsTester::test_constructor() {
        //Whiteboard demo
        Bullet b = Bullet(0.523599, 0, 0);
        assert(b.v == 827);
        assert(b.dx > 413.4 && b.dx < 413.6);
        assert(b.dy > 716.202 && b.dy < 716.204);
        assert(b.ro == 1.225);
        assert(b.gravity == 9.807);
        assert(b.speedOfSound == 340.0);
        assert(b.mach > 2.43234 && b.mach < 2.43236);
        assert(b.c > 0.25953 && b.c < 0.25955);
        assert(b.dragForce > 2048.5 && b.dragForce < 2048.7);
        assert(b.acceleration > 43.8672 && b.acceleration < 43.8674);
        assert(b.ddx > -21.9337 && b.ddx < - 21.9335);
        assert(b.ddy > -47.7973 && b.ddy < - 47.7971);

        //Altitude in data tables 
        b = Bullet(0.523599, 0, 1000);
        assert(b.v == 827);
        assert(b.dx > 413.4 && b.dx < 413.6);
        assert(b.dy > 716.202 && b.dy < 716.204);
        assert(b.ro == 1.112);
        assert(b.gravity == 9.804);
        assert(b.speedOfSound == 336.0);
        assert(b.mach > 2.46130 && b.mach < 2.46132);
        assert(b.c > 0.257564 && b.c < 0.257566);
        assert(b.dragForce > 1845.47 && b.dragForce < 1845.49);
        assert(b.acceleration > 39.5177 && b.acceleration < 39.5179);
        assert(b.ddx > -19.7590 && b.ddx < -19.7588);
        assert(b.ddy > -44.0275 && b.ddy < -44.0273);

        //Interpolation needed
        b = Bullet(0.523599, 0, 1500);
        assert(b.v == 827);
        assert(b.dx > 413.4 && b.dx < 413.6);
        assert(b.dy > 716.202 && b.dy < 716.204);
        assert(b.ro > 1.0594 && b.ro < 1.0596);
        assert(b.gravity > 9.8024 && b.gravity < 9.8026);
        assert(b.speedOfSound == 334.0);
        assert(b.mach > 2.47604 && b.mach < 2.47606);
        assert(b.c > 0.25655 && b.c < 0.25657);
        assert(b.dragForce > 1751.48 && b.dragForce < 1751.50);
        assert(b.acceleration > 37.5051 && b.acceleration < 37.5053);
        assert(b.ddx > -18.7527 && b.ddx < -18.7525);
        assert(b.ddy > -42.2830 && b.ddy < -42.2828);

        //Input zeros 
        b = Bullet(0.0, 0, 0);
        assert(b.v == 827);
        assert(b.dx == 0.0);
        assert(b.dy == 827);
        assert(b.ro == 1.225);
        assert(b.gravity == 9.807);
        assert(b.speedOfSound == 340.0);
        assert(b.mach > 2.43234 && b.mach < 2.43236);
        assert(b.c > 0.25953 && b.c < 0.25955);
        assert(b.dragForce > 2048.5 && b.dragForce < 2048.7);
        assert(b.acceleration > 43.8672 && b.acceleration < 43.8674);
        assert(b.ddx == 0);
        assert(b.ddy > -53.6744 && b.ddy < -53.6742);

        //Max Altitude
        b = Bullet(0.523599, 0, 80000);
        assert(b.v == 827);
        assert(b.dx > 413.4 && b.dx < 413.6);
        assert(b.dy > 716.202 && b.dy < 716.204);
        assert(b.ro > 1.84e-05 && b.ro < 1.86e-05);
        assert(b.gravity > 9.72 && b.gravity < 9.74);
        assert(b.speedOfSound == 324.0);
        assert(b.mach > 2.55246 && b.mach < 2.55248);
        assert(b.c > 0.25134 && b.c < 0.25136);
        assert(b.dragForce > 0.0299617 && b.dragForce < 0.0299619);
        assert(b.acceleration > 0.00064157 && b.acceleration < 0.00064159);
        assert(b.ddx > -0.00032080 && b.ddx < -0.00032078);
        assert(b.ddy > -9.73057 && b.ddy < -9.73055);

        //Side shot
        b = Bullet(1.570796, 0, 0);
        assert(b.v == 827);
        assert(b.dx > 826.9 && b.dx < 827.1);
        assert(b.dy > -0.1 && b.dy < 0.1);
        assert(b.ro == 1.225);
        assert(b.gravity == 9.807);
        assert(b.speedOfSound == 340.0);
        assert(b.mach > 2.43234 && b.mach < 2.43236);
        assert(b.c > 0.25953 && b.c < 0.25955);
        assert(b.dragForce > 2048.5 && b.dragForce < 2048.7);
        assert(b.acceleration > 43.8672 && b.acceleration < 43.8674);
        assert(b.ddx > -43.8674 && b.ddx < -43.8672);
        assert(b.ddy > -9.808 && b.ddy < -9.806);

    }
};


void AngleTester::run() {
    testConstructor();
    testGetDegrees();
    testGetRadians();
    testSetDegrees();
    testSetRadians();
    testNormalize();
}


void AngleTester::testConstructor() {
    Angle tester = Angle();
    assert(tester.radians == 0.0);
    delete tester;
    
    Angle tester = Angle(120);
    assert(tester.radians == 2.094);
    delete tester;
    
    Angle tester = Angle(430);
    assert(tester.radians == 7.505);
    delete tester;
    
    Angle tester = Angle(0);
    assert(tester.radians == 0.0);
    delete tester;
    
    Angle tester = Angle(-120);
    assert(tester.radians == -2.094);
    delete tester;
    
    Angle tester = Angle(720);
    assert(tester.radians == 12.566);
    delete tester;
}

void AngleTester::testGetDegrees() {
    Angle tester = Angle();
    
    tester.radians = 0.0;
    assert(tester.getDegrees() == 0.0);
    
    tester.radians = 10.0;
    assert(tester.getDegrees() == 572.958);
    
    tester.radians = -15.0;
    assert(tester.getDegrees() == -859.437);
    
    tester.radians = 2.0;
    assert(tester.getDegrees() == 114.592);
    
    tester.radians = 3.7;
    assert(tester.getDegrees() == 211.994);
    
    tester.radians = 4.3;
    assert(tester.getDegrees() == 246.372);
    
    delete tester;
}

void AngleTester::testGetRadians() {
    Angle tester = Angle();
    
    tester.radians = 0.0;
    assert(tester.getRadians() == 0.0);
    
    tester.radians = 10.0;
    assert(tester.getRadians() == 10.0);
    
    tester.radians = -15.0;
    assert(tester.getRadians() == -15.0);
    
    tester.radians = 2.0;
    assert(tester.getRadians() == 2.0);
    
    tester.radians = 3.7;
    assert(tester.getRadians() == 3.7);
    
    tester.radians = 4.3;
    assert(tester.getRadians() == 4.3);
    
    delete tester;
}

void AngleTester::testSetDegrees() {
    Angle tester = Angle();
    
    tester.setDegrees(0.0);
    assert(tester.radians == 0.0);
    assert(tester.getDegrees() == 0.0);
    
    tester.setDegrees(5.0);
    assert(tester.radians == 0.087);
    assert(tester.getDegrees() == 5.0);
    
    tester.setDegrees(360.0);
    assert(tester.radians == 6.283);
    assert(tester.getDegrees() == 360.0);
    
    tester.setDegrees(-125.0);
    assert(tester.radians == -2.181);
    assert(tester.getDegrees() == -125.0);
    
    tester.setDegrees(290.3);
    assert(tester.radians == 5.067);
    assert(tester.getDegrees() == 290.3);
    
    tester.setDegrees(39.25);
    assert(tester.radians == 0.685);
    assert(tester.getDegrees() == 39.25);
    
    tester.setDegrees(-212.3);
    assert(tester.radians == -3.705);
    assert(tester.getDegrees() == -212.3);
    
    delete tester;
}


void AngleTester::testSetRadians() {
    Angle tester = Angle();
    
    tester.setRadians(0.0);
    assert(tester.radians == 0.0);
    
    tester.setRadians(5.0);
    assert(tester.radians == 5.0);
    
    tester.setRadians(3.0);
    assert(tester.radians == 3.0;
    
    tester.setRadians(-15.3);
    assert(tester.radians == -15.3);
    
    tester.setRadians(2.9);
    assert(tester.radians == 2.9);

    tester.setRadians(-1.5);
    assert(tester.radians == -1.5);
    
    tester.setRadians(-2);
    assert(tester.radians == -2);
    
    delete tester;
}

void AngleTester::testNormalize() {
        Angle tester = Angle();
        
        assert(tester.normalize(0.0) == 0.0);
        assert(tester.normalize(3.142) == 3.142);
        assert(tester.normalize(6.283) == 6.283);
        assert(tester.normalize(5.2) == 5.2);
        assert(tester.normalize(15.0) == 2.434);
        assert(tester.normalize(-3.142) == -3.142);
        assert(tester.normalize(-5.2) == -5.2);
        
        delete tester;
    }


