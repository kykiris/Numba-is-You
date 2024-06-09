//////////     TODO     ////////////////////////////////////
// Declare your Equal class
#pragma once
#include "item/ItemBase.hpp"

// class ItemBase;
class CellObjBase;
class Equal: public ItemBase
{
    public:
    Equal(CellObjBase * obj);
    ~Equal();
    std::string GetExpression(Direction dir);

    ItemType GetType() const { return ItemType::EQUALS; };
    char GetIcon() const { return '='; };
};






















//////////   TODO END   ////////////////////////////////////
