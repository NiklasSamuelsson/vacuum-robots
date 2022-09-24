#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <vector>

using namespace std;

struct agentPosition{
    int dim1;
    int dim2;
};

struct transition{
    vector<vector<int>> oldState;
    int action;
    int reward;
    vector<vector<int>> newState;
    bool done;
};

/**
 * Simulates a 2D room enviroment with an agent acting in it.
 * The agent can perform one of five actions every timestep:
 * move up, down, left, right or idle.
 * A reward (cost) of 1 is given every timestep.
 * The task is completed when every position has been visited.
*/
class Room{
    private:
        int m, n;
        agentPosition cAgentPos;
        // 3D vector: row, col, map overlay[cleaning status, action location]
        vector<vector<vector<int>>> grid;
        vector<vector<int>> state;

        bool CheckIfDone(){
            bool done = true;
            for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j < grid.at(i).size(); j++){
                    if(grid.at(i).at(j).at(0) == 0){
                        done = false;
                        break;
                    }
                }
            }
            return done;
        }

        int TakeAction(int action){
            // 1: up (-1 in dim1)
            // 2: down (+1 in dim1)
            // 3: left (-1 in dim2)
            // 4: right (+1 in dim2)
            // 5: idle
            int reward;

            reward = 1;
            grid.at(cAgentPos.dim1).at(cAgentPos.dim2).at(1) = 0;

            switch (action){
                case 1:
                    cAgentPos.dim1 = (cAgentPos.dim1 - 1 < 0) ? cAgentPos.dim1: cAgentPos.dim1 - 1;
                    break;
                case 2:
                    cAgentPos.dim1 = (cAgentPos.dim1 + 1 == m) ? cAgentPos.dim1: cAgentPos.dim1 + 1;
                    break;
                case 3:
                    cAgentPos.dim2 = (cAgentPos.dim2 - 1 < 0) ? cAgentPos.dim2: cAgentPos.dim2 - 1;
                    break;
                case 4:
                    cAgentPos.dim2 = (cAgentPos.dim2 + 1 == n) ? cAgentPos.dim2: cAgentPos.dim2 + 1;
                    break;
                case 5:
                    break;
            }
            grid.at(cAgentPos.dim1).at(cAgentPos.dim2).at(0) = 1;
            grid.at(cAgentPos.dim1).at(cAgentPos.dim2).at(1) = 2;
            return reward;
        }

    public:
        Room(int m, int n){
            this->m = m;
            this->n = n;
            Reset();
        }

        void Reset(){
            grid.clear();
            grid.assign(m, vector(n, vector<int>(2, 0)));
            // Assign agent start location
            cAgentPos.dim1 = 0;
            cAgentPos.dim2 = 0;
            grid.at(cAgentPos.dim1).at(cAgentPos.dim2).at(1) = 2;
            // Mark the first postion as cleaned
            grid.at(cAgentPos.dim1).at(cAgentPos.dim2).at(0) = 1;
        }

        void Render(int layer){
            for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j < grid.at(i).size(); j++){
                    cout<<grid.at(i).at(j).at(layer);
                }
                cout<<"\n";
            }
        }

        vector<vector<int>> GetState(){
            int maxval, gridval;
            state.clear();
            state.assign(m, vector<int>(n, -99));
            for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j < grid.at(i).size(); j++){
                    maxval = -99;
                    for(int l = 0; l < grid.at(i).at(j).size(); l++){
                        gridval = grid.at(i).at(j).at(l);
                        if(gridval > maxval){
                            maxval = gridval;
                        }
                    }
                    state.at(i).at(j) = maxval;
                }
            }
            return state;
        }

        transition Step(int action){
            transition newTransition;

            newTransition.oldState = GetState();
            newTransition.action = action;
            newTransition.reward = TakeAction(action);
            newTransition.newState = GetState();
            newTransition.done = CheckIfDone();

            return newTransition;
        }
};

#endif