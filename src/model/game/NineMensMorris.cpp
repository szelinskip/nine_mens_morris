#include "NineMensMorris.hpp"

#include "player/Player.hpp"

#include <algorithm>
#include <iostream>

namespace model {

NineMensMorris::NineMensMorris(std::unique_ptr<Player> whitePlayer, std::unique_ptr<Player> blackPlayer)
    : whitePlayer(std::move(whitePlayer))
    , blackPlayer(std::move(blackPlayer))
    , currentPlayer(nullptr)
{
}

NineMensMorris::~NineMensMorris() = default;

void NineMensMorris::startGame()
{
    std::cout << __FUNCTION__ << std::endl;
    bool gameOver = false;
    Player* winner = nullptr;
    while(!gameOver)
    {
        if(!checkGameOverCondition())
        {
            currentPlayer = getCurrentPlayer();
            currentPlayer->makeMove(gameState);
            if(lastMoveCreatedMill())
            {
                currentPlayer->millMove(gameState);
            }
            gameStatesHistory.emplace_back(gameState);
        }
        else
        {
            gameOver = true;
            if(!isGameEndedWithDraw())
                winner = currentPlayer;
        }
    }
    if(winner != nullptr)
        std::cout << "winner: " << winner->getName() << std::endl;
    else
        std::cout << "draw" << std::endl;
}

bool NineMensMorris::checkGameOverCondition() const
{
    bool checkersCondition = gameState.isGameOverState();
    if(checkersCondition)
    {
        return true;
    }
    else
    {
        auto stateRepetitionsInPast =
            std::count_if(gameStatesHistory.cbegin(),
                          gameStatesHistory.cend(),
                          [this](const auto& stateFromPast)
                          {return stateFromPast.isBoardEqual(gameState);});
        return stateRepetitionsInPast == 3;
    }
}

Player *NineMensMorris::getCurrentPlayer() const
{
    if(currentPlayer == whitePlayer.get())
        return blackPlayer.get();
    else if(currentPlayer == blackPlayer.get())
        return whitePlayer.get();
    else  // currentPlayer == nullptr
        return whitePlayer.get();
}

bool NineMensMorris::isGameEndedWithDraw() const
{
    auto stateRepetitionsInPast =
        std::count_if(gameStatesHistory.cbegin(),
                      gameStatesHistory.cend(),
                      [this](const auto& stateFromPast)
                      {return stateFromPast.isBoardEqual(gameState);});
    return stateRepetitionsInPast == 3;
}

bool NineMensMorris::lastMoveCreatedMill() const
{
    return false; // TODO
}

} // namespace model
