#include <iostream>
#include <vector>
#include <map>
#include <random>
#include "environment.h"

using namespace std;

class QAgent{
    private:
        float discount, learning_rate, exploration_factor;
        Room& env;
        map<vector<vector<int>>, map<int, float>> Q;
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dist_exp(0.0, 1.0);
        // TODO: make this dynamic to adapt to the action space
        uniform_int_distribution<> dist_actions(1, 5);

        int GetAction(vector<vector<int>> state){
            int action;

            if(dist(gen) < exploration_factor){
                action = GetRandomAction();
            }
            else{
                action = GetGreedyAction(state);
            }

            return action;
        }

        int GetGreedyAction(vector<vector<int>> state){
            int action;
            // TODO: find key for lowest value
            return action;
        }

        int GetRandomAction(){
            return dist_actions(gen);
        }

        void InitStateInQ(vector<vector<int>> state){
            // TODO: make dynamic action space
            for(int i = 1; i <= 5; i++){
                Q[state][i] = 0.0;
            }
        }

    public:
        QAgent(float discount, 
               float learing_rate, 
               float exploration_factor,
               Room& env) : env(env){
            this->discount = discount;
            this->learning_rate = learing_rate;
            this->exploration_factor = exploration_factor;
        }

        int TrainOneEpisode(){
            vector<vector<int>> state;
            int action;
            transition cTransition;
            int noSteps = 0;
            bool done = false;

            env.Reset()
            state = env.GetState();
            while(!done){
                // Initialize state in Q if it's new
                if(Q.find(state) == Q.end()){
                    InitStateInQ(state);
                }
                // action = GetAction(state);
                cTransition = env.Step(action);
                // UpdateQ(cTransition.oldState, cTransition.action, cTransition.reward, cTransition.newState);
                state = cTransition.newState;
                done = cTransition.done;
                noSteps += 1;
            }
            return noSteps;
        }
};