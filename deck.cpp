// ==================================================================================
// Implement all functions that you listed by prototype in deck.h
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// NOTE: These are standalone functions, not part of a class.
// ==================================================================================

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
        curr1 = curr1->after;
        curr2 = curr2->after;
    }
    return true;
}

// Check if deck1 is reverse primary order of deck2
bool ReversePrimaryOrder(Node* deck1, Node* deck2){
    if (DeckSize(deck1) != DeckSize(deck2)) return false;
    Node* curr1 = deck1;
    Node* curr2 = deck2;
    Node* prev2 = NULL;
    Node* after2 = NULL;
    
    // Reverse deck2 to make is start at the other end
    while (curr2 != NULL){
        after2 = curr2;
        curr2 = prev2;
        prev2 = curr2;
        curr2 = after2;
    }

    // Loop through both lists and see if every value is equal after reverse
    while (curr1 != NULL){
        if (curr1->getCard().getString() != curr2->getCard().getString() ||\
            curr1->getCard().getCard() != curr2->getCard().getCard()){
            return false;
        }
        curr1 = curr1->after;
        curr2 = curr2->before;
    }
    return true;
}

// Copy the contents of the original deck
Node* CopyDeck(Node* deck){
    Node* new_deck = NULL; 
    Node* old_curr = deck;
    std::string current_suit;
    int current_face_value;
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
    cut1 = NULL;
    cut2 = NULL;
    std::string current_suit;
    int current_face_value;
    int deck_size = DeckSize(deck);
    int count = 1;
    if (type == "perfect"){
        while (curr != NULL){
            current_suit = curr->getCard().getSuit();
            current_face_value = curr->getCard().getCard();
            if (count <= deck_size/2){
                DeckPushBackCard(cut1, current_suit, current_face_value);
            } else {
                DeckPushBackCard(cut2, current_suit, current_face_value);
            }
            curr = curr->after;
            count++;
        }
    }
}

// Shuffle function
Node* Shuffle(Node* cut1, Node* cut2, const std::string &type){
    Node* shuffled_deck = NULL;
    std::string current_suit;
    int current_face_value;
    int count = 1;
    int size = DeckSize(cut1) + DeckSize(cut2);
    if (type == "perfect"){
        while (count <= size){ 
            if (count % 2 == 0){
                current_suit = cut2->getCard().getSuit();
                current_face_value = cut2->getCard().getCard();
                cut2 = cut2->after;
            } else {
                current_suit = cut1->getCard().getSuit();
                current_face_value = cut1->getCard().getCard();
                cut1 = cut1->after;
            }
            DeckPushBackCard(shuffled_deck, current_suit, \
            current_face_value);
            count++; 
        }
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
            // Checks if card in deck is less than card in sorted deck
            // and if the card on the sorted deck is NULL
            if (new_deck == NULL ||\
                curr_card->getCard() < new_deck->getCard()){
                curr_card->sorted_next = new_deck;
                new_deck = curr_card;
                new_deck->sorted_prev = NULL;
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
                        tmp_deck->sorted_next->sorted_prev = tmp_deck;
                        break;
                    }
                }
            }
        }
    return new_deck;
}



// Deal funciton

void Deal(Node* &deck, Node** hands, int num_hands,\
const std::string &type, int num_cards){
    int i = 0;
    std::string current_suit;
    int current_face_value;
    int count = 0;
    int deck_size = DeckSize(deck);
    int total = num_cards * num_hands;
    Node* old_deck;
    for (int j = 0; j < num_hands; j++){
        hands[j] = NULL;
    }
    if (type == "one-at-a-time"){
        while (count < total){
            old_deck = deck;
            current_face_value = deck->getCard().getCard();
            current_suit = deck->getCard().getSuit();
            if (i == num_hands) i = 0;
            DeckPushBackCard(hands[i], current_suit, current_face_value);
            deck = deck->after;
            delete old_deck;
            old_deck = NULL;
            i++;
            count++;
        }
        if (deck == NULL && total == deck_size) delete deck;
    }
}