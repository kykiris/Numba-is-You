#include "item/Operator.hpp"

Operator::Operator(CellObjBase* obj, OpType op) : ItemBase(obj), op(op)
{
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Number.hpp.

char Operator::GetIcon() const{
    if(this->op == OpType::ADD){
        return '+';
    }
    else if(this->op == OpType::MUL){
        return '*';
    }
    else if(this->op == OpType::SUB){
        return '-';
    }
}


//////////   TODO END   ////////////////////////////////////
