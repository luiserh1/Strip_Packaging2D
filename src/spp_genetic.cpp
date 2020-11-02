#include <list>
#include <iostream>

#include "blocks.h"
#include "spp_genetic.h"

extern int verbose;

// TODO -> Cambiar la semilla de los rand() con respecto a la hora

StripPackingProblem::StripPackingProblem(int numBlocks, int maxHeigth, int maxWidth,
	int individualsPerGen, Block *blocks) : numBlocks(numBlocks),
	maxHeigth(maxHeigth), maxWidth(maxWidth), individualsPerGen(individualsPerGen), 
	blocks(blocks), minBlockHeigth(-1), minBlockWidth(-1)
{ 		
	init();
}

StripPackingProblem::StripPackingProblem(int numBlocks, int maxHeigth, int maxWidth,
	int individualsPerGen, Block *blocks, int minBlockHeigth, int minBlockWidth) :
	numBlocks(numBlocks),maxHeigth(maxHeigth), maxWidth(maxWidth),
	individualsPerGen(individualsPerGen), blocks(blocks),
	minBlockHeigth(minBlockHeigth), minBlockWidth(minBlockWidth)
{ 		
	init();
}



// TODO (provisional)
void StripPackingProblem::init()
{
	individuals.reserve(individualsPerGen);
	for (int i = 0; i < individualsPerGen; i++)
		individuals.push_back(Individual(numBlocks, maxHeigth, maxWidth, blocks,
			minBlockHeigth, minBlockWidth));
	printf("Problema inicializado\n");
}
