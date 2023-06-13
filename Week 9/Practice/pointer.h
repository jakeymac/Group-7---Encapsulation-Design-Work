/*************************************************************
 * 1. Name:
 *      Jacob Johnson and Jaden Myers
 * 2. Assignment Name:
 *      Practice 09: Pointer Arithmetic
 * 3. Assignment Description:
 *      Traverse a string using pointer notation
 * 4. What was the hardest part? Be as specific as possible.
 *      very nice, yesterday's reading set us up perfectly
 * 5. How long did it take for you to complete the assignment?
 *      10 minutes
 **************************************************************/


/**************************************
 * COUNT - ARRAY
 **************************************/
int countArray(char text[256], char letter) {
    int count = 0;

    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == letter) {
            count++;
        }
    }

    return count;
}

/**************************************
 * COUNT - POINTER
 **************************************/
int countPointer(char text[256], char letter) {
    int count = 0;

    for (char* p = text; *p; p++) {
        if (*p == letter) {
            count++;
        }
    }
    
    return count;
}
