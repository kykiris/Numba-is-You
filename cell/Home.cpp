//////////     TODO     ////////////////////////////////////
// Implement the methods of your Home class



#include "cell/Home.hpp"


Home::Home(Map* map, int row, int col, char c) : Cell(map, row, col)
{
    this->cellType = CellType::HOME;
    this->targetNumber = c;
    // this->obj = new CellObjBase(this);
}

char Home::GetIcon() const{
    if(obj==nullptr){
        return targetNumber;
    }
    else{
        //idk it is right, but anyway added... 240606 1:08
        if(obj->GetItem()!=nullptr){
            return obj->GetItem()->GetIcon();
        }
        else{
            return ' ';
        }
        
    }
}

HomeCheckResult Home::Check(){
    // if(obj->GetItem()->GetType()==ItemType::NUMBER){
    //     int num_value = obj->GetItem()->GetIcon() - '0';
    //     if(this->target_number == num_value){
    //         return HomeCheckResult::CORRECT;
    //     }
    //     else{
    //         return HomeCheckResult::WRONG;
    //     }
    // }
    if(obj!=nullptr){
        if(obj->GetItem()!=nullptr && obj->GetItem()->GetIcon() == targetNumber){
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

ColorPair Home::GetColorPair() const{
    ColorPair cp = ColorPair::NORMAL;
    if(obj!=nullptr){
        if(obj->GetType() == ObjectType::PLAYER){
            if(obj->GetIcon()==targetNumber){
                cp = ColorPair::PLAYER_CORRECT;
            }
            else{
                cp = ColorPair::PLAYER_WRONG;
            }
        }
        else{
            if(obj->GetIcon()==targetNumber){
                cp = ColorPair::CORRECT;
            }
            else{
                cp = ColorPair::WRONG;
            }
        }
    }
    return cp;
}

//TODO
AttrType Home::GetAttr() const{
    AttrType at = Terminal::Attr::NORMAL;
    if(obj==nullptr){
        at = Terminal::Attr::UNDERLINE | Terminal::Attr::DIM;
    }
    else{
        at = Terminal::Attr::UNDERLINE;
    }
    if(obj != nullptr){
        if(obj->GetType() == ObjectType::GHOST){
            at = at | Terminal::Attr::DIM;
        }
        else{
            at = at | Terminal::Attr::NORMAL;
        }
    }
    return at;
}
// ColorPair Home::GetColorPair() const{}
// char Home::GetIcon() const{}















//////////   TODO END   ////////////////////////////////////