#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include "utilities.cpp"

using namespace std;

int stringMatchingPoint(vector<string> path, vector<vector<string>> seqVec, vector<int> rewardVec){
    int numOfSeq, i, j, k, points, pathSize, seqSize;
    vector<string> currSeq;
    bool found;

    numOfSeq = seqVec.size();
    pathSize = path.size();
    points = 0;

    for(i = 0; i < numOfSeq; i++){
        currSeq = seqVec[i];
        seqSize = currSeq.size();
        j = 0;
        found = false;

        while(j <= pathSize-seqSize && !found){
            k = 0;
            while(k <= seqSize && currSeq[k] == path[j+k]){
                k++;
            }
            if(k == seqSize){
                found = true;
            }else{
                j++;
            }
        }

        if(found){
            points += rewardVec[i];
        }
    }
    return points;
}

void findPath(vector<vector<string>> playMatrix, int currRow, int currCol, int remainingBuffer, bool isVertical, vector<string> &path, vector<vector<bool>> &visited, int &maxPoints, vector<string> &bestPath, vector<vector<string>> seqVec, vector<int> rewardVec, vector<pair<int, int>> &pathCoordinates, vector<pair<int, int>> &bestPathCoordinates){
    int row = playMatrix.size();
    int col = playMatrix[0].size();

    if(!(currRow >= 0 && currRow < row && currCol >= 0 && currCol < col && !visited[currRow][currCol])){
        return;
    }

    visited[currRow][currCol] = true;
    path.push_back(playMatrix[currRow][currCol]);
    pathCoordinates.push_back({currCol+1, currRow+1});

    int points = stringMatchingPoint(path, seqVec, rewardVec);
    if(points > maxPoints){
        maxPoints = points;
        bestPath = path;
        bestPathCoordinates = pathCoordinates;
    }

    if(remainingBuffer > 1){
        if(isVertical) {
            for(int nextRow = 0; nextRow < row; nextRow++){
                if(nextRow != currRow && !visited[nextRow][currCol]) {
                    findPath(playMatrix, nextRow, currCol, remainingBuffer - 1, false, path, visited, maxPoints, bestPath, seqVec, rewardVec, pathCoordinates, bestPathCoordinates);
                }
            }
        }else{
            for(int nextCol = 0; nextCol < col; nextCol++){
                if(nextCol != currCol && !visited[currRow][nextCol]){
                    findPath(playMatrix, currRow, nextCol, remainingBuffer - 1, true, path, visited, maxPoints, bestPath, seqVec, rewardVec, pathCoordinates, bestPathCoordinates);
                }
            }
        }
    }

    visited[currRow][currCol] = false;
    path.pop_back();
    pathCoordinates.pop_back();
}

void bruteForceSolution(vector<vector<string>> playMatrix, int bufferSize, vector<vector<string>> seqVec, vector<int> rewardVec, int &maxPoints, vector<string> &bestPath, vector<pair<int, int>> &bestPathCoordinates, long long &runTime){
    auto start = chrono::high_resolution_clock::now();
    int row, col;
    vector<pair<int, int>> pathCoordinates;

    row = playMatrix.size();
    col = playMatrix[0].size();
    vector<vector<bool>> visited(row, vector<bool>(col, false));

    for(int currCol = 0; currCol < col; currCol++){
        vector<string> path;
        findPath(playMatrix, 0, currCol, bufferSize, true, path, visited, maxPoints, bestPath, seqVec, rewardVec, pathCoordinates, bestPathCoordinates);
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    runTime = duration.count();
}