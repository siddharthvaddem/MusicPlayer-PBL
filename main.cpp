#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <unistd.h>

using namespace std;

typedef struct info
{
    string artist;
    string album;
    string song;
    string genre;
    string link;
} Info;
struct playlist : info //Inheriting from info structure
{
    struct playlist *next;
} * head;
typedef struct login
{
    string username;
    string password;
    string masterplaylist;
} Login;

Login details[100];
int arr[100];
int size = 0;
string userplaylist;

void create_playlist_menu();
void edit_record_menu();
void play_playlist_menu();
void display_record_menu(Info data[]);
int readFile(Info data[], string filename);
void display_all_records(Info data[], int size);
void shuffle();
void randomize(int arr[], int);
void swap(int arr[], int, int);
string signin();
string signup();
void addLoginData(string, string, string);
int readLoginData(Login details[]);

//----------------------------------------------MAIN FUNCTION----------------------------------------------------
int main()
{
    Info data[100];
    int loginchoice;
    bool entered = false;
    system("color B5");
    cout << "OPENING APPLICATION ";
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            cout.flush();
            sleep(1);
        }
        cout << "\b\b\b   \b\b\b";
    }
login:
    cin.clear();
    cin.sync();
    system("CLS");
    system("color F1");
    cout << "WELCOME TO ZUNE " << endl;
    cout << "SIGN IN TO CONTINUE- " << endl;
    cout << "1>ALREADY HAVE AN ACCOUNT?" << endl;
    cout << "2>CREATE NEW ACCOUNT" << endl;
    cout << "3>QUIT APPLICATION" << endl;
    cout << "ENTER YOUR CHOICE- ";
    cin >> loginchoice;
    cout << endl;
    switch (loginchoice)
    {
    case 1: //call signin func
        userplaylist = signin();
        entered = true;
        break;
    case 2: //call signup function
        userplaylist = signup();
        entered = true;
        break;
    case 3:
        system("color B5");
        system("CLS");
        cout << "CLOSING APPLICATION";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            cout.flush();
            sleep(1);
        }
        cout << "\b\b\b   \b\b\b";
        exit(0);
        break;
    default:
        cout << "Invalid Input" << endl;
        sleep(1);
        break;
    }
    if (!entered)
    {
        goto login;
    }
lbl:
    int choice, subchoice;
    string input;
    cin.clear();
    cin.sync();
    system("CLS");
    system("color E4");
    cout << "MENU\n";
    cout << "1>CREATE PLAYLIST" << endl;
    cout << "2>DISPLAY RECORDS" << endl;
    cout << "3>EDIT YOUR PLAYLIST" << endl;
    cout << "4>PLAY YOUR PLAYLIST" << endl;
    cout << "5>LOGOUT" << endl;
    cout << "6>EXIT" << endl;
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
        system("color F4");
        break;
    case 5: //function5
        cout << "SURE YOU WANT TO LOGOUT (Y/N)?" << endl;
        cin >> input;
        cout << endl;
        if (input == "Y" || input == "y")
        {
            goto login;
        }
        else
        {
            goto lbl;
        }
        break;
    case 6: //function5
        system("CLS");
        system("color B5");
        cout << "CLOSING APPLICATION...";
        sleep(2);
        exit(0);
        break;
    default:
        cout << "INVALID INPUT" << endl;
        sleep(1);
        break;
    }
    goto lbl;
    return 0;
}
//-------------------------------------------------CREATING A PLAYLIS--------------------------------------------
void write_to_playlist(playlist *song, string name)
{
    ofstream fout;
    fout.open(name);
    if (!fout)
    {
        cout << "ERROR IN OPENING FILE" << endl;
    }
    else
    {
        while (song != NULL)
        {
            fout << song->song << "," << song->album << "," << song->artist << "," << song->genre << "," << song->link << "\n";
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
    system("CLS");
    cout << "ENTER THE NAME OF THE PLAYLIST:";
    cin >> name;
    cout << endl;
    name = userplaylist + name + ".csv";
    ofstream fout;
    fout.open(userplaylist + ".csv", ios::app);
    fout << name << "\n";
    fout.close();
    size = readFile(data, "dummy.csv");
lbl:
    cin.clear();
    cin.sync();
    system("CLS");
    cout << "Menu" << endl;
    cout << "1>DISPLAY AVAILABLE SONGS" << endl;
    cout << "2>ADD SONG TO PLAYLIST" << endl;
    cout << "3>VIEW SONGS IN CURRENT PLAYLIST" << endl;
    cout << "4>SAVE THE PLAYLIST" << endl;
    cout << "ENTER YOUR CHOICE:";
    cin >> choice;
    cout << endl;
    cin.clear();
    cin.sync();
    bool notfound = true;
    switch (choice)
    {
    case 1:
        display_all_records(data, size);
        break;
    case 2:
        cout << "ENTER THE NAME OF THE SONG TO BE ADDED:";
        getline(cin, song_name);
        notfound = true;
        for (auto &c : song_name)
        {
            c = tolower(c);
        }
        for (int i = 0; i < size; i++)
        {
            for (auto &c : data[i].song)
            {
                c = tolower(c);
            }
            if (data[i].song == song_name)
            {
                new_song = new playlist();
                new_song->song = data[i].song;
                new_song->album = data[i].album;
                new_song->artist = data[i].artist;
                new_song->genre = data[i].genre;
                new_song->link = data[i].link;
                new_song->next = NULL;
                notfound = false;
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
        if (notfound){
            cout << "song not found" << endl;
            sleep(2);
        }
        break;
    case 3:
        song = head;
        while (song != NULL)
        {
            cout << song->song << "," << song->album << "," << song->artist << "," << song->genre << "\n";
            song = song->next;
        }
        sleep(4);
        break;
    case 4:
        write_to_playlist(new_song, name);
        delete new_song;
        cout << "SAVING PLAYLIST";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            cout.flush();
            sleep(1);
        }
        cout << "\b\b\b   \b\b\b";
        system("color 2E");
        system("CLS");

        cout << endl;
        cout << "PLAYLIST SAVED" << endl;
        sleep(2);
        system("color F4");
        system("CLS");
        return;
        break;
    default:
        cout << "INVALID INPUT";
        sleep(1);
        break;
    }
    goto lbl;
}

//------------------------------------EDIT PLAYLIST-------------------------------------------------------------

void insert_song()
{
    cin.clear();
    cin.sync();
    string search, playlistName, filename = userplaylist + ".csv";
    bool notfound = true;
    cout << "ENTER THE NAME OF THE PLAYLIST YOU WANT TO INSERT THE SONG INTO:";
    getline(cin, search);
    for (auto &c : search)
    {
        c = tolower(c);
    }
    cout << endl;
    ifstream fin(filename);
    if (!fin)
    {
        cout << "FILE COULDN'T BE OPENED!!" << endl;
        sleep(1);
    }
    else
    {
        search = userplaylist + search + ".csv";
        while (!fin.eof())
        {
            getline(fin, playlistName);
            for (auto &c : playlistName)
            {
                c = tolower(c);
            }
            if (search == playlistName)
            {
                notfound = false;
                break;
            }
        }
    }
    if (notfound)
    {
        cout << "PLAYLIST NOT FOUND, PLEASE CREATE PLAYLIST AND THEN TRY!!" << endl;
        sleep(1);
        return;
    }
    fin.close();
lblelse:
    cin.clear();
    cin.sync();
    fstream fio(search, ios::in | ios::out | ios::app);
    if (!fio)
    {
        cout << "ERROR IN OPENING FILE!!" << endl;
        sleep(1);
    }
    else
    {
        Info data_song_list[30], data_song_playlist[30];
        string songname;
        cout << "Enter THE NAME OF THE SONG YOU WOULD LIKE TO ADD:";
        getline(cin, songname);
        for (auto &c : songname)
        {
            c = tolower(c);
        }
        bool songnotfound = true;
        int size = readFile(data_song_list, "dummy.csv");
        for (int i = 0; i < size; i++)
        {
            string song_name = data_song_list[i].song;
            for (auto &c : song_name)
            {
                c = tolower(c);
            }
            if (songname == song_name)
            {
                int size_playlist = readFile(data_song_playlist, search);
                for (int j = 0; j < size_playlist; j++)
                {
                    string song_name_playlist = data_song_playlist[j].song;
                    for (auto &c : song_name_playlist)
                    {
                        c = tolower(c);
                    }
                    if (songname == song_name_playlist)
                    {
                        cout << "SONG ALREADY EXISTS IN PLAYLIST ,ADD A DIFFERENT SONG!!" << endl;
                        sleep(1);
                        songnotfound = false;
                        fio.close();
                        goto lblelse;
                    }
                }
                if (songnotfound)
                {
                    fio << data_song_list[i].song << "," << data_song_list[i].album << "," << data_song_list[i].artist << "," << data_song_list[i].genre << "," << data_song_list[i].link << "\n";
                    cout << "\nSONG INSERTED\n";
                    fio.close();
                    sleep(2);
                    break;
                }
            }
        }
    }
}
void remove_song()
{
    cin.clear();
    cin.sync();
    string search, playlistName, filename = userplaylist + ".csv";
    bool notfound = true;
    cout << "ENTER THE NAME OF THE PLAYLIST YOU WANT TO DELETE THE SONG FROM:";
    getline(cin, search);
    for (auto &c : search)
    {
        c = tolower(c);
    }
    cout << endl;
    ifstream fin(filename);
    if (!fin)
    {
        cout << "FILE COULDN'T BE OPENED!!" << endl;
        sleep(1);
    }

    else
    {
        search = userplaylist + search + ".csv";
        while (!fin.eof())
        {
            getline(fin, playlistName);
            for (auto &c : playlistName)
            {
                c = tolower(c);
            }
            if (search == playlistName)
            {
                notfound = false;
                break;
            }
        }
    }
    if (notfound)
    {
        cout << "PLAYLIST NOT FOUND , CREATE ONE AND TRY AGAIN!!" << endl;
        sleep(1);
        return;
    }
    fin.close();
    int pos;
    string songname;
    Info data_song_playlist[20];
    bool songnotfound = true;
    cout << "ENTER THE NAME OF THE SONG TO BE REMOVED:";
    getline(cin, songname);
    for (auto &c : songname)
    {
        c = tolower(c);
    }
    cout << endl;
    int size = readFile(data_song_playlist, search);
    for (int i = 0; i < size; i++)
    {
        string song_name_playlist = data_song_playlist[i].song;
        for (auto &c : song_name_playlist)
        {
            c = tolower(c);
        }
        if (songname == song_name_playlist)
        {
            songnotfound = false;
            pos = i;
            break;
        }
    }
    if (songnotfound)
    {
        cout << "SONG NOT FOUND IN THE PLAYLIST!!" << endl;
        sleep(1);
        return;
    }
    ofstream fio;
    fio.open(search);
    for (int i = 0; i < size - 1; i++)
    {
        if (i == pos)
        {
            continue;
        }
        else
        {
            fio << data_song_playlist[i].song << "," << data_song_playlist[i].album << "," << data_song_playlist[i].artist << "," << data_song_playlist[i].genre << "," << data_song_playlist[i].link << "\n";
        }
    }
    cout << "SONG DELETED\n";
    fio.close();
    sleep(2);
}
void edit_record_menu()
{
lbl:
    int subchoice;
    cin.clear();
    cin.sync();
    system("CLS");
    cout << "EDIT RECORDS MENU" << endl;
    cout << "1>INSERT SONG INTO YOUR PLAYLIST" << endl;
    cout << "2>REMOVE SONG FROM YOUR PLAYLIST" << endl;
    cout << "3>RETURN TO MAIN MENU" << endl;
    cout << "ENTER YOUR CHOICE:";
    cin >> subchoice;
    cout << endl;
    switch (subchoice)
    {
    case 1: //subfunction1
        system("CLS");
        insert_song();
        break;
    case 2: //subfunction2
        system("CLS");
        remove_song();
        break;
    case 3:
        system("CLS");
        return;
        break;
    default:
        cout << "INVALID INPUT" << endl;
        sleep(1);
        system("CLS");
        break;
    }
    goto lbl;
}
//-----------------------------------------DISPLAY RECORDS----------------------------------------------------
void display_playlist()
{
    cout << "YOUR PLAYLIST'S ARE:" << endl;
    string filename = userplaylist + ".csv", playlistName;
    ifstream fin(filename);
    if (!fin)
    {
        cout << "FILE COULDN'T BE OPENED!!" << endl;
        sleep(1);
    }
    else
    {
        while (!fin.eof())
        {
            getline(fin, playlistName);
            if (playlistName.length() != 0)
            {
                playlistName = playlistName.erase(0, userplaylist.length());
                int length = playlistName.length() - 4;
                playlistName = playlistName.erase(length);
                cout << playlistName << endl;
            }
        }
    }
    sleep(3);
    fin.close();
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
    cin.clear();
    cin.sync();
    system("CLS");
    cout << "FILTER BY -" << endl;
    cout << "1>ARTIST " << endl;
    cout << "2>SONG  " << endl;
    cout << "3>ALBUM " << endl;
    cout << "4>GENRE " << endl;
    cout << "5>RETURN TO PREVIOUS MENU" << endl;
    cout << "ENTER YOUR CHOICE ";
    cin >> Subchoice;
    cout << endl;
    cin.sync();
    switch (Subchoice)
    {
    case 1: //filter by artist
        system("CLS");
        fin.open("dummy.csv");
        if (!fin)
        {
            cout << "FILE COULDN'T BE OPENED" << endl;
            sleep(1);
        }
        else
        {
            cout << "ENTER THE NAME OF THE ARTIST:";
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
                    getline(fin, temp[i].genre, ',');
                    getline(fin, temp[i].link, '\n');
                    filtered[i].genre = temp[i].genre;
                    filtered[i].link = temp[i].link;
                    if (a == 0)
                    {
                        cout << " Results for " << filtered[i].artist << "-" << endl;
                        cout << "SONG" << setw(30) << "ALBUM" << setw(30) << "GENRE" << endl;

                        a++;
                    }
                    cout << filtered[i].song << setw(30) << filtered[i].album << setw(30) << filtered[i].genre << endl;
                    sleep(0.5);
                }
                else
                {
                    getline(fin, trash, '\n');
                }
                i++;
            }
            sleep(3);
            if (notfound)
            {
                cout << "NO RESULTS FOUND" << endl;
                sleep(1);
            }
        }
        fin.close();
        break;
    case 2: //filter by song
        system("CLS");
        fin.open("dummy.csv");
        if (!fin)
        {
            cout << "FILE COULDN'T BE OPENED" << endl;
            sleep(1);
        }
        else
        {
            cout << "ENTER THE NAME OF THE SONG:";
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
                    getline(fin, temp[i].genre, ',');
                    getline(fin, temp[i].link, '\n');
                    filtered[i].album = temp[i].album;
                    filtered[i].artist = temp[i].artist;
                    filtered[i].genre = temp[i].genre;
                    filtered[i].link = temp[i].link;
                    if (a == 0)
                    {
                        cout << "Results for " << filtered[i].song << "- " << endl;
                        cout << "ARTIST" << setw(30) << "ALBUM" << setw(30) << "GENRE" << endl;
                        a++;
                    }
                    cout << filtered[i].artist << setw(30) << filtered[i].album << setw(30) << filtered[i].genre << endl;
                    sleep(0.5);
                }
                else
                {
                    getline(fin, trash, '\n');
                }
                i++;
            }
            sleep(3);
            if (notfound)
            {
                cout << "NO RESULTS FOUND" << endl;
                sleep(1);
            }
        }
        fin.close();
        break;
    case 3: //filter by album
        system("CLS");
        fin.open("dummy.csv");
        if (!fin)
        {
            cout << "FILE COULDN'T BE OPENED" << endl;
            sleep(1);
        }
        else
        {
            cout << "ENTER THE NAME OF THE ALBUM:";
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
                    getline(fin, temp[i].genre, ',');
                    getline(fin, temp[i].link, '\n');
                    filtered[i].artist = temp[i].artist;
                    filtered[i].genre = temp[i].genre;
                    filtered[i].link = temp[i].link;
                    if (a == 0)
                    {
                        cout << "Results for the album " << filtered[i].album << "- " << endl;
                        a++;
                    }
                    cout << filtered[i].song << endl;
                    sleep(0.5);
                }
                else
                {
                    getline(fin, trash, '\n');
                }
                i++;
            }
            sleep(3);
            if (notfound)
            {
                cout << "NO RESULTS FOUND" << endl;
                sleep(1);
            }
        }
        fin.close();
        break;
    case 4: //filter by genre
        system("CLS");
        fin.open("dummy.csv");
        if (!fin)
        {
            cout << "FILE COULDN'T BE OPENED" << endl;
            sleep(1);
        }
        else
        {
            cout << "ENTER THE GENRE YOU WOULD LIKE TO SEARCH:";
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
                getline(fin, read, ',');
                for (auto &c : read)
                {
                    c = tolower(c);
                }
                if (read == search)
                {
                    getline(fin, temp[i].link, '\n');
                    for (auto &c : read)
                    {
                        c = toupper(c);
                    }
                    notfound = false;
                    filtered[i].genre = read;
                    filtered[i].song = temp[i].song;
                    filtered[i].artist = temp[i].artist;
                    filtered[i].album = temp[i].album;
                    filtered[i].link = temp[i].link;
                    if (a == 0)
                    {
                        cout << "Results for the genre " << filtered[i].genre << "- " << endl;
                        cout << "SONG" << setw(30) << "ARTIST" << endl;
                        a++;
                    }
                    cout << filtered[i].song << setw(30) << filtered[i].artist << endl;
                    sleep(0.5);
                }
                else
                {
                    getline(fin, trash, '\n');
                }
                i++;
            }
            sleep(3);
            if (notfound)
            {
                cout << "NO RESULTS FOUND" << endl;
                sleep(1);
            }
        }
        fin.close();
        break;
    case 5:
        system("CLS");
        return;
        break;
    default:
        cout << "INVALID INPUT" << endl;
        sleep(1);
        break;
    }
    goto lbl2;
}

void display_record_menu(Info data[])
{
lbl:
    int subchoice;
    int size;
    cin.clear();
    cin.sync();
    system("CLS");
    cout << endl
         << endl;
    cout << "DISPLAY RECORDS" << endl;
    cout << "1>DISPLAY ALL SONGS" << endl;
    cout << "2>FILTER SONGS AND SEARCH" << endl;
    cout << "3>DISPLAY YOUR PLAYLISTS " << endl;
    cout << "4>RETURN TO MAIN MENU" << endl;
    cout << "ENTER YOUR CHOICE:";
    cin >> subchoice;
    cout << endl;
    switch (subchoice)
    {
    case 1: //subfunction1
        system("CLS");
        cout << "ALL RECORDS" << endl;
        cout << endl;
        size = readFile(data, "dummy.csv");
        display_all_records(data, size);
        break;
    case 2: //subfunction2
        system("CLS");
        filter_records();
        break;
    case 3:
        system("CLS");
        display_playlist();
        break;
    case 4:
        system("CLS");
        return;
        break;
    default:
        cout << "INVALID INPUT" << endl;
        sleep(1);
        system("CLS");
        break;
    }
    goto lbl;
}

//------------------------------------------PLAY PLAYLIST------------------------------------------------------
void shuffle()
{
lbl3:
    int choice, i = 0;
    Info data[100];
    bool notfound = true;
    cin.clear();
    cin.sync();
    system("CLS");
    string search, playlistName, filename = userplaylist + ".csv";
    cout << "ENTER THE NAME OF THE PLAYLIST YOU WANT TO PLAY:";
    getline(cin, search);
    search = userplaylist + search + ".csv";
    int size = readFile(data, search);
    size = size - 1;
    cout << size << endl;
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        arr[i] = count;
        count++;
    }
    randomize(arr, size);
lbl1:
    string link = "open " + data[arr[i]].link + " alias MyFile";
    int a = 0;
    mciSendStringA(link.c_str(), NULL, 0, 0);
    mciSendString(TEXT("play MyFile "), NULL, 0, 0);
lbl:
    system("CLS");
    if (a == 0)
    {
        cout << "Options\n1>PAUSE\n2>PLAY NEXT SONG\n3>PLAY PREVIOUS SONG\n4>CHOOSE ANOTHER PLAYLIST\n5>STOP\nENTER YOUR CHOICE:" << endl;
        cout << "NOW playing  " << data[arr[i]].song << " by " << data[arr[i]].artist << " ";
        cout.flush();
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            cout.flush();
            sleep(1);
        }
        cout << "\b\b\b   \b\b\b";
        cout << endl;
        cin >> choice;
        choice = choice + 1;
    }
    else
    {
        cout << "Options\n1>CONTINUE\n2>PAUSE\n3>PLAY NEXT SONG\n4>PLAY PREVIOUS SONG\n5>CHOOSE ANOTHER PLAYLIST\n6>STOP\nENTER YOUR CHOICE:" << endl;
        cout << "NOW playing  " << data[arr[i]].song << " by " << data[arr[i]].artist << " ";
        cout.flush();
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            cout.flush();
            sleep(1);
        }
        cout << "\b\b\b   \b\b\b";
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        mciSendString(TEXT("play MyFile "), NULL, 0, 0);
        break;
    case 2:
        a++;
        mciSendString(TEXT("pause MyFile "), NULL, 0, 0);
        break;
    case 3:
        if (i + 1 <= (size - 1))
        {
            i = i + 1;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            goto lbl1;
        }
        else
        {
            cout << "-.-.-" << endl;
            i = 0;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            randomize(arr, size);
            goto lbl1;
        }
        break;
    case 4:
        if (i - 1 >= 0)
        {
            i = i - 1;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            goto lbl1;
        }
        else
        {
            i = size - 1;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            goto lbl1;
        }
        break;
    case 5:
        mciSendString(TEXT("close MyFile"), NULL, 0, 0);
        goto lbl3;
        break;
    case 6:
        mciSendString(TEXT("close MyFile"), NULL, 0, 0);
        return;
    default:
        cout << "INVALID CHOICE" << endl;
        sleep(1);
        break;
    }
    goto lbl;
}

void randomize(int arr[], int size)
{
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(arr, i, j);
    }
}
void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void play_playlist()
{
lbl3:
    int choice, i = 0, size;
    Info data[100];
    bool notfound = true;
    cin.clear();
    cin.sync();
    system("CLS");
    string playlistName, search, filename = userplaylist + ".csv";
    cout << "ENTER THE NAME OF THE PLAYLIST YOU WANT TO PLAY:";
    getline(cin, search);
    cout << endl;
    ifstream fin(filename);
    if (!fin)
    {
        cout << "FILE COULDN'T BE OPENED!!" << endl;
        sleep(1);
    }
    else
    {
        search = userplaylist + search + ".csv";
        while (!fin.eof())
        {
            getline(fin, playlistName);
            if (search == playlistName)
            {
                notfound = false;
                break;
            }
        }
    }
    if (notfound)
    {
        cout << "PLAYLIST NOT FOUND,PLEASE CREATE ONE AND TRY AGAIN!!" << endl;
        sleep(1);
        return;
    }
    size = readFile(data, search);
lbl1:
    string link = "open " + data[i].link + " alias MyFile";
    int a = 0;
    mciSendStringA(link.c_str(), NULL, 0, 0);
    mciSendString(TEXT("play MyFile "), NULL, 0, 0);
lbl:
    system("CLS");
    if (a == 0)
    {
        cout << "Options\n1>PAUSE\n2>PLAY NEXT SONG\n3>PLAY PREVIOUS SONG\n4>CHOOSE ANOTHER PLAYLIST\n5>STOP\nENTER YOUR CHOICE:" << endl;
        cout << "NOW playing  " << data[i].song << " by " << data[i].artist << " ";
        cout.flush();
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            cout.flush();
            sleep(1);
        }
        cout << "\b\b\b   \b\b\b";
        cout << endl;
        cin >> choice;
        choice = choice + 1;
    }
    else
    {
        cout << "Options\n1>CONTINUE\n2>PAUSE\n3>PLAY NEXT SONG\n4>PLAY PREVIOUS SONG\n5>CHOOSE ANOTHER PLAYLIST\n6>STOP\nENTER YOUR CHOICE: " << endl;
        cout << "NOW playing  " << data[i].song << " by " << data[i].artist << " ";
        cout.flush();
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            cout.flush();
            sleep(1);
        }
        cout << "\b\b\b   \b\b\b";
        cout << endl;
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        mciSendString(TEXT("play MyFile "), NULL, 0, 0);
        break;
    case 2:
        a++;
        mciSendString(TEXT("pause MyFile "), NULL, 0, 0);
        break;
    case 3:
        if (i + 1 < (size - 1))
        {
            i = i + 1;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            goto lbl1;
        }
        else
        {
            cout << "-.-.-" << endl;
            i = 0;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            goto lbl1;
        }
        break;
    case 4:
        if (i - 1 >= 0)
        {
            i = i - 1;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            goto lbl1;
        }
        else
        {
            i = size - 2;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            goto lbl1;
        }
        break;
    case 5:
        mciSendString(TEXT("close MyFile"), NULL, 0, 0);
        goto lbl3;
        break;
    case 6:
        mciSendString(TEXT("close MyFile"), NULL, 0, 0);
        return;
    default:
        cout << "INVALID CHOICE" << endl;
        sleep(1);
        break;
    }
    goto lbl;
}

void play_playlist_menu()
{
lbl:
    cin.clear();
    cin.sync();
    system("CLS");
    system("color 0B");
    int subchoice;
    cout << "PLAY" << endl;
    cout << "1>PLAY FROM PLAYLIST" << endl;
    cout << "2>SHUFFLE PLAY " << endl;
    cout << "3>RETURN TO MAIN MENU" << endl;
    cout << "ENTER YOUR CHOICE:";
    cin >> subchoice;
    cout << endl;
    switch (subchoice)
    {
    case 1: //subfunction1
        system("CLS");
        play_playlist();
        break;
    case 2: //subfunction2
        system("CLS");
        cout << "SHUFFLE PLAY" << endl;
        shuffle();
        break;
    case 3:
        system("CLS");
        return;
        break;

    default:
        cout << "INVALID INPUT" << endl;
        sleep(1);
        break;
    }
    goto lbl;
}

void display_all_records(Info data[], int size)
{
    system("CLS");
    cout << setw(30) << "SONG" << setw(30) << "ALBUM" << setw(30) << "ARTIST" << setw(30) << "GENRE" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << setw(30) << data[i].song << setw(30) << data[i].album << setw(30) << data[i].artist << setw(30) << data[i].genre << endl;
        sleep(0.5);
    }
    sleep(7);
}

//-------------------------------OTHER IMPORTANT FUNCTIONS------------------------------------------------------
int readFile(Info data[], string filename)
{
    ifstream fin;
    int size = 0;
    fin.open(filename);
    bool notfound = true;
    if (!fin)
    {
        cout << "FILE COULDN'T BE OPENED" << endl;
        sleep(1);
    }
    else
    {
        int i = 0;
        while (!fin.eof())
        {
            getline(fin, data[i].song, ',');
            getline(fin, data[i].album, ',');
            getline(fin, data[i].artist, ',');
            getline(fin, data[i].genre, ',');
            getline(fin, data[i].link, '\n');
            i++;
            size++;
        }
    }
    return size;
}

string signup()
{
    string username, password, confirmpass;
    system("color 90");
    cout << "FILL IN THE REQUIRED DETAILS" << endl;
    cout << "USERNAME:";
    cin.clear();
    cin.sync();
    getline(cin, username);
    cout << endl;
l1:
    sleep(1);
    system("color 90");
    cout << "PASSWORD:";
    getline(cin, password);
    cout << endl;
    if (password.length() < 6)
    {
        system("color C0");
        cout << "PASSWORD SHOULD HAVE A MIN OF 6 CHARACTERS" << endl;
        password = "";
        goto l1;
    }
    cout << "Re-enter PASSWORD: ";
    getline(cin, confirmpass);

    if (password != confirmpass)
    {
        system("color C0");
        cout << "PASSWORDS DONT MATCH , PLEASE RETRY" << endl;
        password = "";
        confirmpass = "";
        goto l1;
    }
    for (int i = 0; i < password.length(); i++)
        password.at(i) = password.at(i) + password.length();
    string filename = username;
    addLoginData(username, password, filename);
    userplaylist = signin();
    return userplaylist;
}

string signin()
{
label:
    string input;
    int size, i;
    bool usernotfound = true;
    bool passnotfound = true;
    cin.clear();
    cin.sync();
    string username, password;
    password = "";
    char hash;
    system("color F4");
    cout << "ENTER LOGIN CREDENTIALS" << endl;
    cout << "USERNAME:";
    getline(cin, username);
    size = readLoginData(details);
    for (i = 0; i < size; i++)
    {
        if (details[i].username == username)
        {
            cout << endl;
            usernotfound = false;
        retry:
            cout << "PASSWORD:";
            hash = _getch();
            while (hash != 13) //this is for enter
            {
                if (hash == 8)
                {
                    password.pop_back();
                    putch('\b');
                    putch(' ');
                    putch('\b');
                    goto back;
                }
                password.push_back(hash);
                cout << "*";
            back:
                hash = _getch();
            }
            for (int i = 0; i < password.length(); i++)
                password.at(i) = password.at(i) + password.length();
            if (details[i].password == password)
            {
                system("color 2E");
                cout << endl;
                cout << "LOGIN SUCCESSFUL";
                sleep(2);
                cout << endl;
                system("CLS");
                system("color E4");
                cout << "WELCOME BACK " << details[i].username << endl;
                break;
            }

            else
            {

                sleep(1);
                system("CLS");
                system("color C0");
                cout << "INCORRECT PASSWORD . PLEASE TRY AGAIN  " << endl;
                sleep(2);
                system("color F4");
                system("CLS");
                password = "";
                goto retry;
            }
        }
    }
    if (usernotfound)
    {
        cout << "USERNAME NOT FOUND" << endl;
        cout << "ARE YOU SURE YOU HAVE AN ACCOUNT IN EXISTENCE? (Y/N)" << endl;
        cin >> input;
        cout << endl;
        if (input == "Y" || input == "y")
            goto label;
        else
        {
            cout << "MAKE A NEW ACCOUNT , ITS EASY" << endl;
            signup();
        }
    }
    cout << endl;
    return details[i].masterplaylist;
}

void addLoginData(string username, string password, string filename)
{
    string username1 = username;
    string password1 = password;
    string name1 = filename;
    fstream fout;
    fout.open("accountdata.csv", ios::out | ios::app);
    fout << username1 << "," << password1 << "," << name1 << "\n";

    system("color 2E");
    cout << "ACCOUNT CREATED SUCCESSFULLY" << endl;
    sleep(1);
    system("color F4");
    system("CLS");
    fout.close();
}

int readLoginData(Login details[])
{
    ifstream fin;
    int size = 0;
    fin.open("accountdata.csv");
    if (!fin)
    {
        cout << "FILE COUDLN'T BE OPENED" << endl;
        sleep(1);
    }
    else
    {
        int i = 0;
        while (!fin.eof())
        {
            getline(fin, details[i].username, ',');
            getline(fin, details[i].password, ',');
            getline(fin, details[i].masterplaylist, '\n');
            i++;
            size++;
        }
    }
    fin.close();
    return size;
}