// Si Jine Roh
// CSCE 315 - 505
// Due: January 30, 2015
// Project1.cpp
/*
If this program shows you an error, please use the command above to compile.
I've get the basic concept of this problem from the lecture and Wikipedia.
The way of solving this problem is finding the shortest neighbor and keep moving on.
Yin Qu helped me to optimize my solution.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct nodeSet {
	// custom structure to store index value and distance
	int id; // this store index value of node
	double distance; // this store distance between this node and a given node
};

vector<double> XList; // save x coordinates of given file
vector<double> YList; // save y coordinates of given file
vector<bool> UsedList; // save node is used or not, false = not used, true = used
vector<vector<nodeSet>> DistanceTable; // save distance from first index node to each node
vector<int> ShortestPath; // save the shortest path list
double ShortestDistance; // save the shortest path distance

vector<nodeSet> sortVector(vector<nodeSet> v) {
	// sort a given vector v by ascending order based on nodeSet.distance and return v
	int tempID;
	double tempDistance;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			if (v[i].distance < v[j].distance) {
				tempID = v[i].id;
				tempDistance = v[i].distance;
				v[i].id = v[j].id;
				v[i].distance = v[j].distance;
				v[j].id = tempID;
				v[j].distance = tempDistance;
			}
		}
	}
	return v;
}

vector<bool> resetUsedList(vector<bool> v) {
	// put false into all of elements of given vector v and return v
	for (int i = 0; i < v.size(); ++i) {
		v[i] = false;
	}
	return v;
}

void printPath(vector<int> v, double d) {
	// print out the path of node index and the distance
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << endl;
	}
	cout << d << endl;
}

int putXYList() {
	// get XY coordinates from a given file and save it.
	// returns total number of nodes.
	int totalNodes = 0; // total numbers of Nodes
	string inputString; // save line by line into this var
	bool isEOF = false;
	while (getline (cin,inputString) && !cin.eof()) {
		if (inputString[0] == '#'); // check the input line is a comment or not
		// else if (inputString == "^D") { // check current input string is EOF or not
		// 	isEOF = true;
		// }
		else {
			XList.push_back(stod(inputString.substr(0, inputString.find("\t"))));
			YList.push_back(stod(inputString.substr(inputString.find("\t") + 1)));
			UsedList.push_back(false);
			totalNodes ++;
		}
	}
	return totalNodes;
}

void buildDistanceTable(int totalNodes) {
	// build Distance Table for every nodes
	// save distance between index node to other nodes
	double squareX; // save absolute value of difference between X coordinate
	double squareY; // save absolute value of difference between Y coordinate
	for (int i = 0; i < totalNodes; ++i) {
		vector<nodeSet> tempDistanceRow;
		for (int j = 0; j < totalNodes; ++j) {
			if (i != j) {
				squareX = XList[i] - XList[j];
				squareY = YList[i] - YList[j];
				nodeSet intoTempRow;
				intoTempRow.id = j;
				intoTempRow.distance = sqrt((squareX * squareX) + (squareY * squareY));
				tempDistanceRow.push_back(intoTempRow);
			}
		}
		tempDistanceRow = sortVector(tempDistanceRow);
		DistanceTable.push_back(tempDistanceRow);
	}
}

void findShortestPath(int totalNodes){
		for (int i = 0; i < totalNodes; ++i) {
		int cnt = 1;
		int currentNode = i;
		double tempDistance = 0;
		vector<int> tempPath;
		while (cnt <= totalNodes) {
			int j;
			for (j = 0; UsedList[DistanceTable[currentNode][j].id]; ++j);
			UsedList[DistanceTable[currentNode][j].id] = true;
			tempDistance += DistanceTable[currentNode][j].distance;
			currentNode = DistanceTable[currentNode][j].id;
			tempPath.push_back(DistanceTable[currentNode][j].id);
			cnt ++;
		}
		UsedList = resetUsedList(UsedList);
		if (i == 0) {
			ShortestDistance = tempDistance;
			ShortestPath = tempPath;
		}
		else if (ShortestDistance > tempDistance) {
			ShortestDistance = tempDistance;
			ShortestPath = tempPath;
		}
	}
}

int main(){
	int totalNodes = putXYList(); // put XY coordinates into vectors
	buildDistanceTable(totalNodes); // build distance table
	findShortestPath(totalNodes);
	printPath(ShortestPath, ShortestDistance);
	return 0;
}