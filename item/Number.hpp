#pragma once
#include <string>

#include "item/ItemBase.hpp"

class Number : public ItemBase
{
private:
    int value = 0;

public:
    Number(CellObjBase* obj, int value);
    // int GetValue();

    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from ItemBase.
    // You don't have to override them if you want to keep using the ItemBase functions.

    // Implement Number::GetType that returns NUMBER.

    // Implement Number::GetIcon.
    // Return the value in printable form.


    
    virtual ItemType GetType() const { return ItemType::NUMBER; };
    virtual char GetIcon() const { return value+'0'; };
    int GetNumber() {return value;};

    //////////   TODO END   ////////////////////////////////////
};
