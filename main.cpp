#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>

using namespace std;

typedef struct info
{
    char artist[100];
    char title[100];
    char song[100];
    char genre[100];
} Info;

struct node
{
    Info data;
    struct node *prev;
    struct node *next;
} Node;

int main()
{
    lbl:
    int choice, subchoice;
    cout << "MENU\n";
    cout << "1>Create playlist" << endl;
    cout << "2>Display records" << endl;
    cout << "3>Edit records" << endl;
    cout << "4>Play Playlist" << endl;
    cout << "5>Exit" << endl;
    cout << "Enter your choice:";
    cin >> choice;
    cout << endl;
    switch (choice)
    {

    case 1: //fucntion1
        cout << "Create playlist" << endl;
        break;
    case 2: //function2
        cout << "Display records" << endl;
        cout << " 1>Display all records" << endl;
        cout << " 2>Sort" << endl;
        cout << " Enter your choice:" << endl;
        cin >> subchoice;
        switch (subchoice)
        {
        case 1: //subfunction1
            cout << "all records" << endl;
            break;
        case 2: //subfunction2
            cout << "filtered records" << endl;
            break;
        default:
            cout << "Invalid Input" << endl;
        }

        break;
    case 3: //function3
        cout << "Edit records" << endl;
        cout << " 1>Insert record" << endl;
        cout << " 2>Delete record" << endl;
        cout << " Enter your choice:" << endl;
        cin >> subchoice;
        switch (subchoice)
        {
        case 1: //subfunction1
            cout << "Insert record" << endl;
            break;
        case 2: //subfunction2
            cout << "Delete record" << endl;
            break;
        default:
            cout << "Invalid Input" << endl;
        }
        break;
    case 4: //function4
        cout << "Play playlist" << endl;
        cout << "1>Play from song" << endl;
        cout << "2>Shuffle play" << endl;
        cout << " Enter your choice:" << endl;
        cin >> subchoice;
        switch (subchoice)
        {
        case 1: //subfunction1
            cout << "Play from song" << endl;
            break;
        case 2: //subfunction2
            cout << "Shuffle play" << endl;
            break;
        default:
            cout << "Invalid Input" << endl;
        }
        break;

    case 5: //function5
        exit(0);
        break;

    default:
        cout << "Invalid Input." << endl;
    }
    goto lbl;
    return 0;
}
