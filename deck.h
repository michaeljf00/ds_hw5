#include "playing_card.h"
#include "node.h"

// ==================================================================================
// prototypes for provided functions (implemented in main.cpp)
// ==================================================================================

bool SanityCheckPrimary(Node* top);
bool SanityCheckSorted(Node* first);
Node* CreateDeck(int numCards);
void DeckPushBackCard(Node* &deck, const std::string& suit, int num);
void PrintDeckPrimary(const std::string &description, Node* deck);
void PrintDeckSorted(const std::string &description, Node* deck);
int DeckSize(Node* deck);
bool SamePrimaryOrder(Node* deck1, Node* deck2);
bool ReversePrimaryOrder(Node* deck1, Node* deck2);
Node* CopyDeck(Node* deck);
void DeleteAll(Node* &deck);
void CutDeck(Node* &deck, Node* &cut1, Node* &cut2, const std::string &type);
Node* Shuffle(Node* cut1, Node* cut2, const std::string &type);

// ==================================================================================
//
// Write all the prototypes for the your functions here
// (they will be implemented in deck.cpp)
//
// NOTE: These are standalone functions, not part of a class.
//
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// ==================================================================================

