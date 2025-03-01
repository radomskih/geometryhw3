#include <time.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <random>
#include "kd_tree.cpp"
#include "RangeTree.h"
#include "plot.h"

using namespace std;

int main() {

	//pick range to search for all trees
	int xmax = rand() % 1000;
	int xmin = rand() % xmax;
	int ymax = rand() % 1000;
	int ymin = rand() % ymax;

	vector<int> lowers({ xmin, ymin }); //construct range input for trees
	vector<int> uppers({ xmax, ymax });

	vector<bool> borders({ true, true });


	//1. range searches with 100 random points
	
	//generate 100 random points 
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(0, 1000);
	vector<int> point;
	vector<vector<int>>* points1 = new vector<vector<int>>;
	vector<RangeTree::Point<int, int>>* rangePoints1 = new vector<RangeTree::Point<int, int>>;
	for (int i = 0; i < 100; ++i) {
		point.push_back(distribution(gen));
		point.push_back(distribution(gen));
		points1->push_back(point);
		RangeTree::Point<int, int> newPoint(point, 0);
		rangePoints1->push_back(newPoint);
		point.clear();
	}


	//1A. kd tree search
	auto start = chrono::high_resolution_clock::now(); //time the construction of the tree
	KDTree<int>* kdTree1 = new KDTree<int>;
	for (vector<int> pt : *points1) {
		kdTree1->insert(pt);
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdBuild1 = end - start;

	start = chrono::high_resolution_clock::now(); //time the query
	vector<vector<int>> kdResults1 = kdTree1->orthogonal_search(lowers, uppers);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdQuery1 = end - start;
	

	//1B. range tree search
	start = chrono::high_resolution_clock::now(); //time the  construction
	RangeTree::RangeTree<int, int>* rangeTree1 = new RangeTree::RangeTree<int, int>(*rangePoints1);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeBuild1 = end - start;

	start = chrono::high_resolution_clock::now(); //time the query 
	vector<RangeTree::Point<int, int>> rangeResults1 = rangeTree1->pointsInRange(lowers, uppers, borders, borders);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeQuery1 = end - start;

	//deallocate memory used for points and trees
	delete points1;
	delete rangePoints1;
	delete kdTree1;
	delete rangeTree1;

	//2. range searches with 1,000 random points
	vector<vector<int>>* points2 = new vector<vector<int>>;
	vector<RangeTree::Point<int, int>>* rangePoints2 = new vector<RangeTree::Point<int, int>>;
	for (int i = 0; i < 1000; ++i) { //generate points
		point.push_back(distribution(gen));
		point.push_back(distribution(gen));
		points2->push_back(point);
		RangeTree::Point<int, int> newPoint(point, 0);
		rangePoints2->push_back(newPoint);
		point.clear();
	}


	//2A. kd tree search

	start = chrono::high_resolution_clock::now(); //time construction
	KDTree<int>* kdTree2 = new KDTree<int>;
	for (vector<int> pt : *points2) {
		kdTree2->insert(pt);
	}
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdBuild2 = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<vector<int>> kdResults2 = kdTree2->orthogonal_search(lowers, uppers);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdQuery2 = end - start;


	//2B. range tree search
	start = chrono::high_resolution_clock::now(); //time construction
	RangeTree::RangeTree<int, int>* rangeTree2 = new RangeTree::RangeTree<int, int>(*rangePoints2);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeBuild2 = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<RangeTree::Point<int, int>> rangeResults2 = rangeTree2->pointsInRange(lowers, uppers, borders, borders);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeQuery2 = end - start;

	delete points2;
	delete rangePoints2;
	delete kdTree2;
	delete rangeTree2;

	//3. range searches with 10,000 random points
	vector<vector<int>>* points3 = new vector<vector<int>>;
	vector<RangeTree::Point<int, int>>* rangePoints3 = new vector<RangeTree::Point<int, int>>;
	for (int i = 0; i < 10000; ++i) {
		point.push_back(distribution(gen));
		point.push_back(distribution(gen));
		points3->push_back(point);
		RangeTree::Point<int, int> newPoint(point, 0);
		rangePoints3->push_back(newPoint);
		point.clear();
	}


	//3A. kd tree search
	start = chrono::high_resolution_clock::now(); //time construction
	KDTree<int>* kdTree3 = new KDTree<int>;
	for (vector<int> pt : *points3) {
		kdTree3->insert(pt);
	}
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdBuild3 = end - start;


	start = chrono::high_resolution_clock::now(); //time query
	vector<vector<int>> kdResults3 = kdTree3->orthogonal_search(lowers, uppers);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdQuery3 = end - start;


	//3B. range tree search
	start = chrono::high_resolution_clock::now(); //time construction
	RangeTree::RangeTree<int, int>* rangeTree3 = new RangeTree::RangeTree<int, int>(*rangePoints3);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeBuild3 = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<RangeTree::Point<int, int>> rangeResults3 = rangeTree3->pointsInRange(lowers, uppers, borders, borders);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeQuery3 = end - start;

	delete points3;
	delete rangePoints3;
	delete kdTree3;
	delete rangeTree3;

	//4. range searches with 100,000 random points
	vector<vector<int>>* points4 = new vector<vector<int>>;
	vector<RangeTree::Point<int, int>>* rangePoints4 = new vector<RangeTree::Point<int, int>>;
	for (int i = 0; i < 100000; ++i) {
		point.push_back(distribution(gen));
		point.push_back(distribution(gen));
		points4->push_back(point);
		RangeTree::Point<int, int> newPoint(point, 0);
		rangePoints4->push_back(newPoint);
		point.clear();
	}


	//4A. kd tree search
	start = chrono::high_resolution_clock::now(); //time construction
	KDTree<int>* kdTree4 = new KDTree<int>;
	for (vector<int> pt : *points4) {
		kdTree4->insert(pt);
	}
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdBuild4 = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<vector<int>> kdResults4 = kdTree4->orthogonal_search(lowers, uppers);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdQuery4 = end - start;


	//4B. range tree search
	start = chrono::high_resolution_clock::now(); //time construction
	RangeTree::RangeTree<int, int>* rangeTree4 = new RangeTree::RangeTree<int, int>(*rangePoints4);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeBuild4 = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<RangeTree::Point<int, int>> rangeResults4 = rangeTree4->pointsInRange(lowers, uppers, borders, borders);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeQuery4 = end - start;

	delete points4;
	delete rangePoints4;
	delete kdTree4;
	delete rangeTree4;

	//5. Plot Times for Random Point Sets
	signalsmith::plot::Plot2D buildPlot; //create plot for build times
	buildPlot.x.label("Point Set Size").range(log, 100, 100000).ticks(100, 1000, 10000, 100000);
	buildPlot.y.label("Time (s)");

	auto& kdLineb = buildPlot.line(); //add a line for each tree
	kdLineb.add(100, kdBuild1.count());
	kdLineb.add(1000, kdBuild2.count());
	kdLineb.add(10000, kdBuild3.count());
	kdLineb.add(100000, kdBuild4.count());
	kdLineb.label("kd");

	auto& rangeLineb = buildPlot.line();
	rangeLineb.add(100, rangeBuild1.count());
	rangeLineb.add(1000, rangeBuild2.count());
	rangeLineb.add(10000, rangeBuild3.count());
	rangeLineb.add(100000, rangeBuild4.count());
	rangeLineb.label("range");

	buildPlot.write("buildTimesUniform.svg"); //save to a file

	signalsmith::plot::Plot2D queryPlot; //create plot for query times
	queryPlot.x.label("Point Set Size").range(log, 100, 100000).ticks(100, 1000, 10000, 100000);
	queryPlot.y.label("Time (s)");

	auto& kdLineq = queryPlot.line(); //create line for kd
	kdLineq.add(100, kdQuery1.count());
	kdLineq.add(1000, kdQuery2.count());
	kdLineq.add(10000, kdQuery3.count());
	kdLineq.add(100000, kdQuery4.count());
	kdLineq.label("kd");

	auto& rangeLineq = queryPlot.line(); //create line for range
	rangeLineq.add(100, rangeQuery1.count());
	rangeLineq.add(1000, rangeQuery2.count());
	rangeLineq.add(10000, rangeQuery3.count());
	rangeLineq.add(100000, rangeQuery4.count());
	rangeLineq.label("range");

	queryPlot.write("queryTimesUniform.svg"); //save to file


	//now repeat, for a different distribution

	binomial_distribution<int> distributionb(1000, 0.5);

	//6. range searches with 100 points with binomial distribution

	//generate 100 random points 
	vector<vector<int>>* points1b = new vector<vector<int>>;
	vector<RangeTree::Point<int, int>>* rangePoints1b = new vector<RangeTree::Point<int, int>>;
	for (int i = 0; i < 100; ++i) {
		point.push_back(distributionb(gen));
		point.push_back(distributionb(gen));
		points1b->push_back(point);
		RangeTree::Point<int, int> newPoint(point, 0);
		rangePoints1b->push_back(newPoint);
		point.clear();
	}


	//6A. kd tree search
	start = chrono::high_resolution_clock::now(); //time the construction of the tree
	KDTree<int>* kdTree1b = new KDTree<int>;
	for (vector<int> pt : *points1b) {
		kdTree1b->insert(pt);
	}
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdBuild1b = end - start;

	start = chrono::high_resolution_clock::now(); //time the query
	vector<vector<int>> kdResults1b = kdTree1b->orthogonal_search(lowers, uppers);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdQuery1b = end - start;


	//6B. range tree search
	start = chrono::high_resolution_clock::now(); //time the  construction
	RangeTree::RangeTree<int, int>* rangeTree1b = new RangeTree::RangeTree<int, int>(*rangePoints1b);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeBuild1b = end - start;

	start = chrono::high_resolution_clock::now(); //time the query 
	vector<RangeTree::Point<int, int>> rangeResults1b = rangeTree1b->pointsInRange(lowers, uppers, borders, borders);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeQuery1b = end - start;

	//deallocate memory used for points and trees
	delete points1b;
	delete rangePoints1b;
	delete kdTree1b;
	delete rangeTree1b;

	//7. range searches with 1,000 points with binomial distribution
	vector<vector<int>>* points2b = new vector<vector<int>>;
	vector<RangeTree::Point<int, int>>* rangePoints2b = new vector<RangeTree::Point<int, int>>;
	for (int i = 0; i < 1000; ++i) { //generate points
		point.push_back(distributionb(gen));
		point.push_back(distributionb(gen));
		points2b->push_back(point);
		RangeTree::Point<int, int> newPoint(point, 0);
		rangePoints2b->push_back(newPoint);
		point.clear();
	}


	//7A. kd tree search

	start = chrono::high_resolution_clock::now(); //time construction
	KDTree<int>* kdTree2b = new KDTree<int>;
	for (vector<int> pt : *points2b) {
		kdTree2b->insert(pt);
	}
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdBuild2b = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<vector<int>> kdResults2b = kdTree2b->orthogonal_search(lowers, uppers);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdQuery2b = end - start;


	//7B. range tree search
	start = chrono::high_resolution_clock::now(); //time construction
	RangeTree::RangeTree<int, int>* rangeTree2b = new RangeTree::RangeTree<int, int>(*rangePoints2b);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeBuild2b = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<RangeTree::Point<int, int>> rangeResults2b = rangeTree2b->pointsInRange(lowers, uppers, borders, borders);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeQuery2b = end - start;

	delete points2b;
	delete rangePoints2b;
	delete kdTree2b;
	delete rangeTree2b;

	//8. range searches with 10,000 points with binomial distribution
	vector<vector<int>>* points3b = new vector<vector<int>>;
	vector<RangeTree::Point<int, int>>* rangePoints3b = new vector<RangeTree::Point<int, int>>;
	for (int i = 0; i < 10000; ++i) {
		point.push_back(distributionb(gen));
		point.push_back(distributionb(gen));
		points3b->push_back(point);
		RangeTree::Point<int, int> newPoint(point, 0);
		rangePoints3b->push_back(newPoint);
		point.clear();
	}


	//8A. kd tree search
	start = chrono::high_resolution_clock::now(); //time construction
	KDTree<int>* kdTree3b = new KDTree<int>;
	for (vector<int> pt : *points3b) {
		kdTree3b->insert(pt);
	}
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdBuild3b = end - start;


	start = chrono::high_resolution_clock::now(); //time query
	vector<vector<int>> kdResults3b = kdTree3b->orthogonal_search(lowers, uppers);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdQuery3b = end - start;


	//8B. range tree search
	start = chrono::high_resolution_clock::now(); //time construction
	RangeTree::RangeTree<int, int>* rangeTree3b = new RangeTree::RangeTree<int, int>(*rangePoints3b);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeBuild3b = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<RangeTree::Point<int, int>> rangeResults3b = rangeTree3b->pointsInRange(lowers, uppers, borders, borders);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeQuery3b = end - start;

	delete points3b;
	delete rangePoints3b;
	delete kdTree3b;
	delete rangeTree3b;

	//9. range searches with 100,000 points with binomial distribution
	vector<vector<int>>* points4b = new vector<vector<int>>;
	vector<RangeTree::Point<int, int>>* rangePoints4b = new vector<RangeTree::Point<int, int>>;
	for (int i = 0; i < 100000; ++i) {
		point.push_back(distributionb(gen));
		point.push_back(distributionb(gen));
		points4b->push_back(point);
		RangeTree::Point<int, int> newPoint(point, 0);
		rangePoints4b->push_back(newPoint);
		point.clear();
	}


	//9A. kd tree search
	start = chrono::high_resolution_clock::now(); //time construction
	KDTree<int>* kdTree4b = new KDTree<int>;
	for (vector<int> pt : *points4b) {
		kdTree4b->insert(pt);
	}
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdBuild4b = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<vector<int>> kdResults4b = kdTree4b->orthogonal_search(lowers, uppers);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> kdQuery4b = end - start;


	//9B. range tree search
	start = chrono::high_resolution_clock::now(); //time construction
	RangeTree::RangeTree<int, int>* rangeTree4b = new RangeTree::RangeTree<int, int>(*rangePoints4b);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeBuild4b = end - start;

	start = chrono::high_resolution_clock::now(); //time query
	vector<RangeTree::Point<int, int>> rangeResults4b = rangeTree4b->pointsInRange(lowers, uppers, borders, borders);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> rangeQuery4b = end - start;

	delete points4b;
	delete rangePoints4b;
	delete kdTree4b;
	delete rangeTree4b;

	//10. Plot times for binomial point sets
	signalsmith::plot::Plot2D buildPlotb; //create plot for build times
	buildPlotb.x.label("Point Set Size").range(log, 100, 100000).ticks(100, 1000, 10000, 100000);
	buildPlotb.y.label("Time (s)");

	auto& kdLinebb = buildPlotb.line(); //add a line for each tree
	kdLinebb.add(100, kdBuild1b.count());
	kdLinebb.add(1000, kdBuild2b.count());
	kdLinebb.add(10000, kdBuild3b.count());
	kdLinebb.add(100000, kdBuild4b.count());
	kdLinebb.label("kd");

	auto& rangeLinebb = buildPlotb.line();
	rangeLinebb.add(100, rangeBuild1b.count());
	rangeLinebb.add(1000, rangeBuild2b.count());
	rangeLinebb.add(10000, rangeBuild3b.count());
	rangeLinebb.add(100000, rangeBuild4b.count());
	rangeLinebb.label("range");

	buildPlotb.write("buildTimesBinomial.svg"); //save to a file

	signalsmith::plot::Plot2D queryPlotb; //create plot for query times
	queryPlotb.x.label("Point Set Size").range(log, 100, 100000).ticks(100, 1000, 10000, 100000);
	queryPlotb.y.label("Time (s)");

	auto& kdLineqb = queryPlotb.line(); //create line for kd
	kdLineqb.add(100, kdQuery1b.count());
	kdLineqb.add(1000, kdQuery2b.count());
	kdLineqb.add(10000, kdQuery3b.count());
	kdLineqb.add(100000, kdQuery4b.count());
	kdLineqb.label("kd");

	auto& rangeLineqb = queryPlotb.line(); //create line for range
	rangeLineqb.add(100, rangeQuery1b.count());
	rangeLineqb.add(1000, rangeQuery2b.count());
	rangeLineqb.add(10000, rangeQuery3b.count());
	rangeLineqb.add(100000, rangeQuery4b.count());
	rangeLineqb.label("range");

	queryPlotb.write("queryTimesBinomial.svg"); //save to file

	return 0;
}