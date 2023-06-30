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
    void run() {
        testConstructor();
        testGetDegrees();
        testGetRadians();
        testSetDegrees();
        testSetRadians();
        testNormalize();
        std::cout << "All tests passed" << std::endl;
    }


private:
    void testConstructor() {
        Angle tester = Angle();
        assert(tester.radians == 0.0);
        delete tester;
        
        tester = Angle(120);
        assert(tester.radians == 2.094);
        
        tester = Angle(430);
        assert(tester.radians == 7.505);
        
        tester = Angle(0);
        assert(tester.radians == 0.0);
        
        tester = Angle(-120);
        assert(tester.radians == -2.094);
        
        tester = Angle(720);
        assert(tester.radians == 12.566);
        
        delete tester;
    }

    void testGetDegrees() {
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

    void testGetRadians() {
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

     void testSetDegrees() {
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


     void testSetRadians() {
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

        void testNormalize() {
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
