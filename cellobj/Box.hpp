#pragma once
#include "cellobj/CellObjBase.hpp"

class Box : public CellObjBase
{
public:
    Box(Cell* cell);

    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from CellObjBase.
    // You don't have to override them if you want to keep using the CellObjBase functions.

    // Implement Box::GetType that returns BOX.

    // Implement Box::GetAttr that returns NORMAL.

    // Implement Box::GetIcon.
    // No default icon - return the item's icon.

    virtual ~Box();

    virtual ObjectType GetType() const;
    virtual AttrType GetAttr() const;
    virtual char GetIcon() const;

    virtual bool TryPush(Direction dir);

    //////////   TODO END   ////////////////////////////////////
};
