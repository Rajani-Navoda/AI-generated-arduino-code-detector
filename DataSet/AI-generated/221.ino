#include <AceSorting.h>  // Include the AceSorting library

struct Player {
    String name;
    int score;
};

// Function to compare players by name
bool compareByName(const Player &a, const Player &b) {
    return a.name < b.name;
}

// Function to compare players by (score, name)
bool compareByScoreAndName(const Player &a, const Player &b) {
    if (a.score == b.score) {
        return a.name < b.name;
    }
    return a.score < b.score;
}

// Function to print the players
void printPlayers(const Player players[], int size) {
    for (int i = 0; i < size; i++) {
        Serial.print(players[i].name);
        Serial.print(" ");
        Serial.println(players[i].score);
    }
}

void setup() {
    Serial.begin(9600);
    delay(1000);  // Give time for Serial Monitor to open

    // Create an array of players
    Player players[] = {
        {"Michael", 3},
        {"Soren", 1},
        {"Arun", 5},
        {"Meilin", 6},
        {"Emilia", 3},
        {"Dimitri", 2},
        {"Dembe", 8},
        {"Nasir", 10},
        {"Hiromi", 9},
        {"Petra", 6}
    };
    const int numPlayers = sizeof(players) / sizeof(players[0]);

    // Print unsorted players
    Serial.println("Unsorted");
    Serial.println("--------");
    printPlayers(players, numPlayers);

    // Sort by name
    shellSortKnuth(players, numPlayers, compareByName);
    Serial.println("\nSorted by name");
    Serial.println("--------------");
    printPlayers(players, numPlayers);

    // Sort by (score, name)
    shellSortKnuth(players, numPlayers, compareByScoreAndName);
    Serial.println("\nSorted by (score, name)");
    Serial.println("-----------------------");
    printPlayers(players, numPlayers);
}

void loop() {
    // Do nothing
}
