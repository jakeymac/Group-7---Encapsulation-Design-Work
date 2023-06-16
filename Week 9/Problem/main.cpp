#include <iostream>
#include <cassert>
#include <string>

using namespace std;

double computePay(double hours, double wage)
{
    if (hours < 40.0)
        return hours * wage;
    else
        return (wage * 40.0) + (wage * 1.5 * (hours - 40.0));
}

void test_computePay() {
    //Zeros
    assert(computePay(0.0, 0.0) == 0.0);

    //No time
    assert(computePay(0.0, 8.0) == 0.0);

    //One hour
    assert(computePay(1.0, 8.0) == 8.0);

    //No wage
    assert(computePay(1.0, 0.0) == 0.0);

    //Just under full time
    assert(computePay(39.0, 10.0) == 390.0);

    //Full time
    assert(computePay(40.0, 10.0) == 400.0);

    //One hour overtime
    assert(computePay(41.0, 10.0) == 415.0);

    //Double time
    assert(computePay(80.0, 10.0) == 1000.0);

    //Negative hours
    try {
        computePay(-1.0, 10.0);
        assert(("This line of code should not have been reached, Negative hours should have thrown exception", false));
    }
    catch (string message) {
        assert(message == "Hours cannot be negative");
    }

    //Negative wage
    try {
        computePay(1.0, -8.0);
        assert(("This line of code should not have been reached, Negative wage should have thrown exception", false));
    }
    catch (string message) {
        assert(message == "Wage cannot be negative");
    }

    //Unreasonable hours
    try {
        computePay(168, 10.0);
        assert(("This line of code should not have been reached, Unreasonable hours should have thrown exception", false));
    }
    catch (string message) {
        assert(message == "Unreasonable hours");
    }


    cout << "all tests passed" << endl;


}

class Percent
{
public:
    double percent;              // stored in value 0.0 – 1.0
    Percent() : percent(0.0) {}
    double get() { return percent * 100.0; }
    void set(double input)
    {
        if (input >= 0.0 && input <= 100.0)
            percent = input / 100.0;
    }
};


class TestPercent {
public:
    void test_getter() {
    //Get default

        //Setup
        Percent myPercent = Percent();

        //Exercise 
        double returnValue = myPercent.get();

        //Verify
        assert(returnValue == 0.0);
        assert(myPercent.percent == 0.0);

    //Get 50%

        //Setup
        Percent myPercent = Percent();

        //Exercise 
        double returnValue = myPercent.get();

        //Verify
        assert(returnValue == 0.0);
        assert(myPercent.percent == 0.0);

    //Get 100%

        //Setup
        Percent myPercent = Percent();
        myPercent.percent = 1.0;

        //Exercise 
        double returnValue = myPercent.get();

        //Verify
        assert(returnValue == 100.0);
        assert(myPercent.percent == 1.0);

    }

    void test_setter() {
    //Set 50%

        //Setup
        Percent myPercent = Percent();

        //Exercise 
        myPercent.set(50.0);

        //Verify
        assert(myPercent.percent == 0.5);

    //Set 100%

        //Setup
        Percent myPercent = Percent();

        //Exercise 
        myPercent.set(100.0);

        //Verify
        assert(myPercent.percent == 1.0);

    //Higher than 100%

        //Setup
        Percent myPercent = Percent();

        try {
            //Exercise 
            myPercent.set(101.0);

            //Verify
            assert(("This line of code should not be reached, set(101.0) should throw exception", false));
        }
        catch (string message) {
            assert(message == "Percent cannot be greater than 100");
        }
    }
};

int main()
{
    //test_computePay();
    TestPercent test = TestPercent();
    test.test_getter();

    return 0;
}
