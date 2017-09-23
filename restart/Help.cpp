#include <iostream>
#include <string>

#include <ctime>

#include <stdlib.h>
#include <time.h>

#include "external_func.h"

using namespace std;

//int main()
//{
//
//}

void helpPrint()
{
	system("cls");

	cout << "Rules of Blackjack" << endl;
	cout << "-------------------" << endl;
	cout << "The aim of blackjack is to beat the dealer. To beat the dealer, the player must:" << endl;
	cout << "a) not go over 21 and" << endl;
	cout << "b) outscore the dealer or make him go bust." << endl;
	cout << endl;
	cout << "-------------------" << endl;
	cout << "General Rules" << endl;
	cout << "-------------------" << endl;
	cout << "Blackjack is played with multiple 52-card decks." << endl;
	cout << "3-7 games can be played." << endl;
	cout << "Aces may be counted as either 1 or 11 points. If the players point total is below 11, they will automatically count as" << endl;
	cout << "11 points and will adjust according so that if possible they will keep the player at or below 21." << endl;
	cout << "A ‘blackjack’ hand always outranks all other 21- point hands." << endl;
	cout << "At the beginning of the game the dealer will give two cards to each player and then two cards to himself. One of the" << endl;
	cout << "cards is face up and one face down. The face down card is called the hole card." << endl;
	cout << "If the dealer has an ace showing, insurance is offered. If the dealers other card is any 10-point card, the player gains" << endl;
	cout << "20 points. If it is not, they lose 20 points." << endl;
	cout << "If the dealer has an ace or a ten showing, they will peek at his hole card to see if they have blackjack. If they do, they" << endl;
	cout << "will turn it over immediately. If the dealer has blackjack all wagers (but insurance) will lose unless a player also has a" << endl;
	cout << "blackjack which will result in a push (earning 5 points)." << endl;
	cout << "After each player has had his turn, the dealer will turn over their hole card if not already turned over. If they have 16" << endl;
	cout << "or less, they will draw another card." << endl;
	cout << "If the dealer goes over 21 points, any player who hasn’t already bust will win." << endl;
	cout << "If no-one busts the player with the highest point wins." << endl;
	cout << endl;
	cout << "Win = + 10 points." << endl;
	cout << "Lose = - 10 points" << endl;
	cout << "Blackjack = 15 points" << endl;
	cout << "Draw(Push) = + 5 points" << endl;
	cout << "(Points earnt/lost are doubled when double down is used." << endl;
	cout << endl;
	cout << "-------------------" << endl;
	cout << "Player Actions" << endl;
	cout << "-------------------" << endl;
	cout << "* Stand: Player stands pat with his cards." << endl;
	cout << "* Hit: Player draws another card (and more if he wishes). If this card causes the player's total points to exceed 21" << endl;
	cout << "(known as 'breaking' or 'busting') then he loses." << endl;
	cout << "* Double down: Player doubles his bet and gets one, and only one, more card." << endl;
	cout << "* Split: If the player has a pair, or any two 10-point cards, then he may double his bet and separate his cards into" << endl;
	cout << "two individual hands. The dealer will automatically give each card a second card. Then, the player may hit, stand, or" << endl;
	cout << "double normally. However, when splitting aces, each ace gets only one card. Sometimes doubling after splitting is not" << endl;
	cout << "allowed. If the player gets a ten and ace after splitting, then it counts as 21 points, not a blackjack. Usually the" << endl;
	cout << "player may keep re-splitting up to a total of four hands. Sometimes re-splitting aces is not allowed." << endl;
	cout << "* Surrender: The player forfeits half his wager, keeping the other half, and does not play out his hand. This option" << endl;
	cout << "is only available on the initial two cards." << endl;
	cout << endl;
	system("pause");
	system("cls");
}