// ==================================================================================
// Implement all functions that you listed by prototype in deck.h
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// NOTE: These are standalone functions, not part of a class.
// ==================================================================================

#include <chrono>
#include <random>
#include <iostream>
#include <cassert>
#include "playing_card.h"
#include "node.h"
#include "deck.h"

// ==================================================================================

// Get the total size (number of cards) in a deck
int DeckSize(Node* deck){
    int count = 0;
    Node* curr = deck;
    while (curr != NULL){
        curr = curr->after;
        count += 1;
    }
    return count;
}

// Print deck after it is sorted (secondary order)
void PrintDeckSorted(const std::string &description, Node* deck){
    std::cout << description;
    Node *tmp = deck;
    while (tmp != NULL) {
        std::cout << " " << tmp->getCard().getString();
        tmp = tmp->sorted_next;
    }
    std::cout << std::endl;
}

// Check if deck1 is same primary order as deck2
bool SamePrimaryOrder(Node* deck1, Node* deck2){
    if (DeckSize(deck1) != DeckSize(deck2)) return false;
    Node* curr1 = deck1;
    Node* curr2 = deck2;
    while (curr1 != NULL and curr2 != NULL){
        if (curr1->getCard().getString() != curr2->getCard().getString() ||\
            curr1->getCard().getCard() != curr2->getCard().getCard()){
            return false;
        }
        // Loop through deck and check if each once matches with each other
        curr1 = curr1->after;
        curr2 = curr2->after;
    }
    return true;
}

// Check if deck1 is reverse primary order of deck2
bool ReversePrimaryOrder(Node* deck1, Node* deck2){
    if (DeckSize(deck1) != DeckSize(deck2)) return false;

    // Iterate deck to the end to print backwards
    while (deck1->after != NULL){
        deck1 = deck1->after;
    }

    // While loop check if reverse is the same as forward
    while (1){
        if (deck1->getCard() != deck2->getCard())
            return false;
        deck1 = deck1->before;
        deck2 = deck2->after;
        if (!deck1 && !deck2) break;
    }
    return true;
}


// Copy the contents of the original deck
Node* CopyDeck(Node* deck){
    Node* new_deck = NULL; 
    Node* old_curr = deck;
    std::string current_suit;
    int current_face_value;

    // While to get each card from original deck and copy to new deck
    while (old_curr != NULL) {
        current_suit = old_curr->getCard().getSuit();
        current_face_value = old_curr->getCard().getCard();
        DeckPushBackCard(new_deck, current_suit, current_face_value); 
        old_curr = old_curr->after;
  }
  return new_deck;
}

// Recursive delete function
void DeleteAllCards(Node* &deck){
    if (deck != NULL){
        DeleteAllCards(deck->after);
        delete deck;
        deck = NULL;
    } 
}

// Cut deck functions to split the deck in half
void CutDeck(Node* &deck, Node* &cut1, Node* &cut2, const std::string &type){
    Node* curr = deck;
    int deck_size = DeckSize(deck);
    
    // If type is perfect
    if (type == "perfect"){
        for (int count = 0; count < deck_size/2; count++) {
            curr = curr->after;
        }
        curr->before->after = NULL;
        curr->before = NULL;
        cut1 = deck;
        cut2 = curr;

    // If type is random
    } else if (type == "random") {
        
        // Create seed and have randomness range be based off the current time
        unsigned seed = std::chrono::system_clock::now()\
        .time_since_epoch().count();
        std::default_random_engine gen_num(seed);
        std::uniform_int_distribution<int> range(1,8);

        // Deck size is adjusted to have the cuts be different each time
        deck_size = deck_size - range(gen_num);

        for (int count = 0; count < deck_size/2; count++) {
            curr = curr->after;
        }
        curr->before->after = NULL;
        curr->before = NULL;
        cut1 = deck;
        cut2 = curr;
    }
}

// Shuffle function
Node* Shuffle(Node* cut1, Node* cut2, const std::string &type){
    Node* shuffled_deck = cut1;
    Node* t_tmp = NULL; 
    Node* b_tmp = NULL;

    // If type is perfect
    if (type == "perfect"){
        for (t_tmp = cut1->after, b_tmp = cut2->after;\
        t_tmp != NULL && b_tmp != NULL;\
        t_tmp = cut1->after, b_tmp = cut2->after) {
            cut1->after = cut2;
            cut1->after->before = cut1;
            cut2->after = t_tmp;
            cut2->after->before = cut2;
            cut1 = t_tmp;
            cut2 = b_tmp;
        }

        // In the case of odd number of cards, make the last node connect
        if (b_tmp == NULL && t_tmp != NULL){
            cut2->after = t_tmp;
            t_tmp->before = cut2;
        }
    cut1->after = cut2;
    cut1->after->before = cut1;

    // Create seed and base the range of randomness on current time
    } else if (type == "random") {
       unsigned seed = std::chrono::system_clock::now()\
       .time_since_epoch().count();
       std::default_random_engine gen_num(seed);
       std::uniform_int_distribution<int> range(1,8);

        // Loop uses Shuffle and CutDeck to randomize the shuffle of the cards
        Node* tmp_deck = NULL;
        for (int i = 0; i < range(gen_num); i++){
            tmp_deck = Shuffle(cut1, cut2, "perfect");
            CutDeck(tmp_deck, cut1, cut2, "random");
        }

        for (t_tmp = cut1->after, b_tmp = cut2->after;\
        t_tmp != NULL && b_tmp != NULL;\
        t_tmp = cut1->after, b_tmp = cut2->after) {
            cut1->after = cut2;
            cut1->after->before = cut1;
            cut2->after = t_tmp;
            cut2->after->before = cut2;
            cut1 = t_tmp;
            cut2 = b_tmp;
        }
        if (b_tmp == NULL && t_tmp != NULL){
            cut2->after = t_tmp;
            t_tmp->before = cut2;
        }
    cut1->after = cut2;
    cut1->after->before = cut1;
    }

    return shuffled_deck;

}

// SortHand function

Node* SortHand(Node* deck){
    // If statement checks if the size of list is one or zero
    if (deck->after == NULL || deck == NULL) return deck;
        // After variables initialize, for loop commences
        // to start appending nodes from deck to the new sorted deck
        Node* tmp_deck;
        Node* curr_card;
        Node* new_deck = NULL;
        while (deck != NULL){
            curr_card = deck;
            deck = deck->after;

            // If statement initializes the first card in the sorted deck
            if (new_deck == NULL ||\
                curr_card->getCard() < new_deck->getCard()){
                curr_card->sorted_next = new_deck;
                new_deck = curr_card;
            } else {
                // Loop through to check at what new_cardoint value is higher
                // than the curent card from the deck
                tmp_deck = new_deck;
                for (tmp_deck = new_deck; tmp_deck != NULL;\
                tmp_deck = tmp_deck->sorted_next){
                    if (tmp_deck->sorted_next == NULL ||
                    curr_card->getCard() < tmp_deck->sorted_next->getCard()){
                        curr_card->sorted_next = tmp_deck->sorted_next;
                        tmp_deck->sorted_next = curr_card;
                        break;
                    }
                }
            }
        }

    // Loop through and make sure the sorted previous pointers are setup
    Node* curr = new_deck;
    while(curr->sorted_next != NULL){
        curr->sorted_next->sorted_prev = curr;
        curr = curr->sorted_next;
    }
    return new_deck;
}


// Deal funciton
void Deal(Node* &deck, Node* hands[], int num_hands,\
const std::string &type, int num_cards){
    int i = 0;
    int count = 0;
    int limit = num_hands;
    int total = num_cards * num_hands;

    // Intialize each node in the array as the first few cards in the deck
    for (int j = 0; j < num_hands; j++){
        hands[j] = deck;
        deck = deck->after;
    }
    Node** tmp_hands = new Node* [num_hands];
    for (int k = 0; k < num_hands; k++){
        tmp_hands[k] = hands[k];
    }
    
    // If type is one-at-a-time
    if (type == "one-at-a-time"){
        // Alternate and make sure each node connects to the appropiate spots
        while (deck != NULL){
            hands[i]->after = deck;
            hands[i]->after->before = hands[i];
            hands[i] = hands[i]->after;
            deck = deck->after;
            count++;
            if (count == total - num_hands) break;
            i++;
            if (i == limit) i = 0;
        }
        int new_deck_size = DeckSize(deck);
        if (new_deck_size > 0){
            deck->before = NULL;
        }
        
        // Loop through and sever the nodes from connectng to each other
        for (int i = 0; i < num_hands; i++){
            if (i != num_hands - 1)
                hands[i]->after->before = NULL;
            hands[i]->after = NULL;
            hands[i] = tmp_hands[i];
            hands[i]->before = NULL;
        }

        delete [] tmp_hands;

        // Loop through and attach the before of the last node
        for (int j = 0; j < num_hands; j++){
            Node* tmp = hands[j];
            while (tmp->after->after != NULL){
                tmp = tmp->after;
            }
            tmp->after->before = tmp;
        }
    }
}