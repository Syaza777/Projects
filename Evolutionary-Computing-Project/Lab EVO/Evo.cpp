#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

const int GENE = 16;
const int POP_SIZE = 30;
const float CROSSOVER_PROBABILITY = 0.8;
const float MUTATION_PROBABILITY = 0.3;
const int MAXIMUM_GENERATION = 80;
//new const variable
const int LIMIT_MELODY = 150;//limit melody
const int MIN_SMOOTHNESS = 7000;
const int FREQUENCY[12][8] = { {32,65,130,261,523,1047,2093,4168},
							   {34,69,138,277,554,1109,2217,4435},
							   {36,73,146,293,587,1175,2349,4699},
							   {38,77,155,311,622,1245,2489,4978},
							   {41,82,164,329,659,1319,2637,5274},
							   {43,87,174,349,698.1397,2794,5588},
							   {46,92,185,369,739,1480,2960,5920},
							   {49,98,196,392,784,1568,3136,6272},
							   {52,104,208,415,830,1661,3322,6645},
							   {55,110,220,440,880,1760,3520,7040},
							   {58,116,233,466,932,1865,3729,7459},
							   {61,123,246,493,987,1976,3951,7905} }; //{ {},{},{},{},{},{},{},{},{},{},{},{} }; template

const string NOTES[12][8] = { {" C1"," C2"," C3"," C4"," C5"," C6"," C7"," C8"},
							  {"C#1","C#2","C#3","C#4","C#5","C#6","C#7","C#8"},
							  {" D1"," D2"," D3"," D4"," D5"," D6"," D7"," D8"},
							  {"D#1","D#2","D#3","D#4","D#5","D#6","D#7","D#8"},
							  {" E1"," E2"," E3"," E4"," E5"," E6"," E7"," E8"},
							  {" F1"," F2"," F3"," F4"," F5"," F6"," F7"," F8"},
							  {"F#1","F#2","F#3","F#4","F#5","F#6","F#7","F#8"},
							  {" G1"," G2"," G3"," G4"," G5"," G6"," G7"," G8"},
							  {"G#1","G#2","G#3","G#4","G#5","G#6","G#7","G#8"},
							  {" A1"," A2"," A3"," A4"," A5"," A6"," A7"," A8"},
							  {"A#1","A#2","A#3","A#4","A#5","A#6","A#7","A#8"},
							  {" B1"," B2"," B3"," B4"," B5"," B6"," B7"," B8"} };

float fitnessValue[POP_SIZE];
int chromosome[POP_SIZE][GENE];
int parents[2][GENE];
int children[2][GENE];
int mutaChild[2][GENE];
int survivor[POP_SIZE][GENE];
int counterSurvivor;

//Notes
string chromosomeNotes[POP_SIZE][GENE];
string parentsNotes[2][GENE];
string childrenNotes[2][GENE];
string mutaChildNotes[2][GENE];
string survivorNotes[POP_SIZE][GENE];

double averageFitness = 0;
double bestFitness = 2;
int bestChromosome[GENE];
string bestChromosomeNotes[GENE];//NOTES
ofstream ACP_File("ACP_File.txt");
ofstream BSF_File("BSF_File.txt");
ofstream bestChromosome_File("bestChromosome_File.txt");
ofstream bestChromosomeNotes_File("bestChromosomeNotes_File.txt");
//QUESTION 3 lab5

void initializePopulation() {
	//1. For every chromosome, c
	//1.1 For every genes, g, in the chromosome, c
	//1.1.1 Generate either 0 or 1
	//1.1.2 Assign to the g of c
	int randomRow = 0, randomColumn = 0;

	for (int c = 0; c < POP_SIZE; c++)
	{
		for (int g = 0; g < GENE; g++)
		{
			randomRow = rand() % 12;
			randomColumn = rand() % 8;
			chromosome[c][g] = FREQUENCY[randomRow][randomColumn];
			chromosomeNotes[c][g] = NOTES[randomRow][randomColumn];
			//if %2 = 0/1
			//if %10 = 0~9
		}
	}
}

void printChromosome() {
	//1. For every chromosome, c
	//1.1 Print Chromosome number
	//1.2 For every genes g, in the chromosome, c
	//1.2.3 Print g of c

	for (int c = 0; c < POP_SIZE; c++)
	{
		cout << "\t" << "C" << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)//print FREQUENCY
		{
			cout << chromosome[c][g] << " ";
		}
		cout << endl;
		cout << "\tN" << c + 1 << ": ";
		for (int i = 0; i < GENE; i++)//print NOTES
		{
			cout << chromosomeNotes[c][i] << " ";
		}
		cout << endl;
	}
}

void evaluateChromosome()
{
	//1. For every chromosome, c 
	//1.1 set accumulatedWeight to 0 
	//1.2 set accumulatedValue to 0 
	//1.2 for every genes, g in chromosome c  

	int smoothness, totalSmoothness, totalMelody, melody, totalFrequency;
	string melodyDesc;

	for (int c = 0; c < POP_SIZE; c++)
	{
		cout << "\n\tC" << c + 1 << ":";
		totalSmoothness = 0, totalMelody = 0, totalFrequency = 0;
		for (int g = 1; g < GENE; g++)
		{
			melody = 0, smoothness = 0;
			smoothness = chromosome[c][g] - chromosome[c][g - 1];
			totalFrequency = totalFrequency + chromosome[c][g];
			if (smoothness < 0)////modulus
				smoothness = smoothness * -1;
			totalSmoothness = totalSmoothness + smoothness;
			if (chromosome[c][g - 1] < chromosome[c][g])
			{
				melody = 4;//high
			}
			else if (chromosome[c][g - 1] > chromosome[c][g])
			{
				melody = 5;//fall
			}
			else
			{
				melody = 1;//stable
			}
			totalMelody = totalMelody + melody;
		}
		cout << "\tTotal Smoothness: " << totalSmoothness;
		cout << "\tTotal Melody: " << totalMelody;
		if (totalMelody < LIMIT_MELODY || totalSmoothness < MIN_SMOOTHNESS)
			fitnessValue[c] = (totalSmoothness / (float)totalFrequency) * 1.5; //penalty
		else
			fitnessValue[c] = totalSmoothness / (float)totalFrequency;

		cout << "\n\tFitness Value: " << fitnessValue[c];
	}
}

void parentSelection()
{
	//declare necessary variables
	//1. For the first parent
	//1.1 Pick a random number to be the index for player 1
	//1.2 Pick another random number to be the index for player 2
	//1.3 Compare fitness between player 1 and 2, pick the best one to be parent 1
	//2. Repeat (1) for parent 2
	//3. Print parent 1 & 2
	//NOTE: After you done, improve your code to avoid the same number picked for
	//player 1 and player 2, and also avoid the same chromosome picked for parent 1
	//and 2

	int IndexPlayer1, IndexPlayer2;
	int winner[2];

	do {
		for (int p = 0; p < 2; p++)
		{
			do {
				IndexPlayer1 = rand() % POP_SIZE;
				IndexPlayer2 = rand() % POP_SIZE;
			} while (IndexPlayer1 == IndexPlayer2);
			cout << "\nRound " << p + 1;
			cout << "\n\t Player 1: " << IndexPlayer1 + 1 << "\n\t Player 2: " << IndexPlayer2 + 1;
			if (fitnessValue[IndexPlayer1] < fitnessValue[IndexPlayer2])
			{
				winner[p] = IndexPlayer1;
				cout << "\nwinner: " << IndexPlayer1 + 1 << endl;
			}
			else
			{
				winner[p] = IndexPlayer2;
				cout << "\nwinner: " << IndexPlayer2 + 1 << endl;
			}
		}
	} while (winner[0] == winner[1]);
	cout << "\nResult";
	for (int c = 0; c < 2; c++)
	{
		cout << "\n\tParents " << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			parents[c][g] = chromosome[winner[c]][g];
			cout << parents[c][g] << " ";
		}
		//notes parent
		cout << "\n\tParents Notes" << c + 1 << ": ";
		for (int h = 0; h < GENE; h++)
		{
			parentsNotes[c][h] = chromosomeNotes[winner[c]][h];
			cout << parentsNotes[c][h] << " ";
		}
	}
}

void crossover()//1-point
{
	float randomValue;
	int crossoverPoint = 0;
	//copy parents to children
	for (int r = 0; r < 2; r++)
	{
		for (int g = 0; g < GENE; g++)
		{
			children[r][g] = parents[r][g];
			childrenNotes[r][g] = parentsNotes[r][g];
		}
	}//copy
	//before crossover
	cout << "\nBefore Crossover";
	for (int c = 0; c < 2; c++)
	{
		cout << "\n\tChildren " << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << children[c][g] << " ";
		}
		cout << "\n\t   Notes " << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << childrenNotes[c][g] << " ";
		}
	}
	randomValue = (rand() % 10) / 10.0;
	cout << "\n\tRandom Value = " << randomValue;
	//2.1 generate a random crossover point
	if (randomValue < CROSSOVER_PROBABILITY)
	{
		crossoverPoint = rand() % GENE;
		cout << "\n\tRandom point = " << crossoverPoint;
		for (int c = crossoverPoint; c < GENE; c++)
		{
			children[0][c] = parents[1][c];
			children[1][c] = parents[0][c];
			childrenNotes[0][c] = parentsNotes[1][c];
			childrenNotes[1][c] = parentsNotes[0][c];
		}
	}//close if
	//after crossover
	cout << "\n\nAfter Crossover";
	for (int c = 0; c < 2; c++)
	{
		cout << "\n\tChildren " << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << children[c][g] << " ";
		}
		cout << "\n\t   Notes " << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << childrenNotes[c][g] << " ";
		}
	}
}

void mutation()//swap mutation
{
	float randomValue;
	int mutationBit = -1;
	int randomPosition1 = 0;
	int randomPosition2 = 0;
	for (int c = 0; c < 2; c++)
	{
		cout << "\nChildren " << c + 1;
		randomValue = (rand() % 10) / 10.0;
		cout << "\n\tRandom Value = " << randomValue;

		for (int g = 0; g < GENE; g++)
		{
			mutaChild[c][g] = children[c][g];
			mutaChildNotes[c][g] = childrenNotes[c][g];
		}

		if (randomValue < MUTATION_PROBABILITY)
		{
			do {
				randomPosition1 = rand() % GENE;
				randomPosition2 = rand() % GENE;
			} while (randomPosition1 == randomPosition2);
			cout << "\n\tRandom Position 1: " << randomPosition1 + 1;
			cout << "\n\tRandom Position 2: " << randomPosition2 + 1;
			//swap happen
			mutaChild[c][randomPosition1] = children[c][randomPosition2];
			mutaChild[c][randomPosition2] = children[c][randomPosition1];
			mutaChildNotes[c][randomPosition1] = childrenNotes[c][randomPosition2];
			mutaChildNotes[c][randomPosition2] = childrenNotes[c][randomPosition1];
			//insert back for the value
			children[c][randomPosition1] = mutaChild[c][randomPosition1];
			children[c][randomPosition2] = mutaChild[c][randomPosition2];
			childrenNotes[c][randomPosition1] = mutaChildNotes[c][randomPosition1];
			childrenNotes[c][randomPosition2] = mutaChildNotes[c][randomPosition2];
		}

	}
	cout << "\nSwap Mutation";
	for (int c = 0; c < 2; c++)
	{
		cout << "\n\tChildren " << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << children[c][g] << " ";
		}
		cout << "\n\tChildren Notes" << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)//Notes
		{
			cout << childrenNotes[c][g] << " ";
		}
	}
}

void survivalSelection()
{
	//1. For each chromosome
		//1.2. For each gene
		//1.3 Copy children to the survival chromosome array
		//survivor=children
	//2. Update array counter
	//3. Print chromosome in the new population so far
	for (int r = 0; r < 2; r++)
	{
		for (int g = 0; g < GENE; g++)
		{
			survivor[counterSurvivor][g] = children[r][g];
			survivorNotes[counterSurvivor][g] = childrenNotes[r][g];
		}
		counterSurvivor++;
	}//copy children to survivor
	for (int r = 0; r < POP_SIZE; r++)
	{
		cout << "\tSurvivor " << r + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << survivor[r][g] << " ";
		}
		cout << endl;
	}//print children to survivor

}

void copyChromosome()
{
	//1. For each chromosome
	//1.2. For each gene
	//1.3 Copy newChromosome to chromosome
	for (int r = 0; r < POP_SIZE; r++)
	{
		for (int g = 0; g < GENE; g++)
		{
			chromosome[r][g] = survivor[r][g];
			chromosomeNotes[r][g] = survivorNotes[r][g];
		}
	}//copy children to survivor
	for (int r = 0; r < POP_SIZE; r++)
	{
		cout << "\tNew Parents " << r + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << chromosome[r][g] << " ";
		}
		cout << endl;
	}//print children to survivor
}

void calculateAverageFitness() {
	//1. Declare a variable for totalFitness, initialize to 0
	//2. For every chromosome
	//2.1 Accumulate the fitness into totalFitness
	//3. Divide the totalFitness with population size
	//4. Print out the average to the screen
	//5. Print out the average to an output file that keep average fitness
	double totalFitness = 0;

	for (int i = 0; i < POP_SIZE; i++)
	{
		totalFitness = totalFitness + fitnessValue[i];
	}

	averageFitness = totalFitness / POP_SIZE;
	cout << "\n\n\tAverage fitness = " << averageFitness;
	ACP_File << averageFitness << endl;
}

void recordBestFitness() {
	//1. Declare the bestChromosome data structure
	//2. For each chromosome
	//2.1. if (fitness current chromosome better than bestFitness){
	//2.1.1. bestFitness = fitness for the current chromosome
	//2.1.2. copy the chromosome to bestChromosome
	//3. Print the bestFitness and bestChromosome to the screen
	//4. Print the bestFitness and bestChromosome to two separate files
	int chromo = 0;//what number of chromosome

	for (int i = 0; i < POP_SIZE; i++)
	{
		if (bestFitness > fitnessValue[i])
		{
			bestFitness = fitnessValue[i];
			for (int g = 0; g < GENE; g++)
			{
				bestChromosome[g] = chromosome[i][g];
				bestChromosomeNotes[g] = chromosomeNotes[i][g];
			}
			chromo = i;
		}
	}
	cout << "\n\tBest Fitness = " << bestFitness;
	BSF_File << bestFitness << endl;

	cout << "\n\tBest Chromosome(" << chromo + 1 << "): ";
	for (int g = 0; g < GENE; g++)
	{
		cout << bestChromosome[g] << " ";
		bestChromosome_File << bestChromosome[g] << " ";
	}
	bestChromosome_File << endl;
	cout << "\n\tBest Chromosome Notes(" << chromo + 1 << "): ";
	for (int g = 0; g < GENE; g++)
	{
		cout << bestChromosomeNotes[g] << " ";
		bestChromosomeNotes_File << bestChromosomeNotes[g] << " ";
	}
	bestChromosomeNotes_File << endl;
}

int main() {
	srand((unsigned int)time(NULL));
	cout << "\nINITIALIZATION\n" << endl;
	initializePopulation();

	for (int j = 0; j < MAXIMUM_GENERATION; j++)
	{
		cout << ":::::::::::: GENERATION " << j + 1 << "::::::::::::" << endl;
		printChromosome();
		cout << "\nFITNESS VALUE" << endl;
		evaluateChromosome();
		calculateAverageFitness();
		recordBestFitness();
		cout << endl << endl;
		counterSurvivor = 0;
		for (int i = 0; i < POP_SIZE / 2; i++)
		{
			cout << "---- ROUND " << i + 1 << "----";
			cout << "\nPARENT SELECTION\n";
			parentSelection();
			cout << endl;
			cout << "\nCROSSOVER\n";
			crossover();
			cout << "\n\nMUTATION\n";
			mutation();
			cout << endl;
			cout << "\nSURVIVAL SELECTION\n\n";
			survivalSelection();
			cout << endl;
		}
		cout << "NEW PARENTS\n\n";
		copyChromosome();
		cout << endl;
	}
	ACP_File.close();
	BSF_File.close();
	bestChromosome_File.close();
	bestChromosomeNotes_File.close();

	system("PAUSE");
	return 0;
}