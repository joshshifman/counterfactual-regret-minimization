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
    vector<double> strat;
    vector<double> stratSum;
    vector<double> oppStrat = {.4, .3, .3};
    
    vector<double> getStrat();
    
public:
    
    vector<double> getAction(vector<double> strat);
    void train(int iters);
    vector<double> getAvgStrat();
    
    
    
};




#endif /* RPSTrainer_hpp */
