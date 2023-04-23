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
    int num_slots;

    Agent(int num_slots, int iters=1000) : num_slots(num_slots), times_used(num_slots, 1), iterations(iters) { // times used start at 1 to avoid divide by zero

    }

    void run_experiment(Slots* slots, string optimizer="epsilon greedy", float epsilon=0.3, float c=0.125){ //epsilon gredy, ucb
        // if random number is less than epsilon we choose a random arm else choose the highest q arm
        double cumulative_reward=0;
        double max_q_value = 0;

        for(int n=0; n < iterations; n++){
            int idx = -1;
            max_q_value = 0;

            if(optimizer == "epsilon greedy"){
                random_device rd;
                mt19937 gen(rd());
                uniform_real_distribution<> dis(0.0, 1.0);
                double random_number = dis(gen);

                if (epsilon > random_number){
                    // if random number less than epsilon choose a random index
                    uniform_real_distribution<> dis_idx(0.0, num_slots);
                    idx = dis_idx(gen);
                } else {
                    for(int i=0; i < num_slots; i++){
                        if(slots->q_vals[i] > max_q_value){
                            max_q_value = slots->q_vals[i]; // issue is values are becoming negative
                            idx = i;
                        }
                    }
                }

            } else {
                // https://www.geeksforgeeks.org/upper-confidence-bound-algorithm-in-reinforcement-learning/
                double max_q_value = 0;
                // cout << num_slots << endl;
                for(int i=0; i<num_slots; i++){
                    double candidate = slots->q_vals[i] + c * sqrt(log(n+1)/times_used[i]);
                    // cout << candidate << endl;
                    if(candidate > max_q_value){
                        idx = i;
                        max_q_value = candidate;
                        // cout << idx << endl;

                    }
                }
            }
            assert(idx >= 0);
            // cout << idx << endl;
            double reward = slots->roll(idx);
            cumulative_reward += reward;
            times_used[idx] += 1;

            if((n) % 1 == 0){
                cout << n << ", " << cumulative_reward/(slots->total_sum) << endl;
                cumulative_reward = 0;
            }
        }
        

    }
};