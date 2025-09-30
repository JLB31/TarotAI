#pragma once

#include <vector>
#include <functional>

#include "Card.hpp"
#include "Rules.hpp"

namespace TarotGame
{
    struct Levee
    {
        std::vector<Card> cartes;
        int gagnantIndex;
    };

    struct PartieComplète
    {
        int preneur;
        TarotRules::Contract contrat;
        std::vector<Levee> levees;
        float pointsPreneur;
        bool contratRéussi;
    };

    PartieComplète jouerPartie(std::vector<std::vector<Card>> &players,
                          std::vector<Card> &chien,
                          sf::RenderWindow &window,
                          std::function<void(sf::RenderWindow&, std::vector<std::vector<Card>>&, std::vector<Card>&)> positionnerTout,
                               int seed = -1);

    void trierMain(std::vector<Card> &main);
}
