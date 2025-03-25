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

const vector <string> deck = createDeck();
int deck_index = 0;
vector <string> player_hand = {deck[deck_index++], deck[deck_index++]};
vector <string> dealer_hand = {deck[deck_index++], deck[deck_index++]};



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





void printHand(const vector <string> & hand, const bool hide) {
    size_t max_card_index = hand.size();

    if (hide) {
        max_card_index -= 1;
    }

    for (size_t card_index = 0; card_index < max_card_index; ++card_index) {
        cout << hand[card_index];
        if (card_index < max_card_index - 1) {
            cout << ", ";
        }
    }
    if (hide) {
        cout << ", ?? of ??????" << endl;
    }
    else {
        cout << endl;
        array<int, 2> hand_score = calculateHandScore(hand);

        if (hand_score[0] != hand_score[1] && hand_score[1] <= 21 && hand_score[1] != 21) {
            cout << "Total = " << hand_score[0] << " / " << hand_score[1] << endl;
        }
        else if (hand_score[1] == 21) {
            cout << "Total = " << hand_score[1] << endl;
        }
        else {
            cout << "Total = " << hand_score[0] << endl;
        }
    }

}

bool checkBlackjack(const vector <string> & hand) {
    array<int, 2> hand_score = calculateHandScore(hand);

    if (hand_score[0] == 21 || hand_score[1] == 21) {
        cout << "\033[32mBLACKJACK WINS !\033[0m" << endl; // Green text
        return true;
    }
    return false;
}

bool checkBust(const vector <string> & hand) {
    array<int, 2> hand_score = calculateHandScore(hand);
    if (hand_score[0] > 21 && hand_score[1] > 21) {
        cout << "\033[31mBUST :(\033[0m" << endl; // Red text
        return true;
    }
    return false;
}



bool playerTurn() {
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

    if (choice == 1) {
        cout << "You hit" << endl;
        cout << endl;
        player_hand.push_back(deck[deck_index++]);
        printHand(player_hand, false);
    }
    else if (choice == 2) {
        cout << "You stand" << endl;
        cout << endl;

        return false;
    }
    return true;
}

bool dealerTurn() {
    if (calculateHandScore(dealer_hand)[0] >= 17) {
        cout << "Dealer stands" << endl;
        cout << endl;

        return false;
    }

    cout << "Dealer hits" << endl;
    cout << endl;

    dealer_hand.push_back(deck[deck_index++]);
    printHand(dealer_hand, false);

    return true;
}


int main() {

    cout << endl;
    cout << "Dealer's hand: " << endl;
    printHand(dealer_hand, true);
    cout << endl;

    cout << "Your hand: " << endl;
    printHand(player_hand, false);


    if (checkBlackjack(player_hand) == true) {
        cout << "\033[32mYOU WIN !\033[0m" << endl; // Green text
        return 0;
    }

    while (true) {
        if (playerTurn() == false) {
            break;
        }
        if (checkBust(player_hand) == true) {
            cout << "\033[31mDEALER WINS !\033[0m" << endl; // Red text

            return 0;
        }
        if (checkBlackjack(player_hand) == true) {
            cout << "\033[32mYOU WIN !\033[0m" << endl; // Green text

            return 0;
        }
    }



    cout << "--- Dealer's turn ---" << endl;
    cout << endl;
    if (checkBlackjack(dealer_hand) == true) {
        cout << "\033[31mDEALER WINS !\033[0m" << endl; // Red text

        return 0;
    }
    cout << "Dealer's hand: " << endl;
    printHand(dealer_hand, false);
    while (true) {
        if (dealerTurn() == false) {
            break;
        }
        if (checkBust(dealer_hand) == true) {
            cout << "\033[32mYOU WIN !\033[0m" << endl; // Green text

            return 0;
        }
        if (checkBlackjack(dealer_hand) == true) {

            return 0;
        }
    }
    cout << "player and dealer are both standing" << endl;


    int final_player_score;
    if (calculateHandScore(player_hand)[1] < 21 && calculateHandScore(player_hand)[1] != 0) {
        final_player_score = calculateHandScore(player_hand)[1];
    }
    else {
        final_player_score = calculateHandScore(player_hand)[0];
    }

    int final_dealer_score;
    if (calculateHandScore(dealer_hand)[1] < 21 && calculateHandScore(dealer_hand)[1] != 0) {
        final_dealer_score = calculateHandScore(dealer_hand)[1];
    }
    else {
        final_dealer_score = calculateHandScore(dealer_hand)[0];
    }

    if (final_player_score > final_dealer_score) {
        cout << "\033[32mYOU WIN !\033[0m" << endl; // Green text
    }
    else if (final_dealer_score > final_player_score) {
        cout << "\033[31mDEALER WINS !\033[0m" << endl; // Red text
    }
    else if (final_player_score == final_dealer_score) {
        cout << "\033[32mITS A TIE !\033[0m" << endl;
    }

    return 0;
}