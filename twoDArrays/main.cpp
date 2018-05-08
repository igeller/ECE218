#include <iostream>
#include "arrayTemplate.h"

using namespace std;


/**
 * The method is used to multiply two matricies and return their result
 * @param A the matrix variable containing the matrix A
 * @param B the matrix variable containing the matrix B
 * @param result the matrix variable that will hold the result of the matrix multiplication
 * @return result - the matrix holding the result of the multiplication of matrix A * matrix B
 */
twoDArrayHW<int>  &multiply(twoDArrayHW<int> & A, twoDArrayHW<int> & B, twoDArrayHW<int> & result){
    if(A.getCols() != B.getRows()){
        cout << "The number of columns in array " << A.getName() << " is not equal to the number of rows in array "  << B.getName() << " and cannot be multiplied... EXITING\n";
        exit(1);
    }
    result.resize(A.getRows(), B.getCols());
    int aVal =  0, bVal = 0, mult = 0, final = 0;
    for(int rA = 0; rA < A.getRows(); rA++){
        for(int cB = 0; cB < B.getCols(); cB++) {
            for (int cA = 0; cA < A.getCols(); cA++) {
                aVal = A.getVal(rA, cA);            //gets the value of A at (row _, col _)
                bVal = B.getVal(cA, cB);            //gets the value of B (at colA_ , colB_) -- colA = rows of B
                mult = aVal * bVal;
                final += mult;
            }
            result.setVal(rA, cB, final);
            final = 0;
        }
    }
    cout << "Answer:" << endl;
    return result;
}//end multiply



/**prints all the values of the specified array as the matrix would appear*/
void printAll(twoDArrayHW<int>  & M){
    cout << "Printing all the values for the matrix named: " << M.getName() << endl;
    int r = M.getRows(), c = M.getCols();
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << setw(5) << M.getVal(i, j);
        }
        cout << endl;
    }
}//end printAll()





int main() {
    twoDArrayHW<int> result(1, 1, "result");

    //TEST 1: CORRECT DIMENSIONS FOR MULTIPLICATION
    cout << "Test 1: " << endl;
    twoDArrayHW<int> A(2, 3, "A");
    twoDArrayHW<int> B(3, 2, "B");

    A.setVal(0, 0, 1);
    A.setVal(0, 1, 2);
    A.setVal(0, 2, 1);
    A.setVal(1, 0, 2);
    A.setVal(1, 1, 1);
    A.setVal(1, 2, 3);

    B.setVal(0, 0, 2);      B.setVal(0, 1, 1);
    B.setVal(1, 0, 0);      B.setVal(1, 1, 3);
    B.setVal(2, 0, 3);      B.setVal(2, 1, 2);

    printAll(A);
    printAll(B);
    result = multiply(A, B, result);
    printAll(result);
    cout << endl << endl << endl;




    //TEST 2: CORRECT DIMENSIONS FOR MULTIPLICATION
    cout << "Test 2: " << endl;
    twoDArrayHW<int> S(2, 2, "S");
    twoDArrayHW<int> T(2, 3, "T");

    S.setVal(0, 0, 0);       S.setVal(0, 1, 4);
    S.setVal(1, 0, -1);      S.setVal(1, 1, 1);

    T.setVal(0, 0, 6);      T.setVal(0, 1, -3);     T.setVal(0, 2, -4);
    T.setVal(1, 0, 0);      T.setVal(1, 1, 1);      T.setVal(1, 2, -2);


    printAll(S);
    printAll(T);
    result = multiply(S, T, result);
    printAll(result);
    cout << endl << endl << endl;



/*
    //TEST 3: INCORRECT DIMENSIONS FOR MULTIPLICATION
    cout << "Test 3: " << endl;
    twoDArrayHW<int> Q(2, 2, "Q");
    twoDArrayHW<int> R(3, 3, "R");

    Q.setVal(0, 0, 47);      Q.setVal(0, 1, 16);
    Q.setVal(1, 0, -8);      Q.setVal(1, 1, 15);


    R.setVal(0, 0, 6);      R.setVal(0, 1, -3);     R.setVal(0, 2, -4);
    R.setVal(1, 0, 0);      R.setVal(1, 1, 1);      R.setVal(1, 2, -2);
    R.setVal(2, 0, 14);     R.setVal(2, 1, 8);      R.setVal(2, 2, -7);


    printAll(Q);
    printAll(R);
    result = multiply(Q, R, result);
    printAll(result);
*/
}//end main

