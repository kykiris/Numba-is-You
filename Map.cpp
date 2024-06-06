#include "Map.hpp"

#include <istream>
#include "utils/Terminal.hpp"

#include "cell/Cell.hpp"
#include "cell/Home.hpp"
#include "cell/Wall.hpp"
#include "cellobj/CellObjBase.hpp"


Map::Map(Game* game) : parent(game), initialized(false)
{
    this->objects[ObjectType::BOX] = std::vector<CellObjBase*>();
    this->objects[ObjectType::PLAYER] = std::vector<CellObjBase*>();
    this->objects[ObjectType::GHOST] = std::vector<CellObjBase*>();
}


Map::~Map()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Initialize this map (only if this has not been initialized yet).
/// @param rowsize number of rows of the level
/// @param colsize number of columns of the level
/// @param ist istream that contains the level information string
/// @note The usage of 'ist' is similar to that of std::cin, since they both inherit std::istream.
void Map::Initialize(int rowsize, int colsize, std::istream& ist)
{
    if (this->initialized) return;
    this->cells.resize(rowsize);

    std::string line;
    //////////     TODO     ////////////////////////////////////
    // 1. Read cell map and construct each cell.
    // 2. Initialize each object and its item.

    for(int i=0;i<rowsize;i++){
        std::getline(ist, line);
        int j=0;
        std::vector<Cell*> eachCells;
        for(char c:line){
            Cell* eachCell = new Cell(this, i, j);
            eachCells.push_back(eachCell);
            if(c>='0' && c<='9'){
                homes.push_back(eachCell);
            }
            j++;
        }
        cells.push_back(eachCells);
    }

    // the code below needs #include <sstream>
    // std::getline(ist, line);
    // std::stringstream ss;
    // ss << line;
    // ss >> num_obj;

    int num_obj;
    ist >> num_obj;
    ist.ignore();

    std::string obj_type;
    char objItem;
    int objRow, objCol;
    for(int i=0;i<num_obj;i++){
        ist>>obj_type>>objItem>>objRow>>objCol;
        ist.ignore();
        GetCell(objRow, objCol)->InitObject(obj_type);
        GetCell(objRow, objCol)->GetObject()->InitItem(objItem);
    }




    //////////   TODO END   ////////////////////////////////////
    this->initialized = true;
}


void Map::PrintAll() const
{
    int rowsize = this->GetRowsize();
    int colsize = this->GetColsize();
    for (int r = 0; r < rowsize; r++)
    {
        for (int c = 0; c < colsize; c++)
        {
            this->PrintCell(r, c);
        }
    }
}


void Map::PrintCell(int row, int col) const
{
    this->cells[row][col]->Print();
}


bool Map::IsCleared() const
{
    //////////     TODO     ////////////////////////////////////
    // Check if every home has the correct number.



    //////////   TODO END   ////////////////////////////////////
}


/// @brief Spawn every ghosts with the correct order.
void Map::SpawnGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Sort this->equals to match spawning order.
    // For every equal, evaluate left/upper expression, get result string, and spawn ghosts.





    //////////   TODO END   ////////////////////////////////////
}


/// @brief Remove every ghosts.
void Map::RemoveGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Remove every ghosts and clear this->objects[GHOST].



    //////////   TODO END   ////////////////////////////////////    
}
