//////////     TODO     ////////////////////////////////////
// Declare your Home class
#pragma once
#include "cell/Cell.hpp"

class Home : public Cell{
public:
    Home(Map* map, int row, int col);
    HomeCheckResult Check();
    virtual AttrType GetAttr() const;
    virtual ColorPair GetColorPair() const;
    virtual char GetIcon() const;
    int target_number;
};
//////////   TODO END   ///////////////////////////////////