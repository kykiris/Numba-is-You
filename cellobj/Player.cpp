#include "cellobj/Player.hpp"

#include "Map.hpp"
#include "cell/Cell.hpp"
#include "item/ItemBase.hpp"
#include "cellobj/CellObjBase.hpp"

Player::Player(Cell* cell) : CellObjBase(cell)
{
}
Player::~Player(){
    
}
bool Player::TryPush(Direction dir)
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

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Player.hpp.

ObjectType Player::GetType() const{
    return ObjectType::PLAYER;
}
// AttrType Player::GetAttr() const{
//     return Terminal::Attr::NORMAL;
// }

char Player::GetIcon() const{
    if(GetItem()!=nullptr){
        return GetItem()->GetIcon();
    }
    else{
        return ' ';
    }
}



//////////   TODO END   ////////////////////////////////////
