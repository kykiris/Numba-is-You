#include "cellobj/CellObjBase.hpp"

#include "Enums.hpp"
#include "Map.hpp"
#include "cell/Cell.hpp"
#include "item/Number.hpp"
#include "item/Operator.hpp"
#include "item/Equal.hpp"

#define DO_NOTHING

CellObjBase::CellObjBase(Cell* cell) : parent(cell)
{
}

CellObjBase::~CellObjBase()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    delete item;
    delete parent;
    item = nullptr;
    parent = nullptr;

    //////////   TODO END   ////////////////////////////////////
}

bool CellObjBase::TryMove(Direction dir)
{
    //////////     TODO     ////////////////////////////////////
    // Try to move and return if it actually moved.
    // 1. Get a neighbor in that direction
    // 2. If that neighbor exists, then check its cell type
    // 3. If the neighbor is not Wall, then get its object
    // 4. If the neighbor didn’t have any object, then
    //    swap between the neighbor and return true
    // 5. If any one of 2 to 4 is false, then return false

    if(parent->GetNeighbor(dir)!=nullptr){
        
        //check its cell type
        if(parent->cellType!=CellType::WALL){
            //check its object
            if(parent->GetObject()==nullptr){
                parent->SwapObject(parent->GetNeighbor(dir));
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
    //////////   TODO END   ////////////////////////////////////
}

void CellObjBase::InitItem(char itemIcon)
{
    //////////     TODO     ////////////////////////////////////
    // Create this->item.
    // itemIcon == ‘+’: Create ADD operator.
    // itemIcon == ‘-’: Create SUB operator.
    // itemIcon == ‘*’: Create MUL operator.
    // itemIcon == ‘=‘: Create equal, then push back into map->equals.
    // ‘0’ <= itemIcon <= ‘9’: Create the corresponding number.
    // ‘@’: Do nothing (this indicates an empty player).
    // else: Don’t care (throwing runtime_error is best).

    if(itemIcon == '+'){
        this->item = new Operator(this, OpType::ADD);
    }
    else if(itemIcon=='-'){
        this->item = new Operator(this, OpType::SUB);
    }
    else if(itemIcon == '*'){
        this->item = new Operator(this, OpType::MUL);
    }
    else if(itemIcon == '='){
        Equal* newEqual = new Equal(this);
        // this->item = new Equal(this);
        this->item = newEqual;
        parent->parent->equals.push_back(newEqual);
    }
    else if(itemIcon >= '0' && itemIcon <= '9'){
        this->item = new Number(this, itemIcon-'0');
    }
    else if(itemIcon == '@'){
        DO_NOTHING;
    }
    else{
        throw std::runtime_error("Unavailable item");
    }



    //////////   TODO END   ////////////////////////////////////
}
