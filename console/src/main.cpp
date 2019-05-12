#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>

#include <src/tools/logging/Logger.hpp>
#include <src/tools/logging/ConsoleLoggingPolicy.hpp>
#include <console/src/model/game/GameManager.hpp>
#include <src/model/game/player/PlayerFactory.hpp>
#include <src/model/game/NineMensMorris.hpp>
#include <src/model/game/player/Player.hpp>

using namespace model;
using namespace std::chrono_literals;

int main()
{
    std::cout << "main start" << std::endl;

    tools::Logger logger(std::make_unique<tools::ConsoleLoggingPolicy>());

    // model part
    model::GameManager gameManager;


    PlayerFactory factory(logger, 0s);

    PlayerType whitePlayerType = convertStringToPlayerType("AI AlphaBeta");
    PlayerHeuristic whitePlayerHeuristic = convertStringToPlayerHeuristic("Checkers arrangement");
    uint32_t whitePlayerDepth = 5;

    PlayerType blackPlayerType = convertStringToPlayerType("AI AlphaBeta");
    PlayerHeuristic blackPlayerHeuristic = convertStringToPlayerHeuristic("Left checkers diff");
    uint32_t blackPlayerDepth = 6;

    auto whitePlayer = factory.makePlayer(gameManager,
                                          "Player white",
                                          PlayerColor::White,
                                          whitePlayerType,
                                          whitePlayerHeuristic,
                                          whitePlayerDepth);

    auto blackPlayer = factory.makePlayer(gameManager,
                                          "Player black",
                                          PlayerColor::Black,
                                          blackPlayerType,
                                          blackPlayerHeuristic,
                                          blackPlayerDepth);


    NineMensMorris game(std::move(whitePlayer),
                        std::move(blackPlayer),
                        &gameManager,
                        logger);

    auto start = std::chrono::steady_clock::now();
    game.startGame();
    auto stop = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    logger.log("%s(): total time elapsed=%.3f [s]", __FUNCTION__, elapsed.count() / 1000.0);

    std::cout << "going to return main" << std::endl;

    return 0;
}
