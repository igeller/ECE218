#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void start_calc();              //make sure stack is empty (do you mean the literal stack or just the vector named stack??)
void deal_with(double val);      //push the value onto the Stack
void deal_with(string op);      //perform operation indicated by operators (+, -, /, *, and a few others to make it useful)
double answer();               //return the current answer from the Stack (can I change answer to accept parameters???)*/


class revPolCal{
    //global variables
    vector <double> stack;

public: revPolCal(){

    };

    /**
    Give user instructions and receive their input
    */
    /* void userInteraction(){
         start_calc();
         string eqn="";

         cout <<"Welcome to the Reverse Polish Calculator!\n\n";
         cout << "The calculator has the following functions:\n";
         cout << "Type clear to restart and make a new calculation\n";
         cout << "(+)    Addition\n";
         cout << "(-)    Subtraction\n";
         cout << "(*)    Multiplication\n";
         cout << "(\\)    Division\n";
         cout << "(^)    Exponents\n";
         cout << "(sqrt) Square Roots\n\n";


         cout << "Enter the equation in a manner that a polish calculator understands\n (EX: Equation: 12 13 + ) then hit enter or type 'quit' to quit" << endl;
         cout << "Equation: ";

         cin >> eqn;
         while (eqn != "exit"){
             if(eqn[0] >= '0' && eqn[0] <= '9') {
                 double v = atof(eqn.c_str());
                 deal_with(v);
             }
             else
                 deal_with(eqn);
             cin >> eqn;
             //cout << "answer = " << answer() << endl;
         }



        /* while(eqn != "quit"){


             //cout << endl;
             //getline(cin, eqn);
             /*#if 0
             cout << eqn;
             #endif
             if(eqn == "clear"){
                 start_calc();
                 eqn = "";
             }

             /*
             else if (eqn[0] >= '0' && eqn[0] <= '9'){
             double v = atof(eqn.c_str());
             deal_with(v);
         }
         else
         deal_with(eqn);

         //cout << "Answer = " << answer() << endl;


         cin >> eqn;

         //deal with equation charact3er by character
         string strnumber = "";
         for(int i = 0; i < eqn.length(); i++){
             if(eqn[i] >= '0' && eqn[i] <= '9'){
                 strnumber += eqn[i];
             }
             else {
                 double number = atof(strnumber.c_str());
                 deal_with(number);
                 strnumber = "";
                 if(eqn[i] == 's'){
                     deal_with("sqrt");
                     i += 3; //account for sqrt
                 }
                 else if(eqn[i] != ' '){
                     deal_with(eqn[i]);
                 }
             }
         }
         //cout << "Answer = " << answer() << endl;

     //end of loop


     cout << "Thank you for using the polish calculator!";
 }*/

    void start_calc(){
        bool ready = stack.empty();
        if(ready != true){
            while(ready != true)
                stack.pop_back();
        }
        cout << "Stack is empty. Reverse Polish Calculator is ready.\n";
    }//end start_calc


    void deal_with(double val){
        stack.push_back(val);
    }//end deal_with(num)

    void deal_with(string op){
        if(stack.empty() == true){
            cout <<"Stack is empty cannot make calculations. Using default equation...\n";
            start_calc();
            deal_with(2);
            deal_with(3);
            deal_with("+");
            deal_with(4);
            deal_with(5);
            deal_with("+");
            deal_with("*");

        }

        else{
            double a = stack.back();    stack.pop_back();
            double b = stack.back();    stack.pop_back();


            if(op == "+")
                stack.push_back(a+b);
            else if(op == "-")
                stack.push_back(b-a);
            else if(op == "*")
                stack.push_back(a*b);
            else if(op == "/"){
                if(a == 0){
                    cout << "Divide by 0 detected, adding 1 to fix the issue.\n";
                    a += 1;
                    stack.push_back(b/a);
                }
                else
                    stack.push_back(b/a);
            }
            else if(op == "^")
                stack.push_back(pow(b, a));
            else if(op == "sqrt") {
                stack.push_back(b);
                stack.push_back(sqrt(a));
            }
        }//end deal_with(operators)*/
    }
    double answer(){
        return stack.back();
    }
};