#include <vector>
#include <random> // for std::normal_distribution and std::default_random_engine

using namespace std;
#pragma once


class Slots{
// https://medium.com/@isurualagiyawanna/step-up-into-artificial-intelligence-and-reinforcement-learning-solving-the-multi-armed-bandit-d82b8b28544a
public:
    vector<double> slot_means;
    vector<double>  q_val;
    vector<int> times_used; // counter of times slot machiens was used
    int size=3;

    Slots(int num_slots) :
    q_val(num_slots, 0),
    times_used(num_slots, 0)
    {
        random_device rd;  // obtain a random seed from the hardware
        default_random_engine eng(rd());  // seed the generator

        // Define the range of the random numbers
        uniform_real_distribution<double> distr(1.0, 15.0); // random slot means betwen 1 and 15

        // Generate the random numbers and add them to the vector
        for (int i = 0; i < num_slots; i++) {
            double rand_num = distr(eng);  // generate a random number in the range [1, 10]
            slot_means.push_back(rand_num);
        }
    }

    int roll(int idx){
        // Create a random number generator with a normal distribution
        default_random_engine generator;
        normal_distribution<double> distribution(0.0, 3.0);
        double random_value = distribution(generator);
        update_vals(random_value + slot_means[idx], idx); // update internal counters
        return random_value + slot_means[idx];
    }

    void update_vals(double reward, int idx){
        times_used[idx] += 1;
        double step_size = 1/times_used[idx];
        q_val[idx] += step_size*(reward-q_val[idx]); // literally just updating the mean q = total_rewards / total_visits
    }
};