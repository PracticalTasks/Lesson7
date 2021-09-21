#include<algorithm>
#include<vector>
#include<ctime>
#include"BlackJack.h"

//Class Card
Card::Card(CardSuit _suit, CardRank _rank, bool _isFaceUp) : suit(_suit), rank(_rank), isFaceUp(_isFaceUp)
{}

void Card::Flip()
{
	isFaceUp = !(isFaceUp);
}

int Card::GetValue()
{
	int value{};

	if (isFaceUp)
	{
		value = rank;
		if (value > 10)
		{
			value = 10;
		}
	}

	return value;
}

ostream& operator<< (ostream& out, const Card& card)
{
	const std::string RANKS[]{ "0","A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	const std::string SUITS[]{ "c","d","h","s" };

	if (card.isFaceUp)
		out << RANKS[card.rank] << SUITS[card.suit];
	else
		out << "XX";

	return out;
}

Hand::~Hand()
{
	Clear();
}

void Hand::Add(Card* newCard)
{
	cards.push_back(newCard);
}

void Hand::Clear()
{
	std::vector<Card*>::iterator iter = cards.begin();
	for (iter = cards.begin(); iter != cards.end(); ++iter)
	{
		delete* iter;
		*iter = 0;
	}
	cards.clear();
}

int Hand::GetTotal()const
{
	if (cards.empty())
		return 0;

	if (cards[0]->GetValue() == 0)
		return 0;

	// находит сумму очков всех карт, каждый туз дает 1 очко
	int total{};
	for (int i{}; i < cards.size(); ++i)
	{
		total += cards[i]->GetValue();
	}

	// определяет, держит ли рука туз
	bool containsAce{};
	for (int i{}; i < cards.size(); ++i)
	{
		if (cards[i]->GetValue() == CardRank::ace)
			containsAce = true;
	}

	// если рука держит туз и сумма довольно маленькая, туз дает 11 очков
	if (containsAce && total <= 11)
		total += 10;        // добавляем только 10 очков, поскольку мы уже добавили
							// за каждый туз по одному очку

	return total;
}

//Class GenericPlayer
GenericPlayer::GenericPlayer(const std::string& _name): name(_name)
{}

bool GenericPlayer::isBusted()
{
	return (GetTotal() > 21);
}

void GenericPlayer::Bust()
{
	std::cout << name << " busts.\n";
}

ostream& operator<<(ostream& out, const GenericPlayer& gp)
{
	out << gp.name <<":\t";

	std::vector<Card*>::const_iterator pCard;

	if (!gp.cards.empty())
	{
		for (pCard = gp.cards.begin(); pCard != gp.cards.end(); ++pCard)
		{
			out << *(*pCard) << '\t';
		}

		if (gp.GetTotal() != 0)
			cout << '(' << gp.GetTotal() << ')';

	}
	else
		out << "<empty>";

	return out;
}

//Class Player
Player::Player(const std::string& _name)
{
	name = _name;
}

bool Player::isHitting() 
{
	std::cout <<name<< ", do you want a hit? (Y/N):\n";
	char response{};
	while (true)
	{
		cin.ignore(1000, '\n');
		cin.get(response);
		if (response != 'y' && response != 'Y' && response != 'n' && response != 'N')
		{
			std::cout << name << ", do you want a hit? (Y/N):\n";
			continue;
		}
		else
			break;
	}

	return (response == 'y' || response == 'Y');
}

void Player::Win() const
{
	std::cout << name << " wins.\n";
}

void Player::Lose()const
{
	std::cout << name << " loses.\n";
}

void Player::Push()const
{
	cout << name << " pushes.\n";
}

//Class House
House::House(const std::string& _name)
{
	name = _name;
}

House::~House()
{}

bool House::isHitting()
{
	return (GetTotal() <= 16);
}

void House::FlipFirstCard()
{
	if (!(cards.empty()))
		cards[0]->Flip();
	else
		cout << "No card to flip!\n";
}

void Deck::Populate()
{
	for (int s{ CardSuit::club }; s <= CardSuit::spade; ++s)
	{
		for (int r{ CardRank::ace }; r <= CardRank::king; ++r)
		{
			Add(new Card((CardSuit)s,(CardRank)r));
		}
	}

}

void Deck::Shuffle()
{
	random_shuffle(cards.begin(),cards.end());
}

void Deck::Deal(Hand& hand)
{
	if (!cards.empty())
	{
		hand.Add(cards.back());
		cards.pop_back();
	}
	else
		cout << "Out of cards. Unable to deal.";
}

void Deck::AdditionalCards(GenericPlayer& genericPlayer)
{
	cout << std::endl;

	while (!(genericPlayer.isBusted()) && genericPlayer.isHitting())
	{
		Deal(genericPlayer);
		std::cout << genericPlayer<<'\n';

		if (genericPlayer.isBusted())
			genericPlayer.Bust();
	}
}

//Class Game
Game::Game(const vector<string>& names)
{
	//deck.Clear();
	vector<string>::const_iterator pName;
	for (pName = names.begin(); pName != names.end(); ++pName)
	{
		players.push_back(Player(*pName));
	}

	// запускает генератор случайных чисел
	srand(static_cast<unsigned int>(time(0)));
	deck.Populate();
	deck.Shuffle();
}

void Game::Play()
{
	// раздает каждому по две стартовые карты
	for (int i{}; i < 2; ++i)
	{
		for (int j{}; j < players.size(); ++j)
		{
			deck.Deal(players[j]);
		}
		deck.Deal(house);
	}

	// прячет первую карту дилера
	house.FlipFirstCard();

	//Открывает руки всех игроков
	for (int i{}; i < players.size(); ++i)
		cout << players[i] << endl;
	cout << house << endl;

	//Раздаёт игрокам доп. карты
	for (int i{}; i < players.size(); ++i)
		deck.AdditionalCards(players[i]);

	//Показывает первую карту дилера 
	house.FlipFirstCard();
	cout << endl << house;

	//Раздаёт дилеру дополнительные карты
	deck.AdditionalCards(house);

	if (house.isBusted())
	{
		//Все кто остался в игре побеждают
		for (int i{}; i < players.size(); ++i)
		{
			if (!(players[i].isBusted()))
			{
				players[i].Win();
			}
		}
	}
	else
	{
		//Сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
		for (int i{}; i < players.size(); ++i)
		{
			if (!(players[i].isBusted()))
			{
				if (players[i].GetTotal() > house.GetTotal())
					players[i].Win();

				else if (players[i].GetTotal() < house.GetTotal())
					players[i].Lose();

				else
					players[i].Push();
			}
		}
	}

	//Очищает руки всех игроков
	for (int i{}; i < players.size(); ++i)
		players[i].Clear();
	house.Clear();
}