#pragma once
#include <string>

#include "Enums.hpp"
#include "cell/Cell.hpp"
#include "cellobj/CellObjBase.hpp"

class CellObjBase;

class ItemBase
{
public:
    CellObjBase* parent;

    ItemBase(CellObjBase* obj);
    virtual ~ItemBase() = default;

    //////////     TODO     ////////////////////////////////////
    // Optional: if you wish, you can implement some of these functions
    // in this virtual class, and change them into non-pure virtual functions.

    virtual ItemType GetType() const = 0;
    virtual char GetIcon() const = 0;

    // virtual int GetNumber();

    //////////   TODO END   ////////////////////////////////////
};
