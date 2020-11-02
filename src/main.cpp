#include <string.h>
#include <list>
#include <iostream>
#include <fstream>

#include "blocks.h"
#include "spp_tests.h"
#include "spp_genetic.h"
#include "spp_gfx_rep.h"

const int MAX_NUM = 2^31;

int verbose = 0;

int main()
{
	using namespace std;

	char filePath[] = "./customs/default.txt";
	int numBlocks;
	int maxHeigth, maxWidth;
	Block *blocks;

	int minBlockHeigth = MAX_NUM, minBlockWidth = MAX_NUM;
	// Extrcting info from file
	fstream f(filePath);
	if (f.is_open())
	{
		string line; 
		if (getline(f, line)) numBlocks = stoi(line);
		if (getline(f, line)) maxHeigth = stoi(line);
		if (getline(f, line)) maxWidth = stoi(line);
		if (verbose > 1)
			cout << "numBlocks: " << numBlocks << " | AreaSize(" << maxHeigth
			<< ", " << maxWidth << ")" << endl;
		blocks = new Block[numBlocks];
		int i = 0;
		while (getline(f, line) && i < numBlocks)
		{
			int x = stoi(line.substr(0, line.find(" ")));
			int y = stoi(line.substr(line.find(" ")+1, line.size()));
			blocks[i].sizeX = x;
			blocks[i].sizeY = y;
			if (y < minBlockHeigth) minBlockHeigth = y;
			if (x < minBlockWidth) minBlockWidth = x;
			if (verbose > 1)
				cout << "Block_" << i << "->Size(" << x << ", " << y << ")" << endl;
			i++;
		}
		if (i != numBlocks) 
		{
			if (verbose > 0) 
				cout << "ERROR: The number of blocks specified and "
				"the number of them available do'nt match" << endl;
			return -1;
		}
		if (verbose > 0) 
				cout << "minBlockHeigth=" << minBlockHeigth << " | minBlockWidth="
				<< minBlockHeigth << endl;
	}
	else
	{
		if (verbose > 0) cout << "ERROR: Cannot open file" << endl;
		return -1;
	}
	f.close();

	// At this point all the info from the file has been got, let's use it
	//StripPackingProblem problem(numBlocks, maxHeigth, maxWidth, 1, blocks, minBlockHeigth, minBlockWidth);

	testSegmentIntersectionDetector();

	return 0;
}
