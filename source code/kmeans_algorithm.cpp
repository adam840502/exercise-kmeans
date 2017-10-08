#include "kmeans_algorithm.h"

using namespace std;


//public
    //statics

/**
���o�Τ߰_�l�I
data: �ƾڸ��, �ΥH�o��Τߪ�l�I���H���d��
sampleSize: �˥���
coreSize: �n�H�����Τ߼�
dim: ����
*/
std::vector<double> Kmeans_algorithm::getCore(std::vector<double> data, int sampleSize, int coreSize, int dim){

    std::vector<double> core;
    std::vector<double> rangeVector = getRange(data, sampleSize, dim);
    double temp;

    cout << "�Τ߰_�l��m: " << endl;
    for(int i=0;i<coreSize;i++){
        cout << "\t" << i+1 << ": ";
        for(int j=0;j<dim;j++){

            temp = (double(rand())/double(32767))*rangeVector[j*2]+rangeVector[j*2+1];
            core.push_back(temp);

            cout << temp;
            if(j==dim-1) cout << endl;
            else  cout << ", ";

        }
    }
    vec_clr(rangeVector);
    return core;
}

    //constructors

/**
�����O�������N���ƻPSSE
*/
Kmeans_algorithm::Kmeans_algorithm():itrTimes(0), sse(-1){}


    //gets

/**
���o�w���N����
*/
int Kmeans_algorithm::getItrTimes(){return this->itrTimes;}

/**
���o�̫�@����SSE
*/
double Kmeans_algorithm::getSSE(){return this->sse;}

    //member functions

/**
����@��assign�M�@��update
data: �ƾڸ��
sampleSize: �˥���
core: �Τߦ�m
coreSize: �Τ߼�
dim: ����
result: ����assign���G
*/
int Kmeans_algorithm::runOne(const std::vector<double> &data, int sampleSize, std::vector<double> &core, int coreSize, int dim, std::vector<int> &result){

    double temp;

    temp = dataAssign(data, sampleSize, core, coreSize, dim, result);

    //cout << "SSE: " << temp << "\tlast SSE: " << sse << endl;
    if(temp==sse){
            cout << "���ħ����A�|�N " << this->itrTimes << "��" << endl << endl;
            return 1;
    }

    update(data, sampleSize, core, coreSize, dim, result);

    this->sse = temp;
    this->itrTimes++;
    return 0;
}



//protected

/**
�Ndata���C���ƾڤ��t�����ݪ��Τߤ�, ���t���G���result��, �^�ǭȦ^sse
data: ��Ƽƾ�
sampleSize: �˥���
core: �Τߦ�m
coreSize: �Τ߼�
dim: ����
result: �ӱ����t���G
return sse: �Ҧ���SquareOfDistance���`�M(�~�t����M)
*/
double Kmeans_algorithm::dataAssign(const std::vector<double> &data, int sampleSize, const std::vector<double> &core, int coreSize, int dim, std::vector<int> &result){

    int closest, isFirstTime;

    if(result.size()==0) isFirstTime = 1;
    else isFirstTime = 0;

    double closestDistance=0, tmp, sse=0;
    for(int i=0;i<sampleSize;i++){
        for(int m=0;m<coreSize;m++){
            tmp = squareOfDistance(data, i, core, m, dim);
            if(m==0){
                closest = 0;
                closestDistance = tmp;
            }else if(closestDistance>tmp){
                closestDistance = tmp;
                closest = m;
            }
        }
        if(isFirstTime==1)    result.push_back(closest);
        else    result[i] = closest;
        sse += closestDistance;
    }

    return sse;
}

/**
�p���(dataIndex)�Ӽ˥��P��(coreIndex)�ӧΤߤ������Z��
data: ��Ƽƾ�
dataIndex: ���p�⪺�˥�index
core: �Τߦ�m
coreIndex: ���p�⪺�Τ�index
dim: ����
return squareOfDistance: �Z��������
*/
double Kmeans_algorithm::squareOfDistance(const std::vector<double> &data, int dataIndex, std::vector<double> core, int coreIndex, int dim){
    double ss = 0;
    for(int i=0;i<dim;i++){
        ss += pow((data[dataIndex*dim+i]-core[coreIndex*dim+i]), 2);
    }
    return ss;
}

/**
�N���ݩ��i���֪�data push�igroupList���A�Q��updateSingleCore()��X�s�֤ߦ�m�A�ç�s�U�֤�
data: ��Ƽƾ�
sampleSize: �˥���
core: �Τߦ�m
coreSize: �Τ߼�
dim: ����
result: �̫�@��assign�����ݸs�յ��G
*/
void Kmeans_algorithm::update(const std::vector<double> &data, int sampleSize, std::vector<double> &core, int coreSize,
                              int dim, const std::vector<int> &result){

    for(int i=0;i<coreSize;i++){
        std::vector<double> groupList;
        int numInGroup = 0;

        for(int j=0;j<sampleSize;j++){
            if(result[j]==i){
                for(int m=0;m<dim;m++){
                    groupList.push_back(double(data[j*dim+m]));
                }
                numInGroup++;
            }
        }

        updateSingleCore(groupList, numInGroup, core, dim, i);
        vec_clr(groupList);
    }
}

/**
��s�Y�@�ժ��֤ߦ�m(��X�Ӳժ�������m, �Y���Τ߷s��m)
data: ��Ƽƾ�
sampleSize: �˥���
core: �Τߦ�m
dim: ����
coreIndex: ����s���Τ�Index
*/
void Kmeans_algorithm::updateSingleCore(const std::vector<double> &data, int sampleSize, std::vector<double> &core,
                                       int dim, int coreIndex){
    if(sampleSize>0){
        for(int i=0;i<dim;i++){
            double total = 0;
            for(int j=0;j<sampleSize;j++){
                total += data[j*dim+i];
            }
            core[coreIndex*dim+i] = total/sampleSize;
        }
    }
}

/**
�o��data���U�����̤p�P�̤j�[���ȡA��X��(range, min), ...
data: ��Ƽƾ�
sampleSize: �˥���
dim: ����
return vector: (range, min) of core1, (range, min) of core2, (range, min) of core3, ...
*/
std::vector<double> Kmeans_algorithm::getRange(const std::vector<double> &data, int sampleSize, int dim){
    std::vector<double> rangeVector;
    double temp = 0;
    double tempMin = 0, tempMax = 0;

    for(int i=0;i<dim;i++){
        for(int j=0;j<sampleSize;j++){
            if(j==0){
                tempMax=data[i];
                tempMin=data[i];
            }else{
                if(data[j*dim+i]<tempMin) tempMin = data[j*dim+i];
                if(data[j*dim+i]>tempMax) tempMax = data[j*dim+i];
            }
        }
        temp = double(tempMax-tempMin);
        rangeVector.push_back(temp);
        rangeVector.push_back(tempMin);
    }
    return rangeVector;
}
