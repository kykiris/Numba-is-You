#include "cellobj/Box.hpp"
#include "item/ItemBase.hpp"
#include "cellobj/CellObjBase.hpp"
#include "cell/Cell.hpp"

Box::Box(Cell* cell) : CellObjBase(cell)
{
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Box.hpp.

Box::~Box(){};
ObjectType Box::GetType() const{
    return ObjectType::BOX;
}
AttrType Box::GetAttr() const{
    return Terminal::Attr::NORMAL;
}
char Box::GetIcon() const{
    return GetItem()->GetIcon();
}

bool Box::TryPush(Direction dir)
{
    //////////     TODO     ////////////////////////////////////
    // Try to push other object and return if it actually pushed.
    // 1. Get a neighbor in that direction.
    // 2. If that neighbor exists, then check its cell type.
    // 3. If the neighbor is not Wall, then get its object.
    // 4. If the neighbor had an object, then try to move that object in that direction and return the result.
    // 5. If any one of 2 to 4 is false, then return false.
    bool PushAvailable = false;
    if(parent->GetNeighbor(dir)==nullptr){
        PushAvailable = false;
        return PushAvailable;
    }
    if(parent->GetNeighbor(dir)->cellType == CellType::WALL){
        PushAvailable = false;
        return PushAvailable;
    }
    // if(parent->GetNeighbor(dir)->GetObject()->GetType() == ObjectType::GHOST){
    //     PushAvailable = false;
    //     return PushAvailable;
    // }
    if(parent->GetNeighbor(dir)->GetObject()!=nullptr){
        if(parent->GetNeighbor(dir)->GetObject()->TryMove(dir)){
            return TryMove(dir);
        }
        else if(parent->GetNeighbor(dir)->GetObject()->TryPush(dir)){
            return TryMove(dir);
        }
        else{
            return false;
        }
    }
    return PushAvailable;
    //////////   TODO END   ////////////////////////////////////
}

//////////   TODO END   ////////////////////////////////////
