//////////     TODO     ////////////////////////////////////
// Declare your Equal class

#include "item/ItemBase.hpp"

class Equal: public ItemBase{
    public:
    Equal(CellObjBase * obj);

    virtual ItemType GetType() const { return ItemType::EQUALS; };
    virtual char GetIcon() const { return '='; };
};






















//////////   TODO END   ////////////////////////////////////
