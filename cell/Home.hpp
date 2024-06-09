//////////     TODO     ////////////////////////////////////
// Declare your Home class
#pragma once
#include "cell/Cell.hpp"

class Home : public Cell{
public:
    Home(Map* map, int row, int col, char c);
    HomeCheckResult Check();
    AttrType GetAttr() const;
    ColorPair GetColorPair() const;
    char GetIcon() const;
    char targetNumber;
    // char GetNum() {return targetNumber;};
};
//////////   TODO END   ///////////////////////////////////