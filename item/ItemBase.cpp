#include "item/ItemBase.hpp"

ItemBase::ItemBase(CellObjBase* obj) : parent(obj)
{
}
int ItemBase::GetNumber(){
    return 0;
}
// ItemBase::~ItemBase(){}