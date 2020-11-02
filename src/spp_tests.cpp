#include "spp_tests.h"

void testSegmentIntersectionDetector()
{
	std::list<FrontierPoint> testFrontier;

	testFrontier.push_back(FrontierPoint(2, 6, 8));

	testFrontier.push_back(FrontierPoint(2, 8, 8));

	std::set<int> blockIDs;
	blockIDs.insert(5);
	blockIDs.insert(-1);
	testFrontier.push_back(FrontierPoint(0, 8, blockIDs));

	testFrontier.push_back(FrontierPoint(0, 10, -1));

	blockIDs.clear();
	blockIDs.insert(6);
	blockIDs.insert(-1);
	testFrontier.push_back(FrontierPoint(10, 10, blockIDs));

	testFrontier.push_back(FrontierPoint(10, 9, 6));

	blockIDs.clear();
	blockIDs.insert(6);
	blockIDs.insert(1);
	testFrontier.push_back(FrontierPoint(11, 9, blockIDs));

	testFrontier.push_back(FrontierPoint(11, 8, 1));

	testFrontier.push_back(FrontierPoint(12, 8, 1));

	blockIDs.clear();
	blockIDs.insert(1);
	blockIDs.insert(-1);
	testFrontier.push_back(FrontierPoint(12, 10, blockIDs));
	
	testFrontier.push_back(FrontierPoint(15, 10, -1));

	testFrontier.push_back(FrontierPoint(15, 0, -1));

	blockIDs.clear();
	blockIDs.insert(2);
	blockIDs.insert(-1);
	testFrontier.push_back(FrontierPoint(14, 0, blockIDs));

	testFrontier.push_back(FrontierPoint(14, 5, 2));

	testFrontier.push_back(FrontierPoint(13, 5, 2));

	blockIDs.clear();
	blockIDs.insert(2);
	blockIDs.insert(-1);
	testFrontier.push_back(FrontierPoint(13, 0, blockIDs));

	blockIDs.clear();
	blockIDs.insert(7);
	blockIDs.insert(-1);
	testFrontier.push_back(FrontierPoint(12, 0, blockIDs));

	testFrontier.push_back(FrontierPoint(12, 6, 7));

	testFrontier.push_back(FrontierPoint(10, 6, 7));

	blockIDs.clear();
	blockIDs.insert(7);
	blockIDs.insert(9);
	testFrontier.push_back(FrontierPoint(10, 4, blockIDs));

	blockIDs.clear();
	blockIDs.insert(9);
	blockIDs.insert(4);
	testFrontier.push_back(FrontierPoint(8, 4, blockIDs));

	testFrontier.push_back(FrontierPoint(8, 6, 4));

	testFrontier.push_back(FrontierPoint(4, 6, 4));

	blockIDs.clear();
	blockIDs.insert(4);
	blockIDs.insert(3);
	testFrontier.push_back(FrontierPoint(4, 3, blockIDs));

	blockIDs.clear();
	blockIDs.insert(3);
	blockIDs.insert(5);
	testFrontier.push_back(FrontierPoint(1, 3, blockIDs));

	blockIDs.clear();
	blockIDs.insert(5);
	blockIDs.insert(8);
	testFrontier.push_back(FrontierPoint(1, 6, blockIDs));

	std::cout << "Frontier for the test: " << std::endl;
	printFrontierPoints(testFrontier.begin(), testFrontier.end());

	Block testBlock(12, 2);
	Coords testPos(2, 6);
	std::cout << "Dimensions of the block to test: (" << testBlock.sizeX << ", " << testBlock.sizeY << ")" << std::endl;
	std::cout << "Position of the block to test: (" << testPos.x << ", " << testPos.y << ")" << std::endl;

	std::set<FrontierPoint> A01, A12, A23, A30;
	std::list<FrontierPoint>::iterator vtxA, vtxB;
	vtxA = testFrontier.begin();
	vtxB = vtxA;
	++vtxB;

	Coords 	b0Coords(testPos.x, testPos.y),
			b1Coords(testPos.x, testPos.y + testBlock.sizeY),
			b2Coords(testPos.x + testBlock.sizeX, testPos.y + testBlock.sizeY),
			b3Coords(testPos.x + testBlock.sizeX, testPos.y);

	std::cout << "The vertices of the block are, then: " << std::endl;
	std::cout << "\tB0: (" << b0Coords.x << ", " << b0Coords.y << ")" << std::endl;
	std::cout << "\tB1: (" << b1Coords.x << ", " << b1Coords.y << ")" << std::endl;
	std::cout << "\tB2: (" << b2Coords.x << ", " << b2Coords.y << ")" << std::endl;
	std::cout << "\tB3: (" << b3Coords.x << ", " << b3Coords.y << ")" << std::endl;

	std::list<FrontierPoint> testFrontierRes;
	while (vtxA != testFrontier.end())
	{

		// A01
		Intersections intersectA01 = getSegmentIntersects(	b0Coords,
															b1Coords,
															*vtxA,
															*vtxB,
															COORDS_ORDERING::Y,
															22);
		// A12
		Intersections intersectA12 = getSegmentIntersects(	b1Coords,
															b2Coords,
															*vtxA,
															*vtxB,
															COORDS_ORDERING::X,
															22);
		// A23
		Intersections intersectA23 = getSegmentIntersects(	b2Coords,
															b3Coords,
															*vtxA,
															*vtxB,
															COORDS_ORDERING::Y_REVERSE,
															22);
		// A30
		Intersections intersectA30 = getSegmentIntersects(	b3Coords,
															b0Coords,
															*vtxA,
															*vtxB,
															COORDS_ORDERING::X_REVERSE,
															22);

		FrontierPoint newPoint = *vtxA;

		if (intersectA01.t == INTERSECTION::TOUCH)
			for (std::set<FrontierPoint>::iterator it = intersectA01.points.begin(); it != intersectA01.points.end(); ++it)
			{
				A01.insert(*it);
				if (it->coords == newPoint.coords)
					newPoint.blockIDs.insert(it->blockIDs.begin(), it->blockIDs.end());
			}
		else if (intersectA01.t == INTERSECTION::COLLISION)
			break;

		if (intersectA12.t == INTERSECTION::TOUCH)
			for (std::set<FrontierPoint>::iterator it = intersectA12.points.begin(); it != intersectA12.points.end(); ++it)
			{
				A12.insert(*it);
				if (it->coords == newPoint.coords)
					newPoint.blockIDs.insert(it->blockIDs.begin(), it->blockIDs.end());
			}
		else if (intersectA01.t == INTERSECTION::COLLISION)
			break;

		if (intersectA23.t == INTERSECTION::TOUCH)
			for (std::set<FrontierPoint>::iterator it = intersectA23.points.begin(); it != intersectA23.points.end(); ++it)
			{
				A23.insert(*it);
				if (it->coords == newPoint.coords)
					newPoint.blockIDs.insert(it->blockIDs.begin(), it->blockIDs.end());
			}
		else if (intersectA01.t == INTERSECTION::COLLISION)
			break;

		if (intersectA30.t == INTERSECTION::TOUCH)
			for (std::set<FrontierPoint>::iterator it = intersectA30.points.begin(); it != intersectA30.points.end(); ++it)
			{
				A30.insert(*it);
				if (it->coords == newPoint.coords)
					newPoint.blockIDs.insert(it->blockIDs.begin(), it->blockIDs.end());
				if (it->coords == vtxB->coords)
					newPoint.blockIDs.insert(vtxB->blockIDs.begin(), vtxB->blockIDs.end());
			}
		else if (intersectA01.t == INTERSECTION::COLLISION)
			break;

		testFrontierRes.push_back(newPoint);

		++vtxB;
		if (vtxB == testFrontier.end())
		{
			vtxB = testFrontier.begin();
		}
		++vtxA;
	}

	std::cout << "Key indexes in A01: ";
	printFrontierPoints(A01.begin(), A01.end());
	std::cout << "Key indexes in A12: ";
	printFrontierPoints(A12.begin(), A12.end());
	std::cout << "Key indexes in A23: ";
	printFrontierPoints(A23.begin(), A23.end());
	std::cout << "Key indexes in A30: ";
	printFrontierPoints(A30.begin(), A30.end());

	std::cout << "Frontier after additions: " << std::endl;
	printFrontierPoints(testFrontierRes.begin(), testFrontierRes.end());

} 