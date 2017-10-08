#include "readfile.h"

using namespace std;


/**
讀取檔案中的資料
fileName: 欲讀取的檔名
data: 承接讀到的double型別資料
stringData: 承接讀到的文字類資料
sampleSize: 樣本數
dim: 數值型的資料維度, 變數量
stringDim: 類別型(文字型, 字串型)的資料維度, 變數量
*/
int Readfile::read(const std::string &fileName, std::vector<double> &data, std::vector<std::string> &stringData,
                   int &sampleSize, int &dim, int &stringDim){

    std::string line, cell;
    double value;
    int isFirstLine = 1;
    sampleSize = 0;
    dim = 0;
    stringDim = 0;

    ifstream rf;
    rf.open(fileName.c_str());

    if(rf.fail()) return 1;

    while(!rf.eof()){
        rf >> line;
        if(line!="")sampleSize++;
        cout << line << endl;
        stringstream lineStream(line);
        while(getline(lineStream, cell, ',')){
            cout << "\t" << cell << endl;
            if(cell=="0"||cell=="0.0"){
                data.push_back(0);
                if(isFirstLine) dim++;
            }else{
                value = strtod(cell.c_str(), NULL);
                if(value){
                    data.push_back(value);
                if(isFirstLine) dim++;
                }else{
                    stringData.push_back(cell);
                    if(isFirstLine) stringDim++;
                }
            }
        }
        if(isFirstLine) isFirstLine = 0;
        line = "";
    }
    cout << "sampleSize: " << sampleSize << ", dim: " << dim << ", stringdim: " << stringDim << endl << endl;
    rf.close();
    return 0;
}

/**
將讀到的string型別的vector轉換成int型別的vector
stringData: string型別資料
sampleSize: 樣本數
dim: 維度
*/
std::vector<std::vector<int> > Readfile::stringtoint(const std::vector<std::string> &stringData, int sampleSize, int dim){
    std::vector<int> vecLevelsNum;      //各維度等級(levels)的數量
    std::vector<std::vector<int> > toReturn;    //傳回結果, 外層為維度, 內層為轉換結果
    std::vector<std::vector<std::string> > vecVecLevelsString;     //紀錄各維度(外層)中各個等級(levels)的名稱

    for(int i=0;i<dim;i++){
        //cout << "dim " << dim << ": " << endl;
        int levels = 0;     //紀錄此維度的等級數
        std::vector<int> tempResult;    //紀錄此維度的轉換結果
        std::vector<std::string> tempVecLevels;     //紀錄此維度已有之等級(levels)

        for(int j=0;j<sampleSize;j++){
            if(j==0){
                tempVecLevels.push_back(stringData[i]);     //把第一樣本的第i維度的string推進vector中
                tempResult.push_back(0);
                levels++;
            }else{
                //檢查是否為新的等級
                int isNew = 1;
                for(int k=0;k<levels;k++){
                    if(stringData[j*dim+i]==tempVecLevels[k]){
                        tempResult.push_back(k);
                        isNew = 0;
                    }
                }

                if(isNew){
                    tempVecLevels.push_back(stringData[j*dim+i]);
                    tempResult.push_back(levels);
                    levels++;
                }
            }
        }

        vecLevelsNum.push_back(levels);
        vecVecLevelsString.push_back(tempVecLevels);
        toReturn.push_back(tempResult);

        vec_clr(tempVecLevels);
        vec_clr(tempResult);
    }

    cout << "levels number of each string dimension: \n\t";
    for(int i=0;i<dim;i++){
        cout << vecLevelsNum[i];
        if(i==dim-1)    cout << endl;
        else  cout << ", ";
    }
    cout << endl;
    cout << "converted result: " << endl;
    for(int i=0;i<dim;i++){
        cout << "\tdim" << i+1 << ": " << endl;
        for(int j=0;j<vecLevelsNum[i];j++){
            cout << "\t\t" << vecVecLevelsString[i][j] << "  ->  " << j << endl;
        }
    }

    vec_clr(vecLevelsNum);
    vec_clr(vecVecLevelsString);

    return toReturn;
}
