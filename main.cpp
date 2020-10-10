#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

typedef struct info
{
    string artist;
    string album;
    string song;
    string genre;
    string link;
} Info;
typedef struct login
{
    string username;
    string password;
    string masterplaylist;
} Login;

Login details[100];
int arr[100];

struct playlist : info //Inheriting from info structure
{
    struct playlist *next;
} * head;

int size = 0;

void create_playlist_menu();
void edit_record_menu();
void display_record_menu(Info data[]);
int readFile(Info data[], string filename);
void display_all_records(Info data[], int size);
void play_playlist_menu();
void filter_records();
void shuffle();
void randomize(int arr[],int);
void swap(int arr[],int,int);
string signin();
string signup();
void addLoginData(string, string, string);
int readLoginData(Login details[]);
string userplaylist;
int main()
{
    Info data[100];
    int loginchoice;
login:
    cout << "WELCOME TO insert_name " << endl;
    cout << "Sign in To continue" << endl;
    cout << "1>Already have an account?" << endl;
    cout << "2>Create new account" << endl;
    cout << "3>Quit application" << endl;
label:
    cout << "Enter your choice- ";
    cin >> loginchoice;
    cout << endl;
    switch (loginchoice)
    {
    case 1: //call signin func
        userplaylist = signin();
        break;
    case 2: //call signup function
        userplaylist = signup();
        break;
    case 3:
        exit(0);
        break;
    default:
        cout << "Invalid Input" << endl;
        goto label;
    }
lbl:
    int choice, subchoice;
    string input;
    cout << "MENU\n";
    cout << "1>Create playlist" << endl;
    cout << "2>Display records" << endl;
    cout << "3>Edit your playlist" << endl;
    cout << "4>Play Playlist" << endl;
    cout << "5>Logout" << endl;
    cout << "6>Exit" << endl;
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
        cout << "Are you sure you want to logout (Y/N)?" << endl;
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
    cout << "Enter the name of the playlist:";
    cin >> name;
    cout << endl;
    name = userplaylist + name + ".csv";
    ofstream fout;
    fout.open(userplaylist + ".csv", ios::app);
    fout << name << "\n";
    fout.close();
    size = readFile(data, "dummy.csv");
lbl:
    cout << "Menu" << endl;
    cout << "1>Display available songs" << endl;
    cout << "2>Add song to playlist" << endl;
    cout << "3>View songs in current playlist" << endl;
    cout << "4>Save the playlist" << endl;
    cout << "Enter your choice:";
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
void insert_song()
{
    cin.clear();
    cin.sync();
    string search, playlistName, filename = userplaylist + ".csv";
    bool notfound = true;
    cout << "Enter the name of the playlist you want to insert the song into:";
    getline(cin, search);
    for (auto &c : search)
    {
        c = tolower(c);
    }
    cout << endl;
    ifstream fin(filename);
    if (!fin)
    {
        cout << "file could not be opened!!" << endl;
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
        cout << "playlist not found , pls create playlist and then try!!" << endl;
        return;
    }
    fin.close();
lblelse:
    cin.clear();
    cin.sync();
    fstream fio(search, ios::in | ios::out | ios::app);
    if (!fio)
    {
        cout << "Error in opening file!!" << endl;
    }
    else
    {
        Info data_song_list[30], data_song_playlist[30];
        string songname;
        cout << "Enter the name of the song you would like to enter:";
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
                        cout << "Song already exists in the playlist,Enter another a song!!" << endl;
                        songnotfound = false;
                        fio.close();
                        goto lblelse;
                    }
                }
                if (songnotfound)
                {
                    fio << data_song_list[i].song << "," << data_song_list[i].album << "," << data_song_list[i].artist << "," << data_song_list[i].genre << "," << data_song_list[i].link << "\n";
                    cout << "\nSong inserted\n";
                    fio.close();
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
    cout << "Enter the name of the playlist you want to delete the song from:";
    getline(cin, search);
    for (auto &c : search)
    {
        c = tolower(c);
    }
    cout << endl;
    ifstream fin(filename);
    if (!fin)
    {
        cout << "file could not be opened!!" << endl;
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
        cout << "playlist not found , pls create playlist and then try!!" << endl;
        return;
    }
    fin.close();
    int pos;
    string songname;
    Info data_song_playlist[20];
    bool songnotfound = true;
    cout << "Enter the name of the song to be removed:";
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
        cout << "song not found in playlist!!" << endl;
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
    cout << "\nSong deleted\n";
    fio.close();
}
void edit_record_menu()
{
lbl:
    int subchoice;
    cout << "Edit records Menu" << endl;
    cout << "1>Insert song into your playlist" << endl;
    cout << "2>Remove song from your playlist" << endl;
    cout << "3>Return to main menu" << endl;
    cout << "Enter your choice:";
    cin >> subchoice;
    cout << endl;
    switch (subchoice)
    {
    case 1: //subfunction1
        insert_song();
        break;
    case 2: //subfunction2
        remove_song();
        break;
    case 3:
        return;
        break;
    default:
        cout << "Invalid Input" << endl;
    }
    goto lbl;
}

void display_record_menu(Info data[])
{
lbl:
    int subchoice;
    int size;
    cout << "Display records" << endl;
    cout << "1>Display all songs" << endl;
    cout << "2>Filter songs and search" << endl;
    cout << "3>Return to main menu" << endl;
    cout << "Enter your choice:";
    cin >> subchoice;
    cout << endl;

    switch (subchoice)
    {
    case 1: //subfunction1
        cout << "all records" << endl;
        cout << endl;
        size = readFile(data, "dummy.csv");
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
                    getline(fin, temp[i].genre,',');
                    getline(fin,temp[i].link,'\n');
                    filtered[i].genre = temp[i].genre;
                    filtered[i].link=temp[i].link;
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
                    getline(fin, temp[i].genre,',');
                    getline(fin, temp[i].link, '\n');
                    filtered[i].album = temp[i].album;
                    filtered[i].artist = temp[i].artist;
                    filtered[i].genre = temp[i].genre;
                    filtered[i].link=temp[i].link;
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
                    getline(fin, temp[i].genre,',');
                    getline(fin, temp[i].link, '\n');
                    filtered[i].artist = temp[i].artist;
                    filtered[i].genre = temp[i].genre;
                    filtered[i].link=temp[i].link;
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
                getline(fin, read,',');
                for (auto &c : read)
                {
                    c = tolower(c);
                }
                if (read == search)
                {
                    getline(fin,temp[i].link,'\n');
                    for (auto &c : read)
                    {
                        c = toupper(c);
                    }
                    notfound = false;
                    filtered[i].genre = read;
                    filtered[i].song = temp[i].song;
                    filtered[i].artist = temp[i].artist;
                    filtered[i].album = temp[i].album;
                    filtered[i].link= temp[i].link;
                    if (a == 0)
                    {
                        cout << "Results for the genre " << filtered[i].genre << "- " << endl;
                        cout << "Song" << setw(30) << "artist" << endl;
                        a++;
                    }
                    cout << filtered[i].song << setw(30) << filtered[i].artist << endl;
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
    case 5:
        return;
        break;
    default:
        cout << "invalid input" << endl;
    }
    goto lbl2;
}
void shuffle()
{

lbl3:
    int choice, i = 0;
    Info data[100];
    bool notfound = true;
    cin.clear();
    cin.sync();
    string search, playlistName, filename = userplaylist + ".csv";
    cout << "enter the name of the playlist you want to play:";
    getline(cin, search);
     search = userplaylist + search + ".csv";
    int size = readFile(data,search);
    size=size-1;
    cout<<size<<endl;
    int count=0;

    for(int i=0;i<size;i++)
    {
        arr[i]=count;
        count++;
    }
    randomize(arr,size);
    

    lbl1:
    for (int i = 0; i < size; i++) 
		cout << arr[i] << " "; 
	cout << "\n";
    string link = "open " + data[arr[i]].link + " alias MyFile";
    int a = 0;
    mciSendStringA(link.c_str(), NULL, 0, 0);
    mciSendString(TEXT("play MyFile "), NULL, 0, 0);
lbl:
    if (a == 0)
    {
        cout << "Options\n1>pause\n2>Play next song\n3>Play previous song\n4>Choose another playlist\n5>stop\nEnter your choice:";
        cin >> choice;
        choice = choice + 1;
    }
    else
    {
        cout << "Options\n1>continue\n2>pause\n3>Play next song\n4>Play previous song\n5>Choose another playlist\n6>stop\nEnter your choice:";
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
            cout << "in else" << endl;
            i = 0;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            randomize(arr,size);
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
        cout << "Invalid choice" << endl;
    }
    goto lbl;
 


}

void randomize(int arr[],int size)
{
    srand(time(NULL));
    for(int i=size-1;i>0;i--)
    {
        int j=rand()%(i+1);
        swap(arr,i,j);
    }
}
void swap(int arr[],int i,int j)
{
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
void play_playlist()
{
lbl3:
    int choice, i = 0, size;
    Info data[100];
    bool notfound = true;
    cin.clear();
    cin.sync();
    string playlistName, search, filename = userplaylist + ".csv";
    cout << "enter the name of the playlist you want to play:";
    getline(cin, search);
    cout << endl;
    ifstream fin(filename);
    if (!fin)
    {
        cout << "file could not be opened!!" << endl;
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
        cout << "playlist not found , pls create playlist and then try!!" << endl;
        return;
    }
    size = readFile(data, search);
    
lbl1:
    string link = "open " + data[i].link + " alias MyFile";
    int a = 0;
    mciSendStringA(link.c_str(), NULL, 0, 0);
    mciSendString(TEXT("play MyFile "), NULL, 0, 0);
lbl:
    if (a == 0)
    {
        cout << "Options\n1>pause\n2>Play next song\n3>Play previous song\n4>Choose another playlist\n5>stop\nEnter your choice:";
        cin >> choice;
        choice = choice + 1;
    }
    else
    {
        cout << "Options\n1>continue\n2>pause\n3>Play next song\n4>Play previous song\n5>Choose another playlist\n6>stop\nEnter your choice:";
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
            cout << "in else" << endl;
            i = 0;
            mciSendString(TEXT("close MyFile"), NULL, 0, 0);
            goto lbl1;
        }
        break;
    case 4:
        if (i-1>=0)
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
        cout << "Invalid choice" << endl;
    }
    goto lbl;
}

void play_playlist_menu()
{
lbl:
    int subchoice;
    cout << "Play playlist" << endl;
    cout << "1>Play song from playlist" << endl;
    cout << "2>Shuffle play" << endl;
    cout << "3>Return to main menu" << endl;
    cout << "Enter your choice:";
    cin >> subchoice;
    cout << endl;
    switch (subchoice)
    {
    case 1: //subfunction1
        play_playlist();
        break;
    case 2: //subfunction2
        cout << "Shuffle play" << endl;
        shuffle();
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
int readFile(Info data[], string filename)
{
    ifstream fin;
    int size = 0;
    fin.open(filename);
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
    cout << "Fill in the required details" << endl;
    cout << "USERNAME:";
    cin.clear();
    cin.sync();
    getline(cin, username);
    cout << endl;
l1:
    cout << "PASSWORD:";
    getline(cin, password);
    cout << endl;
    if (password.length() < 6)
    {
        cout << "Password should have a minimum of 6 characters" << endl;
        password = "";
        goto l1;
    }
    cout << "Re-enter PASSWORD: ";
    getline(cin, confirmpass);

    if (password != confirmpass)
    {
        cout << "Passwords dont match,Retry" << endl;
        password = "";
        confirmpass = "";
        goto l1;
    }
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
    cout << "Enter login credentials" << endl;
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
            getline(cin, password);
            if (details[i].password == password)
            {
                cout << endl;
                cout << "Welcome back " << details[i].username << endl;
                break;
            }

            else
            {
                cout << "Incorrect password .Please Try again " << endl;
                goto retry;
            }
        }
    }
    if (usernotfound)
    {
        cout << "Username not found" << endl;
        cout << "Are you sure you have an account in existence? (Y/N)" << endl;
        cin >> input;
        cout << endl;
        if (input == "Y" || input == "y")
            goto label;
        else
        {
            cout << "Make a new account now .Its easy" << endl;
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

    cout << "Account created successfully" << endl;
    fout.close();
}

int readLoginData(Login details[])
{
    ifstream fin;
    int size = 0;
    fin.open("accountdata.csv");
    if (!fin)
    {
        cout << "file could not be opened" << endl;
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