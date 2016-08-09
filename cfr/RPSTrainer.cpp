//
//  RPSTrainer.cpp
//  cfr
//
//  Created by Josh Shifman on 8/3/16.
//  Copyright © 2016 Josh Shifman. All rights reserved.
//

#include "RPSTrainer.hpp"


vector<double> RPSTrainer::getStrategy(){
    
    double normSum = 0;
    
    for (int i = 0; i < NUM_ACTIONS; i++){
        strategy[i] = (regretSum[i] > 0) ? regretSum[i] : 0;
        normSum += strategy[i];
    }
    
    for (int i = 0; i < NUM_ACTIONS; i++){
        if (normSum){
            strategy[i] /= normSum;
        }
        else{
            strategy[i] = 1.0 / NUM_ACTIONS;
        }
        strategySum[i] += strategy[i];
    }
    
    return strategy;
}

int RPSTrainer::getAction(vector<double> strat){
    
    //seed
    srand((unsigned)time(NULL));
    double r = rand() / (RAND_MAX + 1.);
    
    int i = 0;
    double cumulativeProb = 0;
    while (i < NUM_ACTIONS - 1) {
        cumulativeProb += strategy[i];
        if (r < cumulativeProb){
            break;
        }
        i++;
    }
    return i;
}

void RPSTrainer::train(int iters){
    vector<double> actionUtils(NUM_ACTIONS);
    for (int i = 0; i < iters; i++){
        
        // get strategies/actions
        vector<double> strategy = getStrategy();
        int myAction = getAction(strategy);
        int villainAction = getAction(villainStrat);
        
        // compute action utilities
        actionUtils[villainAction] = 0;
        actionUtils[villainAction == NUM_ACTIONS - 1 ? 0: villainAction + 1] = 1;
        actionUtils[villainAction == 0 ? NUM_ACTIONS - 1 : villainAction - 1] = -1;
        
        //accumulate regrets
        for (int i = 0; i < NUM_ACTIONS; i++){
            regretSum[i] += actionUtils[i] - actionUtils[myAction];
        }
    }
}

vector<double> RPSTrainer::getAvgStrategy(){
    vector<double> avgStrategy(NUM_ACTIONS);
    double normSum = 0;
    
    for (int i = 0; i < NUM_ACTIONS; i++){
        normSum += strategySum[i];
    }
    for (int i = 0; i < NUM_ACTIONS; i++){
        if (normSum > 0){
            avgStrategy[i] = strategySum[i] / normSum;
        }
        else{
            avgStrategy[i] = 1.0 / NUM_ACTIONS;
        }
    }
    return avgStrategy;
}
