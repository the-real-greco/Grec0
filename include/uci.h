#ifndef UCI_H
#define UCI_H

#include <string>
#include "board.h"

namespace UCI {
    void loop();
    void setPosition(const std::string& positionCommand);

    extern Board board;  // Declare the board object
}

#endif // UCI_H
