/*
    A solution for the knapsack problem using genetic algorithms
*/
#include <bits/stdc++.h>

using namespace std;

int main()
{
    srand(time(0));
    const int popSize = 1000;
    int t, n, s;
    cin>>t;
    int caseNum = t;
    while(t--) {
        cin>>n>>s;
        int weight[n];
        int value[n];
        for (int i=0;i<n;i++) {
            cin>>weight[i]>>value[i];
        }
        bool population[popSize][n];
        bool newPop[popSize][n];
        int fitness[popSize];
        int totalFitness = 0;
        int accum[popSize];
        int numIter = 50;
        //creating initial pop
        for(int i = 0; i < popSize; ++i){
            for(int j = 0; j < n; ++j){
                int r = rand()%2;
                population[i][j] = r;
                newPop[i][j] = r;
            }
        }

        for(int k = 0; k < numIter; ++k)//iterations for a single test case
        {
            // Fitness
            totalFitness = 0;
            for (int i=0;i<popSize;i++) {
                int sum = 0;
                int totalW = 0;
                for (int j=0;j<n;j++) {
                    if (population[i][j] && totalW + weight[j] < s) {
                        sum += value[j];
                        totalW += weight[j];
                    }
                    else if(population[i][j]){
                        population[i][j] = 0;
                    }
                }
                fitness[i] = sum;
                totalFitness += fitness[i];
                accum[i] = sum;
                if (i) {
                    accum[i] += accum[i-1];
                }
            }
            for (int i=0;i<popSize;i++) {
                accum[i] /= totalFitness;
            }
            // Selection Roulette Wheel
            int selected[popSize];
            for (int i=0;i<popSize;i++) {
                double r = ((double) rand() / (RAND_MAX));
                for (int j=0;j<popSize;j++){
                    if (accum[j] >= r) {
                        selected[i] = j;
                        break;
                    }
                }
            }

            // Cross Over
            for (int i=0;i<popSize-1;i+=2) {
                int r = rand() % 100;
                if ( r <= 70 ){
                    int p1 = rand() % n;
                    int p2 = rand() % n;
                    for (int j=min(p1,p2);j<max(p1,p2);j++) {
                        int temp = newPop[selected[i]][j];
                        newPop[selected[i]][j] = newPop[selected[i+1]][j];
                        newPop[selected[i+1]][j] = temp;
                    }
                }
            }
            // Mutation
            for (int i=0;i<popSize;i++) {
                for (int j=0;j<n;j++) {
                    int r = rand() % 100;
                    if ( r < 10 ) {
                        newPop[i][j] = !newPop[i][j];
                    }
                }
            }
            //Replacement
            //Generational(full) Replacement
 /*           for(int i = 0; i < popSize; ++i){
                for(int j = 0; j < n; ++j)
                    population[i][j] = newPop[i][j];
            }
           */
            //Steady-State Replacement
            int numReplacements = popSize * 0.7;
            while(numReplacements--){
                for(int i = 0; i < popSize; ++i){
                    int r = rand() % 10;
                    if (r < 5){
                        for(int j = 0; j < n; ++j)
                            population[i][j] = newPop[i][j];
                    }
                }
            }

        }//iterations for a single test case

        // Fitness
        for (int i=0;i<popSize;i++) {
            int sum = 0;
            int totalW = 0;
            for (int j=0;j<n;j++) {
                if (population[i][j] && totalW + weight[j] < s) {
                    sum += value[j];
                    totalW += weight[j];
                }
                else if(population[i][j]){
                    population[i][j] = 0;
                }
            }
            fitness[i] = sum;
        }

        int mostFit = 0;
        for(int i = 1; i < popSize; ++i)
            if(fitness[i] > fitness[mostFit])
                mostFit = i;

        cout << "Case " << caseNum - t << ": best value:" << fitness[mostFit] << endl;
        for(int i = 0; i < n; ++i){
            if(population[mostFit][i]){
                cout << "weight: " << weight[i] << ", value: " << value[i] << endl;
            }
        }
        /*
        for(int i = 0; i < n; ++i){
            cout << population[mostFit][i] << " ";
        }
        cout << endl;
        */

    }//loop for all test cases
}




