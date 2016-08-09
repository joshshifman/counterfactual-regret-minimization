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
    
    RPSTrainer trainer;
    trainer.train(1000);
    
    vector<double> avg = trainer.getAvgStrategy();
    
    for (auto i : avg)
        cout << i << endl;
    
    return 0;
}
