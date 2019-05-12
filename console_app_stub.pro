#-------------------------------------------------
#
# Project created by QtCreator 2019-04-25T21:24:50
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4)

TARGET = nine_mens_morris_stub
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

QMAKE_CXXFLAGS += \
            -std=c++17 \
            -Wall \
            -Werror

LIBS += \
        -lstdc++fs \
        -lprofiler

SOURCES += \
        src/model/communication/Action.cpp \
        \
        console/src/model/game/GameManagerStub.cpp \
        src/model/game/GameBoard.cpp \
        src/model/game/GameState.cpp \
        src/model/game/BoardField.cpp \
        src/model/game/NineMensMorris.cpp \
        src/model/game/UnsupportedActionType.cpp \
        src/model/game/ActionTypeMismatchException.cpp \
        \
        src/model/game/player/Player.cpp \
        src/model/game/player/HumanPlayer.cpp \
        src/model/game/player/ComputerPlayer.cpp \
        src/model/game/player/PlayerColor.cpp \
        src/model/game/player/PlayerInfo.cpp \
        src/model/game/player/PlayerFactory.cpp \
        \
        src/model/game/player/ai/AiAlgorithm.cpp \
        src/model/game/player/ai/EvalFunction.cpp \
        src/model/game/player/ai/EvalFnLeftCheckersDiff.cpp \
        src/model/game/player/ai/EvalFnGenericLambda.cpp \
        src/model/game/player/ai/MinMaxAlg.cpp \
        src/model/game/player/ai/AlphaBetaPrunningAlg.cpp \
        \
        src/tools/logging/Logger.cpp \
        src/tools/logging/LoggingPolicy.cpp \
        src/tools/logging/FileLoggingPolicy.cpp \
        src/tools/logging/ConsoleLoggingPolicy.cpp \
        \
        console/src/main.cpp

HEADERS += \
        src/model/communication/Action.hpp \
        src/model/communication/ActionType.hpp \
        \
        console/src/model/game/GameManager.hpp \
        src/model/game/GameBoard.hpp \
        src/model/game/GameState.hpp \
        src/model/game/BoardField.hpp \
        src/model/game/Move.hpp \
        src/model/game/NineMensMorris.hpp \
        src/model/game/UnsupportedActionType.hpp \
        src/model/game/ActionTypeMismatchException.hpp \
        \
        src/model/game/player/Player.hpp \
        src/model/game/player/HumanPlayer.hpp \
        src/model/game/player/ComputerPlayer.hpp \
        src/model/game/player/PlayerColor.hpp \
        src/model/game/player/PlayerInfo.hpp \
        src/model/game/player/PlayerFactory.hpp \
        \
        src/model/game/player/ai/AiAlgorithm.hpp \
        src/model/game/player/ai/EvalFunction.hpp \
        src/model/game/player/ai/EvalFnLeftCheckersDiff.hpp \
        src/model/game/player/ai/EvalFnGenericLambda.hpp \
        src/model/game/player/ai/MinMaxAlg.hpp \
        src/model/game/player/ai/AlphaBetaPrunningAlg.hpp \
        \
        src/tools/logging/Logger.hpp \
        src/tools/logging/LoggingPolicy.hpp \
        src/tools/logging/FileLoggingPolicy.hpp \
        src/tools/logging/ConsoleLoggingPolicy.hpp \
        \
        src/view/CheckerType.hpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
