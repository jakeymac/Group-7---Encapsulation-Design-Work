#include "physics.h"

class PhysicsTester {
public:
    void run() {}

private:
    void test_interpolation() {}
    void test_constructor() {}
    
    
};

class Angle {
    class Angle
    {
    public:
        Angle() { radians = 0.0; }
        Angle(double degrees) { radians = convertToRadians(degrees); }
        Angle(const Angle & r) { radians = r.radians; }
        
        double getDegrees() { return convertToDegrees(radians); }
        double getRadians() const { return radians; }
        void setDegrees(double degrees) { radians = normalize(convertToRadians(degrees)); }
        void setRadians(double radians) { this->radians = normalize(radians); }
        
    private:
        double radians;
        double convertToDegrees(double radians) { return normalize(radians) * 360.0 / TWO_PI; }
        double convertToRadians(double degrees) { return normalize(degrees * TWO_PI / 360.0); }
        double normalize(double radians) { return radians - floor(radians / TWO_PI) * TWO_PI; }
}

class AngleTester {
public:
    void run() {}
    
private:
    void testConstructor() {}
    void testGetDegrees() {}
    void testGetRadians() {}
    void testSetDegrees() {}
    void testSetRadians() {}
    void testNormalize() {}
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
