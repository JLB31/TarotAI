#include "DatasetExporter.hpp"
#include <fstream>

namespace TarotData
{
    void exporterCSV(const std::vector<std::vector<Card>> &players,
                     const TarotSim::GameResult &result,
                     const std::string &filepath)
    {
        std::ofstream file(filepath, std::ios::app);
        const auto &hand = players[result.preneurIndex];

        std::vector<float> features(78, 0.f);
        for (const auto &card : hand)
        {
            features[card.getIndex()] = 1.f;
        }

        file << result.preneurIndex << "," << static_cast<int>(result.contrat) << ","
             << result.pointsPreneur << "," << result.oudlersPreneur << "," << result.contratRéussi;

        for (float f : features)
            file << "," << f;

        file << "\n";
    }
}
