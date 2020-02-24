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
    deck2 = NULL;

    // Loop through both lists and see if every value is equal after reverse
    while (curr1 != NULL){
        if (curr1->getCard().getString() != curr2->getCard().getString() ||\
            curr1->getCard().getCard() != curr2->getCard().getCard()){
            return false;
        }
        curr1 = curr1->after;
        curr2 = curr2->after;
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
void DeleteAll(Node* &deck){
    if (deck != NULL){
        DeleteAll(deck->after);
        delete deck;
        deck = NULL;
    }
}

// Cut deck functions to split the deck in half
void CutDeck(Node* &deck, Node* &cut1, Node* &cut2, const std::string &type){
    Node* curr = deck;
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

Node* Shuffle(Node* cut1, Node* cut2, const std::string &type){
    Node* shuffled_deck = NULL;
    std::string current_suit;
    int current_face_value;
    int count = 1;
    int size = DeckSize(cut1) + DeckSize(cut2);
    if (type == "perfect"){
        while (count <= size){ 
            if (count % 2 == 0){
                current_suit = cut1->getCard().getSuit();
                current_face_value = cut1->getCard().getCard();
                cut1 = cut1->after;
            } else {
                current_suit = cut2->getCard().getSuit();
                current_face_value = cut2->getCard().getCard();
                cut2 = cut2->after;
            }
            DeckPushBackCard(shuffled_deck, current_suit, \
            current_face_value);
            count++; 
        }
    }
    return shuffled_deck;
}

Node* SortHand(Node* deck){
    if (deck == NULL && deck->after == NULL) return deck;
    Node* sorted_hand = NULL;
    while (deck != NULL){
        Node* curr = deck;
        deck = deck->after;
        if (sorted_hand == NULL || curr->getCard() < sorted_hand->getCard()){
            curr->after = sorted_hand;
            sorted_hand = curr;
        } else {
            Node* pos = sorted_hand;
            while (pos != NULL){
                if (pos->after == NULL ||\
                sorted_hand->getCard() < pos->after->getCard()){
                curr->after = pos->after;
                pos->after = curr;
                break;
                }
                pos = pos->after;
            }
        }
    }
    return sorted_hand;
}
