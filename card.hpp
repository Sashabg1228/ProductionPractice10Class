#pragma once

class Card
{
protected:
    char value;
    char color;

public:
    //* Constructors

    // Default constructor
    Card();

    // Constructor with parameters
    Card(char value, char color);

    // Copy constructor
    Card(const Card &other);

    //* Destructor

    ~Card();

    //* Getters

    // Get value
    char getValue() const;

    // Get color
    char getColor() const;

    //* Setters

    // Set value
    void setValue(char value);

    // Set color
    void setColor(char color);

    //* Methods

    // Check Value
    void checkValue(char value);

    // Check Color
    void checkColor(char color);

    // Get points
    int getValuePoints() const;

    int getColorPoints();
};

