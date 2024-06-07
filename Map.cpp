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
    

    // WE MUST!!!! TODO

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
        Cell* eachCell = 0;
        for(char c:line){
            if(c>='0' && c<='9'){
                eachCell = new Home(this, i, j);
                eachCells.push_back(eachCell);
                homes.push_back(eachCell);
            }
            else if(c == '#'){
                eachCell = new Wall(this, i, j);
                eachCells.push_back(eachCell);
                
            }
            else{
                eachCell = new Cell(this, i, j);
                eachCells.push_back(eachCell);
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

    bool isTrue = true;
    for(auto h:homes){
        if(h->Check() == HomeCheckResult::WRONG){
            isTrue = false;
        }
    }

    return isTrue;

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Spawn every ghosts with the correct order.
void Map::SpawnGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Sort this->equals to match spawning order.
    // For every equal, evaluate left/upper expression, get result string, and spawn ghosts.

    // selection sort : ex. (row, col) = (1,1), (1,2), (2,3), (2,5), (4,7)
    
    for(int i=0;i<equals.size()-1;i++){
        Equal* tmp;
        int min_index = i+1;
        for(int j=i+1;j<equals.size();j++){
            if(equals[min_index]->parent->parent->row > equals[j]->parent->parent->row){
                //TODO
                min_index = j;
            }
            else if(equals[min_index]->parent->parent->row == equals[j]->parent->parent->row){
                if(equals[min_index]->parent->parent->col > equals[j]->parent->parent->col){
                    min_index = j;
                }
            }
        }
        if(equals[min_index]->parent->parent->row < equals[i]->parent->parent->row){
            tmp = equals[i];
            equals[i] = equals[min_index];
            equals[min_index] = tmp;
        }
        else if(equals[min_index]->parent->parent->row == equals[i]->parent->parent->row && equals[min_index]->parent->parent->col < equals[i]->parent->parent->col){
            tmp = equals[i];
            equals[i] = equals[min_index];
            equals[min_index] = tmp;
        }
        tmp = nullptr;
    }
    
    //sort end


    // Note: Ghost Making Algorithm
    for(auto e:equals){
        std::string s = e->GetExpression(Direction::LEFT);
        int i=0;
        std::vector<std::string> ExpToVec; // each item is here
        std::vector<char> eachNum; // to make n digit num
        for(auto c:s){
            // if(c=='*' || c=='+' || c=='-'){
                
            // }
            if(c>='0' && c<='9'){
                eachNum.push_back(c);
            }
            else{
                // push back eachNum to ExpToVec
                if(!eachNum.empty()){
                    std::string x;
                    for(auto y:eachNum){
                        x = x+y;
                    }
                    eachNum.clear();
                    ExpToVec.push_back(x);
                }
                std::string z;
                z = z + c;
                ExpToVec.push_back(z);
            }
        }
        if(!eachNum.empty()){
            std::string x;
            for(auto y:eachNum){
                x = x+y;
            }
            eachNum.clear();
            ExpToVec.push_back(x);
        }


        // let's calculate...
        std::string op = "+";
        int num = 0;
        for(auto st:ExpToVec){
            if(st=="+" || st=="-" || st=="*"){
                op = st;
            }
            else if(st[0]>='0' && st[0]<='9'){
                int n = 0;
                for(int i=0;i<st.length();i++){
                    int dig = st[i] - '0';
                    for(int j=0;j<st.length()-1-i;j++){
                        dig *= 10;
                    }
                    n += dig;
                }
                if(op=="+"){
                    num += n;
                }
                else if(op=="-"){
                    num -= n;
                }
                else if(op== "*"){
                    num *= n;
                }
            }
        }

        //now num will be ghost.

        // TODO: NOTE: MAKE GHOST OBJ, after MAKE IT -> edit below


    }

    







    // selection sort again (by column)

    for(int i=0;i<equals.size()-1;i++){
        Equal* tmp;
        int min_index = i+1;
        for(int j=i+1;j<equals.size();j++){
            if(equals[min_index]->parent->parent->col > equals[j]->parent->parent->col){
                //TODO
                min_index = j;
            }
            else if(equals[min_index]->parent->parent->col == equals[j]->parent->parent->col){
                if(equals[min_index]->parent->parent->row > equals[j]->parent->parent->row){
                    min_index = j;
                }
            }
        }
        if(equals[min_index]->parent->parent->col < equals[i]->parent->parent->col){
            tmp = equals[i];
            equals[i] = equals[min_index];
            equals[min_index] = tmp;
        }
        else if(equals[min_index]->parent->parent->col == equals[i]->parent->parent->col && equals[min_index]->parent->parent->row < equals[i]->parent->parent->row){
            tmp = equals[i];
            equals[i] = equals[min_index];
            equals[min_index] = tmp;
        }
        tmp = nullptr;
    }

    // Note: Ghost Making Algorithm
    for(auto e:equals){
        std::string s = e->GetExpression(Direction::UP);
        int i=0;
        std::vector<std::string> ExpToVec; // each item is here
        std::vector<char> eachNum; // to make n digit num
        for(auto c:s){
            // if(c=='*' || c=='+' || c=='-'){
                
            // }
            if(c>='0' && c<='9'){
                eachNum.push_back(c);
            }
            else{
                // push back eachNum to ExpToVec
                if(!eachNum.empty()){
                    std::string x;
                    for(auto y:eachNum){
                        x = x+y;
                    }
                    eachNum.clear();
                    ExpToVec.push_back(x);
                }
                std::string z;
                z = z + c;
                ExpToVec.push_back(z);
            }
        }
        if(!eachNum.empty()){
            std::string x;
            for(auto y:eachNum){
                x = x+y;
            }
            eachNum.clear();
            ExpToVec.push_back(x);
        }


        // let's calculate...
        std::string op = "+";
        int num = 0;
        for(auto st:ExpToVec){
            if(st=="+" || st=="-" || st=="*"){
                op = st;
            }
            else if(st[0]>='0' && st[0]<='9'){
                int n = 0;
                for(int i=0;i<st.length();i++){
                    int dig = st[i] - '0';
                    for(int j=0;j<st.length()-1-i;j++){
                        dig *= 10;
                    }
                    n += dig;
                }
                if(op=="+"){
                    num += n;
                }
                else if(op=="-"){
                    num -= n;
                }
                else if(op== "*"){
                    num *= n;
                }
            }
        }

        //now num will be ghost.
        // EDIT ME EDIT ME EDIT ME EDIT ME
    }

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Remove every ghosts.
void Map::RemoveGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Remove every ghosts and clear this->objects[GHOST].



    //////////   TODO END   ////////////////////////////////////    
}
