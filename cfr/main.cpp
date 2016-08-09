//
//  main.cpp
//  cfr
//
//  Created by Josh Shifman on 8/3/16.
//  Copyright © 2016 Josh Shifman. All rights reserved.
//

#include <iostream>
#include <vector>

#include "RPSTrainer.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    
    Player hero({.1, .6, .3});
    Player villain({.1, .6, .3});
    
    RPSTrainer trainer(hero, villain);
    trainer.train(1);
    
    vector<vector<double>> avgs = trainer.getAvgStrategies();
    
    for (auto strat : avgs){
        for(auto i : strat){
            cout << i << endl;
        }
        cout << endl;
    }
    return 0;
}
