SOURCES += \
        $$PWD/controller/MasterController.cpp \
        $$PWD/controller/AppCleaner.cpp \
        \
        $$PWD/model/communication/Action.cpp \
        \
        $$PWD/model/game/GameManager.cpp \
        $$PWD/model/game/GameBoard.cpp \
        $$PWD/model/game/GameState.cpp \
        $$PWD/model/game/BoardField.cpp \
        $$PWD/model/game/NineMensMorris.cpp \
        $$PWD/model/game/UnsupportedActionType.cpp \
        $$PWD/model/game/ActionTypeMismatchException.cpp \
        \
        $$PWD/model/game/player/Player.cpp \
        $$PWD/model/game/player/HumanPlayer.cpp \
        $$PWD/model/game/player/ComputerPlayer.cpp \
        $$PWD/model/game/player/PlayerColor.cpp \
        $$PWD/model/game/player/PlayerInfo.cpp \
        $$PWD/model/game/player/PlayerFactory.cpp \
        \
        $$PWD/model/game/player/ai/AiAlgorithm.cpp \
        $$PWD/model/game/player/ai/EvalFunction.cpp \
        $$PWD/model/game/player/ai/EvalFnLeftCheckersDiff.cpp \
        $$PWD/model/game/player/ai/EvalFnGenericLambda.cpp \
        $$PWD/model/game/player/ai/MinMaxAlg.cpp \
        $$PWD/model/game/player/ai/AlphaBetaPrunningAlg.cpp \
        \
        $$PWD/view/MainWindow.cpp \
        $$PWD/view/StyleProvider.cpp \
        \
        $$PWD/tools/logging/Logger.cpp \
        $$PWD/tools/logging/LoggingPolicy.cpp \
        $$PWD/tools/logging/FileLoggingPolicy.cpp \
        $$PWD/tools/logging/ConsoleLoggingPolicy.cpp \
        \
        $$PWD/main.cpp

HEADERS += \
        $$PWD/controller/MasterController.hpp \
        $$PWD/controller/AppCleaner.hpp \
        \
        $$PWD/model/communication/Action.hpp \
        $$PWD/model/communication/ActionType.hpp \
        \
        $$PWD/model/game/GameManager.hpp \
        $$PWD/model/game/GameBoard.hpp \
        $$PWD/model/game/GameState.hpp \
        $$PWD/model/game/BoardField.hpp \
        $$PWD/model/game/Move.hpp \
        $$PWD/model/game/NineMensMorris.hpp \
        $$PWD/model/game/UnsupportedActionType.hpp \
        $$PWD/model/game/ActionTypeMismatchException.hpp \
        \
        $$PWD/model/game/player/Player.hpp \
        $$PWD/model/game/player/HumanPlayer.hpp \
        $$PWD/model/game/player/ComputerPlayer.hpp \
        $$PWD/model/game/player/PlayerColor.hpp \
        $$PWD/model/game/player/PlayerInfo.hpp \
        $$PWD/model/game/player/PlayerFactory.hpp \
        \
        $$PWD/model/game/player/ai/AiAlgorithm.hpp \
        $$PWD/model/game/player/ai/EvalFunction.hpp \
        $$PWD/model/game/player/ai/EvalFnLeftCheckersDiff.hpp \
        $$PWD/model/game/player/ai/EvalFnGenericLambda.hpp \
        $$PWD/model/game/player/ai/MinMaxAlg.hpp \
        $$PWD/model/game/player/ai/AlphaBetaPrunningAlg.hpp \
        \
        $$PWD/tools/logging/Logger.hpp \
        $$PWD/tools/logging/LoggingPolicy.hpp \
        $$PWD/tools/logging/FileLoggingPolicy.hpp \
        $$PWD/tools/logging/ConsoleLoggingPolicy.hpp \
        \
        $$PWD/view/MainWindow.h \
        $$PWD/view/StyleProvider.hpp \
        $$PWD/view/CheckerType.hpp
