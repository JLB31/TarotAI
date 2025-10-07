#include "Rules.hpp"
#include <algorithm>
#include <map>
#include <iostream>


namespace TarotRules
{
    int countOudlers(const std::vector<Card> &hand)
    {
        int count = 0;
        for (const auto &card : hand)
        {
            if (card.getName() == "Excuse" ||
                card.getName() == "Trump 1" ||
                card.getName() == "Trump 21")
            {
                ++count;
            }
        }
        return count;
    }

    float totalPoints(const std::vector<Card> &hand)
    {
        float total = 0.f;
        for (const auto &card : hand)
        {
            total += card.getPoints();
        }
        return total;
    }

    int countSuit(const std::vector<Card> &hand, Suit suit)
    {
        return std::count_if(hand.begin(), hand.end(),
                             [suit](const Card &c) { return c.getSuit() == suit; });
    }

    int countTrumps(const std::vector<Card> &hand)
    {
        return countSuit(hand, Suit::Trump);
    }

    std::vector<Suit> missingSuits(const std::vector<Card> &hand)
    {
        std::vector<Suit> all = {Suit::Hearts, Suit::Diamonds, Suit::Clubs, Suit::Spades};
        std::vector<Suit> missing;
        for (Suit s : all)
        {
            if (countSuit(hand, s) == 0)
                missing.push_back(s);
        }
        return missing;
    }

    bool hasPetitSec(const std::vector<Card> &hand)
    {
        return std::count_if(hand.begin(), hand.end(),
                             [](const Card &c) { return c.getName() == "Trump 1"; }) == 1 &&
               countTrumps(hand) == 1;
    }

    bool isHandStrong(const std::vector<Card> &hand)
    {
        int oudlers = countOudlers(hand);
        float points = totalPoints(hand);
        return (oudlers >= 2 && points >= 45.f) || (oudlers == 3);
    }

    Contract recommendContract(const std::vector<Card> &hand)
    {
        int oudlers = countOudlers(hand);
        float points = totalPoints(hand);

        if (oudlers == 3) return Contract::GardeSans;
        if (oudlers == 2 && points >= 50.f) return Contract::Garde;
        if (oudlers == 1 && points >= 40.f) return Contract::Petite;
        return Contract::Pass;
    }

    bool canPlayCard(const Card &card,
                             const std::vector<Card> &hand,
                             Suit demandedSuit,
                             bool hasDemandedSuit,
                             bool hasTrump)
    {
        // L'Excuse peut être jouée à tout moment
        if (card.getName() == "Excuse")
            return true;

        // Si le joueur a la couleur demandée, il doit la jouer
        if (hasDemandedSuit)
            return card.getSuit() == demandedSuit;

        // Sinon, s'il a des atouts, il doit couper
        if (hasTrump)
            return card.getSuit() == Suit::Trump;

        // Sinon, il peut jouer n'importe quelle carte
        return true;
    }

    void faireEcartMaxCoupe(std::vector<Card> &mainPreneur, std::vector<Card> &chien)
    {
        // 1. Compter les cartes par couleur (hors atouts et Excuse)
        std::map<Suit, int> couleurCounts;
        for (const Card &c : mainPreneur)
        {
            if (c.getSuit() != Suit::Trump && c.getName() != "Excuse")
                couleurCounts[c.getSuit()]++;
        }

        // 2. Identifier les deux couleurs les plus courtes
        std::vector<Suit> couleursCourtes;
        for (auto &[suit, count] : couleurCounts)
        {
            if (suit != Suit::Trump)
                couleursCourtes.push_back(suit);
        }

        std::sort(couleursCourtes.begin(), couleursCourtes.end(),
                [&couleurCounts](Suit a, Suit b) {
                    return couleurCounts[a] < couleurCounts[b];
                });


        // 3. Sélectionner les cartes à écarter
        for (const Card &c : mainPreneur)
        {
            if (chien.size() >= 6)
                break;

            if (std::find(couleursCourtes.begin(), couleursCourtes.end(), c.getSuit()) != couleursCourtes.end() &&
                c.getRank() != Rank::King && c.getIndex() != 0 &&
                !(c.getSuit() == Suit::Trump && (c.getIndex() == 0 || c.getIndex() == 21))) // éviter les bouts
            {
                chien.push_back(c);
            }
        }

        // 4. Retirer les cartes de la main
        for (const Card &c : chien)
        {
            auto it = std::find_if(mainPreneur.begin(), mainPreneur.end(),
                                [&c](const Card &x) {
                                    return x.getSuit() == c.getSuit() && x.getIndex() == c.getIndex();
                                });
            if (it != mainPreneur.end())
                mainPreneur.erase(it);
        }

        // 6. Affichage debug
        std::cout << "Écart stratégique du preneur :\n";
        for (const Card &c : chien)
            std::cout << " - " << c.getName() << " (" << static_cast<int>(c.getSuit()) << ")\n";
    }

    int findNextLeader(int leader, std::vector<Card> &levee)
    {
        int newLeader=leader;
        int i=(leader+1)%4;
        do
        {
            if(levee[i].getSuit() == levee[newLeader].getSuit())
            {
                if(static_cast<int>(levee[i].getRank()) > static_cast<int>(levee[newLeader].getSuit()))
                {
                    newLeader = i;
                }
            }
            else if (levee[i].getSuit() == Suit::Trump)
            {
                newLeader = i;
            }
            i=(i+1)%4;
        }while(i!=leader);
        return newLeader;
    }
}
