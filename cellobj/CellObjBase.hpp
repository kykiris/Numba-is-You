#ifndef CELLOBJBASE_H_
#define CELLOBJBASE_H_
#include <string>
#include <memory>

#include "Enums.hpp"
#include "cell/Cell.hpp"
#include "item/ItemBase.hpp"
// #include "item/Number.hpp"
// #include "item/Equal.hpp"
// #include "item/Operator.hpp"
#include "utils/Terminal.hpp"
class Cell;
class ItemBase;
class CellObjBase
{
protected:
    ItemBase* item = nullptr;

public:
    Cell* parent;

    CellObjBase(Cell* cell);
    virtual ~CellObjBase();

    void InitItem(char itemIcon);
    ItemBase* GetItem() const { return this->item; }

    bool TryMove(Direction dir);

    
    //////////     TODO     ////////////////////////////////////
    // Optional: if you wish, you can implement some of these functions
    // in this virtual class, and change them into non-pure virtual functions.

    virtual ObjectType GetType() const = 0;
    virtual AttrType GetAttr() const = 0;
    virtual char GetIcon() const = 0;

    virtual bool TryPush(Direction dir) = 0;

    //////////   TODO END   ////////////////////////////////////
};

#endif