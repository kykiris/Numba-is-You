#include "cellobj/Ghost.hpp"

Ghost::Ghost(Cell* cell) : CellObjBase(cell)
{
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Ghost.hpp.
    // Implement Ghost::GetType that returns GHOST.

    // Implement Ghost::GetAttr that returns DIM.

    // Implement Ghost::GetIcon.
    // No default icon - return the item's icon.

ObjectType Ghost::GetType() const{
    return ObjectType::GHOST;
}
AttrType Ghost::GetAttr() const{
    return Terminal::Attr::DIM;
}
char Ghost::GetIcon() const{
    return GetItem()->GetIcon();
}


//////////   TODO END   ////////////////////////////////////
