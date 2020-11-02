#include "blocks.h"

Coords Coords::operator+(const Coords & other) const
{
    return Coords(x + other.x, y + other.y);
}

Coords Coords::operator-(const Coords & other) const
{
    return Coords(x - other.x, y - other.y);
}

Coords& Coords::operator=(const Coords & other)
{
	x = other.x;
	y = other.y;
    return *this;
}

Coords& Coords::operator-=(const Coords & other)
{
	this->x -= other.x;
	this->y -= other.y;
    return *this;
}

Coords& Coords::operator+=(const Coords & other)
{
	this->x += other.x;
	this->y += other.y;
    return *this;
}

bool Coords::operator==(const Coords & other) const
{
    return (x == other.x && y == other.y);
}

bool Coords::operator!=(const Coords & other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, Coords & c)
{
	out << "(" << c.x << "," << c.y << ")";
	return out;
}

bool Coords::operator<(const Coords & other) const
{
	if (ordering == COORDS_ORDERING::Y)
		return y < other.y;
	else if (ordering == COORDS_ORDERING::X)
		return x < other.x;
	else if (ordering == COORDS_ORDERING::Y_REVERSE)
		return other.y < y;
	else if (ordering == COORDS_ORDERING::X_REVERSE)
		return other.x < x;
	else
		return (x + y - other.x -other.y < 0);
}

bool FrontierPoint::operator<(const FrontierPoint & other) const
{
	return coords < other.coords;
}

bool FrontierPoint::operator==(const FrontierPoint & other) const
{
	return coords == other.coords;
}


Intersections getSegmentIntersects(Coords a1, Coords a2, FrontierPoint v1, FrontierPoint v2, COORDS_ORDERING ord, int newBlockID)
{
	Coords 	b1 = v1.coords,
			b2 = v2.coords;
	INTERSECTION t = INTERSECTION::NONE;
	Intersections intersection(t);

	if (a1.x == a2.x)	// If A is vertical
	{
		if (b1.x == b2.x)	// If B is vertical
		{
			if (a1.x == b1.x)	// If A and B are colinear (may touch)
			{
				if (b1.y < b2.y)	// If B goes UP
				{
					if (a1.y >= b1.y && a1.y <= b2.y)	// a1 is in B
					{
						std::set<int> blockIDsSet;
						if (a1 == b1) blockIDsSet = v1.blockIDs;
						else if (a1 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
					if (a2.y >= b1.y && a2.y <= b2.y)	// a2 is in B
					{
						std::set<int> blockIDsSet;
						if (a2 == b1) blockIDsSet = v1.blockIDs;
						else if (a2 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
				else	// B goes DOWN
				{
					if (a1.y <= b1.y && a1.y >= b2.y)	// a1 is in B
					{
						std::set<int> blockIDsSet;
						if (a1 == b1) blockIDsSet = v1.blockIDs;
						else if (a1 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
					if (a2.y <= b1.y && a2.y >= b2.y)	// a2 is in B
					{
						std::set<int> blockIDsSet;
						if (a2 == b1) blockIDsSet = v1.blockIDs;
						else if (a2 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
			}	// if they are both vertical, but no colinear, then they can't touch		
		}
		else 	// If B is horizontal
		{
			if (a1.y == b1.y) 	// If A and B may touch in a1
			{
				if (b1.x < b2.x) 	// If B goes RIGHT
				{
					if (a1.x >= b1.x && a1.x <= b2.x) 	// If a1 is in B
					{
						std::set<int> blockIDsSet;
						if (a1 == b1) blockIDsSet = v1.blockIDs;
						else if (a1 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
				else	// If B goes LEFT
				{
					if (a1.x <= b1.x && a1.x >= b2.x) 	// If a1 is in B
					{
						std::set<int> blockIDsSet;
						if (a1 == b1) blockIDsSet = v1.blockIDs;
						else if (a1 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
			}
			else if (a2.y == b1.y) 	// If A and B may touch in a2
			{
				if (b1.x < b2.x) 	// If B goes RIGHT
				{
					if (a2.x >= b1.x && a2.x <= b2.x) 	// If a2 is in B
					{
						std::set<int> blockIDsSet;
						if (a2 == b1) blockIDsSet = v1.blockIDs;
						else if (a2 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
				else	// If B goes LEFT
				{
					if (a2.x <= b1.x && a2.x >= b2.x) 	// If a2 is in B
					{
						std::set<int> blockIDsSet;
						if (a2 == b1) blockIDsSet = v1.blockIDs;
						else if (a2 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
			}
			else if (b1.x == a1.x) 	// If A and B may touch in b1
			{
				if (a1.y < a2.y) 	// If A goes UP
				{
					if (b1.y >= a1.y && b1.y <= a2.y) 	// If b1 is in A
					{
						std::set<int> blockIDsSet = v1.blockIDs;
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(b1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
				else	// If A goes DOWN
				{
					if (b1.y <= a1.y && b1.y >= a2.y) 	// If b1 is in A
					{
						std::set<int> blockIDsSet = v1.blockIDs;
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(b1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
			}
			else if (b2.x == a1.x) 	// If A and B may touch in b2
			{
				if (a1.y < a2.y) 	// If A goes UP
				{
					if (b2.y >= a1.y && b2.y <= a2.y) 	// If b2 is in A
					{
						std::set<int> blockIDsSet = v2.blockIDs;
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(b2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
				else	// If A goes DOWN
				{
					if (b2.y <= a1.y && b2.y >= a2.y) 	// If b2 is in A
					{
						std::set<int> blockIDsSet = v2.blockIDs;
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(b2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
			}
			else 	// If A and B may colllide
			{
				if (b1.x < b2.x) 	// If B goes RIGHT
				{
					if (a1.y < a2.y)	// If A goes UP
					{
						if (b1.y >= a1.y && b1.y <= a2.y)	// If the collision may be in y = b1.y
						{
							if (a1.x >= b1.x && a1.x <= b2.x) 	// If there is a collision in x = a1.x
							{
								std::set<int> blockIDsSet;
								blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
								blockIDsSet.insert(newBlockID);
								FrontierPoint newFP(Coords(a1.x, b1.y), blockIDsSet);
								newFP.coords.ordering = ord;
								intersection.addFrontierPoint(newFP);
								intersection.t = INTERSECTION::COLLISION;
							}
						}
					}
					else	// If A goes DOWN
					{
						if (b1.y <= a1.y && b1.y >= a2.y)	// If the collision may be in y = b1.y
						{
							if (a1.x >= b1.x && a1.x <= b2.x) 	// If there is a collision in x = a1.x
							{
								std::set<int> blockIDsSet;
								blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
								blockIDsSet.insert(newBlockID);
								FrontierPoint newFP(Coords(a1.x, b1.y), blockIDsSet);
								newFP.coords.ordering = ord;
								intersection.addFrontierPoint(newFP);
								intersection.t = INTERSECTION::COLLISION;
							}
						}
					}
				}
				else	// If B goes LEFT
				{
					if (a1.y < a2.y)	// If A goes UP
					{
						if (b1.y >= a1.y && b1.y <= a2.y)	// If the collision may be in y = b1.y
						{
							if (a1.x <= b1.x && a1.x >= b2.x) 	// If there is a collision in x = a1.x
							{
								std::set<int> blockIDsSet;
								blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
								blockIDsSet.insert(newBlockID);
								FrontierPoint newFP(Coords(a1.x, b1.y), blockIDsSet);
								newFP.coords.ordering = ord;
								intersection.addFrontierPoint(newFP);
								intersection.t = INTERSECTION::COLLISION;
							}
						}
					}
					else	// If A goes DOWN
					{
						if (b1.y <= a1.y && b1.y >= a2.y)	// If the collision may be in y = b1.y
						{
							if (a1.x <= b1.x && a1.x >= b2.x) 	// If there is a collision in x = a1.x
							{
								std::set<int> blockIDsSet;
								blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
								blockIDsSet.insert(newBlockID);
								FrontierPoint newFP(Coords(a1.x, b1.y), blockIDsSet);
								newFP.coords.ordering = ord;
								intersection.addFrontierPoint(newFP);
								intersection.t = INTERSECTION::COLLISION;
							}
						}
					}
				}
			}
		}
	}
	else // If A is horizontal
	{
		if (b1.x != b2.x)	// If B is horizontal
		{
			if (a1.y == b1.y) 	// If A and B are colinear (may touch)
			{
				if (b1.x < b2.x)	// If B goes RIGHT
				{
					if (a1.x >= b1.x && a1.x <= b2.x)	// a1 is in B
					{
						std::set<int> blockIDsSet;
						if (a1 == b1) blockIDsSet = v1.blockIDs;
						else if (a1 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
					if (a2.x >= b1.x && a2.x <= b2.x)	// a2 is in B
					{
						std::set<int> blockIDsSet;
						if (a2 == b1) blockIDsSet = v1.blockIDs;
						else if (a2 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
				else	// B goes DOWN
				{
					if (a1.x <= b1.x && a1.x >= b2.x)	// a1 is in B
					{
						std::set<int> blockIDsSet;
						if (a1 == b1) blockIDsSet = v1.blockIDs;
						else if (a1 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
					if (a2.x <= b1.x && a2.x >= b2.x)	// a2 is in B
					{
						std::set<int> blockIDsSet;
						if (a2 == b1) blockIDsSet = v1.blockIDs;
						else if (a2 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
			}	// if they are both horizontal, but no colinear, then they can't touch		
		}
		else 	// If B is vertical
		{
			if (a1.x == b1.x) 	// If A and B may touch in a1 
			{
				if (b1.y < b2.y) 	// If B goes UP
					if (a1.y >= b1.y && a1.y <= b2.y) 	// If a1 is in B
					{
						std::set<int> blockIDsSet;
						if (a1 == b1) blockIDsSet = v1.blockIDs;
						else if (a1 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				else	// If B goes DOWN
					if (a1.y <= b1.y && a1.y >= b2.y) 	// If a1 is in B
					{
						std::set<int> blockIDsSet;
						if (a1 == b1) blockIDsSet = v1.blockIDs;
						else if (a1 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
			}
			else if (a2.x == b1.x) 	// If A and B may touch in a2
			{
				if (b1.y < b2.y) 	// If B goes UP
					if (a2.y >= b1.y && a2.y <= b2.y) 	// If a2 is in B
					{
						std::set<int> blockIDsSet;
						if (a2 == b1) blockIDsSet = v1.blockIDs;
						else if (a2 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				else	// If B goes DOWN
					if (a2.y <= b1.y && a2.y >= b2.y) 	// If a2 is in B
					{
						std::set<int> blockIDsSet;
						if (a2 == b1) blockIDsSet = v1.blockIDs;
						else if (a2 == b2) blockIDsSet = v2.blockIDs;
						else blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(a2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
			} 
			else if (b1.y == a1.y) 	// If A and B may touch in b1
			{
				if (a1.x < a2.x) 	// If A goes RIGHT
				{
					if (b1.x >= a1.x && b1.x <= a2.x) 	// If b1 is in A
					{
						std::set<int> blockIDsSet = v1.blockIDs;
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(b1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
				else	// If A goes LEFT
				{
					if (b1.y <= a1.y && b1.y >= a2.y) 	// If b1 is in A
					{
						std::set<int> blockIDsSet = v1.blockIDs;
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(b1, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
			}
			else if (b2.y == a1.y) 	// If A and B may touch in b2
			{
				if (a1.x < a2.x) 	// If A goes RIGHT
				{
					if (b2.x >= a1.x && b2.x <= a2.x) 	// If b2 is in A
					{
						std::set<int> blockIDsSet = v2.blockIDs;
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(b2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
				else	// If A goes LEFT
				{
					if (b2.x <= a1.x && b2.x >= a2.x) 	// If b2 is in A
					{
						std::set<int> blockIDsSet = v2.blockIDs;
						blockIDsSet.insert(newBlockID);
						FrontierPoint newFP(b2, blockIDsSet);
						newFP.coords.ordering = ord;
						intersection.addFrontierPoint(newFP);
						intersection.t = INTERSECTION::TOUCH;
					}
				}
			}
			else 	// If A and B may colllide
			{
				if (b1.y < b2.y) 	// If B goes UP
				{
					if (a1.x < a2.x)	// If A goes RIGHT
					{
						if (b1.x >= a1.x && b1.x <= a2.x)	// If the collision may be in x = b1.x
						{
							if (a1.y >= b1.y && a1.y <= b2.y) 	// If there is a collision in y = a1.y
							{
								std::set<int> blockIDsSet;
								blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
								blockIDsSet.insert(newBlockID);
								FrontierPoint newFP(Coords(a1.x, b1.y), blockIDsSet);
								newFP.coords.ordering = ord;
								intersection.addFrontierPoint(newFP);
								intersection.t = INTERSECTION::COLLISION;
							}
						}
					}
					else	// If A goes LEFT
					{
						if (b1.x <= a1.x && b1.x >= a2.x)	// If the collision may be in x = b1.x
						{
							if (a1.y >= b1.y && a1.y <= b2.y) 	// If there is a collision in y = a1.y
							{
								std::set<int> blockIDsSet;
								blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
								blockIDsSet.insert(newBlockID);
								FrontierPoint newFP(Coords(a1.x, b1.y), blockIDsSet);
								newFP.coords.ordering = ord;
								intersection.addFrontierPoint(newFP);
								intersection.t = INTERSECTION::COLLISION;
							}
						}
					}
				}
				else // If B goes DOWN
				{
					if (a1.x < a2.x)	// If A goes RIGHT
					{
						if (b1.x >= a1.x && b1.x <= a2.x)	// If the collision may be in x = b1.x
						{
							if (a1.y <= b1.y && a1.y >= b2.y) 	// If there is a collision in y = a1.y
							{
								std::set<int> blockIDsSet;
								blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
								blockIDsSet.insert(newBlockID);
								FrontierPoint newFP(Coords(a1.x, b1.y), blockIDsSet);
								newFP.coords.ordering = ord;
								intersection.addFrontierPoint(newFP);
								intersection.t = INTERSECTION::COLLISION;
							}
						}
					}
					else	// If A goes LEFT
					{
						if (b1.x <= a1.x && b1.x >= a2.x)	// If the collision may be in x = b1.x
						{
							if (a1.y <= b1.y && a1.y >= b2.y) 	// If there is a collision in y = a1.y
							{
								std::set<int> blockIDsSet;
								blockIDsSet.insert(getCommonBlockId(v1.blockIDs, v2.blockIDs));
								blockIDsSet.insert(newBlockID);
								FrontierPoint newFP(Coords(a1.x, b1.y), blockIDsSet);
								newFP.coords.ordering = ord;
								intersection.addFrontierPoint(newFP);
								intersection.t = INTERSECTION::COLLISION;
							}
						}
					}
				}
			}
		}
	}

	return intersection;
}

void printFrontierPoints(std::list<FrontierPoint>::iterator frontierBegining, std::list<FrontierPoint>::iterator frontierEnd)
{
	if (frontierBegining != frontierEnd)
	{
		std::list<FrontierPoint>::iterator beforeLast = frontierEnd;
		--beforeLast;
		for (std::list<FrontierPoint>::iterator it = frontierBegining; it != frontierEnd; ++it)
		{
			std::cout << "(" << it->coords.x << ", " << it->coords.y << ": [";
			std::list<int>::iterator it2;
			int blocksInContact = it->blockIDs.size();
			std::set<int>::iterator beforeLast2 = it->blockIDs.end();
			--beforeLast2;
			for (std::set<int>::iterator it2=it->blockIDs.begin(); it2 != it->blockIDs.end(); ++it2)
			{
				std::cout << *it2;
				if (it2 != beforeLast2) std::cout << ", ";
			}
			std::cout << "])";
			if (it != beforeLast) std::cout << " | ";
		}
	}
	std::cout << std::endl;
}

void printFrontierPoints(std::set<FrontierPoint>::iterator frontierBegining, std::set<FrontierPoint>::iterator frontierEnd)
{
	if (frontierBegining != frontierEnd)
	{
		std::set<FrontierPoint>::iterator beforeLast = frontierEnd;
		--beforeLast;
		for (std::set<FrontierPoint>::iterator it = frontierBegining; it != frontierEnd; ++it)
		{
			std::cout << "(" << it->coords.x << ", " << it->coords.y << ": [";
			std::set<int>::iterator it2;
			int blocksInContact = it->blockIDs.size();
			std::set<int>::iterator beforeLast2 = it->blockIDs.end();
			--beforeLast2;
			for (std::set<int>::iterator it2=it->blockIDs.begin(); it2 != it->blockIDs.end(); ++it2)
			{
				std::cout << *it2;
				if (it2 != beforeLast2) std::cout << ", ";
			}
			std::cout << "])";
			if (it != beforeLast) std::cout << " | ";
		}
	}
	std::cout << std::endl;
}

int getCommonBlockId(std::set<int> blockIDsSet1, std::set<int> blockIDsSet2)
{
	for (std::set<int>::iterator it = blockIDsSet1.begin(); it != blockIDsSet1.end(); ++it)
		if (blockIDsSet2.find(*it) != blockIDsSet2.end())
			return *it;
	return -10101;
}
