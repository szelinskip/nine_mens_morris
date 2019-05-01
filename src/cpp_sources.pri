SOURCES += \
        $$PWD/controller/MasterController.cpp \
        $$PWD/controller/AppCleaner.cpp \
        \
        $$PWD/model/communication/Action.cpp \
        \
        $$PWD/model/game/GameManager.cpp \
        $$PWD/model/game/GameBoard.cpp \
        $$PWD/model/game/GameState.cpp \
        $$PWD/model/game/NineMensMorris.cpp \
        $$PWD/model/game/UnsupportedActionType.cpp \
        $$PWD/model/game/ActionTypeMismatchException.cpp \
        \
        $$PWD/model/game/player/Player.cpp \
        $$PWD/model/game/player/HumanPlayer.cpp \
        \
        $$PWD/view/MainWindow.cpp \
        $$PWD/view/StyleProvider.cpp \
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
        $$PWD/model/game/NineMensMorris.hpp \
        $$PWD/model/game/UnsupportedActionType.hpp \
        $$PWD/model/game/ActionTypeMismatchException.hpp \
        \
        $$PWD/model/game/player/Player.hpp \
        $$PWD/model/game/player/HumanPlayer.hpp \
        $$PWD/model/game/player/PlayerColor.hpp \
        \
        $$PWD/view/MainWindow.h \
        $$PWD/view/StyleProvider.hpp \
        $$PWD/view/CheckerType.hpp