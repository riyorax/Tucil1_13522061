#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

void printMatrix(vector<vector<string>> matrix){
    for(auto row : matrix){
        for (auto element : row){
            cout << element << " ";
        }
        cout << endl;
    }
}

void printStringVector(vector<string> vec){
    for(auto elmt : vec) {
        cout << elmt << " ";
    }
    cout << endl;
}

bool readFile(string fileName, int &bufferSize, vector<vector<string>> &playMatrix, vector<vector<string>> &seqVec, vector<int> &rewardVec){
    ifstream file(fileName);

    if(!file.is_open()){
        cout << "File gagal dibuka / tidak ditemukan, silahkan coba lagi!" << endl;
        return false;
    }
    file.exceptions(ifstream::failbit | ifstream::badbit);
    try{
        int row, col, numOfSeq;
        string token;
        file >> bufferSize;
        file >> col >> row;
        playMatrix = vector<vector<string>>(row, vector<string>(col, ""));
        for(int i = 0; i < row; i++){
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
        
    }catch(const std::ifstream::failure& e){
        if (!file.eof()) {
            std::cerr << "Error occurred during file operations: " << e.what() << std::endl;
            return false;
        }
    } catch(...){
        cerr << "Sebuah error terjadi saat pembacaan file!" << endl;
        return false;
    }
    return true;
}

void readTerminal(vector<vector<string>> &playMatrix, vector<vector<string>> &seqVec, int &bufferSize, vector<int> &rewardVec){
    int totUniqueTokens, row, col, numOfSeq, maxSizeSeq;
    vector<string> tokenVec;
    random_device rd;
    mt19937 gen(rd());
    bool valid = false;
    while(!valid){
        cout << "Jumlah token unik: ";
        cin >> totUniqueTokens;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Silahkan coba lagi!" << endl;
            continue;
        }
        cout << "Token: ";
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Silahkan coba lagi!" << endl;
            continue;
        }
        for (int i = 0; i < totUniqueTokens; i++){
            string token;
            cin >> token;
            tokenVec.push_back(token);
        }
        cout << "Ukuran buffer: ";
        cin >> bufferSize;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Silahkan coba lagi!" << endl;
            continue;
        }

        cout << "Ukuran matrix (row,col): ";
        cin >> row >> col;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Silahkan coba lagi!" << endl;
            continue;
        }

        cout << "Jumlah sequence: ";
        cin >> numOfSeq;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Silahkan coba lagi!" << endl;
            continue;
        }

        cout << "Ukuran maximal sequence: ";
        cin >> maxSizeSeq;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Silahkan coba lagi!" << endl;
            continue;
        }else{
            valid = true;
        }
    }
    
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
    cout << endl << "Token Matrix: " << endl;
    printMatrix(playMatrix);
    for(int i = 0; i < numOfSeq; i++){
        cout << endl << "Sequence" << to_string(i+1) << ": ";
        printStringVector(seqVec[i]);
        cout << "Rewards: " << rewardVec[i] << endl;
    }
    cout << endl;
}


void printCoordinates(vector<pair<int, int>> pathCoordinates){
    for(auto coordinates : pathCoordinates){
        cout << coordinates.first << ", " << coordinates.second << endl;
    }
    cout << endl;
}

void printOutput(int maxPoints, vector<string> path, vector<pair<int, int>> pathCoordinates, long long runTime){
    cout << maxPoints << endl;
    printStringVector(path);
    printCoordinates(pathCoordinates);
    cout << endl << runTime << "ms" << endl << endl;
}

void saveFile(int maxPoints, vector<string> bestPath, vector<pair<int,int>> bestPathCoordinates, long long runTime){
    string outputString, extensionString, fileName;
    int count;
    ifstream checkFile;

    outputString = "output";
    extensionString = ".txt";
    count = 1;

    do{
        checkFile.close();
        fileName = "test/" + outputString + to_string(count) + extensionString;
        checkFile.open(fileName);
        count++;
    }while(checkFile.is_open());

    ofstream writeFile(fileName);
    writeFile << maxPoints << endl;
    for(auto token: bestPath){
        writeFile << token << " ";
    }
    writeFile << endl;
    for(auto coordinates : bestPathCoordinates){
        writeFile << coordinates.first << ", " << coordinates.second << endl;
    }
    writeFile << endl;
    writeFile << runTime << "ms" << endl;
    writeFile.close();

    cout << "File output berhasil dibuat, silahkan cek di: " << fileName << endl;
}

void saveFileOptions(int maxPoints, vector<string> bestPath, vector<pair<int,int>> bestPathCoordinates, long long runTime){
    char saveOptions;
    bool valid, save;

    valid = false;
    save = false;
    while (!valid){
        cout << "Apakah ingin menyimpan solusi? (y/n)" << endl << endl << ">>";
        cin >> saveOptions;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Silahkan coba lagi!" << endl;
        }else{
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (saveOptions == 'y' || saveOptions == 'Y'){
                valid = true;
                save = true;
            }else if(saveOptions == 'n' || saveOptions == 'N'){
                valid = true;
            }else{
                cout << "Harap masukkan 'y' untuk ya atau 'n' untuk tidak." << endl;
            }
        }
    }
    if(save){
        saveFile(maxPoints, bestPath, bestPathCoordinates, runTime);
    }
}