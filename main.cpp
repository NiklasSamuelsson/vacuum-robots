#include <iostream>
#include "environment.h"
#include "qagent.h"

using namespace std;

int main(){
    Room env(1, 3);
    QAgent agent(0.99, 0.01, 0.1, env);

    cout<<"TRAINING STARTING"<<endl;
    int noSteps;
    for(int i = 0; i<1000; i++){
        noSteps = agent.RunOneEpisode(true);
        cout<<"Episode "<<i<<". No steps "<<noSteps<<endl;
    }

    cout<<endl<<"TESTING STARTING"<<endl;
    for(int i = 0; i<100; i++){
        noSteps = agent.RunOneEpisode(false);
        cout<<"Episode "<<i<<". No steps "<<noSteps<<endl;
    }
    
}