#include <iostream>
#include <map>
#include <array>
#include <random>
#include <algorithm>
#include <ranges>
using namespace std;

const string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
map<string, int> values = {{"A", 11}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"J", 10}, {"Q", 10}, {"K", 10}};

vector <string> createDeck() {
    vector <string> deck;
    for (const auto & suit : suits) {
        for (const auto & rank : ranks) {
            string card;
            card.append(rank).append(" of ").append(suit);
            deck.push_back(card);
        }
    }
    random_device rd;
    mt19937 rng(rd());
    ranges::shuffle(deck, rng);
    return deck;
}

array<int, 2> calculateHandScore(const vector <string> & hand) {
    array<int, 2> hand_score = {0, 0};

    for (const auto & card : hand) {
        string rank = card.substr(0, card.find(' '));
        const int card_value = values.at(rank);
        if (card_value == 11) {
            hand_score[0]++;
        }
        else {
            hand_score[0] +=  card_value;
        }
        hand_score[1] += card_value;


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

void printHand(const vector <string> & hand, const char who) {
    if (who == 'D') {
        cout << "Dealer's hand: " << endl;
    }
    else if (who == 'P') {
        cout << "Your hand: " << endl;
    }

    for (const auto & card : hand) {
        cout << card << endl;
    }

    array<int, 2> hand_score = calculateHandScore(hand);

    if (hand_score[0] != hand_score[1]) {
        cout << hand_score[0] << " / " << hand_score[1] << endl;
    }
    else {
        cout << hand_score[0] << endl;
    }
}



int main() {
    const vector <string> deck = createDeck();
    int deck_index = 0;

    // for (const auto & card : deck) { cout << card << endl; }

    vector <string> player_hand = {deck[deck_index++], deck[deck_index++]};
    vector <string> dealer_hand = {deck[deck_index++], deck[deck_index++]};

    printHand(dealer_hand, 'D');
    cout << endl;
    printHand(player_hand, 'P');
    cout << endl;

    int player_choice = getPlayerChoice();

    if (player_choice == 1) {
        cout << "You hit" << endl;
    }
    else if (player_choice == 2) {
        cout << "You stand" << endl;
    }

    return 0;
}