/*************************************************************
 * 1. Name:
 *      Jacob and Jaden
 * 2. Assignment Name:
 *      Practice 06: Templates
 * 3. Assignment Description:
 *      Find the biggest element in an array, and a stack data structure.
 * 4. What was the hardest part? Be as specific as possible.
 *      This assignment was very simple to complete. Converting the function and classes to templates was not difficult at all.
 * 5. How long did it take for you to complete the assignment?
 *      This assignment took about 20 minutes.
 **************************************************************/

#pragma once

#include <iostream>

 /***************************************
  * FIND BIGGEST
  **************************************/
template <class T>
double findBiggest(T array[], int numElements)
{
   double biggest = array[0];
   for (int i = 1; i < numElements; i++)
      if (array[i] > biggest)
         biggest = array[i];

   return biggest;
}

class TestStack;

/***************************************
 * STACK
 **************************************/
template <class T>
class Stack
{
   friend TestStack;
    
public:
   Stack() : numElements(0) {}

   // Add an element to the stack
   void push(const T & value)
   {
      if (numElements < 10)
         data[numElements++] = value;
   }

   // Remove an element from the stack
   void pop()
   {
      if (numElements)
         numElements--;
   }

   // Retrieve the top-most element
   double top()
   {
      if (numElements)
         return data[numElements - 1];
      return 0.0;
   }

private:
   double data[10];
   int numElements;
};
