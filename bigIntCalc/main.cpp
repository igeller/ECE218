#include <iostream>
#include <vector>

using namespace std;

class BigInt: public vector<int>
{
    // I am definitng a new class called "bigint", but
    // it borrows and contains the definitions of everything
    // that is inside a vector<int>
    // this is called INHERITANCE

public:
    //Using Dr. Murrells Class for BigInts Add and subtract and the basic functions
    bool negative;

    BigInt()
    { negative = false; }

    void become(string s)
    { clear();
        int end = 0;
        if (s[0] == '-')
        { end = 1;
            negative = true; }
        else if (s[0] == '+')
            end = 1;


        for (int i = s.length()-1; i >= end; i -= 1)
        { int digval = s[i] - '0';
            if (digval < 0 || digval > 9)
            { cerr << "invalid digit\n";
                exit(1); }
            push_back(digval); } }

    void debug()
    { for (int i = 0; i < size(); i += 1)
            cout << i << ": " << at(i) << ", ";
        if (negative)
            cout << "(negative)";
        cout << "\n"; }

    void print()
    {  //added the J variable, so I could limit the number of elements printed per
        //line
        int j = 0;
        if (negative)
            cout << "-";
        for (int i = size()-1; i >= 0; i -= 1){
            cout << at(i);
            j++;
            if(j % 60 == 0)
                cout << endl;
        }

        cout << "\n"; }

    int get_digit(int pos)
    { if (pos >= size())
            return 0;
        return at(pos); }

    void set_digit(int pos, int newval)
    { if (pos == size())
            push_back(newval);
        else
            at(pos) = newval; }

    void increment()
    { int pos = 0;
        while (get_digit(pos) == 9)
        { set_digit(pos, 0);
            pos += 1; }
        set_digit(pos, get_digit(pos)+1); }

    void nines_comp()
    { for (int i = 0; i < size(); i += 1)
            set_digit(i, 9 - get_digit(i)); }

    void trim_leading_zeros() {
        int x = size()-1;

        while(get_digit(x) == 0){
            pop_back();
            x--;
        }
    }

    void add_ignoring_signs(BigInt & A, BigInt & B)
    // assumes A and B are positive, even if they aren't
    { // reference just to avoid wasting time coping,
        // we will not change A or B
        clear();
        int pos = 0, carry = 0;
        while (pos < A.size() || pos < B.size() || carry > 0)
        { int sum = A.get_digit(pos) + B.get_digit(pos) + carry;
            carry = sum / 10;
            push_back(sum % 10);
            pos += 1; }
    }

    void subtract_ignoring_signs(BigInt & A, BigInt & B)
    { // reference just to avoid wasting time coping,
        // we will not change A or B
        clear();
        int pos = 0, borrow = 0;
        while (pos < A.size() || pos < B.size())
        { int diff = A.get_digit(pos) - B.get_digit(pos) - borrow;
            if (diff < 0)
            { diff += 10;
                borrow = 1; }
            else
                borrow = 0;
            push_back(diff);
            pos += 1;
        }
       if (borrow != 0)
        { cout << "Borrow still set\n";
            nines_comp();
            increment();
            negative = true; }
        trim_leading_zeros();
    }


    void add(BigInt & A, BigInt & B) {
        if (A.negative && B.negative)
        { add_ignoring_signs(A, B);
            negative = true; }
        else if (A.negative)
            subtract_ignoring_signs(B, A);
        else if (B.negative)
            subtract_ignoring_signs(A, B);
        else
            add_ignoring_signs(A, B);
        trim_leading_zeros();

    }



    //used an additional add method, beucase multiply and factorial
    //stopped working if at the end of the add method, trim_leading zeros
    //appeared
    void addO(BigInt & A, BigInt & B) {
        if (A.negative && B.negative)
        { add_ignoring_signs(A, B);
            negative = true; }
        else if (A.negative)
            subtract_ignoring_signs(B, A);
        else if (B.negative)
            subtract_ignoring_signs(A, B);
        else
            add_ignoring_signs(A, B);
    }



    void multiply(BigInt & A, BigInt & B){
        clear();

        int posBig = 0, posSml = 0, carry = 0, quotient = 0;
        BigInt n1, n2, sum;
        string num1="", num2="", t="";

        //to loop through the larger # and compare to each smaller digit
        for(int i = 0; i < A.size(); i++) {
            int q = i;
            n1.clear();
            n2.clear();
            //adds the right amount of 0 place holders
            while (q > 0) {
                 n2.push_back(0);
                q--;
            }

            //loops through bigInt B to get the quotient of the last digit
            // in A  times B
            for (int j = 0; j < B.size(); j++) {
                quotient = A.get_digit(i) * B.get_digit(j);

                //places the correct ones digit in the answer, while continuing to
                // add to the answer if necessary, and get to correct carry
                if (carry > 0) {
                    quotient += carry;
                }

                //determines the correct amount to add to the next
                if (quotient > 9 && j != B.size() - 1) {
                    carry = quotient / 10;
                    quotient %= 10;
                }

                //prevents a carry that should not happen for the next number
                else
                    carry = 0;
                //push_back(quotient);
                if(i == 0)
                    n1.push_back(quotient);
                else
                    n2.push_back(quotient);
            }
            //ensures that for the first run, is n1 and n2 is itself
            if(i == 0){
                sum = n1;
            }
            //ensures that for any other run, n1 is not reset to the new quotient
            //rather n1 is set to the most recently calculated sum
            else{
                n1 = sum;
                sum.addO(n1, n2);
            }

            sum.addO(n1, n2);
        }

        //takes the final answer in sum, and pushes its digits onto the heap
        int x;
        for(int g = 0; g <  sum.size(); g++)
        {
            x=sum.get_digit(g);
            push_back(x);
        }
        trim_leading_zeros();

    }//end multiply


    void factorial(BigInt & A){
        clear();


        BigInt one, curVal, oldVal, newVal, mult, zero;
        string s = "";
        one.become("1");
        curVal.become("2");
        zero.become("0");
        newVal = one;

        //ensures that factorial will run if the input has leading zeros
        if(A.at(A.size()-1) == 0 && A != zero){
            A.trim_leading_zeros();
        }
        //ensures that factorial will not have additional values added for
        //1 and 2 and return as is beucase they are only multiplied by 1
        if(A == zero)
            mult = one;
        else if(A == one || A == curVal){
            mult = A;
        }

        else{
            do{
                //multiplies currentValue(2) and newValue(1) and stores it in mult
                //then set newVal = mult so that we can multiply times the current
                //total each time
                mult.multiply(curVal, newVal);
                newVal = mult;

                //set currentValue to oldValue so that the next biggest currentValue
                //(3 after first run) can be stored in currentVal
                oldVal = curVal;
                curVal.addO(oldVal, one);
            } while(curVal != A); //continue the loop while currentValue does not equal A

            //If curVal is equal to A we will need to do one final multiplication to
            // achieve the total
            if(curVal == A){
                mult.multiply(curVal, newVal);
                newVal = mult;
            }
        }

        //takes the final answer in mult, and pushes its digits onto the heap
        int x;
        for(int g = 0; g < mult.size(); g++)
        {
            x=mult.get_digit(g);
            push_back(x);
        }
    }//end factorial

};




int main() {
    BigInt A, B, C;
    string s, choice;
    char option;
    bool run = true;
    bool op = true;

    cout << "BigInt Calc Operation Options: +, -, *, !" << endl;
    cout << "Type 'q' at any time to quit" << endl;

    while (run){
        cout << "Operation: ";
        cin >> choice;

        if(choice.size() == 1 && (choice == "q" || choice == "+" || choice == "-" || choice == "*" || choice == "!")){
            if(choice == "q"){
                cout << "Quitting. Thanks for playing!";
                return 0;
            }

            else if (choice == "+" || choice == "-" || choice == "*" || choice =="!") {
                cout << "operand1: ";
                cin >> s;
                if (s == "q") {
                    cout << "Quitting. Thanks for playing!";
                    return 0;
                }
                A.become(s);

                if(choice == "+" || choice == "-" || choice == "*") {
                    cout << "operand2: ";
                    cin >> s;
                    if (s == "q") {
                        cout << "Quitting. Thanks for playing!";
                        return 0;
                    }
                    B.become(s);
                }
            }
            option = choice.at(0);


            switch(option){
                case '+':
                    C.add(A, B);
                    break;
                case '-':
                    C.subtract_ignoring_signs(A, B);
                    //so the answer of subtraction cannot be negative
                    break;
                case '*':
                    C.multiply(A, B);
                    break;
                case '!':
                    C.factorial(A);
                    break;
            }
            C.print();
            cout << endl;
        }

        else{
            cout << "Operation type is not is not valid please choose: +, -, or !" << endl << endl;

        }


        //set BigInts to their original positive form, so that if a subtraction
        //results in a negative it is not added each of the following calculations
        A.negative = false;
        B.negative = false;
        C.negative = false;



    }



    return 0;
}