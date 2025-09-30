#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <numeric>
#include <algorithm>
#include "Card.hpp"
#include "GameEngine.hpp"
#include "DatasetExporter.hpp"

#define TOTAL_CARDS 78
#define CARDS_PER_PLAYER 18
#define NUM_PLAYERS 4
#define CHIEN_SIZE 6

struct CardInfo
{
    std::string name;
    Suit suit;
    Rank rank;
    float points;
};

CardInfo getCardInfo(int idx)
{
    switch (idx)
    {
        case 0:  return {"Excuse", Suit::Excuse, Rank::Excuse, 4.5f};

        // Atouts 1 à 21
        case 1:  return {"Trump 1", Suit::Trump, Rank::Trump1, 4.5f};
        case 2:  return {"Trump 2", Suit::Trump, Rank::Trump2, 0.5f};
        case 3:  return {"Trump 3", Suit::Trump, Rank::Trump3, 0.5f};
        case 4:  return {"Trump 4", Suit::Trump, Rank::Trump4, 0.5f};
        case 5:  return {"Trump 5", Suit::Trump, Rank::Trump5, 0.5f};
        case 6:  return {"Trump 6", Suit::Trump, Rank::Trump6, 0.5f};
        case 7:  return {"Trump 7", Suit::Trump, Rank::Trump7, 0.5f};
        case 8:  return {"Trump 8", Suit::Trump, Rank::Trump8, 0.5f};
        case 9:  return {"Trump 9", Suit::Trump, Rank::Trump9, 0.5f};
        case 10: return {"Trump 10", Suit::Trump, Rank::Trump10, 0.5f};
        case 11: return {"Trump 11", Suit::Trump, Rank::Trump11, 0.5f};
        case 12: return {"Trump 12", Suit::Trump, Rank::Trump12, 0.5f};
        case 13: return {"Trump 13", Suit::Trump, Rank::Trump13, 0.5f};
        case 14: return {"Trump 14", Suit::Trump, Rank::Trump14, 0.5f};
        case 15: return {"Trump 15", Suit::Trump, Rank::Trump15, 0.5f};
        case 16: return {"Trump 16", Suit::Trump, Rank::Trump16, 0.5f};
        case 17: return {"Trump 17", Suit::Trump, Rank::Trump17, 0.5f};
        case 18: return {"Trump 18", Suit::Trump, Rank::Trump18, 0.5f};
        case 19: return {"Trump 19", Suit::Trump, Rank::Trump19, 0.5f};
        case 20: return {"Trump 20", Suit::Trump, Rank::Trump20, 0.5f};
        case 21: return {"Trump 21", Suit::Trump, Rank::Trump21, 4.5f};

        // Cœurs 1 à Roi (22–35)
        case 22: return {"Hearts 1", Suit::Hearts, Rank::One, 0.5f};
        case 23: return {"Hearts 2", Suit::Hearts, Rank::Two, 0.5f};
        case 24: return {"Hearts 3", Suit::Hearts, Rank::Three, 0.5f};
        case 25: return {"Hearts 4", Suit::Hearts, Rank::Four, 0.5f};
        case 26: return {"Hearts 5", Suit::Hearts, Rank::Five, 0.5f};
        case 27: return {"Hearts 6", Suit::Hearts, Rank::Six, 0.5f};
        case 28: return {"Hearts 7", Suit::Hearts, Rank::Seven, 0.5f};
        case 29: return {"Hearts 8", Suit::Hearts, Rank::Eight, 0.5f};
        case 30: return {"Hearts 9", Suit::Hearts, Rank::Nine, 0.5f};
        case 31: return {"Hearts 10", Suit::Hearts, Rank::Ten, 0.5f};
        case 32: return {"Hearts Jack", Suit::Hearts, Rank::Jack, 1.5f};
        case 33: return {"Hearts Cavalier", Suit::Hearts, Rank::Cavalier, 2.5f};
        case 34: return {"Hearts Queen", Suit::Hearts, Rank::Queen, 3.5f};
        case 35: return {"Hearts King", Suit::Hearts, Rank::King, 4.5f};

        // Carreaux (Diamonds) 36–49
        case 36: return {"Diamonds 1", Suit::Diamonds, Rank::One, 0.5f};
        case 37: return {"Diamonds 2", Suit::Diamonds, Rank::Two, 0.5f};
        case 38: return {"Diamonds 3", Suit::Diamonds, Rank::Three, 0.5f};
        case 39: return {"Diamonds 4", Suit::Diamonds, Rank::Four, 0.5f};
        case 40: return {"Diamonds 5", Suit::Diamonds, Rank::Five, 0.5f};
        case 41: return {"Diamonds 6", Suit::Diamonds, Rank::Six, 0.5f};
        case 42: return {"Diamonds 7", Suit::Diamonds, Rank::Seven, 0.5f};
        case 43: return {"Diamonds 8", Suit::Diamonds, Rank::Eight, 0.5f};
        case 44: return {"Diamonds 9", Suit::Diamonds, Rank::Nine, 0.5f};
        case 45: return {"Diamonds 10", Suit::Diamonds, Rank::Ten, 0.5f};
        case 46: return {"Diamonds Jack", Suit::Diamonds, Rank::Jack, 1.5f};
        case 47: return {"Diamonds Cavalier", Suit::Diamonds, Rank::Cavalier, 2.5f};
        case 48: return {"Diamonds Queen", Suit::Diamonds, Rank::Queen, 3.5f};
        case 49: return {"Diamonds King", Suit::Diamonds, Rank::King, 4.5f};

        // Trèfles (Clubs) 50–63
        case 50: return {"Clubs 1", Suit::Clubs, Rank::One, 0.5f};
        case 51: return {"Clubs 2", Suit::Clubs, Rank::Two, 0.5f};
        case 52: return {"Clubs 3", Suit::Clubs, Rank::Three, 0.5f};
        case 53: return {"Clubs 4", Suit::Clubs, Rank::Four, 0.5f};
        case 54: return {"Clubs 5", Suit::Clubs, Rank::Five, 0.5f};
        case 55: return {"Clubs 6", Suit::Clubs, Rank::Six, 0.5f};
        case 56: return {"Clubs 7", Suit::Clubs, Rank::Seven, 0.5f};
        case 57: return {"Clubs 8", Suit::Clubs, Rank::Eight, 0.5f};
        case 58: return {"Clubs 9", Suit::Clubs, Rank::Nine, 0.5f};
        case 59: return {"Clubs 10", Suit::Clubs, Rank::Ten, 0.5f};
        case 60: return {"Clubs Jack", Suit::Clubs, Rank::Jack, 1.5f};
        case 61: return {"Clubs Cavalier", Suit::Clubs, Rank::Cavalier, 2.5f};
        case 62: return {"Clubs Queen", Suit::Clubs, Rank::Queen, 3.5f};
        case 63: return {"Clubs King", Suit::Clubs, Rank::King, 4.5f};

        // Piques (Spades) 64–77
        case 64: return {"Spades 1", Suit::Spades, Rank::One, 0.5f};
        case 65: return {"Spades 2", Suit::Spades, Rank::Two, 0.5f};
        case 66: return {"Spades 3", Suit::Spades, Rank::Three, 0.5f};
        case 67: return {"Spades 4", Suit::Spades, Rank::Four, 0.5f};
        case 68: return {"Spades 5", Suit::Spades, Rank::Five, 0.5f};
        case 69: return {"Spades 6", Suit::Spades, Rank::Six, 0.5f};
        case 70: return {"Spades 7", Suit::Spades, Rank::Seven, 0.5f};
        case 71: return {"Spades 8", Suit::Spades, Rank::Eight, 0.5f};
        case 72: return {"Spades 9", Suit::Spades, Rank::Nine, 0.5f};
        case 73: return {"Spades 10", Suit::Spades, Rank::Ten, 0.5f};
        case 74: return {"Spades Jack", Suit::Spades, Rank::Jack, 1.5f};
        case 75: return {"Spades Cavalier", Suit::Spades, Rank::Cavalier, 2.5f};
        case 76: return {"Spades Queen", Suit::Spades, Rank::Queen, 3.5f};
        case 77: return {"Spades King", Suit::Spades, Rank::King, 4.5f};

        default: return {"Unknown", Suit::Trump, Rank::Trump2, 0.5f};
    }
}

bool cardLess(const Card &a, const Card &b)
{
    auto suitOrder = [](Suit s)
    {
        switch (s)
        {
            case Suit::Excuse:   return 0;
            case Suit::Trump:    return 1;
            case Suit::Hearts:   return 2;
            case Suit::Diamonds: return 3;
            case Suit::Clubs:    return 4;
            case Suit::Spades:   return 5;
        }
        return 6;
    };

    int sa = suitOrder(a.getSuit());
    int sb = suitOrder(b.getSuit());

    if (sa != sb)
    {
        return sa < sb;
    }

    int ra = static_cast<int>(a.getRank());
    int rb = static_cast<int>(b.getRank());

    if (ra != rb)
    {
        return ra < rb;
    }

    // En cas d’égalité parfaite, on compare les noms pour stabiliser le tri
    return a.getName() < b.getName();
}


void tirer(std::vector<std::vector<Card>> &players, std::vector<Card> &chien, std::vector<Card> &deck)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(deck.begin(), deck.end(), gen);

    players.clear();
    players.resize(NUM_PLAYERS);
    chien.clear();

    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        if (i < NUM_PLAYERS * CARDS_PER_PLAYER)
        {
            players[i / CARDS_PER_PLAYER].push_back(deck[i]);
        }
        else
        {
            chien.push_back(deck[i]);
        }
    }

    for (auto &hand : players)
    {
        TarotGame::trierMain(hand);
    }
}

static void positionnerTout(sf::RenderWindow &window,
                            std::vector<std::vector<Card>> &players,
                            std::vector<Card> &chien)
{
    sf::Vector2u winSize = window.getSize();
    float scale = 0.3f;

    sf::Vector2f tailleCarte = players[0][0].getSize();

    std::cout << "Taille window : " << winSize.x << " x " << winSize.y << "\n";
    std::cout << "Taille carte : " << tailleCarte.x << " x " << tailleCarte.y << "\n";

    auto positionnerCartes = [&](int playerIndex)
    {
        int nb_cards= std::max(18, (int)players[playerIndex].size());
        float needed = (float)nb_cards * tailleCarte.x/3.f + 2.f*tailleCarte.x/3.f;
        scale = std::min((float)winSize.x/needed,(float)winSize.y/needed);

        for (int i = 0; i < CARDS_PER_PLAYER; ++i)
        {
            float x = 0.f, y = 0.f;

            if (playerIndex == 0) // bas
            {
                float x_start = 0.5f*(tailleCarte.y+tailleCarte.x)*scale + (nb_cards-(int)players[playerIndex].size())*tailleCarte.x*scale/6;
                float y_pos = (float)winSize.y;
                float step = (1.f*tailleCarte.x/3.f)*scale;
                x = x_start + (float)i * step;
                y = y_pos;
                players[playerIndex][i].setPosition({x, y});
                players[playerIndex][i].setRotation(sf::degrees(0.f));
                players[playerIndex][i].setScale({scale, scale});
            }

            else if (playerIndex == 1) // droite
            {
                float x_pos = (float)winSize.x;
                float y_start = winSize.y - (tailleCarte.x/2.f)*scale - (nb_cards-(int)players[playerIndex].size())*tailleCarte.x*scale/6;
                float step = (-1.f*tailleCarte.x/3.f)*scale;
                x = x_pos;
                y = y_start + i * step;
                players[playerIndex][i].setPosition({x, y});
                players[playerIndex][i].setRotation(sf::degrees(90.f));
                players[playerIndex][i].setScale({scale, scale});
            }
            else if (playerIndex == 2) // haut
            {
                float x_start = winSize.x - 0.5f*(tailleCarte.y+tailleCarte.x)*scale - (nb_cards-(int)players[playerIndex].size())*tailleCarte.x*scale/6;
                float y_pos =  0.f;
                float step = (-1.f*tailleCarte.x/3.f)*scale;
                x = x_start + i * step;
                y = y_pos;
                players[playerIndex][i].setPosition({x, y});
                players[playerIndex][i].setRotation(sf::degrees(180.f));
                players[playerIndex][i].setScale({scale, scale});
            }
            else if (playerIndex == 3) // gauche
            {
                float x_pos = 0.f;
                float y_start = (tailleCarte.x/2.f)*scale + (nb_cards-(int)players[playerIndex].size())*tailleCarte.x*scale/6;
                float step = (1.f*tailleCarte.x/3.f)*scale;
                x = x_pos;
                y = y_start + i * step;
                players[playerIndex][i].setPosition({x, y});
                players[playerIndex][i].setRotation(sf::degrees(-90.f));
                players[playerIndex][i].setScale({scale, scale});
            }
        }
    };

    for (int p = 0; p < NUM_PLAYERS; ++p)
    {
        positionnerCartes(p);
    }

    float chienStartX = winSize.x/2-((float)chien.size()/2.f-0.5f)*tailleCarte.x*scale;
    float chienY = winSize.y / 2.f;

    for (int i = 0; i < chien.size(); ++i)
    {
        float x = chienStartX + i * tailleCarte.x*scale;
        chien[i].setPosition({x, chienY});
        chien[i].setRotation(sf::degrees(0.f));
        chien[i].setScale({scale, scale});
    }

    window.clear(sf::Color(0, 100, 0)); // tapis vert
    for (int p = 0; p < NUM_PLAYERS; ++p)
    {
        for (auto &card : players[p])
        {
            card.draw(window);
        }
    }

    for (int i = 0; i < chien.size(); ++i)
    {
        for (auto &card : chien)
        {
            card.draw(window);
        }
    }
    window.display();
}


int main()
{
    sf::RenderWindow window
    {
        sf::VideoMode{sf::Vector2u{1024u, 768u}, 32u},
        "Tarot AI"
    };

    // Chargement des textures
    std::vector<sf::Texture> textures(TOTAL_CARDS);
    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        std::string filename = std::string("src/assets/cards/card_") +
                               (i <= 9 ? "0" : "") +
                               std::to_string(i) +
                               ".png";

        if (!textures[i].loadFromFile(filename))
        {
            std::cerr << "Erreur de chargement : " << filename << "\n";
        }
    }

    // Création du jeu complet
    std::vector<Card> deck;
    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        CardInfo info = getCardInfo(i);
        deck.emplace_back(info.name, i, info.suit, info.rank, info.points, textures[i], sf::Vector2f{0.f, 0.f});
    }

    // Mélange et distribution
    std::vector<std::vector<Card>> players(NUM_PLAYERS);
    std::vector<Card> chien;

    bool new_tirage = true;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (auto keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyEvent->code == sf::Keyboard::Key::Space)
                {
                    new_tirage=true;
                }
            }

            if(new_tirage)
            {
                tirer(players, chien, deck);
            }

            positionnerTout(window, players, chien);

            if(new_tirage)
            {
                // 4. Simulation complète
                std::vector<std::vector<Card>> playersCopy = players;
                std::vector<Card> chienCopy = chien;
                auto partie = TarotGame::jouerPartie(playersCopy, chienCopy, window, positionnerTout);

                // 5. Affichage résumé
                std::cout << "Preneur : Joueur " << partie.preneur << "\n";
                std::cout << "Contrat : " << static_cast<int>(partie.contrat) << "\n";
                std::cout << "Points preneur : " << partie.pointsPreneur << "\n";
                std::cout << "Contrat " << (partie.contratRéussi ? "réussi ✅" : "échoué ❌") << "\n";                
                //TarotData::exporterCSV(players, result, "dataset.csv");                
            }

            new_tirage=false;
        }
    }

    return 0;
}
