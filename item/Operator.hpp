#pragma once

#include "item/ItemBase.hpp"

class CellObjBase;
class Operator : public ItemBase
{
private:
    OpType op;

public:
    Operator(CellObjBase* obj, OpType op);
    ~Operator();
    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from ItemBase.
    // You don't have to override them if you want to keep using the ItemBase functions.

    // Implement Operator::GetType that returns OPERATOR.

    // Implement Operator::GetIcon.
    // Return one of the character '+', '-', '*' that matches this->op.

    ItemType GetType() const { return ItemType::OPERATOR; };
    char GetIcon() const;
    
    //////////   TODO END   ////////////////////////////////////
};
