#include <iostream>
#include <vector>

using namespace std;

struct transition{
    vector<vector<int>> oldState;
    int action;
    int reward;
    vector<vector<int>> newState;
    bool done;
};

class Room{
    private:
        int m, n;
        // 3D vector: row, col, map overlay
        // Map overlay: cleaning status, agent location
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
            grid.at(0).at(0).at(1) = 1;
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

            // TODO: implement reward function
            // TakeAction()
            //      GetReward()
            newTransition.reward = 1;
            newTransition.newState = GetState();
            newTransition.done = CheckIfDone();

            return newTransition;
        }
};

int main(){
    Room TestRoom(6, 10);
    TestRoom.Render(0);
    cout<<"\n";
    TestRoom.Render(1);
    cout<<"\n";
    vector<vector<int>> a = TestRoom.GetState();
    for(int i = 0; i <= a.size()-1; i++){
        for(int j = 0; j <= a.at(i).size()-1; j++){
            cout<<a.at(i).at(j);
        }
        cout<<"\n";
    }
}