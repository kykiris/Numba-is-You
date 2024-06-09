#include "item/Number.hpp"

#include <stdexcept>

Number::Number(CellObjBase* obj, int value) : ItemBase(obj), value(value)
{
    if (value < 0 || value > 9) throw std::runtime_error("Number construct error");
}
Number::~Number(){
    // delete parent->parent;
    // delete parent;
    // parent->parent = nullptr;
    // parent = nullptr;
}
//
// int Number::GetValue(){
//     return this->value;
// }
//

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Number.hpp.

// done in number.hpp

//////////   TODO END   ////////////////////////////////////
