# CMakeList.txt : CMake project for DeadlyCorpGame, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (DeadlyCorpGame "DeadlyCorpGame.cpp" "DeadlyCorpGame.h" 
"Game.h" "MoonManager.h" "ItemManager.h"  "AbstractMoon.h" "Weather.h" 
"Item.h"  "Game.cpp" "MoonManager.cpp"  "SendableMoon.h" "SellableMoon.h" 
"Logger.h" "ItemManager.cpp" "util.h" "util.cpp" "IPremium.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DeadlyCorpGame PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
