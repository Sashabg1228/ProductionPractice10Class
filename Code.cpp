#include <iostream> 
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
 
using namespace std; 

class Card
{
	protected:
		char value;
		char color;
	public:
		//* Constructors

		// Default constructor
		Card(){}

		// Constructor with parameters
		Card(char value, char color)
		{
			this->value = value;
			this->color = color;
		}

		// Copy constructor
		Card(const Card& other)
		{
			this->value = other.value;
			this->color = other.color;
		}

		//* Destructor

		~Card(){}

		//* Getters

		// Get value
		char getValue() const
		{
			return value;
		}

		// Get color
		char getColor() const
		{
			return color;
		}

		//* Setters

		// Set value
		void setValue(char value)
		{
			this->value = value;
		}

		// Set color
		void setColor(char color)
		{
			this->color = color;
		}

		//* Methods

		// Check Value
		void checkValue(char value)
		{
			static const char values[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A'};

			if(find(begin(values), end(values), value) == end(values))
			{
				throw "Error: Invalid value";
			}
		}

		// Check Color
		void checkColor(char color)
		{
			static const char colors[] = {'C', 'D', 'H', 'S'};

			if(find(begin(colors), end(colors), color) == end(colors))
			{
				throw "Error: Invalid color";
			}
		}

		// Get points
		int getValuePoints() const
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

		int getColorPoints(){
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
};

class Player
{
	private:
		string name;
		vector<Card> hand;
		int isWinner;
		int points;
        int colorPoints;
	public:
		//* Constructors

		// Default constructor
		Player(){}
		
		// Constructor with parameters
		Player (string name, vector<Card> hand, int isWinner, int points, int colorPoints)
		{
			this->name = name;
			this->hand = hand;
			this->isWinner = isWinner;
			this->points = points;
            this->colorPoints = colorPoints;
		}

		// Copy constructor
		Player(const Player& other)
		{
			this->name = other.name;
			this->hand = other.hand;
			this->isWinner = other.isWinner;
			this->points = other.points;
            this->colorPoints = other.colorPoints;
		}

		//* Destructor

		~Player(){}

		//* Getters

		// Get name	
		string getName()
		{
			return name;
		}

		// Get hand
		vector<Card> getHand()
		{
			return hand;
		}

		// Get isWinner
		int getIsWinner()
		{
			return isWinner;
		}

		// Get points
		int getPoints()
		{
			return points;
		}

        // Get finalePoints
		int getcolorPoints()
		{
			return colorPoints;
		}

		//* Setters

		// Set name
		void setName(string name)
		{
			this->name = name;
		}

		// Set hand
		void setHand(vector<Card> hand)
		{
			this->hand = hand;
		}

		// Set isWinner
		void setIsWinner(int isWinner)
		{
			this->isWinner = isWinner;
		}

		// Set points
		void setPoints(int points)
		{
			this->points = points;
		}

        // Set colorPoints
		void setcolorPoints(int colorPoints)
		{
			this->colorPoints = colorPoints;
		}

		//* Functions

		// Adds a card to the hand of the player
		void addCard(Card card)
		{
			hand.push_back(card);

			sortHand();
			
			checkHand();
		}

		void sortHand()
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

		void switchCards(int index1, int index2)
		{
			Card temp = hand[index1];
			hand[index1] = hand[index2];
			hand[index2] = temp;
		}

		void checkHand()
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

                if(numOfSimilar == 4)
                {
                    setIsWinner(1);
                    setPoints(hand[i].getValuePoints());
                    //cout << "Winner: " << isWinner << endl;
                    //cout << "Points: " << points << endl;
                }
            }
		}

        void getFinaleValuePoints()
        {
            vector<Card> hand2;
            int valuePoints = 0;
            hand2 = getHand();

            for(int i = 0; i < hand2.size(); i++)
            {
                valuePoints += hand2[i].getValuePoints();
            }

            setPoints(valuePoints);
        }
        void getFinaleColorPoints()
        {
            vector<Card> hand2;
            int colorPoints = 0;
            hand2 = getHand();

            for(int i = 0; i < hand2.size(); i++)
            {
                colorPoints += hand2[i].getColorPoints();
            }

            setcolorPoints(colorPoints);
        }
};

//* Declare Functions
void readInput(vector<Card> &cards);
void printPlayer(Player player);
int checkNumberOfWinners(vector<Player> players);
int drawCycle(vector<Card> &cards, vector<Player> &players);
void drawDeck(vector<Card> &cards, vector<Player> &players);

//* Main function
int main()
{ 
	try
	{
    	vector<Card> deck;
		readInput(deck);

		vector<Player> players;
		players.push_back(Player("Player 1", vector<Card>(), 0, 0, 0));
		players.push_back(Player("Player 2", vector<Card>(), 0, 0, 0));
		players.push_back(Player("Player 3", vector<Card>(), 0, 0, 0));
		players.push_back(Player("Player 4", vector<Card>(), 0, 0, 0));

		drawDeck(deck, players);

	}
	catch(char const* error)
	{
		cout << error << endl;
	}
    return 0; 
} 

//* Functions
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

    if(checkNumberOfWinners(players) > 0)////////////////////////////////////////
    {
        return 1;//Ako ima hora s 4 karti
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
