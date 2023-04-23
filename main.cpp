#include "agent.h"
#include "slots.h"

int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 5);
    std::vector<double> q(10);
    // std::vector<double> q{1, 2, 1.5};

    for (int i = 0; i < q.size(); i++) {
        q[i] = dist(gen);
    }


    Slots *s = new Slots(10, q);
    Agent* agent = new Agent(10);
    agent->run_experiment(s);
    return 1;
}
