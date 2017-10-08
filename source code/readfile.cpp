#include "readfile.h"

using namespace std;


/**
Ū���ɮפ������
fileName: ��Ū�����ɦW
data: �ӱ�Ū�쪺double���O���
stringData: �ӱ�Ū�쪺��r�����
sampleSize: �˥���
dim: �ƭȫ�����ƺ���, �ܼƶq
stringDim: ���O��(��r��, �r�ꫬ)����ƺ���, �ܼƶq
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
�NŪ�쪺string���O��vector�ഫ��int���O��vector
stringData: string���O���
sampleSize: �˥���
dim: ����
*/
std::vector<std::vector<int> > Readfile::stringtoint(const std::vector<std::string> &stringData, int sampleSize, int dim){
    std::vector<int> vecLevelsNum;      //�U���׵���(levels)���ƶq
    std::vector<std::vector<int> > toReturn;    //�Ǧ^���G, �~�h������, ���h���ഫ���G
    std::vector<std::vector<std::string> > vecVecLevelsString;     //�����U����(�~�h)���U�ӵ���(levels)���W��

    for(int i=0;i<dim;i++){
        //cout << "dim " << dim << ": " << endl;
        int levels = 0;     //���������ת����ż�
        std::vector<int> tempResult;    //���������ת��ഫ���G
        std::vector<std::string> tempVecLevels;     //���������פw��������(levels)

        for(int j=0;j<sampleSize;j++){
            if(j==0){
                tempVecLevels.push_back(stringData[i]);     //��Ĥ@�˥�����i���ת�string���ivector��
                tempResult.push_back(0);
                levels++;
            }else{
                //�ˬd�O�_���s������
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
