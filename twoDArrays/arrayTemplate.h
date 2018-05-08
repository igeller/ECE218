#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

template <typename T>

class twoDArrayHW{
protected:
    int rows, cols, r, c;
    string name;
    //T * data = new T [0];
    T * data;

public:

    /** Makes the array of the specified size,
     * as explicitly stated, or as the user
     * defines with the previous constructor*/
    twoDArrayHW(int size1, int size2, string n){
        rows = size1;
        cols = size2;
        name = n;
        data = new T [rows*cols];
        //addToArray(, data);
    }//end constructor


    /** the destructor, to clean up */
    ~twoDArrayHW(){
        cout << "Matrix is being deleted\n";
        delete [] data;
    }//end destructor



    //SETTER METHODS
    /** allows the user to set all the values of the specified array
     * especially to be used after the creation of a new empty array*/
    void setAll(){
        cout << "Setting all Values of the Array:";
        int r = getRows();
        int c = getCols();
        int v;
        cout << "The array has " << getRows() << " rows and " << getCols() << " columns\n";
        for(int i = 0; i < getRows(); i++){
            for(int j = 0; j < getCols(); j++){
                cout <<  "row: " <<  i << " cols: " << j << " Set a value for this position: ";
                cin >> v;
                data[i * getCols() + j] = v;
            }
        }
    }//end setAll()

    /** allows the user to explicitly set a single specified
     * value of a single specified array, wihtout needing their
     * interaction*/
    void setVal(int r, int c, int v){
        if(r >= 0 || r < getRows() || c >= 0 || c < getCols())
            data[r * getCols() + c] = v;
        else{
            if(r < 0 || r >= rows)
                cout << "r must be between 0 and " << rows -1 << endl;
            else if (c < 0 || c >= cols){
                cout << "c must be between 0 and " << cols -1 << endl;
            }
        }
    }//end setVal()




    //GET METHODS


    /**returns the value of the specified
     * @param r row location
     * @param c column location
     * @return value at specified location
     */
    int getVal(int r, int c) {
        if (r >= 0 || r < getRows() || c >= 0 || c < getCols()) {
            return data[r * getCols() + c];
        } else {
            cout << "index out of bounds\n";
            abort();
        }
    }

    /**returns the number of columns
     * in the specified array*/
    int getCols(){
        return cols;
    }//end getCols()

    /**returns the number of rows
     * in the specified array*/
    int getRows(){
        return rows;
    }//end getRows()

    /**returns the name of
     * the specified array*/
    string getName(){
        return name;
    }//end getName



    /** resizes the result array to be able to
     * contain the answer of the matrix multiplication*/
    void resize(int newSize1, int newSize2){
        rows = newSize1;
        cols = newSize2;
    }//end resize

};
