#include "card.hpp"

#include <algorithm>

using namespace std;


//* Constructors

// Default constructor
Card::Card(){}

// Constructor with parameters
Card::Card(char value, char color)
{
    this->value = value;
    this->color = color;
}

// Copy constructor
Card::Card(const Card& other)
{
    this->value = other.value;
    this->color = other.color;
}

//* Destructor

Card::~Card(){}

//* Getters

// Get value
char Card::getValue() const
{
    return value;
}

// Get color
char Card::getColor() const
{
    return color;
}

//* Setters

// Set value
void Card::setValue(char value)
{
    this->value = value;
}

// Set color
void Card::setColor(char color)
{
    this->color = color;
}

//* Methods

// Check Value
void Card::checkValue(char value)
{
    static const char values[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A'};

    if(find(begin(values), end(values), value) == end(values))
    {
        throw "Error: Invalid value";
    }
}

// Check Color
void Card::checkColor(char color)
{
    static const char colors[] = {'C', 'D', 'H', 'S'};

    if(find(begin(colors), end(colors), color) == end(colors))
    {
        throw "Error: Invalid color";
    }
}

// Get points
int Card::getValuePoints() const
{
    if(value == 'A')
    {
        return 20;
    }
    else if(value == 'K')
    {
        return 15;
    }
    else if(value == 'Q')
    {
        return 12;
    }
    else if(value == 'J')
    {
        return 10;
    }
    else
    {
        return value - '0';
    }
}

int Card::getColorPoints(){
    if(color == 'C')
    {
        return 1;
    }
    else if(color == 'D')
    {
        return 2;
    }
    else if(color == 'H')
    {
        return 3;
    }
    else if(color == 'S')
    {
        return 4;
    }
    else{
        throw "Error: Invalid color";
    }
}
