#include <iostream>
#include "environment.h"
#include "qagent.h"

using namespace std;

int main(){
    Room env(6, 10);
    QAgent agent(0.99, 0.01, 0.1, env);
}