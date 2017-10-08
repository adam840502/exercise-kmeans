#include "kmeans_algorithm.h"

using namespace std;


//public
    //statics

/**
取得形心起始點
data: 數據資料, 用以得到形心初始點的隨機範圍
sampleSize: 樣本數
coreSize: 要隨機的形心數
dim: 維度
*/
std::vector<double> Kmeans_algorithm::getCore(std::vector<double> data, int sampleSize, int coreSize, int dim){

    std::vector<double> core;
    std::vector<double> rangeVector = getRange(data, sampleSize, dim);
    double temp;

    cout << "形心起始位置: " << endl;
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
此類別紀錄迭代次數與SSE
*/
Kmeans_algorithm::Kmeans_algorithm():itrTimes(0), sse(-1){}


    //gets

/**
取得已迭代次數
*/
int Kmeans_algorithm::getItrTimes(){return this->itrTimes;}

/**
取得最後一次的SSE
*/
double Kmeans_algorithm::getSSE(){return this->sse;}

    //member functions

/**
執行一次assign和一次update
data: 數據資料
sampleSize: 樣本數
core: 形心位置
coreSize: 形心數
dim: 維度
result: 紀錄assign結果
*/
int Kmeans_algorithm::runOne(const std::vector<double> &data, int sampleSize, std::vector<double> &core, int coreSize, int dim, std::vector<int> &result){

    double temp;

    temp = dataAssign(data, sampleSize, core, coreSize, dim, result);

    //cout << "SSE: " << temp << "\tlast SSE: " << sse << endl;
    if(temp==sse){
            cout << "收斂完成，疊代 " << this->itrTimes << "次" << endl << endl;
            return 1;
    }

    update(data, sampleSize, core, coreSize, dim, result);

    this->sse = temp;
    this->itrTimes++;
    return 0;
}



//protected

/**
將data中每筆數據分配到隸屬的形心中, 分配結果位於result中, 回傳值回sse
data: 資料數據
sampleSize: 樣本數
core: 形心位置
coreSize: 形心數
dim: 維度
result: 承接分配結果
return sse: 所有的SquareOfDistance之總和(誤差平方和)
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
計算第(dataIndex)個樣本與第(coreIndex)個形心之間的距離
data: 資料數據
dataIndex: 欲計算的樣本index
core: 形心位置
coreIndex: 欲計算的形心index
dim: 維度
return squareOfDistance: 距離的平方
*/
double Kmeans_algorithm::squareOfDistance(const std::vector<double> &data, int dataIndex, std::vector<double> core, int coreIndex, int dim){
    double ss = 0;
    for(int i=0;i<dim;i++){
        ss += pow((data[dataIndex*dim+i]-core[coreIndex*dim+i]), 2);
    }
    return ss;
}

/**
將隸屬於第i顆核的data push進groupList中，利用updateSingleCore()算出新核心位置，並更新各核心
data: 資料數據
sampleSize: 樣本數
core: 形心位置
coreSize: 形心數
dim: 維度
result: 最後一次assign的隸屬群組結果
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
更新某一組的核心位置(算出該組的平均位置, 即為形心新位置)
data: 資料數據
sampleSize: 樣本數
core: 形心位置
dim: 維度
coreIndex: 欲更新的形心Index
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
得到data中各維的最小與最大觀測值，輸出為(range, min), ...
data: 資料數據
sampleSize: 樣本數
dim: 維度
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
