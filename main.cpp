#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int player_balance = 0;
int player_choice = 0;

string suits[4] = {"clubs", "diamonds", "hearts", "spades"};
string ranks[13] {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

string deck[52] = {};

int main() {
    int card_number = 0;
    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 13; r++) {
            deck[card_number] = ranks[r] + " of " + suits[s];
            card_number++;
        }
    }

    cout << "shuffling deck..." << endl;

    srand(time(NULL));
    // int shuffle_swaps = rand() % 500;
    for (int x = 0; x < 1000; x++) {
        int card_1_index = rand() % card_number;
        int card_2_index = rand() % card_number;
        string card_temp = deck[card_1_index];

        deck[card_1_index] = deck[card_2_index];
        deck[card_2_index] = card_temp;

    }

    // for (int i = 0; i < card_number; i++) {
    //     cout << deck[i] << endl;
    // }

    cout << deck[0] + " and " + deck[1] << endl;

    cout << "hit (1) or stand (2)" << endl;
    cin >> player_choice;

    if (player_choice == 1) {
        cout << "you hit" << endl;
    }
    else if (player_choice == 2) {
        cout << "you stand" << endl;
    }


    return 0;
}
