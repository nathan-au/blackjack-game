#include <iostream>
#include <map>
#include <array>
#include <random>
#include <algorithm>
#include <ranges>
#include <unistd.h>
using namespace std;

constexpr char GREEN[] = "\033[32m";
constexpr char RED[] = "\033[31m";
constexpr char RESET[] = "\033[0m";

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
    for (size_t i = 0; i < hand.size(); ++i) {
        if (hide && i == hand.size() - 1) {
            cout << "?? of ??????" << endl;
        }
        else {
            cout << hand[i];
        }
        if (i < hand.size() - 1) {
            cout << ", ";
        }
        else {
            cout << endl;
        }
    }

    if (hide == false) {
        const array<int, 2> score = calculateHandScore(hand);
        cout << "Total = ";
        if (score[0] != score[1] && score[1] < 21) {
            cout << score[0] << " / " << score[1] << endl;
        }
        else if (score[1] == 21) {
            cout<< score[1] << endl;
        }
        else {
            cout << score[0] << endl;
        }
    }
}

bool checkBlackjack(const vector <string> & hand, const string& who) {
    if (calculateHandScore(hand)[0] == 21 || calculateHandScore(hand)[1] == 21) {
        cout << endl;
        if (who == "dealer") {
            cout << RED << "DEALER BLACKJACK !" << RESET << endl;
        }
        else if (who == "player") {
            cout << GREEN << "PLAYER BLACKJACK !" << RESET << endl;
        }
        return true;
    }
    return false;
}

bool checkBust(const vector <string> & hand, const string& who) {
    if (calculateHandScore(hand)[0] > 21 && calculateHandScore(hand)[1] > 21) {
        cout << endl;
        if (who == "dealer") {
            cout << GREEN << "DEALER BUST !" << RESET << endl;
        }
        else if (who == "player") {
            cout << RED << "PLAYER BUST !" << RESET << endl;
        }
        return true;
    }
    return false;
}

bool playerTurn() {
    int choice;
    cout << "Hit (1) or Stand (2): ";
    while (true) {
        if (cin >> choice && choice >= 1 && choice <= 2) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
        // cin >> choice;
    }
    if (choice == 1) {
        cout << "You hit" << endl << endl;
        player_hand.push_back(deck[deck_index++]);
        printHand(player_hand, false);
        return true;
    }
    cout << "You stand" << endl << endl;
    return false;
}

bool dealerTurn() {
    usleep(250000);

    if (calculateHandScore(dealer_hand)[0] < 17) {
        cout << "Dealer hits" << endl << endl;
        dealer_hand.push_back(deck[deck_index++]);
        printHand(dealer_hand, false);
        return true;
    }
    cout << "Dealer stands" << endl << endl;
    return false;
}

void announceWinner(const string& winner) {
    if (winner == "dealer") {
        cout << RED << "DEALER WINS !" << RESET << endl;
    }
    else if (winner == "player") {
        cout << GREEN << "YOU WIN !" << RESET << endl;
    }
    else if (winner == "tie") {
        cout << "ITS A TIE !" << endl;
    }
    exit(0);
}

int main() {
    cout << endl;
    cout << "Dealer's hand: " << endl;
    printHand(dealer_hand, true);
    cout << "Your hand: " << endl;
    printHand(player_hand, false);

    if (checkBlackjack(player_hand, "player") == true) {
        if (checkBlackjack(dealer_hand, "dealer") == true) {
            announceWinner("tie");
        }
        announceWinner("player");
    }

    while (true) {
        if (playerTurn() == false) {
            break;
        }
        if (checkBust(player_hand, "player") == true) {
            announceWinner("dealer");
        }
        if (checkBlackjack(player_hand, "player") == true) {
            if (checkBlackjack(dealer_hand, "dealer") == true) {
                announceWinner("tie");
            }
            announceWinner("player");
        }
    }

    cout << "--- Dealer's turn ---" << endl << endl;
    cout << "Dealer's hand: " << endl;
    printHand(dealer_hand, false);

    if (checkBlackjack(dealer_hand, "dealer") == true) {
        announceWinner("dealer");
    }

    while (true) {
        if (dealerTurn() == false) {
            break;
        }
        if (checkBust(dealer_hand, "dealer") == true) {
            announceWinner("player");
        }
        if (checkBlackjack(dealer_hand, "dealer") == true) {
            announceWinner("dealer");
        }
    }

    int final_player_score;
    if (calculateHandScore(player_hand)[1] <= 21) {
        final_player_score = calculateHandScore(player_hand)[1];
    }
    else {
        final_player_score = calculateHandScore(player_hand)[0];
    }

    int final_dealer_score;
    if (calculateHandScore(dealer_hand)[1] <= 21) {
        final_dealer_score = calculateHandScore(dealer_hand)[1];
    }
    else {
        final_dealer_score = calculateHandScore(dealer_hand)[0];
    }


    if (final_player_score > final_dealer_score) {
        announceWinner("player");
    }
    else if (final_dealer_score > final_player_score) {
        announceWinner("dealer");
    }
    else if (final_player_score == final_dealer_score) {
        announceWinner("tie");
    }
}