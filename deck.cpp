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