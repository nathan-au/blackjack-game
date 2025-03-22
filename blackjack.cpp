#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

string* createDeck() {
    string suits[4] = {"clubs", "diamonds", "hearts", "spades"};
    string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    static string deck[52] = {};

    int card_index = 0;
    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 13; r++) {
            deck[card_index] = ranks[r] + " of " + suits[s];
            card_index++;
        }
    }

    srand(time(NULL));
    // int shuffle_swaps = rand() % 500;
    for (int x = 0; x < 1000; x++) {
        int card_1_index = rand() % 52;
        int card_2_index = rand() % 52;

        swap(deck[card_1_index], deck[card_2_index]);
    }

    return deck;
}

int player_balance = 0;
int player_choice;
string player_hand[11] = {};
string dealer_hand[11] = {};

int player_hand_score[2] = {0, 0};
int dealer_hand_score = 0;

int main() {


    string* deck;
    deck = createDeck();
    int deck_index = 0;

    // for (int x = 0; x < 52; x++) {
    //     cout << deck[x] << endl;
    // }

    player_hand[0] = deck[0];
    player_hand[1] = deck[2];
    dealer_hand[0] = deck[1];
    dealer_hand[1] = deck[3];

    cout << "Dealer's hand: " << endl;
    for (int x = 0; x < 2; x++) {
        cout << dealer_hand[x] << endl;
    }
    cout << endl;
    // cout << player_hand_score << endl;
    bool ace = false;

    cout << "Your hand: " << endl;
    for (int x = 0; x < 2; x++) {
        cout << player_hand[x] << endl;
        // cout << player_hand[x][0] << endl;
        int card_value = 0;
        // cout << player_hand_score << endl;
        if (isdigit(player_hand[x][0])) {
            card_value = player_hand[x][0] - '0'; // convert ASCII char to type int

            if (isdigit(player_hand[x][1])) {
                card_value = 10;
            }
            player_hand_score[0] += card_value;
            player_hand_score[1] += card_value;

        }
        else if (!isdigit(player_hand[x][0])) {

            if (player_hand[x][0] == 'J' || player_hand[x][0] == 'Q' || player_hand[x][0] == 'K') {
                card_value = 10;

                player_hand_score[0] += card_value;
                player_hand_score[1] += card_value;

            }
            else if (player_hand[x][0] == 'A') {
                cerr << "ace" << endl;
                ace = true;
                player_hand_score[0] += 1;
                player_hand_score[1] += 11;
            }
            else {
                cout << "not digit" << endl;
            }
        }
    }

    if (player_hand_score[0] != player_hand_score[1]) {
        cout << "Hand score: " << player_hand_score[0] << " / " << player_hand_score[1] << endl;
    }
    else {
        cout << "Hand score: " << player_hand_score[0] << endl;
    }
    cout << endl;

    cout << "Hit (1) or Stand (2): ";
    cin >> player_choice;

    // VALIDATE player_choice (type int, 1, or 2)
    while (true) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again: ";
            cin >> player_choice;
        }
        else if (!cin.fail()) {
            if (player_choice != 1 && player_choice != 2) {
                cout << "Invalid input. Try again: ";
                cin >> player_choice;
            }
            else if (player_choice == 1 || player_choice == 2) {
                break;
            }
        }
    }

    if (player_choice == 1) {
        cout << "You hit" << endl;

    }
    else if (player_choice == 2) {
        cout << "You stand" << endl;
    }

    return 0;
}

