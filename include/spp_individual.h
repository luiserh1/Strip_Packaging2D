#ifndef SPP_INDIVUDUAL_H
#define SPP_INDIVUDUAL_H
#include <vector>

class Individual
	{
	private:
		int numBlocks;
		int maxHeigth, maxWidth;
		int fullArea;
		int placedBlocks;
		Block *blocks;
		/* 
		* The chromosome are the block's positions
		* One-dimensional array of coordenates
		* Each index [0..N-1] corresponds to the coordenates of the block
		* with the same index of the 'blocks' array
		*/
		std::vector<Coords> blockPositions;
		// The frontier points are ordered because is easier to delete and add them
		std::list<std::list<FrontierPoint>> frontierPoints;
		int frontierPtsNum; // This way it's no necessary the use of list.size()

		// Atributes dedicated to accelerate the process
		int limitOfIterations;
		int minBlockHeigth, minBlockWidth;
		int minPlacedX = 2^31, minPlacedY = 2^31, maxPlacedX = -2^31, maxPlacedY = -2^31;

		/*
		* Adds a new block to the frontier, modifying it if necessary
		*/
		void addBlockToFrontier(Block *newBlock, bool areaLimitConsidered);

		/*
		* The cheapest way to represent the frontierPoints
		*/
		void printFrontier();
	public:
		Individual(); // TODO se ha de eliminar
		Individual(int, int, int, Block*);
		Individual(int, int, int, Block*, int, int);
		
		/*
		* Code that is called from the constructor
		*/
		void init();

		/*
		* Starting from the current state of the individual's chromosome this function
		* sets a configuration for it that cannot accept more blocks in it
		*/
		int setChromosome();

		/*
		* This functions gives a score to the individual for the current problem
		*/
		int evaluate();

		/*
		* The cheapest way to represent the chromosome of the Individual
		*
		* If justPlaced is set to true it will only print the placed blocks
		*/
		void printChromosome(bool justPlaced);
};

#endif