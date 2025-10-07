#include <random>
#include <iostream>
#include <algorithm>

#include "GameEngine.hpp"
#include "Rules.hpp"

namespace TarotGame
{
    PartieComplète jouerPartie(std::vector<std::vector<Card>> &players,
                               std::vector<Card> &chien,
                               sf::RenderWindow &window,
                               std::function<void(sf::RenderWindow&, std::vector<std::vector<Card>>&, std::vector<Card>&)> positionnerTout,
                               int seed)
    {
        if (seed >= 0) std::srand(seed);

        // Choix du preneur
        int preneur = -1;
        float meilleurRemaining = 100.f; // valeur haute arbitraire

        for (size_t i = 0; i < players.size(); ++i)
        {
            const auto &mainJoueur = players[i];
            float points = TarotRules::totalPoints(mainJoueur);
            int oudlers = TarotRules::countOudlers(mainJoueur);

            float seuil = (oudlers == 3) ? 36.f :
                        (oudlers == 2) ? 41.f :
                        (oudlers == 1) ? 51.f : 56.f;

            float remaining = seuil - points;

            std::cout << "Joueur " << i << " : " << points << " pts, " << oudlers << " bouts → reste à faire : " << remaining << "\n";

            if (remaining < meilleurRemaining)
            {
                meilleurRemaining = remaining;
                preneur = static_cast<int>(i);
            }
        }

        auto contrat = TarotRules::recommendContract(players[preneur]);

        sf::sleep(sf::milliseconds(1000));        
        
        // Fusion du chien (simplifiée)
        for (auto &card : chien)
        {
            card.setOwner(preneur);
        }
        players[preneur].insert(players[preneur].end(), chien.begin(), chien.end());
        chien.clear();
        TarotGame::trierMain(players[preneur]);
        positionnerTout(window,players,chien);
        sf::sleep(sf::milliseconds(2000));


        TarotRules::faireEcartMaxCoupe(players[preneur], chien);
        for (auto &card : chien)
        {
            card.setOwner(-1);
        }
        positionnerTout(window,players,chien);
        sf::sleep(sf::milliseconds(5000));

        std::vector<Levee> levees;
        int leader = 0;

        for (int tour = 0; tour < 18; ++tour)
        {
            Levee levee;
            Suit demanded = Suit::None;

            for (int i = 0; i < 4; ++i)
            {
                int joueur = (leader + i) % 4;
                const auto &hand = players[joueur];

                // Choix de carte (aléatoire ou selon règles)
                Card chosen;
                for (const Card &c : hand)
                {
                    if (TarotRules::canPlayCard(c, hand, demanded,
                                                TarotRules::countSuit(hand, demanded) > 0,
                                                TarotRules::countTrumps(hand) > 0))
                    {
                        chosen = c;
                        break;
                    }
                }

                levee.cartes.push_back(chosen);
                // Retirer la carte de la main
                players[joueur].erase(std::remove(players[joueur].begin(), players[joueur].end(), chosen),
                                      players[joueur].end());

                if (i == 0) demanded = chosen.getSuit();
            }

            // Détermination du gagnant (simplifiée)
            int gagnant = TarotRules::findNextLeader(leader, levee.cartes);
            levee.gagnantIndex = gagnant;
            levees.push_back(levee);
            leader = gagnant;

            positionnerTout(window,players,levee.cartes);
            sf::sleep(sf::milliseconds(1000));
        }

        // Calcul des points du preneur
        float total = 0.f;
        for (const auto &levee : levees)
        {
            if (levee.gagnantIndex == preneur)
            {
                for (const Card &c : levee.cartes)
                    total += c.getPoints();
            }
        }

        int oudlers = TarotRules::countOudlers(players[preneur]);
        float seuil = (oudlers == 3) ? 36.f : (oudlers == 2) ? 41.f : (oudlers == 1) ? 51.f : 56.f;
        bool réussi = total >= seuil;

        std::cout << "Partie complète : Joueur " << preneur << " a " << total << " points\n";
        std::cout << "Contrat " << (réussi ? "réussi ✅" : "échoué ❌") << "\n";

        return {preneur, contrat, levees, total, réussi};
    }

    void trierMain(std::vector<Card> &main)
    {
        std::sort(main.begin(), main.end(), [](const Card &a, const Card &b)
        {
            auto suitOrder = [](Suit s)
            {
                switch (s)
                {
                    case Suit::Hearts:   return 0;
                    case Suit::Clubs:    return 1;
                    case Suit::Diamonds: return 2;
                    case Suit::Spades:   return 3;
                    case Suit::Excuse:   return 4;
                    case Suit::Trump:    return 5;
                }
                return 6;
            };

            int keyA = suitOrder(a.getSuit()) * 1000 + static_cast<int>(a.getRank());
            int keyB = suitOrder(b.getSuit()) * 1000 + static_cast<int>(b.getRank());

            return keyA < keyB;
        });
    }
}
