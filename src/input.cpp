#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

void readFile(string fileName, int &bufferSize, vector<vector<string>> &playMatrix, vector<vector<string>> &seqVec, vector<int> &rewardVec){
    ifstream file(fileName);
    if(!file.is_open()){
        cout << "File gagal dibuka, silahkan coba lagi!" << endl;
    }else{
        int row, col, numOfSeq;
        string token;
        file >> bufferSize;
        file >> row >> col;
        playMatrix = vector<vector<string>>(row, vector<string>(col, ""));
        for (int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                file >> token;
                playMatrix[i][j] = token;
            }
        }
        file >> numOfSeq;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        seqVec.resize(numOfSeq);
        string line;
        for (int i = 0; i < numOfSeq; i++){
            getline(file, line);
            stringstream strStream(line);
            while(strStream >> token){
                seqVec[i].push_back(token);
            }
            int temp;
            file >> temp;
            rewardVec.push_back(temp);
            file.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
    }
}

void readTerminal(vector<vector<string>> &playMatrix, vector<vector<string>> &seqVec, int &bufferSize, vector<int> &rewardVec){
    int totUniqueTokens, row, col, numOfSeq, maxSizeSeq;
    vector<string> tokenVec;
    random_device rd;
    mt19937 gen(rd());
    cin >> totUniqueTokens;
    for (int i = 0; i < totUniqueTokens; i++){
        string token;
        cin >> token;
        tokenVec.push_back(token);
    }
    cin >> bufferSize;
    cin >> row >> col;
    cin >> numOfSeq;
    cin >> maxSizeSeq;
    seqVec.resize(numOfSeq);
    for (int i = 0; i < numOfSeq; i++){
        uniform_int_distribution<> disSeqSize(2, maxSizeSeq);
        int seqSize = disSeqSize(gen);
        for(int j = 0; j < seqSize; j++){
            uniform_int_distribution<> disTokenIndex(0, totUniqueTokens-1);
            int randTokenIndex = disTokenIndex(gen);
            seqVec[i].push_back(tokenVec[randTokenIndex]);
        }
        uniform_int_distribution<> disReward(10, 50);
        int reward = disReward(gen);
        rewardVec.push_back(reward);
    }
    playMatrix = vector<vector<string>>(row, vector<string>(col, ""));
    for (int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            uniform_int_distribution<> disMatrix(0, totUniqueTokens-1);
            int randTokenIndex = disMatrix(gen);
            playMatrix[i][j] = tokenVec[randTokenIndex];
        }
    }
}

void printMatrix(const vector<vector<string>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

void printVector(const vector<int>& vec) {
    for (const auto& value : vec) {
        cout << value << " ";
    }
    cout << endl;
}

// int main(){
//     string namaFile;
//     int bufferSize;
//     vector<vector<string>> playMatrix;
//     vector<vector<string>> seqVec;
//     vector<int> rewardVec;
//     cout << "Masukkan namafile" << endl;
//     cin >> namaFile;
//     readFile(namaFile, bufferSize, playMatrix, seqVec, rewardVec);
//     printMatrix(playMatrix);
//     printMatrix(seqVec);
//     printVector(rewardVec);
//     return 0;
// }

// int main(){
//     string namaFile;
//     int bufferSize;
//     vector<vector<string>> playMatrix;
//     vector<vector<string>> seqVec;
//     vector<int> rewardVec;
//     readTerminal(playMatrix, seqVec, bufferSize, rewardVec);
//     printMatrix(playMatrix);
//     printMatrix(seqVec);
//     printVector(rewardVec);
//     return 0;
// }