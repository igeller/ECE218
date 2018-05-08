#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sys/resource.h>

using namespace std;

double get_cpu_time()
{ struct rusage ruse;
    getrusage(RUSAGE_SELF, &ruse);
    return ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec/1000000.0 +
           ruse.ru_stime.tv_sec+ruse.ru_stime.tv_usec/1000000.0;
};



void print(string A[], int N){
    for(int i = 1; i <= N; i++) {
        cout << A[i-1] << "     ";
        if(i % 10 == 0)
            cout << endl;
    }
    cout << endl;
}//end print



void print(string A[], int N, char t){
    if (t == 's')
        cout << "Selection Sort: " << endl;
    else if(t == 'b')
        cout << "Bubble Sort: " << endl;
    print(A, N);
}//end print



void selection_sort(string A[], int N)
{   int minPos;
    string temp;

    //print(A, N, 's');

    for(int i = 0; i < N-1; i++){
        minPos = i;
        for(int j = i+1; j < N; j++){
            if(A[j] < A[minPos]){
                minPos = j;
            }

        }
       if(minPos != i) {
            temp = A[i];
            A[i] = A[minPos];
            A[minPos] = temp;
        }
    }

    //print(A, N);
}//end selection sort



void bubble_sort(string A[], int N) {
    string temp;

    //print(A, N, 'b');

    for(int i = 0; i < N-1; i++){
        for (int j = 0; j < N-i-1; j++) {
            if(A[j] > A[j+1]){
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                //run = true;
            }
        }
    }

    //prints the array in order
    //print(A, N);
}//end bubble sort





string random_string()
{ string s = "";
    for (int i = 0; i < 10; i += 1)
        s += "abcdefghijklmnopqrstuvwxyz"[random() % 26];
    return s;
}//end randomString



int main(int argc, char * argv[])
{
    srandomdev();
    cout << "The command line contained:\n";
    for (int i = 0; i < argc; i += 1)
        cout << i << ": " << argv[i] << "\n";
    int N = atoi(argv[1]);

    string * A1 = new string[N];
    for (int i = 0; i < N; i += 1) {
        A1[i] = random_string();
    }

    string * A2 = new string[N];
    for (int i = 0; i < N; i += 1)
        A2[i] = A1[i];



    double t1 = get_cpu_time();
    selection_sort(A1, N);
    double t2 = get_cpu_time();
    bubble_sort(A2, N);
    double t3 = get_cpu_time();

    cout << "selection sort took " << t2-t1 << " seconds\n";
    cout << "bubble sort took " << t3-t2 << " seconds\n";

    return 0;
}//end main

