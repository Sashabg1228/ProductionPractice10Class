#include "player.hpp"
#include "card.hpp"

#include <iostream>
#include <vector>

using namespace std;

//* Constructors

// Default constructor
Player::Player(){}

// Constructor with parameters
Player::Player (string name, vector<Card> hand, int isWinner, int points, int colorPoints)
{
    this->name = name;
    this->hand = hand;
    this->isWinner = isWinner;
    this->points = points;
    this->colorPoints = colorPoints;
}

// Copy constructor
Player::Player(const Player& other)
{
    this->name = other.name;
    this->hand = other.hand;
    this->isWinner = other.isWinner;
    this->points = other.points;
    this->colorPoints = other.colorPoints;
}

//* Destructor

Player::~Player(){}

//* Getters

// Get name	
string Player::getName()
{
    return name;
}

// Get hand
vector<Card> Player::getHand()
{
    return hand;
}

// Get isWinner
int Player::getIsWinner()
{
    return isWinner;
}

// Get points
int Player::getPoints()
{
    return points;
}

// Get finalePoints
int Player::getcolorPoints()
{
    return colorPoints;
}

//* Setters

// Set name
void Player::setName(string name)
{
    this->name = name;
}

// Set hand
void Player::setHand(vector<Card> hand)
{
    this->hand = hand;
}

// Set isWinner
void Player::setIsWinner(int isWinner)
{
    this->isWinner = isWinner;
}

// Set points
void Player::setPoints(int points)
{
    this->points = points;
}

// Set colorPoints
void Player::setcolorPoints(int colorPoints)
{
    this->colorPoints = colorPoints;
}

//* Functions

// Adds a card to the hand of the player
void Player::addCard(Card card)
{
    hand.push_back(card);

    sortHand();
    
    checkHand();
}

void Player::sortHand()
{
    for(int i = 0; i < hand.size(); i++)
    {
        for(int j = i + 1; j < hand.size(); j++)
        {
            if(hand[i].getValuePoints() < hand[j].getValuePoints())
            {
                switchCards(i, j);
            }
            else if(hand[i].getValuePoints() == hand[j].getValuePoints()){
                if(hand[i].getColorPoints() < hand[j].getColorPoints())
                {
                    switchCards(i, j);
                }
            }
        }
    }
}

void Player::switchCards(int index1, int index2)
{
    Card temp = hand[index1];
    hand[index1] = hand[index2];
    hand[index2] = temp;
}

void Player::checkHand()
{
    //If there are 4 similar cards next to each other isWinner = 1 and points = getValuePoints
    char similar;
    int numOfSimilar = 1;

    for(int i = hand.size(); i > 1; i--){
        similar = hand[i].getValue();
        if(similar == hand[i - 1].getValue()){
            numOfSimilar++;
        }
        else{
            numOfSimilar = 1;
        }

        //cout << "Similar Numbers: " << numOfSimilar << endl;

        if(numOfSimilar == 4){
            setIsWinner(1);
            setPoints(hand[i].getValuePoints());
            cout << "Winner: " << isWinner << endl;
            cout << "Points: " << points << endl;
        }
    }
}

void Player::getFinaleValuePoints(){
    vector<Card> hand2;
    int valuePoints = 0;
    hand2 = getHand();

    for(int i = 0; i < hand2.size(); i++){
        valuePoints += hand2[i].getValuePoints();
    }

    setPoints(valuePoints);
}
void Player::getFinaleColorPoints(){
    vector<Card> hand2;
    int colorPoints = 0;
    hand2 = getHand();

    for(int i = 0; i < hand2.size(); i++){
        colorPoints += hand2[i].getColorPoints();
    }

    setcolorPoints(colorPoints);
}
