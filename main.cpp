#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

typedef struct info
{
    string artist;
    string album;
    string song;
    string genre;
} Info;

struct playlist : info //Inheriting from info structure
{
    struct playlist *next;
} * head;

int size = 0;

void create_playlist_menu();
void edit_record_menu();
void display_record_menu(Info data[]);
int readFile(Info data[]);
void display_all_records(Info data[], int size);
void play_playlist_menu();
void filter_records();

int main()
{
    Info data[100];
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
        create_playlist_menu();

        break;
    case 2: //function2
        display_record_menu(data);
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

void write_to_playlist(playlist *song, string name)
{

    ofstream fout;
    fout.open(name);
    if (!fout)
    {
        cout << "Error in opening file" << endl;
    }
    else
    {
        while (song != NULL)
        {
            fout << song->song << "," << song->album << "," << song->artist << "," << song->genre << "\n";
            song = song->next;
        }
    }
    fout.close();
}
void create_playlist_menu()
{
    Info data[20];
    string name, song_name;
    playlist *new_song, *song;
    int size, choice;
    head = NULL;
    cout << "Enter the name of the playlist:";
    cin >> name;
    cout << endl;
    name = name + ".csv";
    size = readFile(data);
lbl:
    cout << "Menu" << endl;
    cout << "1>Display available songs" << endl;
    cout << "2>Add song to playlist" << endl;
    cout << "3>View songs in current playlist" << endl;
    cout << "4>Save the playlist" << endl;
    cout << "Eneter your choice:";
    cin >> choice;
    cout << endl;
    cin.clear();
    cin.sync();

    switch (choice)
    {
    case 1:
        display_all_records(data, size);
        break;
    case 2:

        cout << "Enter the name of the song to be added:";
        getline(cin, song_name);
        for (int i = 0; i < size; i++)
        {
            if (data[i].song == song_name)
            {
                new_song = new playlist();
                new_song->song = data[i].song;
                new_song->album = data[i].album;
                new_song->artist = data[i].artist;
                new_song->genre = data[i].genre;
                new_song->next = NULL;
                if (head == NULL)
                {
                    head = new_song;
                }
                else
                {
                    playlist *temp;
                    temp = head;
                    head = new_song;
                    new_song->next = temp;
                }
            }
        }
        break;
    case 3:
        song = head;
        while (song != NULL)
        {
            cout << song->song << "," << song->album << "," << song->artist << "," << song->genre << "\n";
            song = song->next;
        }
        break;
    case 4:
        write_to_playlist(new_song, name);
        delete new_song;
        cout << "Playlist saved" << endl;
        return;
        break;
    default:
        cout << "Invalid choice";
    }
    goto lbl;
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

void display_record_menu(Info data[])
{
lbl:
    int subchoice;
    int size;
    cout << "Display records" << endl;
    cout << "1>Display all records" << endl;
    cout << "2>Filter" << endl;
    cout << "3>Return to main menu" << endl;
    cout << "Enter your choice:";
    cin >> subchoice;
    cout << endl;

    switch (subchoice)
    {
    case 1: //subfunction1
        cout << "all records" << endl;
        cout << endl;
        size = readFile(data);
        display_all_records(data, size);
        break;
    case 2: //subfunction2
        filter_records();
        break;

    case 3:
        return;
        break;
    default:
        cout << "Invalid Input" << endl;
    }
    goto lbl;
}

void filter_records()
{
    int Subchoice;
    Info filtered[100], temp[100];
lbl2:
    string read, search, trash;
    ifstream fin;
    bool notfound = true;
    int i = 0, a = 0;
    cout << "Filter by -" << endl;
    cout << "1>Artist " << endl;
    cout << "2>Song  " << endl;
    cout << "3>Album " << endl;
    cout << "4>Genre " << endl;
    cout << "5>Return to previous menu" << endl;
    cout << "Enter your choice: ";
    cin >> Subchoice;
    cout << endl;
    cin.clear();
    cin.sync();
    switch (Subchoice)
    {
    case 1: //filter by artist

        fin.open("dummy.csv");
        if (!fin)
        {
            cout << "file could not be opened" << endl;
        }
        else
        {
            cout << "Enter the name of the artist:";
            getline(cin, search);
            for (auto &c : search)
            {
                c = tolower(c);
            }
            cout << endl;
            while (!fin.eof())
            {

                getline(fin, temp[i].song, ',');
                getline(fin, temp[i].album, ',');
                getline(fin, read, ',');
                for (auto &c : read)
                {
                    c = tolower(c);
                }
                if (read == search)
                {
                    for (auto &c : read)
                    {
                        c = toupper(c);
                    }

                    notfound = false;
                    filtered[i].song = temp[i].song;
                    filtered[i].album = temp[i].album;
                    filtered[i].artist = read;
                    getline(fin, temp[i].genre, '\n');
                    filtered[i].genre = temp[i].genre;
                    if (a == 0)
                    {
                        cout << " Results for " << filtered[i].artist << "-" << endl;
                        cout << "song" << setw(30) << "album" << setw(30) << "genre" << endl;
                        a++;
                    }
                    cout << filtered[i].song << setw(30) << filtered[i].album << setw(30) << filtered[i].genre << endl;
                }
                else
                {
                    getline(fin, trash, '\n');
                }
                i++;
            }
            if (notfound)
            {
                cout << "No results found" << endl;
            }
        }
        fin.close();
        break;
    case 2: //filter by song
        fin.open("dummy.csv");
        if (!fin)
        {
            cout << "file could not be opened" << endl;
        }
        else
        {
            cout << "Enter the name of the song:";
            getline(cin, search);
            for (auto &c : search)
            {
                c = tolower(c);
            }
            cout << endl;
            while (!fin.eof())
            {

                getline(fin, read, ',');
                for (auto &c : read)
                {
                    c = tolower(c);
                }
                if (read == search)
                {
                    for (auto &c : read)
                    {
                        c = toupper(c);
                    }

                    notfound = false;
                    filtered[i].song = read;
                    getline(fin, temp[i].album, ',');
                    getline(fin, temp[i].artist, ',');
                    getline(fin, temp[i].genre, '\n');
                    filtered[i].album = temp[i].album;
                    filtered[i].artist = temp[i].artist;
                    filtered[i].genre = temp[i].genre;
                    if (a == 0)
                    {
                        cout << "Results for " << filtered[i].song << "- " << endl;
                        cout << "artist" << setw(30) << "album" << setw(30) << "genre" << endl;
                        a++;
                    }
                    cout << filtered[i].artist << setw(30) << filtered[i].album << setw(30) << filtered[i].genre << endl;
                }
                else
                {
                    getline(fin, trash, '\n');
                }
                i++;
            }
            if (notfound)
            {
                cout << "No results found" << endl;
            }
        }
        fin.close();

        break;
    case 3: //filter by album
        fin.open("dummy.csv");
        if (!fin)
        {
            cout << "file could not be opened" << endl;
        }
        else
        {
            cout << "Enter the name of the album:";
            getline(cin, search);
            cout << endl;
            for (auto &c : search)
            {
                c = tolower(c);
            }
            while (!fin.eof())
            {
                getline(fin, temp[i].song, ',');
                getline(fin, read, ',');
                for (auto &c : read)
                {
                    c = tolower(c);
                }

                if (read == search)
                {
                    for (auto &c : read)
                    {
                        c = toupper(c);
                    }

                    notfound = false;
                    filtered[i].song = temp[i].song;
                    filtered[i].album = read;
                    getline(fin, temp[i].artist, ',');
                    getline(fin, temp[i].genre, '\n');
                    filtered[i].artist = temp[i].artist;
                    filtered[i].genre = temp[i].genre;
                    if (a == 0)
                    {
                        cout << "Results for the album " << filtered[i].album << "- " << endl;
                        a++;
                    }
                    cout << filtered[i].song << endl;
                }
                else
                {
                    getline(fin, trash, '\n');
                }
                i++;
            }
            if (notfound)
            {
                cout << "No results found" << endl;
            }
        }
        fin.close();
        break;
    case 4: //filter by genre
        fin.open("dummy.csv");
        if (!fin)
        {
            cout << "file could not be opened" << endl;
        }
        else
        {
            cout << "Enter the genre you would like to search:";
            getline(cin, search);
            for (auto &c : search)
            {
                c = tolower(c);
            }
            cout << endl;
            while (!fin.eof())
            {
                getline(fin, temp[i].song, ',');
                getline(fin, temp[i].album, ',');
                getline(fin, temp[i].artist, ',');
                getline(fin, read, '\n');
                for (auto &c : read)
                {
                    c = tolower(c);
                }
                if (read == search)
                {
                    for (auto &c : read)
                    {
                        c = toupper(c);
                    }
                    notfound = false;
                    filtered[i].genre = read;
                    filtered[i].song = temp[i].song;
                    filtered[i].artist = temp[i].artist;
                    filtered[i].album = temp[i].album;
                    if (a == 0)
                    {
                        cout << "Results for the genre " << filtered[i].genre << "- " << endl;
                        cout << "Song" << setw(30) << "artist" << endl;
                        a++;
                    }
                    cout << filtered[i].song << setw(30) << filtered[i].artist << endl;
                } /*
                else
                {
                    getline(fin, trash, '\n');
                }*/

                i++;
            }
            if (notfound)
            {
                cout << "No results found" << endl;
            }
        }
        fin.close();
        break;
    case 5:
        return;
        break;
    default:
        cout << "invalid input" << endl;
    }
    goto lbl2;
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

void display_all_records(Info data[], int size)
{
    cout << "song" << setw(30) << "album" << setw(30) << "artist" << setw(30) << "genre" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << data[i].song << setw(30) << data[i].album << setw(30) << data[i].artist << setw(30) << data[i].genre << endl;
    }
}
int readFile(Info data[])
{
    ifstream fin;
    int size = 0;
    fin.open("dummy.csv");
    bool notfound = true;
    if (!fin)
    {
        cout << "file could not be opened" << endl;
    }
    else
    {
        int i = 0;
        while (!fin.eof())
        {
            getline(fin, data[i].song, ',');
            getline(fin, data[i].album, ',');
            getline(fin, data[i].artist, ',');
            getline(fin, data[i].genre, '\n');
            i++;
            size++;
        }
    }
    return size;
}
