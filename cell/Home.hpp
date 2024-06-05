//////////     TODO     ////////////////////////////////////
// Declare your Home class
#pragma once
#include "cell/Cell.hpp"

class Home : public Cell{
public:
    Home(Map* map, int row, int col);
    HomeCheckResult Check();
};
//////////   TODO END   ///////////////////////////////////