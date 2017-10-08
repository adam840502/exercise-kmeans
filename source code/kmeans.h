#ifndef KMEANS_H
#define KMEANS_H

//#include <time.h> //srand((unsigned)time)

#include "basicfunc.h"
#include "readfile.h"
#include "kmeans_algorithm.h"
#include "gnuprint.h"
//"basicfunc.h"


class Kmeans
{
    public:

        /**
        fileName: 檔名
        multiTimes: Kmeans執行次數
        waitTime: 兩次繪圖之間的間隔時間(Sleep(waitTime);)
        data: 樣本數據, ex: {sample1dim1, sample1dim2, sample1dim3, sample2dim1, sample2dim2, ...}
        sampleSize: 樣本數
        coreSize: 形心數
        */

        //讀取檔案, 執行Kmeans
        static int doKmeans(std::string fileName, int coreSize, int multiTimes, int waitTime);

        //執行多次Kmeans, getCore須先呼叫過srand()
        static int runMulti(const std::vector<double> &data, int sampleSize, int dim, int coreSize, int multiTimes, int waitTime);

        //執行一次Kmeans, getCore須先呼叫過srand()
        static int runOne(const std::vector<double> &data, int sampleSize, int dim, int coreSize, int waitTime);

    private:

        /**
        將資料轉換成可繪製之結構
        data: 樣本數據, ex: {sample1dim1, sample1dim2, sample1dim3, sample2dim1, sample2dim2, ...}
        sampleSize: 樣本數
        dim: 維度數
        plotDim1: 要繪製的第一維為資料的第幾維
        plotDim2: 要繪製的第二維為資料的第幾維
        coreSize: 形心數
        result: 樣本的assign結果
        mat: 承接可繪製的資料結構, 有三層, 第一層為第i群, 第二層為群中第j個點, 第三層為該點的x, y座標
        */
        static int toXYPlotFormat(const std::vector<double> &data, int sampleSize, int dim,
                                int plotDim1, int plotDim2, int coreSize, const std::vector<int> &result, std::vector<std::vector<boost::tuple<double, double> > > &mat);

};


#endif // KMEANS_H
