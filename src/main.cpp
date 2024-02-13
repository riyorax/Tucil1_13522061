#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "algorithm.cpp"

using namespace std;

int main(){
    int bufferSize, maxPoints, options;
    long long runTime;
    vector<vector<string>> playMatrix, seqVec;
    vector<int> rewardVec;
    vector<pair<int, int>> bestPathCoordinates;
    vector<string> bestPath;
    bool running;

    maxPoints = 0;
    running = true;
    while(running){
        bufferSize = 0;
        maxPoints = 0;
        runTime = 0;
        playMatrix.clear();
        seqVec.clear();
        rewardVec.clear();
        bestPathCoordinates.clear();
        bestPath.clear();
        cout << "---------------------------------------------------------" << endl;
        cout << "Cyberpunk 2077 Breach Protocol with Brute Force Algorithm" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "Pilih opsi input:                                    " << endl;
        cout << "1. File (txt)" << endl;
        cout << "2. Command Line Interface" << endl;
        cout << "3. Exit" << endl << endl << ">> ";
        cin >> options;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Input harus berupa angka! Silahkan coba lagi!" << endl;
            continue;
        }

        switch(options){
            case 1: {
                string fileName, filePath;
                cout << "Masukkkan nama file, pastikan berada di folder test: " << endl << endl << ">> ";
                cin >> fileName;
                filePath = "test/" + fileName;
                if(readFile(filePath, bufferSize, playMatrix, seqVec, rewardVec)){
                    bruteForceSolution(playMatrix, bufferSize, seqVec, rewardVec, maxPoints, bestPath, bestPathCoordinates, runTime);
                    if(maxPoints > 0){
                        printOutput(maxPoints, bestPath, bestPathCoordinates, runTime);
                        saveFileOptions(maxPoints, bestPath, bestPathCoordinates, runTime);
                    }else{
                        cout << "Tidak ada solusi!!" << endl;
                        cout << "0ms" << endl;
                    }
                }
                break;
            }
            case 2:
                readTerminal(playMatrix, seqVec, bufferSize, rewardVec);
                bruteForceSolution(playMatrix, bufferSize, seqVec, rewardVec, maxPoints, bestPath, bestPathCoordinates, runTime);
                if(maxPoints > 0){
                    printOutput(maxPoints, bestPath, bestPathCoordinates, runTime);
                    saveFileOptions(maxPoints, bestPath, bestPathCoordinates, runTime);
                }else{
                    cout << "Tidak ada solusi!!" << endl;
                    cout << "0ms" << endl;
                }
                break;
            case 3:
                running = false;
                break;
            default:
                cout << "Pastikan input antara 1-3! Silahkan coba kembali" << endl;
                break;
        }
    }
    return 0;
}