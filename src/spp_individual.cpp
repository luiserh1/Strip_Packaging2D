#include <list>
#include <iostream>

#include "blocks.h"
#include "spp_individual.h"

extern int verbose;

Individual::Individual() {} // TODO Se ha de eliminar

Individual::Individual(int numBlocks, int maxHeigth, int maxWidth,
	Block *blocks) : numBlocks(numBlocks), maxHeigth(maxHeigth), maxWidth(maxWidth),
	blocks(blocks),	minBlockHeigth(-1), minBlockWidth(-1)
{ 
	init();
}

Individual::Individual(int numBlocks, int maxHeigth, int maxWidth,
	Block *blocks, int minBlockHeigth, int minBlockWidth) : numBlocks(numBlocks),
	maxHeigth(maxHeigth), maxWidth(maxWidth), blocks(blocks),
	minBlockHeigth(minBlockHeigth),	minBlockWidth(minBlockWidth)
{
	init();
}


// TODO (provisional)
void Individual::init()
{
	limitOfIterations = 1000;

	fullArea = maxHeigth * maxWidth;
	blockPositions.reserve(numBlocks);
	for (int i = 0; i < numBlocks; i++) blockPositions.push_back(Coords());
	placedBlocks = 0;

	setChromosome();
	printf("Individuo inicializado\n");
	printChromosome(true);
}

// TODO
int Individual::setChromosome()
{
	// Built from 0
	if (!placedBlocks)
	{
		std::list<FrontierPoint> fPs;
		frontierPoints.push_back(fPs);
		// reloading the basic frontier, the maximum rectangle area. Frontier blockID = -1
		fPs.push_back(FrontierPoint(0, 0, -1));
		fPs.push_back(FrontierPoint(0, maxHeigth, -1));
		fPs.push_back(FrontierPoint(maxWidth, maxHeigth, -1));
		fPs.push_back(FrontierPoint(maxWidth, 0, -1));
		frontierPtsNum = 4;
		// The first step consists in fitting a block in the lower-left corner
		bool placed = false;
		int i = 0;
		int index = random() % numBlocks;
		while (!placed && i < numBlocks)
		{
			printFrontier();
			Block *newBlock = &blocks[index];
			if (newBlock->sizeX <= maxWidth && newBlock->sizeY <= maxHeigth)
			{
				blockPositions[index] = Coords(0, 0);
				addBlockToFrontier(newBlock, true);
				placed = true;
			}

			i++;
			index++;
			if (index == numBlocks)
				index = 0;
			printFrontier();
		}
	}

	return evaluate();
}

int Individual::evaluate()
{ 
	return placedBlocks;
}

void Individual::addBlockToFrontier(Block *newBlock, bool areaLimitConsidered)
{
	/*
	* The vertex of a new block are called 0, 1, 2 and 3. The lower-left corner is the 0 and then the value
	* increases clockwisely.
	* A01 represents the edge that joins 0 and 1. In this list the key indexes are stored
	*/
	std::list<FrontierPoint> A01, A12, A23, A30;

	// Randomly choosing the vertices of the edge where we'll try to put the new block
	std::list<FrontierPoint>::iterator vtxA, vtxB; // The B vertex is the one after the A
	
	int vtxAIndex = random() % frontierPtsNum;
	if (vtxAIndex == frontierPtsNum-1)
	{
		vtxA = frontierPoints.begin()->end();
		--vtxA;
		vtxB = frontierPoints.begin()->begin();
	}
	else 
	{
		vtxA = frontierPoints.begin()->begin();
		for (int i = 0; i < vtxAIndex; i++)
			++vtxA;
		vtxB = vtxA;
		++vtxB; 
	}

	bool placed = false;
	int i = 0;
	while (!placed && i < frontierPtsNum)
	{
		int j = 0; // TODO -> Randomize first block
		while (!placed && j < numBlocks)
		{
			Block *block = &blocks[j];
			bool verticalSeg = (vtxA->coords.x == vtxB->coords.x);
			bool v0Touches; // If the vertex  of the block will be part of the segment
			Coords delta;
			if (verticalSeg)
				if ( vtxB->coords.y > vtxA->coords.y ) // Up direction
				{
			 		delta = Coords(0, 1);
			 		v0Touches = true;
				}
			 	else // Down direction
			 	{
			 		delta = Coords(0, -1);
			 		v0Touches = false;
			 	}
			else // (!verticalSeg) ==> Horizontal segment
				if ( vtxB->coords.x > vtxA->coords.x )  // Right direction
				{
			 		delta = Coords(1, 0);
			 		v0Touches = false;
				}
			 	else // Left direction
			 	{
			 		delta = Coords(-1, 0);
			 		v0Touches = true;
			 	}
			Coords 	pos = vtxB->coords,
					posEnd = vtxA->coords;
			// The pos is always the lower-left corner, so when the edge's direction is right or down
			// we need to acknwoledge the offset
			if (!v0Touches)
				if (verticalSeg)
				{
					pos.x -= block->sizeX;
					posEnd.x -= block->sizeX;
				}
				else
				{
					pos.y -= block->sizeY;
					posEnd.y -= block->sizeY;
				}


			while (pos != posEnd)
			{
				Coords 	b0(pos.x, pos.y),
						b1(pos.x, pos.y + block->sizeY),
						b2(pos.x + block->sizeX, pos.y + block->sizeY),
						b3(pos.x + block->sizeX, pos.y);
				// A01
				Intersections intersectA01 = getSegmentIntersects(	b0,
																	b1,
																	*vtxA,
																	*vtxB,
																	COORDS_ORDERING::X,
																	22);
				// A12
				Intersections intersectA12 = getSegmentIntersects(	b1,
																	b2,
																	*vtxA,
																	*vtxB,
																	COORDS_ORDERING::Y,
																	22);
				// A23
				Intersections intersectA23 = getSegmentIntersects(	b2,
																	b3,
																	*vtxA,
																	*vtxB,
																	COORDS_ORDERING::X_REVERSE,
																	22);
				// A30
				Intersections intersectA30 = getSegmentIntersects(	b3,
																	b0,
																	*vtxA,
																	*vtxB,
																	COORDS_ORDERING::Y_REVERSE,
																	22);
				if (intersectA01.t == INTERSECTION::COLLISION || intersectA12.t == INTERSECTION::COLLISION
				 || intersectA23.t == INTERSECTION::COLLISION || intersectA30.t == INTERSECTION::COLLISION)
					std::cout << "Loco\n";

				pos -= delta;
			}

			j++;
		}

		++vtxA;
		++vtxB;
		i++;

		if (vtxA == frontierPoints.begin()->end()) vtxA = frontierPoints.begin()->begin();
		if (vtxB == frontierPoints.begin()->end()) vtxB = frontierPoints.begin()->begin();
	}
	

}	

void Individual::printChromosome(bool justPlaced)
{
	for (int i = 0; i < numBlocks; i++)
		if (!justPlaced || blockPositions[i].x > -1)
		std::cout <<  "[" << i << "]->("  << blockPositions[i].x << ", " << blockPositions[i].y
			<< ") ";
	std::cout << std::endl;
}

void Individual::printFrontier()
{
	int subFrontCounter = 0;
	for (std::list<std::list<FrontierPoint>>::iterator it = frontierPoints.begin(); it != frontierPoints.end(); ++it)
	{
		std::cout << "[" << ++subFrontCounter << "]" << " => ";
		printFrontierPoints(it->begin(), it->end());
	}
}
