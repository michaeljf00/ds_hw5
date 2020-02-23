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

int DeckSize(Node* deck){
    int count = 0;
    Node* curr = deck;
    while (curr != NULL){
        curr = curr->after;
        count += 1;
    }
    return count;
}


void PrintDeckSorted(const std::string &description, Node* deck){
    std::cout << description;
    Node *tmp = deck;
    while (tmp != NULL) {
        std::cout << " " << tmp->getCard().getString();
        tmp = tmp->sorted_next;
  }
  std::cout << std::endl;
}

bool SamePrimaryOrder(Node* deck1, Node* deck2){
    if (DeckSize(deck1) != DeckSize(deck2)) return false;
    Node* currD1 = deck1;
    Node* currD2 = deck2;
    while (currD1 != NULL and currD2 != NULL){
        if (currD1->getCard().getString() != currD2->getCard().getString() ||\
            currD1->getCard().getCard() != currD2->getCard().getCard()){
            return false;
        }
        currD1 = currD1->after;
        currD2 = currD2->after;
    }
    return true;
}

bool ReversePrimaryOrder(Node* deck1, Node* deck2){
    
}