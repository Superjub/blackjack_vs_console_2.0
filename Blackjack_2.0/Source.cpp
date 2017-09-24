// test

// header files
#include <Windows.h>

#include <iostream>
#include <string>

#include <ctime>

#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "external_func.h"

// namespaces used

using namespace std;


// called functions

void settingUp();

void dealInitialCards();
int randomValue(int min, int max);

void currentScorePlayer();
int currentScorePlayer_2(int arg1);

void currentScoreDealer();
void currentScoreDealer_2();

int convertCharToInt(char card, int points);

void playerDealtCard();
void playerAction();

void dealerDealtCard();
void dealersAction();

void checkWinner();

void bust();
int victory(int winner, int playerPoints);
void draw(string playerOne, string playerTwo);

string charToString(char arg, string arg2);
int charToInt(char arg, int arg2);

void changeActivePlayer();

void restart();

// when calling the array can use cards[Spades][] instead of cards[0][] for instance
#define Spades 0
#define Hearts 1
#define Diamonds 2
#define Clubs 3

// char array for all the different cards- useful for playing with one deck of cards.
char cards[4][13] = { { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'},
					  { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' },
					  { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' },
					  { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' } };


int noOfPlayers;

int currentActivePlayer = 0;
int currentCardArrStart = 0;

// player's/dealer's cards- due to the nature of the game card # can not exceed 22 (assuming a player gets 22 aces.)

// Player one's cards = [0-1][0-21] Player two's cards  [2-3][0-21] ... Player sevon's cards [12-13][0-21]
char playersCards[14][22];
char dealersCards[2][22];

// used for tracking - if the player/dealer has a blackjack in the first turn, giving nth card correctly etc.
int noOfPlayerCards[7] = { 0, 0, 0, 0, 0, 0, 0 };
int noOfDealerCards = 0;

// default player's/dealer's points
int playersCardsVal[7] = { 0, 0, 0, 0, 0, 0, 0 };
int dealersCardsVal = 0;

int playersPoints[7] = { 100, 100, 100, 100, 100, 100, 100 };
string playerName[7] = { "Player One", "Player Two", "Player Three", "Player Four", "Player Five", "Player Six", "Player Seven" };

bool doubleDown[7] = { false, false, false, false, false, false, false };

// bool to make the dealer's second card hidden on the first turn
bool dealersHidden = true;

bool playersTurn = true;

bool roundEnd = false;
bool blackjack = false;

bool gameOver = false;
bool setUp = false;

// main function
int main()
{	
	
	callTitle();
	do {

		settingUp();
		// used to ensure that a different random value is received on runtime.
		srand((unsigned int)time(NULL));

		// used to prevent a loop from being called later.
		roundEnd = false;
		blackjack = false;

		for (int i = 0; i < noOfPlayers; i++)
		{
			cout << playerName[i] << "'s Points = " << playersPoints[i] << endl;
		}

		// calls function to deal the initial cards to the player and dealer.
		dealInitialCards();

		// calls the functions that gets the current score of the player & dealer.

		currentScorePlayer();

		if (blackjack == false)
		{
			
			currentScoreDealer();

			// calls the function that allows the player to act.

			
			playerAction();
			if (roundEnd == false)
			{
				dealersAction();
			}

		}

		//playerDealtCard();

		//currentScorePlayer();

	} while (gameOver == false);
}

void settingUp()
{
	if (setUp == false) {
		cout << "Do you need to read the rules?" << endl;

		char response;

		cin >> response;

		if (response == 'y')
		{
			helpPrint();
		}

		system("cls");

		cout << "How many players? ";

		cin >> noOfPlayers;

		if (noOfPlayers < 1)
		{
			cout << "You must have at least 1 player." << endl;
		}

		if (noOfPlayers > 7)
		{
			cout << "Number of players can not exceed 7." << endl;
		}

		for (int i = 0; i < noOfPlayers; i++)
		{
			cout << "What is the name of player " << i + 1 << "? : ";
			cin >> playerName[i];
			cout << "Player " << i + 1 << " = " << playerName[i] << endl;
		}

		system("pause");
		system("cls");

		setUp = true;

	}
}

void placeBets()
{
	
}

void dealInitialCards()
{
	int noOfCardsToBeDealt = (noOfPlayers * 2);

	cout << "Starting the game..." << endl;
	Sleep(3000);

	cout << endl;

	int cardSuit;
	int cardValue;

	//cout << "Current active player = " << currentActivePlayer << endl;
	//cout << "Current beginning of active players card array = " << currentCardArrStart << endl;

	for (int i = 0; i < noOfPlayers; i++)
	{

		cardSuit = randomValue(0, 3);
		cardValue = randomValue(0, 12);

		playersCards[currentCardArrStart + 1][0] = cards[cardSuit][cardValue];

		if (cardSuit == 0) playersCards[currentCardArrStart][0] = 's';
		if (cardSuit == 1) playersCards[currentCardArrStart][0] = 'h';
		if (cardSuit == 2) playersCards[currentCardArrStart][0] = 'd';
		if (cardSuit == 3) playersCards[currentCardArrStart][0] = 'c';

		cout << "Player " << playerName[currentActivePlayer] << " drew a " << playersCards[currentCardArrStart + 1][0] << " of " << playersCards[currentCardArrStart][0] << endl;

		noOfPlayerCards[currentActivePlayer]++;
		changeActivePlayer();
		Sleep(1000);
	}

	cardSuit = randomValue(0, 3);
	cardValue = randomValue(0, 12);

	dealersCards[1][0] = cards[cardSuit][cardValue];

	if (cardSuit == 0) dealersCards[0][0] = 's';
	if (cardSuit == 1) dealersCards[0][0] = 'h';
	if (cardSuit == 2) dealersCards[0][0] = 'd';
	if (cardSuit == 3) dealersCards[0][0] = 'c';

	cout << "The dealer drew a " << dealersCards[1][0] << " of " << dealersCards[0][0] << endl;
	cout << endl;

	for (int i = 0; i < noOfPlayers; i++)
	{

		cardSuit = randomValue(0, 3);
		cardValue = randomValue(0, 12);

		playersCards[currentCardArrStart + 1][1] = cards[cardSuit][cardValue];

		if (cardSuit == 0) playersCards[currentCardArrStart][1] = 's';
		if (cardSuit == 1) playersCards[currentCardArrStart][1] = 'h';
		if (cardSuit == 2) playersCards[currentCardArrStart][1] = 'd';
		if (cardSuit == 3) playersCards[currentCardArrStart][1] = 'c';

		cout << "Player " << playerName[currentActivePlayer] << " drew a " << playersCards[currentCardArrStart + 1][1] << " of " << playersCards[currentCardArrStart][1] << endl;

		noOfPlayerCards[currentActivePlayer]++;
		changeActivePlayer();
		Sleep(1000);
	}

	cardSuit = randomValue(0, 3);
	cardValue = randomValue(0, 12);

	dealersCards[1][1] = cards[cardSuit][cardValue];

	if (cardSuit == 0) dealersCards[0][1] = 's';
	if (cardSuit == 1) dealersCards[0][1] = 'h';
	if (cardSuit == 2) dealersCards[0][1] = 'd';
	if (cardSuit == 3) dealersCards[0][1] = 'c';

	cout << "The dealer drew a card and places it face down." << endl;
	cout << "debugging" << endl;
	cout << "-----" << endl;
	cout << "The dealer drew a " << dealersCards[1][1] << " of " << dealersCards[0][1] << endl;
	cout << "-----" << endl;
}

int randomValue(int min, int max) {
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x;
	do {
		x = rand();
	} while (x >= RAND_MAX - remainder);
	return min + x % n;
}

void playerAction() {
	bool turnOver = false;
	char response;
	do {

		if (noOfPlayerCards[currentActivePlayer] == 2)
		{

			cout << "It's Player " << playerName[currentActivePlayer] << "'s turn!" << endl;
			cout << "--------------------" << endl;
			currentScorePlayer();
			cout << "--------------------" << endl;
			cout << "What would you like to do? (s for stand/h for hit/d for double down/q for surrender) : " << endl;
			cin >> response;
			if (response == 's')
			{
				if (currentActivePlayer < noOfPlayers)
				{
					changeActivePlayer();
				}
				else { currentActivePlayer = noOfPlayers + 1; }
			}

			if (response == 'h')
			{
				playerDealtCard();
				currentScorePlayer();
				currentScoreDealer();
			}

			if (response == 'd')
			{
				doubleDown[currentActivePlayer] = true;

				playerDealtCard();
				currentScorePlayer();
				currentScoreDealer();

				if (currentActivePlayer < noOfPlayers)
				{
					changeActivePlayer();
				}
				else { currentActivePlayer = noOfPlayers + 1; }

			}

			if (response == 'q')
			{
				cout << "Player " << playerName[currentActivePlayer] << " has surrendered." << endl;
				playersPoints[0] = playersPoints[currentActivePlayer] - 5;
				if (currentActivePlayer < noOfPlayers)
				{
					changeActivePlayer();
				}
				else { currentActivePlayer = noOfPlayers + 1; }

			}

			else if (response != 's' && response != 'h' && response != 'd')
			{
				cout << "Not valid response." << endl;
			}
		}
		else
		{
			cout << "What would you like to do? (s for stand/h for hit/d for double down) : " << endl;
			cin >> response;
			if (response == 's')
			{
				if (currentActivePlayer < noOfPlayers)
				{
					changeActivePlayer();
				}
				else { currentActivePlayer = noOfPlayers + 1; }
			}

			if (response == 'h')
			{
				playerDealtCard();
				currentScorePlayer();
				currentScoreDealer();
			}

			if (response == 'd')
			{
				doubleDown[currentActivePlayer] = true;

				playerDealtCard();
				currentScorePlayer();
				currentScoreDealer();

				if (currentActivePlayer < noOfPlayers)
				{
					changeActivePlayer();
				}
				else { currentActivePlayer = noOfPlayers + 1; }

			}

			else if (response != 's' && response != 'h' && response != 'd')
			{
				cout << "Not valid response." << endl;
			}
		}

	} while (currentActivePlayer != noOfPlayers + 1);
}

void dealersAction() {

	dealersHidden = false;

	bool getCard = false;
	
	currentScorePlayer_2(0);

	currentScoreDealer_2();

	//for (int i = 0; i < noOfPlayers; i++)
	//{ 
	//	cout << "Player's score = " << playersCardsVal[0] << endl;
	//	cout << "Dealer's score = " << dealersCardsVal << endl;

	//	if (dealersCardsVal < playersCardsVal[i])
	//	{
	//		getCard = true;

	//	}

	//}

	if (dealersCardsVal < playersCardsVal[0])
	{
		getCard = true;
	}

	while (getCard == true)
	{
		dealerDealtCard();

		dealersCardsVal = 0;

		currentScoreDealer();

		currentScorePlayer_2(0);
		currentScoreDealer_2();


		if (dealersCardsVal >= playersCardsVal[0] && dealersCardsVal < 22)
		{
			getCard = false;
			break;
		}

		if (dealersCardsVal > 21)
		{
			bust();
			if (dealersCardsVal > 21)
			{
				getCard = false;
				break;
			}
		}

		Sleep(5000);

		dealersCardsVal = 0;
	}

	if (dealersCardsVal > 21)
	{
		cout << "The dealer went bust!" << endl;
	}

	else
	{
		cout << "The dealer sticks." << endl;
	}

	checkWinner();
}

int currentScorePlayer_2(int arg1) {
	// Set the val int to 0 beforehand - ensures that the points from the last call don't remain.
	for (int i = 0; i < noOfPlayerCards[arg1]; i++)
	{
		playersCardsVal[i] = 0;
	}

	for (int i = 0; i < noOfPlayerCards[0]; i++)
	{
		int playersCardsValPost = convertCharToInt(playersCards[arg1+1][i], playersCardsVal[arg1]);
		playersCardsVal[arg1] = playersCardsValPost;
	}

	return arg1;

}


void currentScorePlayer() {
	
	for (int j = 0; j < noOfPlayerCards[currentActivePlayer]; j++)
	{

		int playersCardsValPost = convertCharToInt(playersCards[currentCardArrStart + 1][j], playersCardsVal[currentActivePlayer]);
		playersCardsVal[currentActivePlayer] = playersCardsValPost;

		cout << "Player " << playerName[currentActivePlayer] << "'s Card  = " << playersCards[currentCardArrStart + 1][j] << " of " << playersCards[currentCardArrStart][j] << endl;

	}

	cout << "Player " << playerName[currentActivePlayer] << "'s Total value = "  << playersCardsVal[currentActivePlayer] << endl;
	cout << endl;

	if (playersCardsVal[currentActivePlayer] > 21)
	{
		cout << "Player " << playerName[currentActivePlayer] << " went bust!" << endl;

		bust();

		if (playersCardsVal[currentActivePlayer] > 21)
		{
			if (currentActivePlayer < noOfPlayers)
			{
				changeActivePlayer();
			}
			else { currentActivePlayer = noOfPlayers + 1; }
		}

		else { 
			playersCardsVal[currentActivePlayer] = 0;
			for (int j = 0; j < noOfPlayerCards[currentActivePlayer]; j++)
			{

				int playersCardsValPost = convertCharToInt(playersCards[currentCardArrStart + 1][j], playersCardsVal[currentActivePlayer]);
				playersCardsVal[currentActivePlayer] = playersCardsValPost;

				cout << "Player " << playerName[currentActivePlayer] << "'s Card  = " << playersCards[currentCardArrStart + 1][j] << " of " << playersCards[currentCardArrStart][j] << endl;

			}

			cout << "Player " << playerName[currentActivePlayer] << "'s Total value = " << playersCardsVal[currentActivePlayer] << endl;
			cout << endl;

		}
	}

	playersCardsVal[currentActivePlayer] = 0;

}

void currentScoreDealer_2() {
	for (int i = 0; i < noOfDealerCards; i++)
	{
		int dealersCardsValPost = convertCharToInt(dealersCards[1][i], dealersCardsVal);
		dealersCardsVal = dealersCardsValPost;
	}
}

void currentScoreDealer() {
	playersTurn = false;
	for (int i = 0; i < noOfDealerCards; i++)
	{
		int dealersCardsValPost = convertCharToInt(dealersCards[1][i], dealersCardsVal);
		dealersCardsVal = dealersCardsValPost;
		if (i == 1 && dealersHidden == true) {}

		else {
			cout << "Dealer's Card #" << (i + 1) << "= " << dealersCards[1][i] << " of " << dealersCards[0][i] << endl;
		}
	}
	if (dealersHidden == true) {
		int knownDealerPoints = convertCharToInt(dealersCards[1][0], 0);
		if (dealersCards[1][0] == 'A') { cout << "Dealer's (known) Total value = 1/11 + ?" << endl; }
		else { cout << "Dealer's (known) Total value = " << knownDealerPoints << " + ?" << endl; }
	}

	else {
		cout << "Dealer's Total value = " << dealersCardsVal << endl;
	}

	dealersCardsVal = 0;

	playersTurn = true;

}

void playerDealtCard()
{
	int cardSuit = randomValue(0, 3);

	int cardValue = randomValue(0, 12);

	playersCards[currentCardArrStart + 1][noOfPlayerCards[currentActivePlayer]] = cards[cardSuit][cardValue];

	if (cardSuit == 0) playersCards[currentCardArrStart][noOfPlayerCards[currentActivePlayer]] = 's';
	if (cardSuit == 1) playersCards[currentCardArrStart][noOfPlayerCards[currentActivePlayer]] = 'h';
	if (cardSuit == 2) playersCards[currentCardArrStart][noOfPlayerCards[currentActivePlayer]] = 'd';
	if (cardSuit == 3) playersCards[currentCardArrStart][noOfPlayerCards[currentActivePlayer]] = 'c';

	cout << "Player " << playerName[currentActivePlayer] << " drew a " << playersCards[currentCardArrStart + 1][noOfPlayerCards[currentActivePlayer]] << " of " << playersCards[currentCardArrStart][noOfPlayerCards[currentActivePlayer]] << endl;

	noOfPlayerCards[currentActivePlayer]++;
}

void dealerDealtCard()
{

	int cardSuit = randomValue(0, 3);

	int cardValue = randomValue(0, 12);

	dealersCards[1][noOfDealerCards] = cards[cardSuit][cardValue];

	if (cardSuit == 0) dealersCards[0][noOfDealerCards] = 's';
	if (cardSuit == 1) dealersCards[0][noOfDealerCards] = 'h';
	if (cardSuit == 2) dealersCards[0][noOfDealerCards] = 'd';
	if (cardSuit == 3) dealersCards[0][noOfDealerCards] = 'c';

	cout << "The dealer drew a " << dealersCards[1][noOfDealerCards] << " of " << dealersCards[0][noOfDealerCards] << endl;

	noOfDealerCards++;
}

void bust()
{
	if (currentActivePlayer < (noOfPlayers + 1))
	{
		for (int i = 0; i < noOfPlayerCards[currentActivePlayer]; i++)
		{

			if (playersCards[currentCardArrStart + 1][i] == 'A')
			{
				while (playersCardsVal[currentActivePlayer] > 21)
				{
					playersCardsVal[currentActivePlayer] = playersCardsVal[currentActivePlayer] - 10;
					playersCards[currentCardArrStart + 1][i] = 'X';
					cout << "Player " << playerName[currentActivePlayer] << " plays an Ace as a 1." << endl;
					cout << "Player " << playerName[currentActivePlayer] << "'s Total Value = " << playersCardsVal[currentActivePlayer] << endl;
				}
			}
		}
	}

	if (currentActivePlayer == (noOfPlayers + 1))
	{
		for (int i = 0; i < noOfDealerCards; i++)
		{
			if (dealersCards[1][i] == 'A')
			{
				while (dealersCardsVal > 21)
				{
					dealersCardsVal = dealersCardsVal - 10;
					dealersCards[1][i] = 'X';
					cout << "Dealer plays an Ace as a 1." << endl;
					cout << "Dealers's Total value = " << dealersCardsVal << endl;
				}

			}
		}
	}
}

void checkWinner()
{
	
	currentScorePlayer_2(0);

	dealersCardsVal = 0;
	currentScoreDealer_2();
	
	cout << dealersCardsVal << endl;
	cout << playersCardsVal[0] << endl;
	if (dealersCardsVal >= playersCardsVal[0] && dealersCardsVal < 22)
	{
		victory(8, playersCardsVal[0]);
	}

	else
	{
		victory(0, playersCardsVal[0]);
	}

	roundEnd = true;
	restart();
}

int victory(int winner, int playerPoints)
{

	if (winner < 7)
	{
		cout << playerName[winner] << " is the winner. " << playerName[winner] << " wins!" << endl;
		cout << "No of player cards = " << noOfPlayerCards[winner] << endl;

		if (noOfPlayerCards[winner] != 2 || playersCardsVal[winner] != 21)
		{
			cout << "points before = " << playersPoints[winner] << endl;
			if (!doubleDown[winner])
			{
				playersPoints[winner] = playersPoints[winner] + 10;
			}
			else
			{
				playersPoints[winner] = playersPoints[winner] + 20;
			}
			cout << "points after = " << playersPoints[winner] << endl;
		}

		if (noOfPlayerCards[winner] == 2 && playersCardsVal[winner] == 21)
		{
			cout << "points before = " << playersPoints[winner] << endl;

			playersPoints[winner] = playersPoints[winner] + 15;

			cout << "points after = " << playersPoints[winner] << endl;
		}
	}

	else
	{
		cout << "The dealer is the winner." << endl;

		cout << "points before = " << playersPoints[0] << endl;
		
		if (!doubleDown[0])
		{
			playersPoints[0] = playersPoints[0] - 10;
		}
		else
		{
			playersPoints[0] = playersPoints[0] - 20;
		}
		cout << "points after = " << playersPoints[0] << endl;

	}

	return playerPoints;

}

void draw(string playerOne, string playerTwo)
{
	cout << "Both player and dealer have a blackjack." << endl;
	roundEnd = true;
	restart();
}

void restart()
{
	cout << "Play again? (y/n) ";
	char response;
	cin >> response;

	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			playersCards[j][i] = '\0';
		}

		dealersCards[0][i] = '\0';
		dealersCards[1][i] = '\0';


	}

	for (int i = 0; i < noOfPlayers; i++)
	{
		noOfPlayerCards[i] = 0;
		playersCardsVal[i] = 0;
		doubleDown[i] = false;
	}

	blackjack = false;
	noOfDealerCards = 0;
	dealersCardsVal = 0;
	dealersHidden = true;

	system("CLS");
	if (response == 'n')
	{
		gameOver = true;
	}
}

int convertCharToInt(char card, int points) {
	if (card == 'X') { points = points + 1; }

	if (card == '2') {  points = points + 2; }
	if (card == '3') {  points = points + 3; }
	if (card == '4') {  points = points + 4; }
	if (card == '5') {  points = points + 5; }
	if (card == '6') {  points = points + 6; }
	if (card == '7') {  points = points + 7; }
	if (card == '8') {  points = points + 8; }
	if (card == '9') {  points = points + 9; }
	if (card == 'T') {  points = points + 10; }
	if (card == 'J') {  points = points + 10; }
	if (card == 'Q') {  points = points + 10; }
	if (card == 'K') {  points = points + 10; }
	if (card == 'A')
	{
		points = points + 11;

		//if (playersTurn == true)
		//{

		//	if (playersCardsVal[0] <= 10)
		//	{
		//		points = points + 11;
		//	}

		//	else
		//	{
		//		points = points + 1;
		//		card = 'X';
		//	}
		//}

		//else
		//{
		//	if (dealersCardsVal <= 10)
		//	{
		//		points = points + 11;
		//	}

		//	else
		//	{
		//		points = points + 1;
		//		card = 'X';
		//	}
		//}
	}


	return points;
}

string charToString(char arg, string arg2)
{
	if (arg == 'J')
	{
		arg2 = "Jack";
	}

	if (arg == 'K')
	{
		arg2 = "King";
	}

	if (arg == 'A' || arg == 'X')
	{
		arg2 = "Ace";
	}

	return arg2;

}

int charToInt(char arg, int arg2)
{
	if (arg == 'T')
	{
		arg2 = 10;
	}

	return arg2;

}

void changeActivePlayer()
{
	if (noOfPlayers > 0)
	{

		if (currentActivePlayer < noOfPlayers)
		{
			currentActivePlayer++;
		}

		if (currentActivePlayer == noOfPlayers)
		{
			currentActivePlayer = 0;
		}

		currentCardArrStart = currentActivePlayer + currentActivePlayer;

		/*cout << "Current active player = " << currentActivePlayer << endl;
		cout << "Current beginning of active players card array = " << currentCardArrStart << endl;*/
	}
}

