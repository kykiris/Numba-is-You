#include "cell/Wall.hpp"


Wall::Wall(Map* map, int row, int col) : Cell(map, row, col)
{
    this->cellType = CellType::WALL;
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Wall.hpp.

// AttrType Wall::GetAttr() const{
//     if(GetObject()!=nullptr){
//         return Terminal::Attr::REVERSE | GetObject()->GetAttr();
//     }
//     else{
//         return Terminal::Attr::REVERSE;
//     }
// }
// ColorPair Wall::GetColorPair() const{
//     if(obj!=nullptr && GetObject()->GetType()==ObjectType::PLAYER){
//         return ColorPair::PLAYER_NORMAL;
//     }
//     else{
//         return ColorPair::NORMAL;
//     }
// }
// char Wall::GetIcon() const{
//     if(GetObject()!=nullptr){
//         return GetObject()->GetIcon();
//     }
//     else{
//         return ' ';
//     }
// }



//////////   TODO END   ////////////////////////////////////
