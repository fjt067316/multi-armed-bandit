#include <vector>
#include <random> // for std::normal_distribution and std::default_random_engine
#include <cassert>
#include <iostream>

#include "slots.h"
using namespace std;
#pragma once

class Agent{
public:
    vector<int> times_used; // counter of times slot machiens was used
    int iterations;

    Agent(int num_slots, int iters=1000) : times_used(num_slots, 0), iterations(iters) {

    }

    void run_experiment(Slots* slots, string optimizer="epsilon gredy", float epsilon=0.1){ 
        // if random number is less than epsilon we choose a random arm else choose the highest q arm
        double cumulative_reward;
        for(int n=0; n < iterations; n++){
            if(optimizer == "epsilon gredy"){
                random_device rd;
                mt19937 gen(rd());
                uniform_real_distribution<> dis(0.0, 1.0);
                int idx = -1;
                double random_number = dis(gen);

                if (epsilon > random_number){
                    // if random number less than epsilon choose a random index
                    uniform_real_distribution<> dis_idx(0.0, slots->size);
                    idx = dis_idx(gen);
                } else {
                    double max_q_value = INT64_MIN;
                    for(int i=0; i < times_used.size(); i++){
                        if(slots->q_val[i] > max_q_value){
                            max_q_value = slots->q_val[i];
                            idx = i;
                        }
                    }
                }
                assert(idx >= 0);
                double reward = slots->roll(idx);
                cumulative_reward += reward;
            }

            if((n+1) % 10 == 0){
                cout << (n+1)/10 << ", " << cumulative_reward/10 << endl;
                cumulative_reward = 0;
            }
        }
        

    }
};