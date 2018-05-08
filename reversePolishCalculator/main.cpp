#include <iostream>
//#include <string>
//#include <vector>
#include "RPC.h"

using namespace std;

int main()
{

    revPolCal calc;
//    calc.userInteraction();
    calc.deal_with(2);
    calc.deal_with(12);
    calc.deal_with("+");
    cout << "Answer = " << endl;
    //calc.start_calc();
    return 0;

}
