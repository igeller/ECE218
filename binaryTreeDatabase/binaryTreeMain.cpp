#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


struct person{
    string fName, lName, dog;
    int socSec, bDay, zip;

    person(int s, int b, string f, string l, int z){
        socSec = s;
        bDay = b;
        fName = f;
        lName = l;
        zip = z;
        dog = "";

    }
};

struct node{
    person * data;
    node *left, *right;

    node(person * d){
        data = d;
        left = NULL;
        right = NULL;
    }
};

struct tree{
    node *root;

    tree(){
        root = NULL;
    }
};

//print all the data of a specified person
void printAllData(node * t){
    cout << t->data->socSec << " " << t->data->bDay << " " << t->data->fName << " " << t->data->lName << " " << setw(5) << setfill( '0' ) << t->data->zip << " " << t->data->dog << endl;
}


//calculates how many people are in the tree
int numInTree(node * r){
    if(r == NULL)
        return 0;
    int numLeft = numInTree(r->left);
    int numRight = numInTree(r->right);
    return 1 + numLeft + numRight;

}

//inserts the names alphabetically into the tree by last name, then by first name
node * treeInsert(node *r, person *p) {
    if (r == NULL) {
        r = new node(p);
    }
    if (p->lName == r->data->lName) {
        //adding in exception to sort by older person if the first and last name are the same
        //if younger then go left (cause like alphabet its smaller), if older then go right
        //if negative that means p is older
        if (p->fName == r->data->fName){
            if (p->bDay - r->data->bDay > 0)
                r->left = treeInsert(r->left, p);
            else if (p->bDay - r->data->bDay < 0)
                r->right = treeInsert(r->right, p);
        }

        else if (p->fName < r->data->fName)
            r->left = treeInsert(r->left, p);
        else //else (p->fName > r->data->fName)
            r->right = treeInsert(r->right, p);
        return r;
    }
    if(p->lName < r->data->lName)
        r->left = treeInsert(r->left, p);
    else
        r->right = treeInsert(r->right, p);
    return r;
}



//read the file and store the person in the tree by names
void readDatabase(ifstream & file, tree *pplTree) {
    int ss, bday, zip;
    string fst, lst;

    while(file >> ss >> bday >> fst >> lst >> zip) {
        person * linePerson = new person(ss, bday, fst, lst, zip);
        node * p = treeInsert(pplTree->root, linePerson);
        pplTree->root = p;
    }
}


//used to print out all the people in find with the specified first
//and last name (called from findPerson)
void sameFirst(node *r, string fst, string lst){
    if(r == NULL)
        return;
    if(lst == r->data->lName && fst == r->data->fName){
        printAllData(r);
    }
    sameFirst(r->left, fst, lst);
    sameFirst(r->right, fst, lst);
}


//find person accounts for multiple people prints all the people with
//the exact same name
node * findPerson(node *r, string fst, string lst, bool &p){
    if(r == NULL)
        return NULL;
    if(lst == r->data->lName){
        if(fst == r->data->fName){
            if(p != true)
                //this prevents the found people from printing when being called from hasdog
                sameFirst(r, fst, lst);
            p = true;
            return r;
        }
        if(fst < r->data->fName)
            r = findPerson(r->left, fst, lst, p);
        else
            r = findPerson(r->right, fst, lst, p);
        return r;
    }
    if(lst < r->data->lName)
        r = findPerson(r->left, fst, lst, p);
    else
        r = findPerson(r->right, fst, lst, p);
    return r;
}


//specified data to print for people in the same zip
void printPersonInZip(node * pInZip){
    cout << pInZip->data->fName << " " << pInZip->data->lName << " " << pInZip->data->dog << endl;
}


//same zip function which prints all the people
//in the same zipcode
node * sameZ(node * r, int z, bool & p){
    if(r == NULL)
        return NULL;
    if (r == NULL)
        return NULL;
    sameZ(r->left, z, p);

    if(z == r->data->zip) {
        //calls printPersonInZip so only specified zip data is printed
        printPersonInZip(r);
        p=true;
    }
    sameZ(r->right, z, p);

    return r;
}




//same last name function, finds and prints all the people
//with the same specified last name
node * sameL(node *r, string lst, bool &p){
    if (r == NULL)
        return NULL;
    r->left = sameL(r->left, lst, p);

    if(lst == r->data->lName) {
        p=true;
        printAllData(r);
    }
    r->right = sameL(r->right, lst, p);
    if(p == false)
        return NULL;
    return r;
}



//OLDEST METHODS

//printing person if 2 people are same age
void printOldest(node * oldest){
    cout << oldest->data->fName << " " << oldest->data->lName << " " << setw(5) << setfill( '0' ) << oldest->data->zip << " " << oldest->data->dog << endl;
}


//finding the oldest person, it also prints people with the same birthday
//since we do not have anything else to differentiate who is truly older,
//like a time
node * findOldest(node *r){
    if(r == NULL)
        return NULL;
    node * oldLeft = findOldest(r->left);
    node * oldRight = findOldest(r->right);
    node * oldest = r;

    //we say if the bday is smaller becuase the int starts with the year
    //and the smaller the year the older the person.
    //EX: I am born 1998 < 2000 when my friend was born however I am older
    if(oldLeft != NULL && oldLeft->data->bDay < oldest->data->bDay)
        oldest = oldLeft;

    if(oldRight != NULL && oldRight->data->bDay < oldest->data->bDay)
        oldest = oldRight;

    return oldest;
}



node * sameBday(node * r, int z) {
    if(r == NULL){
        return NULL;
    }
    if(z == r->data->bDay){
        printOldest(r);
    }
    r->left = sameBday(r->left, z);
    r->right= sameBday(r->right, z);
    return r;
}







void printDataBase(node * t) {
    if (t == NULL)
        return;
    printDataBase(t->left);
    printAllData(t);
    printDataBase(t->right);
}


int depth = 1;
void printDataBaseAsTree(node * t)
{ if (t == NULL)
        return;
    depth += 1;
    printDataBaseAsTree(t->left);
    depth -= 1;
    cout << setw(depth*10) << "" << t->data->lName << ", " << t->data->fName <<endl;
    depth += 1;
    printDataBaseAsTree(t->right);
    depth -= 1; }




int main(){

    //create a tree to store the nodes in
    tree *pplTree = new tree;


    //open file and store file in variable myFile
    string filePath = "/Users/izzy/Documents/College/Freshman (2017 - 2018)/Spring 2018/ECE 218/Homework/binaryTreeDatabase/database.txt";
    string smallFile = "/Users/izzy/Documents/College/Freshman (2017 - 2018)/Spring 2018/ECE 218/Homework/binaryTreeDatabase/smallDatabase.txt";
    string rabbitFilePath = "/home/218/database.txt";
    ifstream myFile;
    myFile.open(filePath.c_str());

    //if the file could not be opened
    if(myFile.fail()){
        cout << "Can't read file\n";
        exit(1);
    }

    readDatabase(myFile, pplTree);
    myFile.close();


    cout << "Welcome to the database!"<<endl;
    string choice;
    while(true){
        cout << "What would you like to do?\n"
             << "\tFIND: display all information about a person\n"
             << "\tZIP: diplay all names of people living in a given zip code\n"
             << "\tALL: display all information about all people have a specified lastname\n"
             << "\tHASDOG: make a note that the specified person has a dog\n"
             << "\tOLDEST: display the name and zipcode of the oldest person in the database\n"
             << "\tEXIT: exit database" << endl;
        cout << "command: ";
        getline(cin, choice);


        if(choice == "EXIT"){
            cout << "... quitting";
            break;
        }
        else if(choice == "FIND"){
            string first, last;
            bool printedP = false;
            cout << "Enter first and last name: ";
            cin >> first >> last;

            node *t =  findPerson(pplTree->root, first, last, printedP);

            if(t == NULL || printedP == false)
                cout << "Sorry the person you are looking for (" << first << " " << last << ") is not in the database\n" << endl;

             getline(cin, choice);
        }
        else if(choice == "ZIP"){
            int zip;
            bool printedZip = false;
            cout << "Enter a zipcode: ";
            cin >> zip;

            node *z = sameZ(pplTree->root, zip, printedZip);

            if(z == NULL || printedZip == false)
                cout << "Sorry no one lives in the zipcode (" << zip << ") you searched for\n" << endl;

            cout << endl;
            getline(cin, choice);
        }
        else if(choice == "ALL"){
            string last;
            bool printedLast = false;
            cout << "Enter a lastname: ";
            cin >> last;

            node *l = sameL(pplTree->root, last, printedLast);


            if(l == NULL || printedLast == false)
                cout << "Sorry no one has the last name (" << last << ") you searched for\n" << endl;
            cout << endl;

            getline(cin, choice);
        }
        else if(choice == "HASDOG"){
            //hasdog did not say how to handle multiple people with dogs
            //so instead of saying everyone with that name has a dog, i just
            //set the first person found with that name has a dog
            string first, last;
            bool printedDP = true;
            cout << "Who has a dog: ";
            cin >> first >> last;

            node * t = findPerson(pplTree->root, first, last, printedDP);

            if(t == NULL || printedDP == false)
                cout << "Sorry the person you are saying owns a dog (" << first << " " << last << ") is not in the database\n" << endl;
            else {
                t->data->dog = "**DOG**";
            }

            getline(cin, choice);
        }
        else if(choice == "OLDEST"){
            node * oldest = findOldest(pplTree->root);
            if(oldest == NULL)
                cout << "Sorry, the database is empty. We cannot find the oldest\n";
            else
                sameBday(pplTree->root, oldest->data->bDay);
        }
        else{

            cout << "Sorry, \"" << choice << "\" is not a valid command. Please try again:" << endl;
        }
        cout << endl;
    }

    return 0;
}
