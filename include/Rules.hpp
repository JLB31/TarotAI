#pragma once

#include <vector>
#include "Card.hpp"

namespace TarotRules
{
    enum class Contract
    {
        Pass,
        Petite,
        Garde,
        GardeSans,
        GardeContre
    };

    // Analyse de la main
    int countOudlers(const std::vector<Card> &hand);
    float totalPoints(const std::vector<Card> &hand);
    int countSuit(const std::vector<Card> &hand, Suit suit);
    int countTrumps(const std::vector<Card> &hand);
    std::vector<Suit> missingSuits(const std::vector<Card> &hand);

    // Évaluation
    Contract recommendContract(const std::vector<Card> &hand);
    bool isHandStrong(const std::vector<Card> &hand);
    bool hasPetitSec(const std::vector<Card> &hand);
    bool canPlayCard(const Card &card,
                 const std::vector<Card> &hand,
                 Suit demandedSuit,
                 bool hasDemandedSuit,
                 bool hasTrump);
    void faireEcartMaxCoupe(std::vector<Card> &mainPreneur, std::vector<Card> &chien);


}
