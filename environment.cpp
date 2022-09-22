#include <iostream>
#include <vector>

using namespace std;

class Room{
    private:
        int m, n;
        // 3D vector: map overlay, row, col
        // Map overlay: cleaning status, agent location
        vector<vector<vector<int>>> grid;

    public:
        Room(int m, int n){
            this->m = m;
            this->n = n;
            Reset();
        }

        void Reset(){
            grid.clear();
            grid.assign(2, vector(m, vector<int>(n, 0)));
            // Assign agent start location
            grid.at(1).at(0).at(0) = 1;
        }

        void Render(int layer){
            for(int i = 0; i <= grid.at(layer).size()-1; i++){
                for(int j = 0; j <= grid.at(layer).at(0).size()-1; j++){
                    cout<<grid.at(layer).at(i).at(j);
                }
                cout<<"\n";
            }
        }
};

int main(){
    Room TestRoom(6, 10);
    TestRoom.Render(0);
    cout<<"\n";
    TestRoom.Render(1);
}