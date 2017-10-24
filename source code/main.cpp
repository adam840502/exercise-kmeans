#include <iostream>
#include <fstream>
#include "kmeans.h"

using namespace std;


int main(int argc, char **argv){

    try{
        string fileName = string(argv[1]);
        int coreSize = atoi(argv[2]);
        int multiTimes = atoi(argv[3]);
        int waitTime = atoi(argv[4]);
        cout << "fileName: " << fileName << endl;
        cout << "coreSize: " << coreSize << endl;
        cout << "multiTimes: " << multiTimes << endl;
        cout << "waitTime: " << waitTime << endl;
        system("pause");

        if(Kmeans::doKmeans(fileName, coreSize, multiTimes, waitTime)==1){
            cout << "ÅªÀÉµo¥Í¿ù»~!" << endl;
            return 1;
        }

    }catch(...){
        cout << "something's wrong" << endl << endl;
        cout << "\nsyntax:\n\tkmeans.exe readFiles numOfCentroid multiTimes delayTime" << endl;
        cout << "\nex:\n\tkmeans.exe iris.data.txt 3 30 0" << endl << endl;
        system("pause");
    }

    return 0;
}
