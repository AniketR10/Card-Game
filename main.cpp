#include <iostream>
#include <array>
#include <cassert>
#include <algorithm>
#include "Random.h"

struct Card {
    enum Rank {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,
        max_ranks,
    };

    enum Suit {
        club,
        diamond,
        heart,
        spade,
        count
    };

    Rank rank{};
    Suit suit{};

    Card() = default;

    Card(Rank r, Suit s) : rank{ r }, suit{ s } {}

    static constexpr std::array allSuits{ club, diamond, heart, spade };
    static constexpr std::array allRanks{
        rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9,
        rank_10, rank_jack, rank_queen, rank_king
        
    };

    friend std::ostream& operator<<(std::ostream& out, const Card& card) {
        static constexpr std::array ranks{ 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array suits{ 'C', 'D', 'H', 'S' };
        out << ranks[card.rank] << suits[card.suit];
        return out;
    }

    int values() const {
        static constexpr std::array rankValues{ 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }
};

class Deck {
    std::array<Card, 52> m_cards{};
    std::size_t m_nextCardIndex{ 0 };

public:
    Deck() {
        std::size_t count{ 0 };
        for (auto suit : Card::allSuits) {
            for (auto rank : Card::allRanks) {
                m_cards[count++] = Card{ rank, suit };
            }
        }
    }

    void shuffle() {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);  // Use Random::mt for shuffling
        m_nextCardIndex = 0;  // Reset the index after shuffling
    }

    Card dealCard() {
        assert(m_nextCardIndex < 52 && "Deck::dealCard ran out of cards");
        return m_cards[m_nextCardIndex++];
    }
};

// game begins

struct Player {
    int score{};
};

namespace Settings {

    int player_busts{ 21 };
    int dealer_stops{ 17 };

}

bool dealerPlays(Deck& deck, Player& dealer) {
    while (dealer.score < Settings::dealer_stops) {
        Card card{ deck.dealCard() };
        dealer.score += card.values();
        std::cout << "the dealer filps a " << card << " they now have a " << dealer.score << '\n';

    }
    if (dealer.score > Settings::dealer_stops) {
        if (dealer.score > Settings::player_busts) {
            std::cout << "The dealer went bust!!!! \n";
            return true;
        }
    }
    return false;
}

bool playGame() {

    Deck deck{};
    deck.shuffle();
    Player dealer{ deck.dealCard().values()};
  
    std::cout << "The dealer has a score of : " << dealer.score << "\n";
    Player player{ deck.dealCard().values() + deck.dealCard().values()};
    std::cout << "The player score is : " << player.score << '\n';
    char ch{};
    while (true) {
        std::cout << "Choose (h) to hit, (s) to stand : \n";
        std::cin >> ch;
        if (ch == 's') break;
       
        Card card{ deck.dealCard() };
        player.score += card.values();
        std::cout << "You are dealt with " <<card << '\n' <<" You have now : " <<player.score<<'\n';
        if (player.score > Settings::player_busts) {
            return false;
        }
    }
   
        if (dealerPlays(deck, dealer)) {
            return true;
        }
    
    
    return (player.score > dealer.score && player.score <= 21);

}




int main() {
   
    Deck deck{};
    //std::cout << deck.dealCard() << " "<<deck.dealCard() << " "<<deck.dealCard() << "\n";
  
    deck.shuffle();
  //  std::cout << deck.dealCard() << " " << deck.dealCard() << " " << deck.dealCard() << '\n';
    
    if (playGame()) std::cout << "The player wins.";
    else std::cout << "The dealer wins ";


    return 0;
}
