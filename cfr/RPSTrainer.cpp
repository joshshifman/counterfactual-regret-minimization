//
//  RPSTrainer.cpp
//  cfr
//
//  Created by Josh Shifman on 8/3/16.
//  Copyright © 2016 Josh Shifman. All rights reserved.
//

#include "RPSTrainer.hpp"


vector<double> RPSTrainer::getStrategy(Player player){
    
    double normSum = 0;
    
    for (int i = 0; i < NUM_ACTIONS; i++){
        player.strategy[i] = (player.regretSum[i] > 0) ? player.regretSum[i] : 0;
        normSum += player.strategy[i];
    }
    for (int i = 0; i < NUM_ACTIONS; i++){
        if (normSum){
            player.strategy[i] /= normSum;
        }
        else{
            player.strategy[i] = 1.0 / NUM_ACTIONS;
        }
        player.strategySum[i] += player.strategy[i];
    }
    return player.strategy;
}

int RPSTrainer::getAction(vector<double> strat){
    
    //seed
    srand((unsigned)time(NULL));
    double r = rand() / (RAND_MAX + 1.);
    
    int i = 0;
    double cumulativeProb = 0;
    while (i < NUM_ACTIONS - 1) {
        cumulativeProb += strat[i];
        if (r < cumulativeProb){
            break;
        }
        i++;
    }
    return i;
}

void RPSTrainer::train(int iters){
    vector<double> heroActionUtils(NUM_ACTIONS);
    vector<double> villainActionUtils(NUM_ACTIONS);
    
    for (int i = 0; i < iters; i++){
        
        // get strategies/actions
        vector<double> heroStrategy = getStrategy(hero);
        vector<double> villainStrategy = getStrategy(villain);
        int heroAction = getAction(heroStrategy);
        int villainAction = getAction(villainStrategy);
        
        // compute action utilities
        heroActionUtils[villainAction] = 0;
        heroActionUtils[villainAction == NUM_ACTIONS - 1 ? 0: villainAction + 1] = 1;
        heroActionUtils[villainAction == 0 ? NUM_ACTIONS - 1 : villainAction - 1] = -1;
        
        villainActionUtils[heroAction] = 0;
        villainActionUtils[heroAction == NUM_ACTIONS - 1 ? 0: heroAction + 1] = 1;
        villainActionUtils[heroAction == 0 ? NUM_ACTIONS - 1 : heroAction - 1] = -1;
        
        //accumulate regrets
        for (int i = 0; i < NUM_ACTIONS; i++){
            hero.regretSum[i] += heroActionUtils[i] - heroActionUtils[heroAction];
            villain.regretSum[i] += villainActionUtils[i] - villainActionUtils[villainAction];
        }
    }
}

vector<vector<double>> RPSTrainer::getAvgStrategies(){
    vector<double> avgStrategyHero(NUM_ACTIONS);
    vector<double> avgStrategyVillain(NUM_ACTIONS);
    double normSumHero = 0;
    double normSumVillain = 0;
    
    
    for (int i = 0; i < NUM_ACTIONS; i++){
        normSumHero += hero.strategySum[i];
        normSumVillain += villain.strategySum[i];
    }
    for (int i = 0; i < NUM_ACTIONS; i++){
        if (normSumHero > 0){
            avgStrategyHero[i] = hero.strategySum[i] / normSumHero;
        }
        else{
            avgStrategyHero[i] = 1.0 / NUM_ACTIONS;
        }
        if (normSumVillain > 0){
            avgStrategyVillain[i] = villain.strategySum[i] / normSumVillain;
        }
        else{
            avgStrategyVillain[i] = 1.0 / NUM_ACTIONS;
        }
        
    }
    vector<vector<double>> strategies(2);
    strategies[0] = avgStrategyHero;
    strategies[1] = avgStrategyVillain;
    
    return strategies;
}
