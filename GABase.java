/*
 * GABase.java
 *
 * Created on November 03, 2004, 4:33 PM
 * Last Modified Nov 04, 2004, 8.16AM
 * surveillance v1.0
 * Copyright (c) 2004 University of Wyoming
 */

package ga;

import java.util.Random;
import java.io.*;

import util.ConfigFile;

/**
 * Class GABase implements Base class for all GAs in surveillance. 
 * @version 	surveillance v1.0 22 July 2004
 * @author 	Suranga Hettiarachchi
 * @since       surveillance v1.0
 *
 */

public abstract class GABase{

   
    public final double weight = 1;
    public static double eMax = 20.0;
    public static double eMin = 1.0;
    
    public static double constMax = 10.0;
    public static double constMin = 1.0;
    
   /** maximum limit of force, default is 5.0 */
    public static double fMax = 5.0;
    
    /** minimum limit of force, default is 1.0 */
    public static double fMin = 1.0;
    
    /** maximum limit of gravity, default is 5000.0 */
    public static double gMax = 5000.0;
    
    /** minimum limit of gravity, default is 100.0 */
    public static double gMin = 100.0;
    
    /** maximum limit of power, default is 2.0 */
    public static double pMax = 2.0;
    
    /** minimum limit of power, default is 0.1 */
    public static double pMin = 0.1; 
    
    /** maximum limit of radius, default is 22.0 */
    public static double rMax = 22.0;
    
    /** minimum limit of radius, default is 5.0 */
    public static double rMin = 5.0;
    
    /** maximum limit of friction, default is 1.0 */
    public static double fricMax = 1.0;
    
    /** minimum limit of friction, default is 0.0 */
    public static double fricMin = 0.0;

    /** length of an individual, default is 10 */
    public static int length = 10;

    
    /** mutation rate of GA, default is 0.01 */
    public static double mutationRate = 0.01;
    
    /** cross over rate of GA, default is 0.6 */
    public static double crossOverRate = 0.6;     
       
    /** number of individuals in a population, default is 150 */
    public static int popSize = 2;    
    
    public static double mutationProbability = 1.0/length;
    
    /** Random instance for random number generator*/
    public static Random rnd;
    
    /** seed for the random number generator */
    public static long gaSeed = -1;
    
    /** population of popSize individuals */
    public double population[][];
    
    /** population of popSize individuals */
    public double population1[][];
    
    /** population of popSize individuals */
    public  double population2[][];
    
    /** number of children for each individual  */
    public int children[];
    
    /** shuffle the individuals around*/
    public int sh[];
    
    /** fitness of each individual*/
    public double fitness[];
    
    /** best individual in a population */
    public double best[];
    
    /** worst individual in a population */
    public double worst[];
    
    /** combine total fitenss of all the individulas in a population */
    public  double totalFitness;
    
    /** average fitness of the population, totalFitness/popSize */
    public double averageFitness;
    
    /** fitness of the best individual in a population */
    public  double bestValue;
    
    /** fitness of the worst individual in a population */
    public double worstValue;
    
    /** track for the change of best individual in a population */
    public boolean newBest;
    
    /** track for the change of worst individual in a population */
    public boolean newWorst;
    
    /** position of the best individual in a population */
    public  int bestIndex;
    
    /** position of the worst individual in a population */
    public int worstIndex;
    
     /** turns on/off graphic visuals for GA*/
    public boolean gaVisual;

    public GABase(){}
    /** 
     * constructor 
     * set common variables of all GAs
     *
     */
    public GABase(int len){
	length         = len;
	newBest        = false;
	newWorst       = false;
	totalFitness   = 0.0;
	averageFitness = 0.0;
	bestValue      = 0.0;
	worstValue     = 10000000.0;
	bestIndex      = -1;
	worstIndex     = -1;
    }
    
    /** average fitness = total fitness / population size  */
    public void findAvgFitness()
    {
	averageFitness = totalFitness / (double) popSize;
	
    }
    
    /** 
     * compute number of children for each individual in the population.
     * this is Stochastic Universal Sampling.    
     */
    public void offspring(){
	
	double prior = 0.0;
	int index = 0;
	int count = 0;
	double r = rnd.nextDouble();
	
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
     * initialize fitness, children arrays, and totalFitness, averageFitness to 0
     * necessary to have initial values at the beginning of every generation
     */
    public void reinitData(){
	
	for (int i = 0; i < popSize; ++i)
	    {
		fitness[i] = 0.0;
		children[i] = 0;
	    }
	totalFitness = 0.0;
	averageFitness = 0.0;
    }
    
    
    /** set the fitenss of individual at index with the given value */ 
    public void setFitness(int index, double value){
	//System.out.println(value);
	fitness[index] = value;
    }

    /** compute and set the totalFitness of this population in this generation
     *  also finds the current best individual and current worst individual of this population
     *  best and worst is picked based on the fitness value of the individual
     */
    public void computeTotalFitness(){
	
	for (int index = 0; index<popSize; index++)
	    {
		totalFitness += fitness[index];
		
		if (fitness[index] > bestValue) 
		    {
			newBest = true;
			copyBest(index);
			bestValue = fitness[index];
		    }
		
		/*if (fitness[index] < worstValue) 
		    {
			newWorst = true;
			copyWorst(index);
			worstValue = fitness[index];
		    }
		*/
		
	    }
    }
    
    
    /**
     *one point crossover at a rate of crossOverRate   
     */
    public void recombination(){
	
	for (int i = 0; i < crossOverRate*popSize; i+=2)
	    {
		int cross = rrand(0, length);
		
		for (int j = cross; j < length; ++j)
		    {
			crossSwap(i, i+1, j);           
		    }
	    }
	saveBest();
    }



    /** create the population for next generation */
    public void createNewPopulation(){

	int index = 0;
	
	for (int i = 0; i < popSize; ++i)
	    {
		for (int j = 0; j < children[i]; ++j)
		    {
			
			double temp[][]=new double[popSize][length];
			
			if (population == population1)
			    {
				temp = population2;
				
			    }
			else
			    {
				temp = population1;           
			    }
			
			sh[index] = i;
			
			for (int k = 0; k < length; ++k)
			    {
				temp[index][k] = population[i][k];             
			    }
			
			++index;
		    }
	    }
	
	swapPops();
	shuffle();
	
    }
    
    /** * keep the best individual on the top of the population */
    public void saveBest(){
	
	for (int i = 0; i < length; ++i)
	    {
		population[0][i] = best[i];
	    }
    }
    
    /** saves the best individual of this population residing at given index */
    public void copyBest(int index){
	
	bestIndex = index;
	best = (double[])population[index].clone(); 
	
    }
    
    /** copy the worst individual of this population */
    public void copyWorst(int index){
	
	worstIndex = index;
	worst = (double[])population[index].clone(); 
	    
    }
    
    
    public void swapPops(){
	
	if (population == population1)
	    population = population2;
	else
	    population = population1;
	
    }
    
    public void swap (int i, int j){
	
	int temp;
	
	temp = sh[i];
	sh[i] = sh[j];
	sh[j] = temp;
	
    }
    
    public void shuffle (){
	
	for (int i = 0; i < popSize; ++i)
	    {
		int temp = rrand(0, popSize);	
		swap(i, temp);
	    }
	
    }
    
    public void crossSwap(int ind1, int ind2, int point){
	
	double save = population[sh[ind1]][point];
	population[sh[ind1]][point] = population[sh[ind2]][point];
	population[sh[ind2]][point] = save;
    }
    
    
    public void showBest(PrintWriter bestworstoutfile, int gen){

	if (newBest)
	    {  
		bestworstoutfile.write("\n");
		
		if (bestIndex != -1)
		    bestworstoutfile.write("BEST  " + gen + "   " + bestIndex + "  ");
		
		for (int i = 0; i < length; ++i)
		    {
			bestworstoutfile.write(best[i] + "    ");
		    }
		
		bestworstoutfile.write("  "+bestValue);
		newBest = false;
		bestIndex = -1;
		
	    }
    }
    
    public static int getPopulationSize(){
	
	return popSize;
	
    }
    
    public boolean getGAVisual(){
	
	return gaVisual;
	
    }
    
    public void showWorst(PrintWriter bestworstoutfile, int gen){

	if (newWorst)
	    {  
		bestworstoutfile.write("\n");
		
		if (worstIndex != -1)
		    bestworstoutfile.write("WORST  " + gen + "   " + worstIndex + "  ");
		
		for (int i = 0; i < length; ++i)
		    {
			bestworstoutfile.write(worst[i] + "    ");
		    }
		
		bestworstoutfile.write("  "+worstValue);
		newWorst = false;
		worstIndex = -1;
		
	    }
    }
    
    
    
    
    public void showBestScreen(){

	if (newBest)
	    {
		System.out.print("The best individual so far: ");
		
		for (int i = 0; i < length; ++i)
		    {
			System.out.print(best[i] + "    ");
		    }
		
		System.out.print("  "+bestValue);
		System.out.print("\n");
		newBest = false;
		System.out.print("\n\n");
		
	    }
    }
    
    public void outputPopulation(PrintWriter out, int counter)
    {
	
	out.write("The current population: " + counter+ "\n");
	for (int i = 0; i < popSize; ++i)
	    {
		for (int j = 0; j < length; ++j)
		    {
			out.write(population[i][j] +"    ");
		    }
		out.write(" "+fitness[i]);
		out.write("\n");
	    }
	out.write("\n\n");
	
    }
    
    
    public void outputPopulationScreen(int counter){
	
	System.out.println("The current population: " + counter + "\n");
	
	for (int i = 0; i < popSize; ++i)
	    {
		for (int j = 0; j < length; ++j)
		    {
			System.out.print(population[i][j] +"    ");
		    }
		
		System.out.print(" "+fitness[i]);
		System.out.println("\n");
	    }
	
	System.out.println();
	
    }
    
    public double rand_data(double max, double min){
	
	double value = min + rnd.nextDouble()*(max-min);
	return value;
    }
    
    public double randDataForRmin(double max, double min, double maxValue){ // if the data range is too small, this may cause problems
	
	double value = min + rnd.nextDouble()*(max-min);
	while (value > maxValue)
	    value = min + rnd.nextDouble()*(max-min);
	return value;
    }
    
    public int rrand(int min, int max){
	
	return(min + (int)(rnd.nextDouble() * (max - min)));
    }
    
    public boolean flip(){
	
	if (rnd.nextDouble() < 0.5)
	    return true;
	else
	    return false;
    }
    
    public boolean getNewBest(){
	return newBest;
    }

    public void loadCommonConfig(ConfigFile con){

	popSize = con.getInt("populationsize");
	length = con.getInt("length");
	fMax = con.getDouble("fmax");
	fMin = con.getDouble("fmin");
	gMax = con.getDouble("gmax");
	gMin = con.getDouble("gmin");
	pMax = con.getDouble("pmax");
	pMin = con.getDouble("pmin");
	rMax = con.getDouble("rmax");
	rMin = con.getDouble("rmin");
	mutationRate = con.getDouble("mutationrate");
	crossOverRate = con.getDouble("crossoverrate");
	gaSeed = con.getLong("gaseed"); 
	gaVisual = con.getBoolean("gavisual");
	
    }

    public abstract void gaussianMutation();
}
