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
