#include "card.hpp"
#include "player.hpp"
#include "functions.hpp"

#include <iostream>
#include <vector>

int main()
{ 
	try
	{
    	std::vector<Card> deck;
		readInput(deck);

		std::vector<Player> players;
		players.push_back(Player("Player 1", std::vector<Card>(), 0, 0, 0));
		players.push_back(Player("Player 2", std::vector<Card>(), 0, 0, 0));
		players.push_back(Player("Player 3", std::vector<Card>(), 0, 0, 0));
		players.push_back(Player("Player 4", std::vector<Card>(), 0, 0, 0));

		drawDeck(deck, players);

	}
	catch(char const* error)
	{
		std::cout << error << std::endl;
	}
    return 0; 
} 
