#include "head.hpp"

int main(){
    std::cout << "Welcome to Blackjack! (Carson Zuniga 2020). Dealer stands on all 17s." << std::endl;
    bool session_over = false;
    while(session_over == false){
    std::cout << "==================================" << std::endl;
    playerHand new_user_hand;
    new_user_hand.name = "Player";
    playerHand new_dealer_hand;
    new_dealer_hand.name = "Dealer";
    start_game(&new_user_hand, &new_dealer_hand);
    print_hand(&new_user_hand, 0);
    print_hand(&new_dealer_hand, 0);
    bool game_over = false;
    

    while(game_over == false){
        if(new_user_hand.hand_held[4] != 0){
            std::cout << "You Win! (cards held = 5)" << std::endl;
            game_over = true;
            continue;
        }
        std::cout << "Hit or Stand (h/s)?" << std::endl;
        char input;
        std::cin >> input;
        std::cout << std::endl;

        if(input == 'h'){
            std::cout << "Hit!" << std::endl;
            DrawCard(&new_user_hand);
            print_hand(&new_user_hand, 1);
            if(new_user_hand.hand_value > 21){
                std::cout << "Bust!" << std::endl;
                game_over = true;
            }
            continue;
        }

        if(input == 's'){
            std::cout << "Stand!" << std::endl;
            while(new_dealer_hand.hand_value < 17 || new_dealer_hand.hand_held[4] != 0){
                DrawCard(&new_dealer_hand);
                print_hand(&new_dealer_hand, 1);
            }
            if(new_dealer_hand.hand_value > 21){
                std::cout << "Dealer Bust! You Win!" << std::endl;
                game_over = true;
                continue;
            }
            if(new_dealer_hand.hand_value >= new_user_hand.hand_value || new_dealer_hand.hand_held[4] != 0){
                std::cout << "Dealer Win! You Lose!" << std::endl;
                game_over = true;
                continue;
            }
            if(new_dealer_hand.hand_value < new_user_hand.hand_value){
                std::cout << "Greater Hand Value! You Win!" << std::endl;
                game_over = true;
                continue;
            }
        }


    }


    end_game(&new_user_hand, &new_dealer_hand);
    std::cout << "Another Game (y/n)?" << std::endl;
    char new_game_input;
    std::cin >> new_game_input;
    if(new_game_input == 'y'){
        continue;
    }
    else {
        session_over == true;
        break;
    }
    }
    return 0;
}