#pragma once
#include "cellobj/CellObjBase.hpp"

class Ghost : public CellObjBase
{
public:
    Ghost(Cell* cell);
    virtual ~Ghost();

    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from CellObjBase.
    // You don't have to override them if you want to keep using the CellObjBase functions.

    // Implement Ghost::GetType that returns GHOST.

    // Implement Ghost::GetAttr that returns DIM.

    // Implement Ghost::GetIcon.
    // No default icon - return the item's icon.

    virtual ObjectType GetType() const;
    // virtual AttrType GetAttr() const;
    virtual char GetIcon() const;

    virtual bool TryPush(Direction dir) {return false;};

    //////////   TODO END   ////////////////////////////////////
};
