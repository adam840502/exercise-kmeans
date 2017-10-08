#ifndef KMEANS_ALGORITHM_H
#define KMEANS_ALGORITHM_H

#include <iostream> //cout, endl
#include <math.h> //pow()

#include "basicfunc.h"  //<vector>

class Kmeans_algorithm{

    public:

        //statics

        /**
        取得形心起始點
        data: 數據資料, 用以得到形心初始點的隨機範圍
        sampleSize: 樣本數
        coreSize: 要隨機的形心數
        dim: 維度
        */
        static std::vector<double> getCore(std::vector<double> data, int sampleSize, int coreSize, int dim);

        //constructors

        /**
        此類別紀錄迭代次數與SSE
        */
        Kmeans_algorithm();

        //gets

        //取得已迭代次數
        int getItrTimes();
        //取得最後一次的SSE
        double getSSE();

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
        int runOne(const std::vector<double> &data, int sampleSize, std::vector<double> &core, int coreSize,
                    int dim, std::vector<int> &result);

    protected:

        //statics

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
        static double dataAssign(const std::vector<double> &data, int sampleSize, const std::vector<double> &core, int coreSize,
                                 int dim, std::vector<int> &result);

        /**
        計算第(dataIndex)個樣本與第(coreIndex)個形心之間的距離
        data: 資料數據
        dataIndex: 欲計算的樣本index
        core: 形心位置
        coreIndex: 欲計算的形心index
        dim: 維度
        return squareOfDistance: 距離的平方
        */
        static double squareOfDistance(const std::vector<double> &data, int dataIndex,
                                       std::vector<double> core, int coreIndex, int dim);

        /**
        將隸屬於第i顆核的data push進groupList中，利用updateSingleCore()算出新核心位置，並更新各核心
        data: 資料數據
        sampleSize: 樣本數
        core: 形心位置
        coreSize: 形心數
        dim: 維度
        result: 最後一次assign的隸屬群組結果
        */
        static void update(const std::vector<double> &data, int sampleSize, std::vector<double> &core, int coreSize,
                           int dim, const std::vector<int> &result);

        /**
        更新某一組的核心位置(算出該組的平均位置, 即為形心新位置)
        data: 資料數據
        sampleSize: 樣本數
        core: 形心位置
        dim: 維度
        coreIndex: 欲更新的形心Index
        */
        static void updateSingleCore(const std::vector<double> &data, int sampleSize, std::vector<double> &core,
                                    int dim, int coreIndex);

        /**
        得到data中各維的最小與最大觀測值，輸出為(range, min), ...
        data: 資料數據
        sampleSize: 樣本數
        dim: 維度
        return vector: (range, min) of core1, (range, min) of core2, (range, min) of core3, ...
        */
        static std::vector<double> getRange(const std::vector<double> &data, int sampleSize, int dim);

    private:

        //member variables

        int itrTimes;
        double sse;
};


#endif // KMEANS_ALGORITHM_H
