//
//  RPSTrainer.hpp
//  cfr
//
//  Created by Josh Shifman on 8/3/16.
//  Copyright © 2016 Josh Shifman. All rights reserved.
//

#ifndef RPSTrainer_hpp
#define RPSTrainer_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;


//constants
const int ROCK = 0;
const int PAPER = 1;
const int SCISSORS = 2;
const int NUM_ACTIONS = 3;



class RPSTrainer{
    
private:
    
    vector<double> regretSum;
    vector<double> strategy;
    vector<double> strategySum;
    vector<double> villainStrat = {.4, .3, .3};
    
    vector<double> getStrategy();
    
public:
    
    RPSTrainer(){
        regretSum.resize(NUM_ACTIONS);
        strategy.resize(NUM_ACTIONS);
        strategySum.resize(NUM_ACTIONS);
    }
    
    int getAction(vector<double> strat);
    void train(int iters);
    vector<double> getAvgStrategy();
    
    
    
};




#endif /* RPSTrainer_hpp */
