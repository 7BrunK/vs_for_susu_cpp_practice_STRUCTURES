#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum styles {
    Funk,
    Soul,
    Jazz,
    Rock
};

struct song {
    string name;
    float duration;
};

struct album {
    string name;
    string artist;
    styles style;
    int year;
    float total_duration;
    int songs_number;
    int listeners = 0;
    song* songs;
};

string formatted_style(styles style) {
    string formatted_style;
    switch (style) {
        case Funk:
            formatted_style = "Funk";
            break;
        case Soul:
            formatted_style = "Soul";
            break;
        case Jazz:
            formatted_style = "Jazz";
            break;
        case Rock:
            formatted_style = "Rock";
            break;
        default:
            formatted_style = "Unknown";
            break;
    }
    return formatted_style;
}

const size_t ALBUMS_COUNT = 20;

album* init() {
    album* albums = new album[ALBUMS_COUNT];

    for (int i = 0; i < ALBUMS_COUNT; i++) {
        albums[i].name = "Album_" + to_string(i);
        albums[i].artist = (i % 3 == 0) ? "Linkin Park" : "Artist_" + to_string(i);

        styles style;
        if (i % 2 == 0) {
            if (i % 4 == 0) style = Funk;
            else style = Soul;
        }
        else if (i % 3 == 0) style = Jazz;
        else style = Rock;
        albums[i].style = style;

        albums[i].year = 2000 + i;
        albums[i].songs_number = 3;

        albums[i].songs = new song[albums[i].songs_number];
        float total = 0;
        for (int j = 0; j < albums[i].songs_number; j++) {
            albums[i].songs[j].name = "Song_" + to_string(j);
            float duration = i + j;
            albums[i].songs[j].duration = duration;
            total += duration;
        }
        albums[i].total_duration = total;
    }

    return albums;
}

album* filter_funk_soul(album* arr, int& size_filtered) {
    album* result = new album[ALBUMS_COUNT];
    size_filtered = 0;
    for (int i = 0; i < ALBUMS_COUNT; i++) {
        if (arr[i].style == Funk || arr[i].style == Soul) {
            result[size_filtered] = arr[i];
            size_filtered++;
        }
    }
    return result;
}

bool cmp_years(const album& lhs, const album& rhs) {
    return lhs.year < rhs.year;
}
void bubble_sort_by(album* arr, int size, bool (*cmp)(const album&, const album&)) {
    for (size_t i = 0; i < size; i++)
    {
        bool sorted = true;
        for (size_t j = 1; j < size - i; j++)
        {
            if (!cmp(arr[j - 1], arr[j])) {
                swap(arr[j - 1], arr[j]);
                sorted = false;
            }
        }
        if (sorted) break;
    }
}

void print_album(const album& a) {
    cout << "\nAlbum: " << a.name
        << "\nArtist: " << a.artist
        << "\nStyle: " << formatted_style(a.style)
        << "\nYear: " << a.year
        << "\nDuration: " << a.total_duration
        << "\nListeners: " << a.listeners
        << "\nSongs:\n";

    for (int i = 0; i < a.songs_number; i++) {
        cout << " - " << a.songs[i].name << " (" << a.songs[i].duration << " min's)\n";
    }
}

bool cmp_durations(const album& lhs, const album& rhs) {
    return lhs.total_duration < rhs.total_duration;
}
void print_top3_longest(album* arr, int size) {
    bubble_sort_by(arr, size, cmp_durations);

    cout << "\n3 longest albums:\n";
    for (int i = 0; i < 3 && i < size; i++) {
        print_album(arr[i]);
    }
}

void edit_album(album& a) {
    cout << "\nEdit album: " << a.name << endl;
    cout << "Enter new name: ";
    cin >> a.name;

    cout << "Enter new year: ";
    cin >> a.year;
}

album* filter_linkin_park(album* arr, int& size_filtered) {
    album* result = new album[ALBUMS_COUNT];
    size_filtered = 0;
    for (int i = 0; i < ALBUMS_COUNT; i++) {
        if (arr[i].artist == "Linkin Park") {
            result[size_filtered] = arr[i];
            size_filtered++;
        }
    }
    return result;
}

void print_array(album* arr, int size) {
    for (int i = 0; i < size; i++) {
        print_album(arr[i]);
    }
}

void free_albums(album* arr, int size) {
    for (int i = 0; i < size; i++) {
        delete[] arr[i].songs;
    }
    delete[] arr;
}

void read_file(album albums[]) {
    ifstream fin;
    int listeners;
    fin.open("listeners.txt");
    int i = 0;
    if (fin.is_open()) {
        while (!fin.eof())
        {
            fin >> listeners;
            albums[i].listeners = listeners;
            i++;
        }
    }
    fin.close();
    cout << "Чтение LISTENERS из файла:\n";
    print_array(albums, ALBUMS_COUNT);
}

void binary_output(album albums[]) {
    ofstream out("binary.txt",
        ios::binary | ios::out);
    for (int i = 0; i < ALBUMS_COUNT; i++)
    {
        out.write((char*)&albums[i], sizeof(albums[i]));
    }
    out.close();
    cout << "Запись в бинарный файл.\n";
}

void binary_input(album albums[]) {
    fstream in("binary.txt", ios::binary | ios::in);
    int i = 0;
    if (in.is_open()) {
        while (!in.eof())
        {
            in.read((char*)&albums[i], sizeof(albums[i]));
            i++;
        }
        in.close();
    }
    
    cout << "Чтение из бинарного файла:\n";
    print_array(albums, ALBUMS_COUNT);
}

int main() {
    album* albums = init();

    int filtered_size;
    album* funk_soul = filter_funk_soul(albums, filtered_size);

    bubble_sort_by(funk_soul, filtered_size, cmp_years);

    cout << "\nFiltered (Funk/Soul) sorted by year:\n";
    print_array(funk_soul, filtered_size);

    print_top3_longest(albums, ALBUMS_COUNT);

    edit_album(albums[0]);

    int lp_size;
    album* lp_albums = filter_linkin_park(albums, lp_size);

    cout << "\nLinkin Park albums:\n";
    print_array(lp_albums, lp_size);

    cout << "\n10 занятие\n\n";
    read_file(albums);
    binary_input(albums);
    binary_output(albums);
    
    // освобождение памяти
    delete[] funk_soul;
    delete[] lp_albums;
    free_albums(albums, ALBUMS_COUNT);

    return 0;
}
