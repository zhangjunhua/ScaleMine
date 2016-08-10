/**
 * Copyright 2016 Ehab Abdelhamid, Ibrahim Abdelaziz

Miner.h

This file is part of ScaleMine.

ScaleMine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

ScaleMine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Grami.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * the base mining class for the master
 */

#ifndef MINER_H_
#define MINER_H_

#include "Pattern.h"
#include "CLMap.h"

class Miner
{
private:
	CLMap processed;
	bool* availableWorker;

protected:
	//expected patterns generated by an approximate miner. These patterns follow the same as the exact ones.
	//it is used to have more candidates when there are not enough candidates to make workers busy.
	vector<CLMap* >* expected_frequentPatterns = 0;
	vector<CLMap* >* expected_infrequentPatterns = 0;

	GraphX* graph = 0;
	int support;
	//frequent edges
	CLMap frequentEdges;
	map<string, long long> isFrerqtimes;
	int numInsertedCandids = 0;
	unsigned long masterProcessingTime = 0;
	//create variables for graph loading time, processing time for each worker
	unsigned long* graphloadingTime;
	unsigned long* processingTime;

	long long graphLoadingElapsed;

	//frequent patterns sorted in a vector, nth element in the vector is hash map of all patterns having n edges
	//each hashmap is keyed by the canonical form of the value graph (pattern)
	vector<CLMap* > frequentPatterns;
	vector<CLMap* > infrequentPatterns;

	vector<CLMap* > candidates;
	void print(vector<CLMap* >& );
	map<int, Pattern* > currentlyChecking;
	virtual void popACandidate(CLMap* , map<int, Pattern*>& , int destination);
	virtual void sendACandidate(string key, Pattern* candidate, map<int, Pattern*>& currentlyChecking, int destination);
	void removePattern(Pattern* pattern, vector<CLMap* >& data);

public:
	static int numIsFreqCalls;
	static int numFreqs;
	static int numInfreq;
	Miner();
	~Miner();
	void initMining(string ,int ,int ,int );
	void startMining(int );
	void loadGraph(string , int , int , CLMap& );
	void printResult();
	void printCandidates();

	int getSupport() {return support; }
	void setSupport(int support) {this->support = support; }
	CLMap& getFrequentEdges() { return frequentEdges; }
	void setFrequentEdges(CLMap& );
	void extendFreqEdges();

	vector<CLMap* >* getFrequentPatterns() { return &frequentPatterns; }
	vector<CLMap* >* getInfrequentPatterns() { return &infrequentPatterns; }

	void setExpectedPatterns(vector<CLMap* >* exFreqPatt, vector<CLMap* >* exInfreqPatt)
	{
		expected_frequentPatterns = exFreqPatt;
		expected_frequentPatterns->at(1)->clear();
		expected_infrequentPatterns = exInfreqPatt;
	}
};

#endif /* MINER_H_ */
