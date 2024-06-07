//////////     TODO     ////////////////////////////////////
// Implement the methods of your Equal class
#pragma once
#include "item/Equal.hpp"
#include "Enums.hpp"
#include "Map.hpp"


Equal::Equal(CellObjBase *obj): ItemBase(obj) {
    
}


Cell* NeighborCell(Direction dir, Cell* c){
    int row = c->row;
    int col = c->col;
    if(dir==Direction::UP){
        row--;
    }
    else if(dir==Direction::DOWN){
        row++;
    }
    else if(dir==Direction::LEFT){
        col--;
    }
    else if(dir==Direction::RIGHT){
        col++;
    }
    if(inRange(row, col, c->parent)){
        return c->parent->GetCell(row, col);
    }
    else{
        return nullptr;
    }
    
}

bool inRange(int row, int col, Map* m){
    if(row<0 || row>m->GetRowsize()-1){
        return false;
    }
    else{
        if(col<0 || col>m->GetColsize()-1){
            return false;
        }
        else{
            return true;
        }
    }
}
std::string Equal::GetExpression(Direction dir){
    int row = parent->parent->row;
    int col = parent->parent->col;
    bool availExp = true;

    //char stack is made
    //reference from GetNeighbor() in cell.cpp
    // int dir_row = row;
    // int dir_col = col;
    std::stack<char> s;
    Cell* nCell = NeighborCell(dir, parent->parent->parent->GetCell(row, col));
    while(nCell!=nullptr && nCell->GetObject()->GetItem()!=nullptr){
        if(nCell->GetObject()->GetItem()->GetIcon() == '='){
            break;
        }
        s.push(nCell->GetObject()->GetItem()->GetIcon());
        nCell = NeighborCell(dir, nCell);
    }
    nCell = nullptr;
    

    // char* c = new char[s.size()];
    std::string exp = "";
    int i=0; // for exp index
    
    while(!s.empty()){
        exp = exp + s.top();
        s.pop();
        // case 1: if the first char is '+' or '-', the second char should be number
        if(i==1 && (exp[0]=='+' || exp[0]=='-')){
            // this includes cases exp with another operator
            if(exp[i] < '0' || exp[i]>'9'){
                availExp = false;
                break;
            }
            else{
                // ex. +8->8
                exp.erase(exp.begin());
                i--;
            }
        }

        // case 2: if exp length is more than 2 (ex. 3+5), number should follow after operator
        if(i>=2){
            if(exp[i-1] == '+' || exp[i-1] == '-' || exp[i-1] == '*'){
                if(exp[i-2] < '0' || exp[i-2] > '9'){
                    availExp = false;
                    break;
                }
                if(exp[i] < '0' || exp[i] > '9'){
                    availExp = false;
                    break;
                }
            }
        }

        // case 3: (number)+(operator) is unavailable, operator cannot come at the end
        if(s.empty()){
            if(exp[i] == '+' || exp[i]=='-' || exp[i]=='*'){
                availExp = false;
                break;
            }
        }
        i++;
    }

    // Note : Do not use i anymore, since it can cause logical error

    // delete[] c;
    // c = nullptr;




    // Note : section for return

    if(availExp==false){
        return "";
    }
    else if(availExp == true){
        return exp;
    }
}

// Equal::~Equal(){}



















//////////   TODO END   ////////////////////////////////////
