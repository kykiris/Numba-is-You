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

    // std::vector<Cell*> eachCells;
    for(int i=0;i<rowsize;i++){
        std::getline(ist, line, '\n');
        int j=0;
        // eachCells.clear();
        Cell* eachCell = 0;
        for(char c:line){
            if(c>='0' && c<='9'){
                eachCell = new Home(this, i, j, c);
                cells[i].push_back(eachCell);
                // cells[i][j]->SetNum(c);
                homes.push_back(eachCell);
            }
            else if(c == '#'){
                eachCell = new Wall(this, i, j);
                cells[i].push_back(eachCell);
            }
            else{
                eachCell = new Cell(this, i, j);
                // eachCells.push_back(eachCell);
                cells[i].push_back(eachCell);
            }
            
            j++;
        }
        // this->cells.push_back(eachCells);
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
    
    for(int i=0;i<num_obj;i++){
        // std::getline(ist, line);
        // if(line[0]=='B'){
        //     obj_type = "Box";
        //     line = line.substr(4);
        // }
        // else if(line[0]=='P'){
        //     obj_type = "Player";
        //     line = line.substr(7);
        // }
        // for(int i=0;i<3;i++){
        //     int j=0;
        //     while(line[j]==' '){

        //     }
        // }

        std::getline(ist, obj_type, ' ');
        std::string inputs;
        std::getline(ist, inputs, ' ');
        objItem = inputs[0];
        std::getline(ist, inputs, ' ');
        // throw std::runtime_error(inputs);
        int objRow = 0;
        int objCol = 0;
        for(int j=0;j<inputs.length();j++){
            int dig = inputs[j] - '0';
            for(int k=0;k<inputs.length()-1-j;k++){
                dig *= 10;
            }
            objRow += dig;
        }
        std::getline(ist, inputs, '\n');
        for(int j=0;j<inputs.length();j++){
            int dig = inputs[j] - '0';
            for(int k=0;k<inputs.length()-1-j;k++){
                dig *= 10;
            }
            objCol += dig;
        }

        // ist>>obj_type>>objItem>>objRow>>objCol;
        // ist.ignore();
        
        //Cell* nC = GetCell(objRow, objCol);
        GetCell(objRow, objCol)->InitObject(obj_type);
        // throw std::runtime_error("This is where you stand"); // Error Check
        GetCell(objRow, objCol)->GetObject()->InitItem(objItem);
        //
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
        if(h->Check() == HomeCheckResult::WRONG || h->Check() == HomeCheckResult::EMPTY){
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
    if(equals.empty()){
        return;
    }
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
        if(s.length()!=0){
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

        //first, let's make integer to char[]
        std::vector<char> preGhost;
        std::stack<char> GhostStack;
        if(num<0){
            preGhost.push_back('-');
            num*=-1;
        }
        
        int prevCal = num; // mogt
        int afterCal = 0; //narmerge
        while(1){
            
            afterCal = prevCal % 10;
            prevCal = prevCal / 10;

            char c = afterCal + '0';
            GhostStack.push(c);
            if(prevCal == 0){
                break;
            }
            else{
                GhostStack.push(c);
            }
        }
        while(!GhostStack.empty()){
            preGhost.push_back(GhostStack.top());
            GhostStack.pop();
        }

        // Cell* GhostMaker = e->parent->parent;
        int row = e->parent->parent->row;
        int col = e->parent->parent->col;
        for(auto g:preGhost){
            // Direction::RIGHT
            col++;
            if(col >= this->GetColsize()){
                break;
            }
            Cell* newCell = GetCell(row, col);
            if(newCell->GetObject()!=nullptr && (newCell->GetObject()->GetType() == ObjectType::BOX || newCell->GetObject()->GetType() == ObjectType::PLAYER)){
                continue;
            }
            else if(newCell->GetObject()!=nullptr && newCell->GetObject()->GetType() == ObjectType::GHOST){
                //if(newCell->GetObject()->GetItem()!=nullptr && newCell->GetObject()->GetItem()->GetIcon() > g){
                if(newCell->GetIcon()!=' ' && newCell->GetIcon() >= g){
                    continue;
                }
            }
            if(newCell!=nullptr && newCell->GetIcon()=='='){
                break;
            }
            
            newCell->InitObject("Ghost");
            newCell->GetObject()->InitItem(g);
        }
        }
        // TODO: NOTE: MAKE GHOST OBJ, after MAKE IT -> edit below
    }

    


// CellObjBase* newGhost = new Ghost(newCell);
            // newGhost->InitItem(g); // g is char
            // newGhost->parent = newCell;
            // newGhost->parent->

            // if(newGhost->parent->GetIcon()!=g) delete newGhost;
            // this->objects[ObjectType::GHOST].push_back(newCell->GetObject());
            // this->objects[ObjectType::GHOST][]



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
        if(s.length()!=0){
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

        std::vector<char> preGhost;
        std::stack<char> GhostStack;
        if(num<0){
            preGhost.push_back('-');
            num*=-1;
        }
        int prevCal = num; // mogt
        int afterCal = 0; //narmerge
        while(1){
            
            afterCal = prevCal % 10;
            prevCal = prevCal / 10;

            char c = afterCal + '0';
            GhostStack.push(c);
            if(prevCal == 0){
                break;
            }
            else{
                GhostStack.push(c);
            }
        }
        while(!GhostStack.empty()){
            preGhost.push_back(GhostStack.top());
            GhostStack.pop();
        }

        // Cell* GhostMaker = e->parent->parent;
        int row = e->parent->parent->row;
        int col = e->parent->parent->col;
        for(auto g:preGhost){
            // Direction::RIGHT
            row++;
            if(row >= this->GetRowsize()){
                break;
            }
            Cell* newCell = GetCell(row, col);
            if(newCell->GetObject()!=nullptr && (newCell->GetObject()->GetType() == ObjectType::BOX || newCell->GetObject()->GetType() == ObjectType::PLAYER)){
                continue;
            }
            else if(newCell->GetObject()!=nullptr && newCell->GetObject()->GetType() == ObjectType::GHOST){
                //if(newCell->GetObject()->GetItem()!=nullptr && newCell->GetObject()->GetItem()->GetIcon() > g){
                if(newCell->GetIcon()!=' ' && newCell->GetIcon() >= g){
                    continue;
                }
            }
            if(newCell!=nullptr && newCell->GetIcon()=='='){
                break;
            }
            
            newCell->InitObject("Ghost");
            newCell->GetObject()->InitItem(g);
        }
        }
    }
    //////////   TODO END   ////////////////////////////////////
}


/// @brief Remove every ghosts.
void Map::RemoveGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Remove every ghosts and clear this->objects[GHOST].

    for(auto o:this->objects[ObjectType::GHOST]){
        // o->GetItem();
        o->parent->InitObject(" ");
        // delete o;
        o = nullptr;
        // delete o->GetItem();
    }
    this->objects[ObjectType::GHOST].clear();

    //////////   TODO END   ////////////////////////////////////    
}
