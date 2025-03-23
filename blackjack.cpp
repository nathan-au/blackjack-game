#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;

const string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
map<string, int> values = {{"A", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"J", 10}, {"Q", 10}, {"K", 10}};

vector <string> createDeck() {

    vector <string> deck;

    for (const auto & suit : suits) {
        for (const auto & rank : ranks) {
            deck.push_back(rank + " of " + suit);
        }
    }

    srand(time(nullptr));
    for (int x = 0; x < 1000; x++) {
        int card_1_index = rand() % 52;
        int card_2_index = rand() % 52;
        swap(deck[card_1_index], deck[card_2_index]);
    }

    return deck;
}

int calculateHandScore(const vector <string> & hand) {
    int hand_score = 0;

    for (const auto & card : hand) {
        string rank = card.substr(0, card.find(' '));
        hand_score +=  values.at(rank);
    }

    return hand_score;
}

int getPlayerChoice() {
    int choice;

    cout << "Hit (1) or Stand (2): ";
    cin >> choice;
    while (true) {
        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again: ";
            cin >> choice;
        }
        else {
            break;
        }
    }

    return choice;
}

int player_balance = 0;
int player_choice;

int player_hand_score[2] = {0, 0};
int dealer_hand_score = 0;

int main() {
    const vector <string> deck = createDeck();
    int deck_index = 0;

    // for (const auto & card : deck) {
    //     cout << card << endl;
    // }
    // cout << endl;

    vector <string> player_hand = {deck[deck_index++], deck[deck_index++]};
    vector <string> dealer_hand = {deck[deck_index++], deck[deck_index++]};

    cout << "Dealer's hand: " << endl;
    for (const auto & card : dealer_hand) {
        cout << card << endl;
    }
    cout << calculateHandScore(dealer_hand) << endl;
    cout << endl;

    cout << "Your hand: " << endl;
    for (const auto & card : player_hand) {
        cout << card << endl;
    }
    cout << calculateHandScore(player_hand) << endl;
    cout << endl;

    player_choice = getPlayerChoice();

    if (player_choice == 1) {
        cout << "You hit" << endl;
    }
    else if (player_choice == 2) {
        cout << "You stand" << endl;
    }

    return 0;
}

