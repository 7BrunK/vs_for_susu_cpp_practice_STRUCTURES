#include <iostream>
#include <string>

using namespace std;

enum style {
    Funk,
    Soul,
    Jazz
};

struct date {
    int year, month, day;
};

struct song {
    string name;
    float duration;
};

struct album {
    song* songs;
    string name;
    string artist;
    int songs_number;
};

const size_t ALBUMS_COUNT = 20;
album* init() {
    album* albums = new album[ALBUMS_COUNT];
    // Альбом 1
    albums[0].name = "Midnight Groove";
    albums[0].artist = "The Funk Masters";
    albums[0].songs_number = 3;
    albums[0].songs = new song[3]{
        {"Night Walk", 3.5},
        {"Groove Machine", 4.2},
        {"Funky Lights", 5.1}
    };
    // Альбом 2
    albums[1].name = "Soul Vibes";
    albums[1].artist = "Linkin Park";
    albums[1].songs_number = 2;
    albums[1].songs = new song[2]{
        {"Deep Love", 4.0},
        {"Heart Whisper", 3.8}
    };
    // Альбом 3
    albums[2].name = "Jazz Nights";
    albums[2].artist = "Linkin Park";
    albums[2].songs_number = 4;
    albums[2].songs = new song[4]{
        {"Late Sax", 6.2},
        {"Smooth Piano", 5.5},
        {"City Rain", 4.7},
        {"Quiet Street", 5.0}
    };
    // Альбом 4
    albums[3].name = "Golden Funk";
    albums[3].artist = "Retro Beat";
    albums[3].songs_number = 3;
    albums[3].songs = new song[3]{
        {"Old School", 3.9},
        {"Vinyl Spin", 4.3},
        {"Back in Time", 4.8}
    };
    // Альбом 5
    albums[4].name = "Soul Emotions";
    albums[4].artist = "Marvin Clay";
    albums[4].songs_number = 2;
    albums[4].songs = new song[2]{
        {"Broken Dreams", 4.6},
        {"Stay With Me", 5.2}
    };
    // Остальные
    for (size_t i = 5; i < ALBUMS_COUNT; i++) {
        albums[i].name = "Album " + to_string(i + 1);
        albums[i].artist = "Unknown Artist";
        albums[i].songs_number = 1;
        albums[i].songs = new song[1]{
            {"Untitled Track", 3.0f}
        };
    }
    return albums;
}

album* albums = init();

int main()
{
    
}
