/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ScoreManager
*/

#include "ScoreManager.hpp"

/**
 * @brief Construct a new Score Manager:: Score Manager object
 */
ScoreManager::ScoreManager()
{
}

/**
 * @brief Destroy the Score Manager:: Score Manager object
 */
ScoreManager::~ScoreManager()
{
}

/**
 * @brief Creates the score directory if it doesn't exist.
 */
void ScoreManager::createScoreDirectory()
{
    if (!std::filesystem::exists("score")) {
        std::filesystem::create_directory("score");
    }
}

/**
 * @brief Loads existing scores from a file.
 * @param fileName The name of the file to load scores from.
 * @return A vector containing pairs of scores and player names.
 */
std::vector<std::pair<float, std::string>> ScoreManager::loadScoresFromFile(
    const std::string &fileName)
{
    std::vector<std::pair<float, std::string>> scores;

    if (!std::filesystem::exists(fileName)) {
        return scores;
    }

    std::ifstream infile(fileName);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            size_t playerStart = line.find("Player: ");
            size_t scoreStart = line.find(" - Score: ");

            if (playerStart != std::string::npos &&
                scoreStart != std::string::npos) {
                std::string playerName = line.substr(
                    playerStart + 8, scoreStart - (playerStart + 8));
                std::string scoreStr = line.substr(scoreStart + 10);
                try {
                    float scoreValue = std::stof(scoreStr);
                    scores.emplace_back(scoreValue, playerName);
                } catch (...) {
                }
            }
        }
        infile.close();
    }
    return scores;
}

/**
 * @brief Updates a player's score or adds a new score.
 * @param scores The vector of current scores.
 * @param newScore The new score to add or update.
 */
void ScoreManager::updatePlayerScore(
    std::vector<std::pair<float, std::string>> &scores,
    const std::pair<float, std::string> &newScore)
{
    bool playerExists = false;

    for (auto &entry : scores) {
        if (entry.second == newScore.second) {
            playerExists = true;
            if (newScore.first > entry.first) {
                entry.first = newScore.first;
            }
            break;
        }
    }

    if (!playerExists) {
        scores.push_back(newScore);
    }

    std::sort(scores.begin(), scores.end(),
        [](const auto &a, const auto &b) { return a.first > b.first; });
}

/**
 * @brief Writes scores to a file.
 * @param fileName The name of the file to write scores to.
 * @param scores The vector of scores to write.
 * @return true if successful, false otherwise.
 */
bool ScoreManager::writeScoresToFile(const std::string &fileName,
    const std::vector<std::pair<float, std::string>> &scores)
{
    std::ofstream outfile(fileName, std::ios::trunc);
    if (!outfile.is_open()) {
        std::cerr << "Unable to open score file for writing: " << fileName
                  << std::endl;
        return false;
    }

    for (const auto &entry : scores) {
        outfile << "Player: " << entry.second << " - Score: " << entry.first
                << "\n";
    }
    outfile.close();
    return true;
}

/**
 * @brief Saves the score to a file.
 * @param score The score to save, as a pair of float and string.
 */
void ScoreManager::saveScore(std::string gameName, std::pair<float, std::string> score)
{
    std::string fileName = "score/score_" + gameName + ".txt";
    auto scores = loadScoresFromFile(fileName);

    if (score.second.empty()) {
        return;
    }
    createScoreDirectory();
    updatePlayerScore(scores, score);
    writeScoresToFile(fileName, scores);
}

