// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>

class ArrayList
{
private:
	std::pair<unsigned int, std::string>* pArray = NULL;
	const unsigned int GROW_SIZE = 512;
	unsigned int currentIndex;
	unsigned int arraySize;
public:
	ArrayList();
	~ArrayList();
	void add(std::pair<unsigned int, std::string> vdata);
	void getAll();
	unsigned int getSize();
};

ArrayList::ArrayList()
{
	pArray = new std::pair<unsigned int, std::string>[GROW_SIZE];
	currentIndex = 0;
	arraySize = GROW_SIZE;
}

ArrayList::~ArrayList()
{
	if (pArray != NULL) {
		delete[] pArray;
	}
}

void ArrayList::add(std::pair<unsigned int, std::string> vdata)
{
	std::pair<unsigned int, std::string>* tmpArray = NULL;

	for (int i = 0; i < currentIndex; i++) {
		if (pArray[i].first == vdata.first) {
			return;
		}
	}
	for (int i = 0; i < currentIndex; i++) {
		if (pArray[i].second == vdata.second) {
			return;
		}
	}
	
	if (currentIndex >= arraySize) {
		arraySize += GROW_SIZE;		// 倍のサイズにするなら(vectorの実装とか)O(1), このやり方だとO(logN)になる？
		tmpArray = new std::pair<unsigned int, std::string>[arraySize];
		for (int i = 0; i < currentIndex; i++) {
			tmpArray[i] = pArray[i];
		}
		delete[] pArray;
		pArray = tmpArray;
	}

	pArray[currentIndex++] = vdata;
}

void ArrayList::getAll()
{
	for (int i = 0; i < currentIndex; i++) {
		std::pair<unsigned int, std::string> v = pArray[i];
	}
}

unsigned int ArrayList::getSize()
{
	return currentIndex;
}



class MapData
{
private:
	typedef std::pair<unsigned int, std::string> pVarData;
	
	std::vector<pVarData> pArray;
	std::map<std::string, pVarData*> nameMap;
	std::map<unsigned int, pVarData*> idMap;
	
public:
	MapData();
	~MapData();
	void add(std::pair<unsigned int, std::string> vdata);
	void getAll();
	unsigned int getSize();
	void resize();
	void deleteMaps();
};

MapData::MapData()
{
}

MapData::~MapData()
{
}

void MapData::add(std::pair<unsigned int, std::string> vdata)
{

	std::map<std::string, pVarData*>::iterator itr = nameMap.find(vdata.second);
	if (itr != nameMap.end()) {
		return;
	}
	std::map<unsigned int, pVarData*>::iterator itr2 = idMap.find(vdata.first);
	if (itr2 != idMap.end()) {
		return;
	}

	pArray.push_back(vdata);
	nameMap[vdata.second] = &vdata;
	idMap[vdata.first] = &vdata;
}

unsigned int MapData::getSize()
{
	return pArray.size();
}

void MapData::getAll()
{
	for (std::vector<pVarData>::iterator i = pArray.begin(); i != pArray.end(); ++i) {
		pVarData v = *i;
	}
}

void MapData::resize()
{
	std::cout << "(before) capacity = " << pArray.capacity() << std::endl;
	std::vector<pVarData>(pArray).swap(pArray);
	std::cout << "(after) capacity = " << pArray.capacity() << std::endl;
}

void MapData::deleteMaps()
{
	nameMap.clear();
	idMap.clear();
}


int main()
{
	const unsigned int VARNUM = 100000;
	const unsigned int MAXSTRLEN = 12;

	std::vector<std::pair<unsigned int, std::string>> varData(VARNUM);

	ArrayList arr;
	MapData mapdata;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < VARNUM; i++) {
		//unsigned int strLen = rand() % MAXSTRLEN + 5;
		unsigned int strLen = 5;
		std::string str = "";
		for (int j = 0; j < strLen; j++) {
			str += 'a' + rand() % 26;
		}
		varData[i] = make_pair(i, str);
	}

	for (int i = 0; i<VARNUM; i++) {
		int j = rand() % VARNUM;
		std::pair<unsigned int, std::string> tmp = varData[i];
		varData[i] = varData[j];
		varData[j] = tmp;
	}

	std::cout << "Start to list.\n";

	clock_t start, end;

	// ここまで6mb

	start = clock();
	for (int i = 0; i < varData.size(); i++) {		// 23.1mb - 6mb = 17.1mb
		mapdata.add(varData[i]);
		//std::cout << varData[i].first << " = " << varData[i].second << "\n";
	}
	end = clock();
	std::cout << "Test2: duration = " << end - start << "msec\n";
	std::cout << "Test2: size = " << mapdata.getSize() << "\n";
	mapdata.resize();
	mapdata.deleteMaps();

	//start = clock();
	//for (int i = 0; i < varData.size(); i++) {			// 12.4mb - 6mb = 6.4mb
	//	arr.add(varData[i]);
	//	//std::cout << varData[i].first << " = " << varData[i].second << "\n";
	//}
	//end = clock();
	//std::cout << "Test1: duration = " << end - start << "msec\n";
	//std::cout << "Test1: size = " << arr.getSize() << "\n";
	
	//start = clock();
	//mapdata.getAll();
	//end = clock();
	//std::cout << "Test2 getAll: duration = " << end - start << "msec\n";

	//start = clock();
	//arr.getAll();
	//end = clock();
	//std::cout << "Test1 getAll: duration = " << end - start << "msec\n";


	system("pause");
	return 0;

}