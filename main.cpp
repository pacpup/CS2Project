/* CSII Project Part 1
Tim Kurczewski tjk99@zips.uakron.edu
Last Work Done on 2/2/2018

*/
#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <limits>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::setprecision;
using std::fixed;
using std::setw;
using std::setfill;
using std::fstream;
using std::ostream;

//This is my class
class User
{
private:
    struct Node
    {
    int id;
    string nameOfStudent;
    struct Node  *next;
    };
Node* head = nullptr;
public:
    int getid();
    string getName();
    void setid(int);
    void setName(string);
    int timeUsed;
    User();
    User(int, string, int);
    int getID();

};

int genID();
void displayuniversities();
bool validateInput(int, int, int, string);
bool isFull(User*);
int mainMenu();
void login(User*[]);
void logoff(User*[]);
void searchForUser(User*[]);
void displayLab(User*[]);
bool checkminutes(int);

//Default constructor
User::User(){id = -1; nameOfStudent=""; timeUsed = 0; }
//Default that accepts values for each variable.
User::User(int newID, string nameOfStudentNew, int timeUsedNew)
{

    Node.id = newID;
    Node.nameOfStudent  = nameOfStudentNew;
    timeUsed = timeUsedNew;
}
int User::getid()
{
    return id;
}
string User::getName()
{
    return nameOfStudent;
}
void User::setid(int newID)
{
    id = newID;
}
void User::setName(string newStudent)
{
    nameOfStudent = newStudent;
}
//Global Constants
// Number of Comp labs
const int NUMLABS = 8;
// Number of computers in each lab
const int LABSIZES[NUMLABS] = {19, 15, 24, 33, 61, 17, 55, 37};
// Names of university of each lab
const string validation_message = "Please enter a valid input." ;
//Names of the colleges.
const string UNIVERSITYNAMES[NUMLABS] =
{"The University of Michigan", "The University of Pittsburgh", "Stanford University",
"Arizona State University", "North Texas State University", "The University of Alabama, Huntsville",
 "Princeton University", "Duquesne University"};

int main()
{
    fstream logFile;
    logFile.open("Log.txt");

    //seed time for our random user id.
    srand(time(0));
    //creates the array of pointers.
    User * ptr[NUMLABS] = {0};
    //creates a new array on the heap for our Users.
    for(int i=0; i<NUMLABS; ++i)
    {
        ptr[i]  = new User[LABSIZES[i]];
    }
    //calls the list of universities.
    displayuniversities();
    int choice = 0;
    do{
    choice = mainMenu();
    // This is where the program will do depending on the choice based off the menu.
    switch(choice)
    {
    case(1):
        login(ptr);
        break;
    case(2):
        logoff(ptr);
        break;
    case(3):
        searchForUser(ptr);
        break;
    case(4):
        displayLab(ptr);
        break;
    case(5):

        break;
    case(6):
        cout<< "Thank you for trying the program";
        break;

    }
    }while(choice != 6);

    return 0;
}
//pre: none
//Post: returns a random 5 digit int.
int genID()
{
int i = 0;
i = (rand())  % 999999;
return i;
}
//pre: none
//Post: Displays the colleges.
void displayuniversities()
{
    cout<<"     Welcome - here is our list of available labs" << endl<< endl;
    for(int i = 0; i< NUMLABS ; ++i)
    {
    cout<< "Lab # "<< (i+1) <<" for " << UNIVERSITYNAMES[i] << endl;
    }
}


//Precondition: Takes an input and it must fall between range 1 and 2.
//otherwise a message will print and a new input will be asked for.
//Post: returns a true or false depending if the input was good.
bool validateInput(int userChoice, int range1, int range2, string message)
{
  bool goodOrNot = false;
  if ((cin.fail()) || ((userChoice < range1) || (userChoice > range2)))
  {
 	cout << message << endl;
    goodOrNot = true;
  }
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return goodOrNot;
}
//pre: takes an array of pointers and and int
//Post: returns a true if the lab is full. otherwise no.
bool isFull(User*ptr[], int labNum)
{
    for(int i =0; i < LABSIZES[labNum-1]; ++i)
    {
        if(ptr[labNum-1][i].getid() == -1)
        {
            return false;
        }
    }
    return true;
}

//pre: none
//Post: displays the menu. returns a menu choice.
int mainMenu()
{
    int choice = 0;
    bool boolflag = true;
    cout<<setw(20)<<"Tim Kurczewski's Computer Lab System"<<endl<<endl;
    cout<<setw(20)<<"Main Menu:"<<endl
    << "1) Simulate Log-in "<<endl
    << "2) Simulate Log-off "<<endl
    << "3) Search "<<endl
    << "4) Display a lab"<<endl
    << "5) Recover a User"<<endl
    << "6) Quit"<<endl;
    cout<<setw(20)<< "Your choice: ";
    do{
    cin>> choice;
    boolflag = validateInput(choice, 1, 6, validation_message);
    } while(boolflag);
    return choice;

}
//pre: takes an array of pointers
//Post: updates the specified object with its new values. "logging them in"
void login(User*ptr[])
{   bool loopflag = false;
    int labNum, stationNum, ID, workTime;
    string NewName = "";
    cout<< "Enter the Lab Number the user is logging in from (1- " << NUMLABS << ") : "<<endl;
    do{
        cin>> labNum;
        loopflag = validateInput(labNum, 1, NUMLABS, validation_message);
    }while(loopflag);
    if(isFull(ptr, labNum))
       {
           cout<< "Lab " << labNum << ", " << UNIVERSITYNAMES[labNum-1]<< " is full. Please try again later.";
       }

    cout<< endl<< "Enter computer station the user is logging in to (1- " << LABSIZES[labNum-1] << ") : "<<endl;
    do{
        cin>> stationNum;
        loopflag = validateInput(stationNum, 1, (LABSIZES[labNum-1]), validation_message);
    }while(loopflag);
    ID = genID();
    cout<< "User id: "<< ID <<endl;
    do{
        cout<< "Please enter the name of this user:"<<endl;
        std::getline(cin,NewName);
    }while(NewName.length() > 35 || NewName == "");
    do
    {
        cout<< "Please enter the minutes of use for the work station (15/30/45/60):"<<endl;
        cin>> workTime;
        loopflag= checkminutes(workTime);
    }while(loopflag);

    ptr[(labNum-1)][(stationNum-1)].setid(ID);
    ptr[labNum-1][stationNum-1].setName(NewName);
    ptr[labNum-1][stationNum-1].timeUsed = workTime;
    cout<< "Log in successful." <<endl;
    system("pause");
}
//pre: takes an array of pointers
//Post: resets the User information to be the default values.
void logoff(User* ptr[])
{
    bool loopflag = true;
    int labNum, stationNum;
    cout<< "Enter the Lab Number the user is logging out from (1- " << NUMLABS << ") : "<<endl;
    do{
        cin>> labNum;
        loopflag = validateInput(labNum, 1, NUMLABS, validation_message);
    }while(loopflag);

    cout<< endl<< "Enter computer station the user is logging out of (1- " << LABSIZES[labNum-1] << ") : "<<endl;
    do{
        cin>> stationNum;
        loopflag = validateInput(stationNum, 1, (LABSIZES[labNum-1]), validation_message);
    }while(loopflag);

    ptr[(labNum-1)][(stationNum-1)].setid(-1);
    ptr[labNum-1][stationNum-1].setName("");
    ptr[labNum-1][stationNum-1].timeUsed = 0;
    cout<< "Log out successful." <<endl;
    system("pause");
}
//pre: takes an array of pointers
//Post: returns a true or false depending on if the user was found.
void searchForUser(User* ptr[])
{   int ID = 0;
    cout<< "Please enter a user you wish to find: " <<endl;
    cin>> ID;
    User *locationptr = nullptr;
    int i = 0;
    int j= 0;
    for ( i = 0; i < NUMLABS; ++i)
        {
            for ( j= 0; j < LABSIZES[i] ; ++j )
            {

             if(ptr[i][j].getid() == ID)
              {
                  locationptr = ptr[i];
                  cout << " User " << ID << " , " << ptr[i][j].getName() <<", is at " << UNIVERSITYNAMES[i] << " at Location " << (j+1)<<endl<<endl ;
                  return;
              }
              cout << "User not found." <<endl;
              return;
            }
        }
    system("pause");
}
//pre: takes an array of pointers
//Post: displays the labs and shows the user ID or empty for each slot.
void displayLab(User* ptr[])
{  int lab = 0;
    cout<< "Please enter the lab to display: " ;
    cin>> lab;
    cout<< "LAB STATUS"<<endl
    << "Lab # "<<lab << "for "<< UNIVERSITYNAMES[lab-1]<<endl
    << "Computer Stations "<<endl;
    for(int i = 0; i < LABSIZES[lab-1]; ++i )
    {
        if((ptr[lab-1][i].getid()) == -1)
        {
            cout<< (i+1) << " : Empty ";
        }
        else
        {
        cout<< (i+1) << " : "<< ptr[lab-1][i].getid()<<endl;
        }
        if(i%5 == 0)
        {
            cout<< endl;
        }
    }
    cout<< endl<<endl;
    system("pause");
}
//pre: takes an int Time
//Post: if it is 15, 30, 45, or 60 it returns true. otherwise false.
bool checkminutes(int Time)
{
 if(Time != 15 && Time != 30 && Time !=45 && Time!= 60)
 {
     return true;
 }
 return false;
}
