#include <cstdlib> // rand
#include <iostream> // I/O
#include <ctime> // time
#include <string>

class playerHand;
void DrawCard(playerHand * hand);
void start_game(playerHand * player_hand, playerHand * dealer_hand);
void end_game(playerHand * player_hand, playerHand * dealer_hand);
void print_hand(playerHand * hand, int player_hand_true);

class playerHand{
    public:
    std::string name;
    int current_drawn = 0;
    int hand_value = 0;
    int hand_held[5] = {0, 0, 0, 0, 0}; // if reaches 5, charlie win!
};

void start_game(playerHand * player_hand, playerHand * dealer_hand){
    std::time_t t = std::time(0);
    srand(t);

    DrawCard(player_hand);
    DrawCard(player_hand);
    DrawCard(dealer_hand);
    DrawCard(dealer_hand);
}

void DrawCard(playerHand * hand){
    int new_card = (rand() % 14) + 1;
    if(new_card > 10) {new_card = 10;}
    hand->hand_held[hand->current_drawn] = new_card;
    hand->current_drawn++;
    hand->hand_value += new_card;
    // std::cout << "Card Drawn: " << new_card << std::endl;
}

void end_game(playerHand * player_hand, playerHand * dealer_hand){
    std::cout << std::endl;
    print_hand(player_hand, 1);
    print_hand(dealer_hand, 1);
    std::cout << "Game over!" << std::endl << std::endl;
    delete player_hand;
    delete dealer_hand;
}

void print_hand(playerHand * hand, int player_hand_true){
    int i = 0;
    if(hand->name.compare("Dealer") == 0 && player_hand_true == 0){
        std::cout << hand->name << " hand: " << std::endl << hand->hand_held[0] << ", ";
        i++;
        while(hand->hand_held[i] != 0){
            std::cout << "???" << ", ";
            i++;
        }
        std::cout << "Total Value: ???";
        std::cout << std::endl;
        return;
    }
    std::cout << hand->name << " hand: " << std::endl;
    while(hand->hand_held[i] != 0){
        std::cout << hand->hand_held[i] << ", ";
        i++;
    }
    std::cout << "Total Value: " << hand->hand_value;
    std::cout << std::endl;
}