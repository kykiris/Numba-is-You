#include "Game.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include "utils/Terminal.hpp"

#include "Enums.hpp"
#include "cell/Home.hpp"


Game::Game(std::string levelName)
{
    const std::string sol_ext = ".sol";
    this->levelName = levelName;  // "levels/1-sokoban.txt"
    this->solutionName = levelName + sol_ext;  // "levels/1-sokoban.txt.sol"
}


Game::~Game()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.
    delete this->map;
    //////////   TODO END   ////////////////////////////////////
}


/// @brief Run the game and start the event loop.
void Game::Run()
{
    Start();
    do
    {
        Update();
    } while (this->gameState != GameState::GAMEOVER);
    End();
}


/// @brief Initialize ncurses environment and load the map.
void Game::Start()
{
    Terminal::InitConsole();
    Load(this->levelName);
    gameState = GameState::PLAYING;
}


/// @brief End the ncurses environment.
void Game::End()
{
    Terminal::EndConsole();
}


/// @brief Run the event loop.
void Game::Update()
{
    Command cmd = Terminal::GetCommand();
    if (this->gameState == GameState::PLAYING)
    {
        switch (cmd)
        {
            case Command::UP:
            case Command::LEFT:
            case Command::DOWN:
            case Command::RIGHT:
                Move((Direction)((int)cmd - (int)Command::UP));
                break;
            case Command::UNDO:
                Undo();
                break;
            case Command::RESTART:
                Load(this->levelName);
                break;
            case Command::SOLVE:
                Load(this->levelName);
                StartSolve(this->solutionName);
                break;
            case Command::EXIT:
                AskExit();
                break;
            default:
                return;
        }
    }
    if (this->gameState == GameState::CLEARED)
    {
        Terminal::PrintMessage(
            "Victory!\n"
            "  q: exit\n"
            "  z: undo\n"
            "  r: restart\n"
        );
        switch (cmd)
        {
            case Command::UNDO:
                Undo();
                this->gameState = GameState::PLAYING;
                Terminal::ClearMessage();
                break;
            case Command::RESTART:
                Load(this->levelName);
                this->gameState = GameState::PLAYING;
                Terminal::ClearMessage();
                break;
            case Command::EXIT:
                this->gameState = GameState::GAMEOVER;
                return;
            default:
                return;
        }
    }
}


/// @brief Load the map from txt file. Also used for resetting the game.
/// @param filename filename of the level file
void Game::Load(std::string filename)
{
    std::ifstream ifs { filename };
    if (!ifs.is_open())
        throw std::runtime_error("Could not open the level file.");

    delete this->map;
    this->map = new Map{ this };

    int rowsize, colsize;
    ifs >> rowsize >> colsize;
    ifs.ignore();  // ignore next '\n' for getline

    this->map->Initialize(rowsize, colsize, ifs);
    
    // make ghosts
    this->map->SpawnGhosts();
    if (this->map->IsCleared())
        this->gameState = GameState::CLEARED;
    this->map->PrintAll();

    

    //////////     TODO     ////////////////////////////////////
    // Add undo-related logic if you needed.

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Simulate inputs written in the solution file.
/// @param filename filename of the solution file
void Game::StartSolve(std::string filename)
{
    Terminal::PrintMessage(
        "Solving state:\n"
        "  Press any key to continue...\n"
        "  Press Q to stop.\n"
    );
    // filename = filename+".sol";
    std::ifstream ifs { filename };
    if (!ifs.is_open())
        throw std::runtime_error("Could not open solution file.");
    std::string line;
    std::getline(ifs, line);

    //////////     TODO     ////////////////////////////////////
    // Implement 'solving state'.
    // If every input in the line has been simulated, then the solving state ends.
    // Any keystroke except ‘Q’ will simulate the given input and will progress to next move.
    // If you press ‘Q’, then the solving state ends.
    // When the solving state ends, clear the terminal message.
    for(auto c:line){
        Command anyKey = Terminal::GetCommand();
        if(anyKey==Command::EXIT){
            break;
        }
        else{
            Command cmd;
            if(c == 'W'){
                cmd = Command::UP;
            }
            else if(c == 'A'){
                cmd = Command::LEFT;
            }
            else if(c == 'S'){
                cmd = Command::DOWN;
            }
            else if(c == 'D'){
                cmd = Command::RIGHT;
            }
            else{
                break;
            }
            
            Move((Direction)((int)cmd - (int)Command::UP));

            if(gameState == GameState::CLEARED){
                break;
            }
        }
        // gameState = GameState::PLAYING;
    }

    Terminal::ClearMessage();


    //////////   TODO END   ////////////////////////////////////
}


void Game::AskExit()
{
    Terminal::PrintMessage(
        "Wanna quit?\n"
        "  q: quit\n"
        "  z: resume\n"
    );
    //////////     TODO     ////////////////////////////////////
    // Implement 'exiting state'.
    // Press ‘Q’ again to quit the game.
    // Press ‘Z’ to resume the game and clear the terminal message.

    
    while(1){
        Command Key = Terminal::GetCommand();
        if(Key == Command::EXIT){
            gameState = GameState::GAMEOVER;
            break;
        }
        else if(Key == Command::UNDO){
            Terminal::ClearMessage();
            break;
        }
    }
    
    //////////   TODO END   ////////////////////////////////////
}


void Game::Move(Direction dir)
{
    //////////     TODO     ////////////////////////////////////
    // Implement move.
    // 1. Remove every ghost.
    // 2. Try push and move every player in the given direction.
    // 3. Spawn ghosts.
    // 4. Check if the game’s clear condition is met, and change the game state.
    // 5. Print the map.
    // 6. Push current map state to undo stack.

    std::vector<Cell*> latestMap;
    for(auto o:map->objects[ObjectType::BOX]){
        Cell* location;
        location = map->GetCell(o->parent->row, o->parent->col);
        latestMap.push_back(location);
    }
    for(auto o:map->objects[ObjectType::PLAYER]){
        Cell* location;
        location = map->GetCell(o->parent->row, o->parent->col);
        latestMap.push_back(location);
    }
    undoStack.push(latestMap);

    map->RemoveGhosts();
    
    int playerNum = map->objects[ObjectType::PLAYER].size();
    std::vector<CellObjBase*> players;
    for(auto o:map->objects[ObjectType::PLAYER]){
        players.push_back(o);
    }
    //sort players
    for(int i=0;i<playerNum-1;i++){
        CellObjBase* stdPly = players[i];
        int stdNum = i;
        for(int j=i+1;j<playerNum;j++){
            if(dir==Direction::UP){
                if(players[j]->parent->row < stdPly->parent->row){
                    stdNum = j;
                    stdPly = players[j];
                }
            }
            else if(dir==Direction::DOWN){
                if(players[j]->parent->row > stdPly->parent->row){
                    stdNum = j;
                    stdPly = players[j];
                }
            }
            else if(dir==Direction::LEFT){
                if(players[j]->parent->col < stdPly->parent->col){
                    stdNum = j;
                    stdPly = players[j];
                }
            }
            else if(dir==Direction::RIGHT){
                if(players[j]->parent->col > stdPly->parent->col){
                    stdNum = j;
                    stdPly = players[j];
                }
            }
        }
        if(stdNum != i){
            CellObjBase* tmp = players[i];
            players[i] = players[stdNum];
            players[stdNum] = tmp;
        }
    }
    //sort end

    for(auto v:players){
        if(v==nullptr){
            break;
        }
        if(v->TryPush(dir)){
            continue;
        }
        else if(v->TryMove(dir)){
            continue;
        }
    }

    map->SpawnGhosts();

    if(map->IsCleared() == false){
        gameState = GameState::PLAYING;
    }
    else{
        gameState = GameState::CLEARED;
    }

    // map->IsCleared();
    

    // UNDO STACK

    // std::vector<std::string> latestMap;
    // for(int i=0;i<map->GetRowsize();i++){
    //     std::string s = "";
    //     for(int j=0;j<map->GetColsize();j++){
    //         s = s + map->GetCell(i, j)->GetIcon();
    //     }
    //     latestMap.push_back(s);
    // }
    // std::string s = "";
    // s = s + (char)(map->objects[ObjectType::BOX].size()+map->objects[ObjectType::PLAYER].size());
    // latestMap.push_back(s);

    
    

    map->PrintAll();
    //////////   TODO END   ////////////////////////////////////
}


void Game::Undo()
{
    //////////     TODO     ////////////////////////////////////
    // Implement undo feature.
    // 1. Remove every ghost.
    // 2. Pop the undo stack and retrieve previous move information.
    // 3. Change each box position manually.
    // 4. Spawn ghosts.
    // 5. Check if the game’s clear condition is met, and change the game state.
    // 6. Print the map.

    if(undoStack.empty()){
        return;
    }
    else{
        map->RemoveGhosts();
        std::vector<Cell*> latest = undoStack.top();
        undoStack.pop();
        // int ObjSize = map->objects[ObjectType::BOX].size()+map->objects[ObjectType::PLAYER].size();
        for(int i=0;i<map->objects[ObjectType::BOX].size();i++){
            // Cell* tmp = map->objects[ObjectType::BOX][i]->parent;
            // map->objects[ObjectType::BOX][i]->parent = latest[i];
            latest[i]->SwapObject(map->objects[ObjectType::BOX][i]->parent);
        }
        for(int i=0;i<map->objects[ObjectType::PLAYER].size();i++){
            int count = i + map->objects[ObjectType::BOX].size();
            // Cell* tmp = map->objects[ObjectType::PLAYER][i]->parent;
            //  = latest[count];
            // latest[count] = tmp;
            latest[count]->SwapObject(map->objects[ObjectType::PLAYER][i]->parent);
        }

        map->SpawnGhosts();

        if(map->IsCleared() == false){
            gameState = GameState::PLAYING;
        }
        else{
            gameState = GameState::CLEARED;
        }

        map->PrintAll();
    }

    //////////   TODO END   ////////////////////////////////////
}
