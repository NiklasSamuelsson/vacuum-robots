#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

class State{
    private:
        int m, n;
        vector<vector<int>> grid;

    public:
        State(int m, int n){
            this->m = m;
            this->n = n;
            Reset();
        }

        void Reset(){
            grid.clear();
            grid.assign(m, vector<int>(n, -99));
        }

        vector<int> at(int i){
            return grid.at(i);
        }

        // Needed to store in a map
        bool operator==(const State& otherState){
            return grid == otherState.grid;
        }
};

int main(){
    State state1(3, 4);
    State state2(3, 4);
    State state3(3, 5);

    cout<<(state1 == state2);
    cout<<endl<<(state1 == state3);
    cout<<endl<<(state2 == state3);

    vector<bool> vec1{true, true, false};
    vector<bool> vec2{true, false, false};

    hash<vector<bool>> hashVec1;
    hash<vector<bool>> hashVec2;

    cout<<endl<<hashVec1(vec1);
    cout<<endl<<hashVec2(vec2);

    // TODO: use unordered_map or implement < operator instead of ==
    // < operator could be comparing sums of visited places
    // Also need a hash function for unordered map
    /*
    unordered_map<State, int> TestMap;
    TestMap[state1] = 1;
    TestMap[state2] = 2;
    TestMap[state3] = 3;

    cout<<endl<<TestMap[state1];
    cout<<endl<<TestMap[state3];
    */

}

#endif