#pragma once

#include <string>
#include <vector>

#include "card.hpp"

class Player
{
private:
    std::string name;
    std::vector<Card> hand;
    int isWinner;
    int points;
    int colorPoints;

public:
    //* Constructors

    // Default constructor
    Player();

    // Constructor with parameters
    Player(std::string name, std::vector<Card> hand, int isWinner, int points, int colorPoints);

    // Copy constructor
    Player(const Player &other);

    //* Destructor

    ~Player();

    //* Getters

    // Get name
    std::string getName();
    // Get hand
    std::vector<Card> getHand();

    // Get isWinner
    int getIsWinner();

    // Get points
    int getPoints();

    // Get finalePoints
    int getcolorPoints();

    //* Setters

    // Set name
    void setName(std::string name);

    // Set hand
    void setHand(std::vector<Card> hand);

    // Set isWinner
    void setIsWinner(int isWinner);

    // Set points
    void setPoints(int points);

    // Set colorPoints
    void setcolorPoints(int colorPoints);

    //* Functions

    // Adds a card to the hand of the player
    void addCard(Card card);
    void sortHand();
    void switchCards(int index1, int index2);
    void checkHand();
    void getFinaleValuePoints();
    void getFinaleColorPoints();
};
