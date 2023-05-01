# Practice 03 : Angle Class

## Program Description

Create a class called Angle which represents an angle. This class will have one attribute: an angle in radians. It will have several public methods:

* getDegrees(): Takes no parameters and return the angle in degrees.
* getRadians(): Takes no parameters and return the angle in radians.
* setDegrees(): Takes a degrees as a parameter and updates the attribute with the passed parameter. If the parameter is above 360 or below zero, then it will "unwrap" so the radians is between 0 and 2π.
* setRadians(): Takes a radian as a parameter and updates the attribute with the passed parameter. If the parameter is above 2π or below zero, then it will "unwrap."
* display(): Takes a ostream & out as a parameter display the value, in degrees, to 1 decimal place of accuracy. This out parameter can be treated exactly the same as cout. You can use it with a.display(cout) if a is the name of your object. Note that you can configure an ostream object like cout to display 1 decimal place of accuracy with:

```
    cout.setf(ios::fixed);     // "fixed" means don't use scientific notation
    cout.setf(ios::showpoint); // "showpoint" means always show the decimal point
    cout.precision(1);         // Set the precision to 1 decimal place of accuracy.
```

The class will also have three private methods:

* convertToDegrees(): Takes a radians as a parameter and returns degrees. Does not utilize the class's attribute.
* convertToRadians(): Takes a degrees as a parameter and returns radians. Does not utilize the class's attribute.
* normalize(): Takes a radian as a parameter and reduce it to between 0 and 2π. For example, 3π will become π, 362° will become 2°, -5° will become 355°, and -7π will become π.

## Test

Please start with the attached files: 230.03.CppClass.zip. Uncompress this ZIP file and open either the .xcode or .sln file (depending on if you are using Xcode on your Apple computer or Visual Studio on your Windows computer). These projects contain the following files:

* angle.h: This is the file that you will edit to create your Angle class. All your code goes here and you will only submit this file.
* testAngle.h: This file is a type of automation called Unit Test. We will learn more about this in Week 09 or in Chapter 25. This will execute a number of tests to ensure your Angle class is correct. Please do not change this file.
* angle.cpp: This file contains main() and will only execute the unit tests. Please do not change this file.
* unitTest.h: This file contains the code which handles unit tests. Basically, it collects errors and displays them in a user-friendly way. Please do not change this file.
* 230.03.Practice.sln and 230.03.Practice.xcodeproj: These are the Visual Studio project files and the xcode project file. Use SLN if you have Visual Studio and use XCODEPROJ is you have Xcode.

## Assignment

Your assignment is to create an Angle to match the program description. Upload your angle.h file here.

|   | Exceptional 100% | Good 90%| Acceptable 70% | Developing 50% | Missing 0% |
| - | ---------------- | ------- | -------------- | -------------- | ---------- |
| Code Quality | Code works and good style was demonstrated | Code works but there are style issues | One or two defects | The problem was attempted | No submission or does not resemble a working solution |	 	 	 	
