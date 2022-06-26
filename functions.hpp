#pragma once

#include "card.hpp"
#include "player.hpp"

#include <vector>

void readInput(std::vector<Card> &cards);
void printPlayer(Player player);
int checkNumberOfWinners(std::vector<Player> players);
int drawCycle(std::vector<Card> &cards, std::vector<Player> &players);
void drawDeck(std::vector<Card> &cards, std::vector<Player> &players);