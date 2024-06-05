//////////     TODO     ////////////////////////////////////
// Declare your Equal class

#include "item/ItemBase.hpp"

class Equal: public ItemBase{
    public:
    Equal(CellObjBase * obj);

    virtual ItemType GetType() { return ItemType::EQUALS; };
    virtual char GetIcon() { return '='; };
};






















//////////   TODO END   ////////////////////////////////////
