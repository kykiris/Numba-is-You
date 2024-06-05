#include "cell/Cell.hpp"

#include <string>
#include "utils/Terminal.hpp"

#include "Map.hpp"
#include "cellobj/Box.hpp"
#include "cellobj/Player.hpp"

Cell::Cell(Map* map, int row, int col) : parent(map), row(row), col(col)
{
    this->cellType = CellType::CELL;
}

Cell::~Cell()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    //delete this;
    delete this->parent;
    this->parent = nullptr;
    //////////   TODO END   ////////////////////////////////////
}

void Cell::InitObject(const std::string& objType)
{
    //////////     TODO     ////////////////////////////////////
    // Initialize object.
    // 1. Delete existing object.
    // 2. Check objType and make corresponding object.
    // 3. push_back the object to the corresponding map->objects[].


    delete obj;
    if(objType == "Box"){
        obj = new Box(this);
        parent->objects[ObjectType::BOX].push_back(obj);
    }
    else if(objType == "Player"){
        obj = new Player(this);
        parent->objects[ObjectType::PLAYER].push_back(obj);
    }
    //////////   TODO END   ////////////////////////////////////
}

void Cell::SwapObject(Cell* other)
{
    //////////     TODO     ////////////////////////////////////
    // Implement object swapping.
    // 1. If this->obj exists: change parent of this->obj.
    // 2. If other->obj exists: change parent of other->obj.
    // 3. Swap this->obj and other->obj.

    if(GetObject()!=nullptr){
        this->obj->parent = other;
    }
    if(other->GetObject()!=nullptr){
        other->obj->parent = this;
    }
    CellObjBase* tmp = this->obj;
    this->obj = other->obj;
    other->obj = tmp;

    //////////   TODO END   ////////////////////////////////////
}

void Cell::Print() const
{
    Terminal::PrintIconAt(row, col, this->GetIcon(), this->GetAttr(), this->GetColorPair());
}

AttrType Cell::GetAttr() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetAttr.
    // Default attr is NORMAL, but if this cell has an object, then OR(|) with the object's attr.

    if(cellType == CellType::CELL){
        //Terminal::Attr::NORMAL = ;
        return Terminal::Attr::NORMAL;
    }
    else if(cellType == CellType::HOME){

        if(GetObject()!=nullptr){
            return Terminal::Attr::UNDERLINE | Terminal::Attr::DIM;
        }
        else{
            return Terminal::Attr::UNDERLINE;
        }
    }
    else if(cellType == CellType::WALL){
        return Terminal::Attr::REVERSE;
    }

    //////////   TODO END   ////////////////////////////////////
}

ColorPair Cell::GetColorPair() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetColorPair.
    // Default ColorPair is NORMAL, but if this->object is a player, then return PLAYER_NORMAL.
    
    
    if(GetObject()->GetType()==ObjectType::PLAYER){
        return ColorPair::PLAYER_NORMAL;
    } 
    else{
        return ColorPair::NORMAL;
    }

    //////////   TODO END   ////////////////////////////////////
}

char Cell::GetIcon() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetIcon.
    // Default icon is ' ', but if this cell has an object, then return the object's icon.

    if(GetObject()!=nullptr){
        //idk it is right, but anyway added... 240606 1:08
        return GetObject()->GetIcon();
    }
    else{
        return ' ';
    }

    //////////   TODO END   ////////////////////////////////////
}

Cell* Cell::GetNeighbor(Direction dir) const
{
    //////////     TODO     ////////////////////////////////////
    // Get neighbor of that direction.
    // If the cell is placed at the border of the map and the direction is outside the map, return nullptr.
    // Else return the neighbor cell.

    int dir_row = row;
    int dir_col = col;
    if(dir==Direction::UP){
        dir_row--;
    }
    else if(dir==Direction::DOWN){
        dir_row++;
    }
    else if(dir==Direction::LEFT){
        dir_col--;
    }
    else if(dir==Direction::RIGHT){
        dir_col++;
    }

    // If the cell is placed at the border of the map and the direction is outside the map, return nullptr.
    
    //TODO
    // if(dir_row < 0 || dir_row > parent->GetRowsize()-1){
    //     return nullptr;
    // }
    // if(dir_col < 0 || dir_col > parent->GetColsize()){
    // }

    if(parent->GetCell(dir_row, dir_col)->cellType==CellType::WALL){
        return nullptr;
    }

    // Else return the neighbor cell.

    //TODO
    else{
        return parent->GetCell(dir_row, dir_col);
    }

    //////////   TODO END   ////////////////////////////////////
}
