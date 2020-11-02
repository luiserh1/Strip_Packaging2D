#ifndef BLOCKS_H
#define BLOCKS_H
#include <list>
#include <vector>
#include <iostream>
#include <set>

enum class COORDS_ORDERING { NONE, X, Y, X_REVERSE, Y_REVERSE };

/*
* Cordenates inside the 2D space of the problem enviroment
*/
struct Coords
{
	int x, y;
	COORDS_ORDERING ordering; // The one that uses the operator has preference

	Coords() : x(-1), y(-1), ordering(COORDS_ORDERING::NONE) {}
	Coords(int x, int y) : x(x), y(y), ordering(COORDS_ORDERING::NONE) {}

	Coords operator+(const Coords & other) const;
	Coords operator-(const Coords & other) const;
	Coords& operator=(const Coords & other);
	Coords& operator-=(const Coords & other);
	Coords& operator+=(const Coords & other);
	bool operator==(const Coords & other) const;
	bool operator<(const Coords & other) const;
	bool operator!=(const Coords & other) const;
	friend std::ostream& operator<<(std::ostream& out, Coords & c);
};

struct FrontierPoint
{
	Coords coords;
	std::set<int> blockIDs;

	FrontierPoint(Coords coords, int blockID) : coords(coords)
	{
		blockIDs.insert(blockID);
	}
	FrontierPoint(int x, int y, int blockID) : coords(Coords(x, y))
	{ 
		blockIDs.insert(blockID);
	}
	FrontierPoint(int x, int y, std::set<int> blockIDsSet) : coords(Coords(x, y))
	{
		for (std::set<int>::iterator it=blockIDsSet.begin(); it != blockIDsSet.end(); ++it)
			blockIDs.insert(*it);
	}
	FrontierPoint(Coords coords, std::set<int> blockIDsSet) : coords(coords)
	{
		if (blockIDsSet.size())
		{
			for (std::set<int>::iterator it=blockIDsSet.begin(); it != blockIDsSet.end(); ++it)
						blockIDs.insert(*it);
		}
	}

	bool operator<(const FrontierPoint & other) const;
	bool operator==(const FrontierPoint & other) const;
};

/*
* Prints to the console a cheap representation of a list of FrontierPoints
*/
void printFrontierPoints(std::list<FrontierPoint>::iterator frontierBegining, std::list<FrontierPoint>::iterator frontierEnd);

void printFrontierPoints(std::set<FrontierPoint>::iterator frontierBegining, std::set<FrontierPoint>::iterator frontierEnd);

/*
* Main pieces of the strip packing problem
*/
struct Block
{
	int sizeX, sizeY;
	int area;

	Block()	{ sizeX = -1; sizeY= -1; area = -1;	}
	Block(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) { area = sizeX * sizeY; }
};

enum class INTERSECTION { NONE, TOUCH, COLLISION };

struct Intersections
{
	std::set<FrontierPoint> points;
	INTERSECTION t;

	Intersections(INTERSECTION t) : t(t) {}
	Intersections(FrontierPoint fp, INTERSECTION& i) : t(i)
	{
		points.insert(fp);
	}

	void addFrontierPoint(FrontierPoint fp) {points.insert(fp);}
};

/*
* Checks wether the segment A, formed by the vertices a1 and a2 does intersect with
* the segment B, formed by the vertices b1 and b2
*/
Intersections getSegmentIntersects(Coords a1, Coords a2, FrontierPoint v1, FrontierPoint v2, COORDS_ORDERING ord, int newBlockID);

/*
* Gets the firs integer in common between the two sets
*/
int getCommonBlockId(std::set<int> blockIDsSet1, std::set<int> blockIDsSet2);

#endif