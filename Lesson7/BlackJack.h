#pragma once
#include<vector>
#include<iostream>

using namespace std;

enum CardSuit
{
	club,
	diamond,
	hearts,
	spade
};

enum CardRank
{
	ace = 1, two, three,
	four, five, six,
	seven, eight, nine,
	ten, jack , queen, king 
};

class Card
{
public:
	CardSuit suit;
	CardRank rank;
	bool isFaceUp;

	Card(CardSuit _suit, CardRank _rank, bool _isFaceUp = false);
	void Flip();
	int GetValue();
	friend ostream& operator<< (ostream& out, const Card& card);
};

class Hand
{
protected:
	std::vector<Card*> cards;
public:
	Hand();
	virtual ~Hand();
	void Add(Card* newCard);
	void Clear();
	int GetTotal()const;
};

//Абстрактный класс
class GenericPlayer : public Hand
{
	friend ostream& operator<< (ostream& out, const GenericPlayer& gp);

protected:
	std::string name;

public:
	GenericPlayer(const string& _name = "");
	virtual ~GenericPlayer();
	virtual bool isHitting() = 0;
	bool isBusted();
	void Bust();
};


class Player : public GenericPlayer
{
public:
	Player(const std::string& _name = "");
	virtual ~Player();
	virtual bool isHitting();
	void Win() const;
	void Lose()const;
	void Push()const;
};

class House : public GenericPlayer
{
public:
	House(const std::string& name = "House");
	virtual ~House();
	virtual bool isHitting();
	void FlipFirstCard();
};

class Deck : public Hand
{
public:
	Deck();
	virtual ~Deck();
	void Populate();
	void Shuffle();
	void Deal(Hand& hand);
	void AdditionalCards(GenericPlayer& genericPlayer);
};

class Game
{
	Deck deck;
	House house;
	vector<Player> players;

public:
	Game(const vector<std::string>& names);
	~Game();
	void Play();
};



