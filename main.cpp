#include "agent.h"
#include "slots.h"

int main(){
    Slots *s = new Slots(10);
    Agent* agent = new Agent(10);
    agent->run_experiment(s);
    return 1;
}
