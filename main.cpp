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

void edit_record_menu();
void display_record_menu();
void play_playlist_menu();

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
        display_record_menu();
        break;
    case 3: //function3
        edit_record_menu();
        break;
    case 4: //function4
        play_playlist_menu();
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

void edit_record_menu()
{
lbl:
    int subchoice;
    cout << "Edit records Menu" << endl;
    cout << "1>Insert record" << endl;
    cout << "2>Delete record" << endl;
    cout << "3>Return to main menu" << endl;
    cout << "Enter your choice:";
    cin >> subchoice;
    cout << endl;
    switch (subchoice)
    {
    case 1: //subfunction1
        cout << "Insert record" << endl;
        break;
    case 2: //subfunction2
        cout << "Delete record" << endl;
        break;
    case 3:
        return;
        break;
    default:
        cout << "Invalid Input" << endl;
        goto lbl;
    }
}

void display_record_menu()
{
lbl:
    int subchoice;
    cout << "Display records" << endl;
    cout << "1>Display all records" << endl;
    cout << "2>Sort" << endl;
    cout << "3>Return to main menu" << endl;
    cout << "Enter your choice:";
    cin >> subchoice;
    cout << endl;
    switch (subchoice)
    {
    case 1: //subfunction1
        cout << "all records" << endl;
        break;
    case 2: //subfunction2
        cout << "filtered records" << endl;
        break;
    case 3:
        return;
        break;
    default:
        cout << "Invalid Input" << endl;
    }
    goto lbl;
}
void play_playlist_menu()
{
lbl:
    int subchoice;
    cout << "Play playlist" << endl;
    cout << "1>Play from song" << endl;
    cout << "2>Shuffle play" << endl;
    cout << "3>Return to main menu" << endl;
    cout << "Enter your choice:";
    cin >> subchoice;
    cout << endl;
    switch (subchoice)
    {
    case 1: //subfunction1
        cout << "Play from song" << endl;
        break;
    case 2: //subfunction2
        cout << "Shuffle play" << endl;
        break;
    case 3:
        return;
        break;

    default:
        cout << "Invalid Input" << endl;
    }
    goto lbl;
}