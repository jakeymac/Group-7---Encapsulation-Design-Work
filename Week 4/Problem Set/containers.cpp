/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 04: Contaiers
 * 3. Assignment Description:
 *      Work with a list and a vector
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/


#include "testContainers.h"
#include <string>
#include <list>
using namespace std;

list<string> arrayToList(string a[], int num)
{
    list<string> myList = list<string>();

    for (int i = 0; i < num; i++) {
        myList.push_back(a[i]);
    }

    return myList;
}

/*****************************
 * ARRAY TO LIST BACKWARDS
 *****************************/
list<string> arrayToListBackwards(string a[], int num)
{
    list<string> myList = list<string>();

    for (int i = 0; i < num; i++) {
        myList.push_front(a[i]);
    }

    return myList;
}

/*****************************
 * LIST TO VECTOR
 *****************************/
vector<string> listToVector(const list<string> & l)
{
    vector<string> return_vector;
    for (auto iterator = l.begin(); iterator != l.end(); iterator++) {
        return_vector.push_back(*iterator);
    }
    return return_vector;
}

/*****************************
 * LIST TO VECTOR BACKWARDS
 *****************************/
vector<string> listToVectorBackwards(const list<string>& l)
{
    vector<string> return_vector;
    for (auto reverse_iterator = l.rbegin(); reverse_iterator != l.rend(); reverse_iterator++) {
        return_vector.push_back(*reverse_iterator);
    }
    return return_vector;
}

/*****************************
 * FIND ELEMENT IN VECTOR
 *****************************/
bool findElementInVector(const vector<string> & v, const string& element)
{
    for (string item : v) {
        if (element == item) {
            return true;
        }
    }
    return false;
}

/*****************************
 * MAIN
 *****************************/
int main()
{
   TestCollection().run();
   return 0;
}
