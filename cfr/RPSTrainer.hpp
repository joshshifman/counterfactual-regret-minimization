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



struct Player{
    
public:
    vector<double> regretSum;
    vector<double> strategy;
    vector<double> strategySum;

    Player(){
        regretSum.resize(NUM_ACTIONS);
        strategy.resize(NUM_ACTIONS);
        strategySum.resize(NUM_ACTIONS);
    }
    Player(vector<double> strategyIn){
        regretSum.resize(NUM_ACTIONS);
        strategy.resize(NUM_ACTIONS);
        strategySum.resize(NUM_ACTIONS);

        strategy = strategyIn;
    }
};


class RPSTrainer{
    
private:
    
    /*
    vector<double> regretSum;
    vector<double> strategy;
    vector<double> strategySum;
    vector<double> villainStrat = {.4, .3, .3};
    */
    
    Player hero;
    Player villain;
    
    vector<double> getStrategy(Player player);
    
public:
    
    RPSTrainer(Player heroIn, Player villainIn){
        
        // Just implement a copy constructor instead
        
        hero.regretSum = heroIn.regretSum;
        hero.strategy = heroIn.strategy;
        hero.strategySum = heroIn.strategySum;
        
        villain.regretSum = villainIn.regretSum;
        villain.strategy = villainIn.strategy;
        villain.strategySum = villainIn.strategySum;
    }
    
    
    int getAction(vector<double> strat);
    void train(int iters);
    vector<vector<double>> getAvgStrategies();
};




#endif /* RPSTrainer_hpp */
