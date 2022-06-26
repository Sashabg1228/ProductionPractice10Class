#include "functions.hpp"
#include "card.hpp"
#include "player.hpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void readInput(vector<Card> &cards)
{
	string line, inputFile = "input.txt"; 
	char symbol, value, color;
	int symbolNumber = 1;

	ifstream inFile(inputFile);										
	if(inFile.is_open())
	{ 												
        while(getline(inFile, line))
		{
			stringstream ss(line);

			while(ss >> symbol)
			{
				if(symbolNumber % 2 != 0)
				{
					value = symbol;

					symbolNumber++;
				}
				else if(symbolNumber % 2 == 0)
				{
					color = symbol;

					symbolNumber++;

					Card card;
					card.setValue(value);
					card.setColor(color);

					cards.push_back(card);
				}
				else
				{
					throw "Error: Invalid input";
				}
			}
		}
        inFile.close();
    }
    else
	{
        throw "Error: Unable to open file";
    }
}

void printPlayer(Player player){
    cout << player.getName() << ": ";
		for(int j = 0; j < player.getHand().size(); j++)
		{
			if(j == 0)
			{
				cout << "(" << player.getHand()[j].getValue() << ", " << player.getHand()[j].getColor() << ")";
			}
			else
			{
				cout << ", (" << player.getHand()[j].getValue() << ", " << player.getHand()[j].getColor() << ")";
			}
		}
		cout << endl;
}

int checkNumberOfWinners(vector<Player> players){
    int numOfWinners = 0;
    static int PlayersNumber = players.size();

    for(int i = 0; i < PlayersNumber; i++){
        //cout << players[i].getIsWinner() << endl;
        if(players[i].getIsWinner() == 1){
            numOfWinners++;
        }
    }

    return numOfWinners;
}

int drawCycle(vector<Card> &cards, vector<Player> &players)
{
	static int PlayersNumber = players.size();
	static Card card;

	for(int i = 0; i < PlayersNumber; i++)
	{
		card = cards.front();
		cards.erase(cards.begin());
		players[i].addCard(card);
	}

    if(checkNumberOfWinners(players) > 0)
    {
        return 1;
    }
    else{
        return 0;
    }
}

void drawDeck(vector<Card> &cards, vector<Player> &players)
{
	int deckSize = cards.size();//TODO: Throw error
	int playersNumber = players.size();//TODO: Throw error	
	int cardsPerPlayer = deckSize / playersNumber;
    int checkTurns;
    int numberOfWinners;

	for(int i = 0; i < cardsPerPlayer; i++)
	{
		checkTurns = drawCycle(cards, players);
        if(checkTurns == 1){
            break;
        }
	}

    numberOfWinners = checkNumberOfWinners(players);

    if(numberOfWinners == 0){
        //cout << "0 Winners:" << numberOfWinners << endl;
        int maxV = 0, maxC = 0;
        vector <int> index;
        vector <int> index2;


        for(int i = 0; i < playersNumber; i++){
            players[i].getFinaleValuePoints();
            players[i].getFinaleColorPoints();
        }

        for(int i = 0; i < playersNumber; i++){
            if(players[i].getPoints() >= maxV){
                maxV = players[i].getPoints();
                index.push_back(i);
            }
        }

        if(index.size() == 1){
            printPlayer(players[index[0]]);
        }
        else{
            for(int i = 0; i < index.size(); i++){
                if(players[index[i]].getcolorPoints() > maxC){
                    maxC = players[index[i]].getcolorPoints();
                    index2.push_back(index[i]);
                }
            }
            if(index2.size() == 1){
                printPlayer(players[index2[0]]);
            }
            else{
                cout << "Tie" << endl;
            }
        }
    }
    else if(numberOfWinners == 1)
    {
        for(int i = 0; i < playersNumber; i++){
            if(players[i].getIsWinner() == 1){
                printPlayer(players[i]);
            }
        }
    }
    else if(numberOfWinners > 1)
    {
        //cout << "Many Winners:" << numberOfWinners << endl;
        int max = 0;
        for(int i = 0; i < playersNumber; i++){
            if(players[i].getPoints() > max){
                max = players[i].getPoints();
                
            }
        }
        for(int i = 0; i < playersNumber; i++){
            if(players[i].getPoints() == max){
                printPlayer(players[i]);
            }
        }
    }
}
