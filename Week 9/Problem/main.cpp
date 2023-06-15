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
        assert(("This line of code should not have been reached, Negative wage should have thrown exception",false ));
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

int main()
{
    test_computePay();

    return 0;
}
