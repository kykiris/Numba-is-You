//////////     TODO     ////////////////////////////////////
// Implement the methods of your Home class



#include "cell/Home.hpp"


Home::Home(Map* map, int row, int col) : Cell(map, row, col)
{
    this->cellType = CellType::CELL;
}

HomeCheckResult Home::Check(){
    if(obj->GetItem()->GetType()==ItemType::NUMBER){
        int num_value = obj->GetItem()->GetIcon() - '0';
        if(this->target_number == num_value){
            return HomeCheckResult::CORRECT;
        }
        else{
            return HomeCheckResult::WRONG;
        }
    }
    else{
        return HomeCheckResult::EMPTY;
    }
//TODO
//TODO
//TODO      
}



//TODO
AttrType Home::GetAttr() const{}
ColorPair Home::GetColorPair() const{}
char Home::GetIcon() const{}















//////////   TODO END   ////////////////////////////////////