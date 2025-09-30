#pragma once

#include <vector>
#include <string>
#include "Card.hpp"

namespace TarotData
{
    void exporterCSV(const std::vector<std::vector<Card>> &players,
                     //const TarotSim::GameResult &result,
                     const std::string &filepath);
}
