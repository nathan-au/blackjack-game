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

void printHand(const vector <string> & hand, const bool hide) {
    size_t max_card_index = hand.size();

    if (hide) {
        max_card_index -= 1;
    }

    for (size_t card_index = 0; card_index < max_card_index; card_index++) {
        if (card_index < max_card_index - 1) {
            cout << hand[card_index] << ", ";
        }
        else {
            cout << hand[card_index];
        }
    }

    if (hide) {
        cout << ", ___ of ______" << endl;
    }
    else {
        cout << endl;
    }

    if (!hide) {
        array<int, 2> hand_score = calculateHandScore(hand);

        if (hand_score[0] != hand_score[1]) {
            cout << "Hand score = " << hand_score[0] << " / " << hand_score[1] << endl;
        }
        else {
            cout << "Hand score = " << hand_score[0] << endl;
        }
    }

}

bool checkBlackjack(const vector <string> & hand) {
    array<int, 2> hand_score = calculateHandScore(hand);

    if (hand_score[1] == 21) {
        return true;
    }
    return false;
}

void checkBust(const vector <string> & hand) {
    array<int, 2> hand_score = calculateHandScore(hand);
    if (hand_score[1] > 21 || hand_score[1] > 21) {
        cout << "Bust!" << endl;
        exit(0);
    }
}

int main() {
    const vector <string> deck = createDeck();
    int deck_index = 0;


    // for (const auto & card : deck) { cout << card << endl; }

    vector <string> player_hand = {deck[deck_index++], deck[deck_index++]};
    vector <string> dealer_hand = {deck[deck_index++], deck[deck_index++]};
    int player_hand_index = 2;
    int dealer_hand_index = 2;

    cout << endl;
    cout << "Dealer's hand: " << endl;
    printHand(dealer_hand, true);
    cout << endl;
    cout << "Your hand: " << endl;
    printHand(player_hand, false);
    cout << endl;

    if (checkBlackjack(player_hand) == true) {
        cout << "Blackjack wins!" << endl;
        exit(0);
    }

    int player_choice = getPlayerChoice();
    cout << endl;
    if (player_choice == 1) {
        cout << "You hit" << endl;
        player_hand.push_back(deck[deck_index++]);
        printHand(player_hand, false);
        checkBust (player_hand);
        cout << "You did not bust" << endl;
    }
    else if (player_choice == 2) {
        cout << "You stand" << endl;

    }

    return 0;
}