//
//  ga.c
//  
//
//  Created by Hettiarachchi, Suranga D on 6/25/15.
//
//

//arraycmd contains function number
//arrayvb contains the user entered variables
//arraycst contains the user entered constants
//arraylen length of the array.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <string.h>


typedef enum { false, true } boolean;

//Global variables

/** length of the individual **/
 int length = 3;

/** mutation rate of GA, default is 0.01 */
 double mutationRate;

/** cross over rate of GA, default is 0.6 */
 double crossOverRate = 0.6;

/** number of individuals in a population, default is 100 */
int popSize = 100;


/** Random instance for random number generator*/
 //Random rnd;

/** seed for the random number generator */
 long gaSeed = -1;

/** population of popSize individuals */
 double **population;

/** population of popSize individuals */
 double **population1 ;

/** population of popSize individuals */
 double **population2;

/** number of children for each individual  */
 int *children ;

/** shuffle the individuals around*/
 int *sh ;

/** fitness of each individual*/
  double *fitness ;

/** best individual in a population */
 double *best;

/** worst individual in a population */
 double *worst;

/** combine total fitenss of all the individulas in a population */
 double totalFitness;

/** average fitness of the population, totalFitness/popSize */
 double averageFitness;

/** fitness of the best individual in a population */
 double bestValue;

/** track for the change of best individual in a population */
 boolean newBest;

/** position of the best individual in a population */
 int bestIndex;




void init(){
    mutationRate = 1.0/length;
    newBest        = false;
    totalFitness   = 0.0;
    averageFitness = 0.0;
    bestValue      = 0.0;
    bestIndex      = -1;
    population     = malloc(sizeof(double[popSize][length]));
    population1    = malloc(sizeof(double[popSize][length]));
    population2    = malloc(sizeof(double[popSize][length]));
    fitness        = malloc(sizeof(double[popSize]));
    children       = malloc(sizeof(int[popSize]));
    sh             = malloc(sizeof(int[popSize]));
    best           = malloc(sizeof(double[length]));
    worst          = malloc(sizeof(double[length]));
    population     = population1;
    
    for (int i = 0; i < popSize; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            double value = ((double)rand()/(double)(RAND_MAX));
            population1[i][j] = value;
            population2[i][j] = value;
        }
        fitness[i] = 0.0;
        children[i] =  0;
    }
    srand(time(NULL));
    
}

 /** average fitness = total fitness / population size  */
void findAvgFitness()
{
    averageFitness = totalFitness / (double) popSize;
    
}
/**
 * compute number of children for each individual in the population.
 * Uses Stochastic Universal Sampling.
 */
void offspring(){
    
    double prior = 0.0;
    int index = 0;
    int count = 0;
    double r = ((double)rand()/(double)(RAND_MAX));
    
    prior = fitness[0] / averageFitness;
    fitness[0] = prior;
    
    for (int i = 1; i < popSize; ++i)
    {
        fitness[i] = ((double) fitness[i] / averageFitness) + prior;
        prior = fitness[i];
        
    }
    
    while (count < popSize)
    {
        
        if (r < fitness[index] )
        {
            children[index]++;
            count++;
            r += 1.0;
        }
        else
        {
            index++;
        }
    }
    
}

/**
 * sets fitness array, children array, and totalFitness, averageFitness to 0
 * Initial values at the beginning of every generation is needed.
 */
void reinitData(){
    
    for (int i = 0; i < popSize; ++i)
    {
        fitness[i] = 0.0;
        children[i] = 0;
    }
    totalFitness = 0.0;
    averageFitness = 0.0;
}

/** set the fitenss of an individual with the given value */
void setFitness(int index, double value){
    fitness[index] = value;
}



/** saves the best individual of this population residing at given index */
void copyBest(int index){
    
    bestIndex = index;
    for (int i = 0; i < length; ++i)
    {
        best[i] = population[index][i];
    }
  

}

/** compute and set the totalFitness of this generation.
 *  finds the current best individual
 */
void computeTotalFitness(){
    
    for (int index = 0; index<popSize; index++)
    {
        totalFitness += fitness[index];
        
        if (fitness[index] > bestValue)
        {
            newBest = true;
            copyBest(index);
            bestValue = fitness[index];
        }
        
    }
}

/* populations are swaped from generation to generation */
void swapPops(){
    
    if (population == population1)
        population = population2;
    else
        population = population1;
    
}


void swap (int i, int j){
    
    int temp;
    temp = sh[i];
    sh[i] = sh[j];
    sh[j] = temp;
    
}

/* shuffling to maintain diversity */
void shuffle (){
    
    for (int i = 0; i < popSize; ++i)
    {
        
        int temp =  rand() % popSize;
        swap(i, temp);
    }
    
}


void crossswap(int ind1, int ind2, int point){
    
    double save = population[sh[ind1]][point];
    population[sh[ind1]][point] = population[sh[ind2]][point];
    population[sh[ind2]][point] = save;
}

/** * keep the best individual on the top of the population, elitist! */
void saveBest(){
    
    for (int i = 0; i < length; ++i)
    {
        population[0][i] = best[i];
    }
}

/**
 *one point crossover at a rate of crossOverRate
 */
 void recombination(){
    
    for (int i = 0; i < crossOverRate*popSize; i+=2)
    {
        int cross = rand() % length;
        
        for (int j = cross; j < length; ++j)
        {
            crossswap(i, i+1, j);
        }
    }
    saveBest();
}


/* check the mutated individuals for their validity.
 * all values should be within original ranges as specified in conf file.
 */
boolean legalBound(double *individual)
{
    
    boolean validBound = true;
    int j;
    
    for (j =0; j<length && validBound; j++)
    {
        // bound checking should happen here.
    }
    return validBound;
}


/* Mutation operator.
 * Uses Gaussian mutation with mean 0.0 and std 1.0
 * Every allel is mutated with 1/length rate.
 * Last worked 07/01/2015. NOT DONE !!!
 */
void gaussianMutation()
{
    
    double *new_individual;
    int i, j;
    
    for (i = 0; i < popSize; ++i)
    {
        
        int mutated = 0;
        new_individual = malloc(sizeof(double[length]));
        
        
        for ( j = 0; j < length; ++j)
        {
            new_individual[j] = population[i][j]; // copy the individual to be mutated
        }
        
        for (j=0; j<length; j++) // mutate the copy
        {
            if ( ((double)rand()/(double)(RAND_MAX)) <= mutationRate){ // mutProb = 1/L, may use mutationRate
                new_individual[j] +=  0.01; // 0.01 reduces stepsize
                mutated++;
            }
            
        }
        if (mutated > 0)
            if (legalBound(new_individual)){ // bound checking of value range
                for ( j = 0; j < length; ++j)
                {
                    population[i][j] = new_individual[j]; //copy the individual back to population
                }
            }
        
    }
}



int main(){
    return 0;
}


