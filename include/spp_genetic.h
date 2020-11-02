#ifndef SPP_GENETIC_H
#define SPP_GENETIC_H
#include "blocks.h"
#include "spp_individual.h"
#include <vector>

/*
* A strip packing problem
*/
class StripPackingProblem
{
private:	

	////////////////
	// Attributes //
	////////////////

	int numBlocks;
	int maxHeigth, maxWidth;
	int individualsPerGen;
	Block *blocks;

	int minBlockHeigth, minBlockWidth;
	
	// Vector that stores the current Individuals
	std::vector<Individual> individuals;

	/////////////
	// Methods //
	/////////////

	/*
	* Code that is called from the constructor
	*/
	void init();

public:
	StripPackingProblem(int, int, int, int, Block*);
	StripPackingProblem(int, int, int, int, Block*, int, int);
};

#endif