/*************************************************************
 * 1. Name:
 *      Jacob and Jaden
 * 2. Assignment Name:
 *      Practice 08: Allocation
 * 3. Assignment Description:
 *      Allocate an array and then use it
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

 /****************************
  * ALLOCATE ONE FLOAT
  ****************************/
float * allocateOneFloat(float input) {
    float * returnPtr = new float(input);
    return returnPtr;
}


/****************************
 * ALLOCATE ARRAY of DOUBLEs
 ****************************/
double * allocateArrayDouble(int num) {
    if (num > 0) {
        double * return_array = new double[num];
        return return_array;
    } else {
        return nullptr;
    }
}

/****************************
 * DELETE ONE FLOAT
 ****************************/
void deleteOneFloat(float *&input) {
    if (input != nullptr) {
        delete input;
        input = nullptr;
        
    }
    
}

/****************************
 * DELETE ARRAY of DOUBLEs
 ****************************/
void deleteArrayDouble(double *&input) {
    if (input != nullptr) {
        delete input;
        input = nullptr;
    }
    
}
