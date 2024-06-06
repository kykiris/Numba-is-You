//////////     TODO     ////////////////////////////////////
// Declare your Equal class

#include "item/ItemBase.hpp"

class Equal: public ItemBase{
    public:
    Equal(CellObjBase * obj);
    ~Equal() = default;

    ItemType GetType() const { return ItemType::EQUALS; };
    char GetIcon() const { return '='; };
};






















//////////   TODO END   ////////////////////////////////////
