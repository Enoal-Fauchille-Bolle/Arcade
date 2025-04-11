/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ScoreManager
*/

#ifndef SCOREMANAGER_HPP_
    #define SCOREMANAGER_HPP_

    #include <dlfcn.h>

    #include <algorithm>
    #include <filesystem>
    #include <fstream>
    #include <iostream>
    #include <memory>
    #include <vector>

class ScoreManager {
    public:
        ScoreManager();
        ~ScoreManager();

        void saveScore(
            std::string gameName, std::pair<float, std::string> score);
        std::vector<std::pair<float, std::string>> loadScoresFromFile(
            const std::string &fileName);

    private:
        void createScoreDirectory(void);
        void updatePlayerScore(
            std::vector<std::pair<float, std::string>> &scores,
            const std::pair<float, std::string> &score);
        bool writeScoresToFile(const std::string &fileName,
            const std::vector<std::pair<float, std::string>> &scores);
};

#endif /* !SCOREMANAGER_HPP_ */
