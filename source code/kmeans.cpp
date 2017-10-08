#include "kmeans.h"

/**
讀檔, 執行多次kmeans, 最後作結果比較, 重繪最佳一次的結果
return 1: 讀檔錯誤
*/
int Kmeans::doKmeans(std::string fileName, int coreSize, int multiTimes, int waitTime){

    std::vector<double> data;       //數值型變數
    std::vector<std::string> stringData;        //類別型變數
    std::vector<std::vector<int> > stringDataint;       //轉換成int的stringData
    int sampleSize, dim, stringDim;         //sampleSize:樣本數, dim:數值型(double)維度數, stringDim:類別型維度數

    srand((unsigned)time(NULL));

    if(Readfile::read(fileName, data, stringData, sampleSize, dim, stringDim))  return 1;
    //Readfile::stringtoint(stringData, 150, stringDim);
    system("pause");

    runMulti(data, sampleSize, dim, coreSize, multiTimes, waitTime);

    vec_clr(data);
    vec_clr(stringData);
    vec_clr(stringDataint);

    return 0;
}

//對同一筆data執行多次kmeans, 各次形心的起始點不一樣
int Kmeans::runMulti(const std::vector<double> &data, int sampleSize, int dim, int coreSize, int multiTimes, int waitTime){

    if(multiTimes<=0) return 1;

    /**
    Todo: 把gp1, gp2改成動態, 也就是繪製的圖數具有彈性, 不再只有兩幅
    */

    int finished;       //存放此次是否收斂完成的變數, 每次update更新一次
    Gnuplot gp1, gp2;       //兩個視窗的session
    std::vector<double> vecCore, vecSSE;        //vecCore:存放形心座標, vecSSE:存放每一次完成收斂後的SSE
    std::vector<int> dataResult, coreResult;        //dataResult:接assign結果用, coreResult:繪製形心用的dummy vector
    std::vector<std::vector<boost::tuple<double, double> > > mat, coreMat;      //可繪製結構, 有三層, 第一層為第i群, 第二層為群中第j個點, 第三層為該點的x, y座標
    std::vector<std::vector<int> > vecResult;       //存放每一次收斂完成後的assign結果, 外層為第i次, 內層為該次的第j個樣本的assign結果
    std::vector<std::vector<double> > vecVecCore;       //存放每一次收斂完成後的形心位置, 外層為第i次, 內層為該次的形心位置的vector


    for(int i=0;i<coreSize;i++) coreResult.push_back(i);        //準備形心所屬群組的vector(形心i隸屬於群組i)，以便使用繪製data的函數繪製形心

    for(int i=0;i<multiTimes;i++){
        std::cout << "開始第" << i+1 << "次" << std::endl;

        finished = 0;
        Kmeans_algorithm kmnAl;     //此class用來紀錄SSE與迭代次數
        vecCore = Kmeans_algorithm::getCore(data, sampleSize, coreSize, dim);

        while(!finished){
            finished = kmnAl.runOne(data, sampleSize, vecCore, coreSize, dim, dataResult);

            toXYPlotFormat(data, sampleSize, dim, 0, 1, coreSize, dataResult, mat);
            toXYPlotFormat(vecCore, coreSize, dim, 0, 1, coreSize, coreResult, coreMat);
            Gnuprint::printGroup(mat, coreMat, coreSize, "dim1", "dim2", gp1);

            toXYPlotFormat(data, sampleSize, dim, 2, 3, coreSize, dataResult, mat);
            toXYPlotFormat(vecCore, coreSize, dim, 2, 3, coreSize, coreResult, coreMat);
            Gnuprint::printGroup(mat, coreMat, coreSize, "dim3", "dim4", gp2);

            Sleep(waitTime);

            gp1.clearTmpfiles();
            gp2.clearTmpfiles();

            if(finished){                           //將收斂結果存起來, 等全部跑完再做比較
                vecSSE.push_back(kmnAl.getSSE());   //紀錄此次SSE
                vecResult.push_back(dataResult);    //紀錄此次assign結果
                vecVecCore.push_back(vecCore);      //紀錄此次形心最終位置
            }
        }
    }

    int minIndex = 0;   //收斂結束後存放最小SSE的索引
    double minSSE, averageSSE = 0;  //minSSE: 最小SSE的值, averageSSE:, 平均SSE

    for(int i=0;i<multiTimes;i++){          //找出最佳的一次結果
        if(i==0)    minSSE = vecSSE[0];
        else if(vecSSE[i]<minSSE){
            minIndex = i;
            minSSE = vecSSE[i];
        }
        averageSSE += vecSSE[i];
        std::cout << "第" << i+1 << "次, SSE: " << vecSSE[i] << std::endl;
    }

    std::cout << "最佳為第" << minIndex+1 << "次, SSE: " << minSSE << std::endl;
    std::cout << "平均SSE: " << (averageSSE/multiTimes) << std::endl;

    //重繪最佳結果
    toXYPlotFormat(data, sampleSize, dim, 0, 1, coreSize, vecResult[minIndex], mat);
    toXYPlotFormat(vecVecCore[minIndex], coreSize, dim, 0, 1, coreSize, coreResult, coreMat);
    Gnuprint::printGroup(mat, coreMat, coreSize, "dim1", "dim2", gp1);

    toXYPlotFormat(data, sampleSize, dim, 2, 3, coreSize, vecResult[minIndex], mat);
    toXYPlotFormat(vecVecCore[minIndex], coreSize, dim, 2, 3, coreSize, coreResult, coreMat);
    Gnuprint::printGroup(mat, coreMat, coreSize, "dim3", "dim4", gp2);

    vec_clr(vecCore);
    vec_clr(vecSSE);
    vec_clr(dataResult);
    vec_clr(coreResult);
    vec_clr(mat);
    vec_clr(coreMat);
    vec_clr(vecResult);
    vec_clr(vecVecCore);

    return 0;
}

//執行一次kmeans
int Kmeans::runOne(const std::vector<double> &data, int sampleSize, int dim, int coreSize, int waitTime){

    Kmeans_algorithm kmnAl;
    Gnuplot gp1, gp2;
    std::vector<double> vecCore = Kmeans_algorithm::getCore(data, sampleSize, 3, 4);
    std::vector<int> dataResult, coreResult;
    std::vector<std::vector<boost::tuple<double, double> > > mat, coreMat;

    int finished = 0;
    for(int i=0;i<coreSize;i++) coreResult.push_back(i);

    while(!finished){
        finished = kmnAl.runOne(data, sampleSize, vecCore, coreSize, dim, dataResult);

        toXYPlotFormat(data, sampleSize, dim, 0, 1, coreSize, dataResult, mat);
        toXYPlotFormat(vecCore, coreSize, dim, 0, 1, coreSize, coreResult, coreMat);
        Gnuprint::printGroup(mat, coreMat, coreSize, "dim1", "dim2", gp1);
        toXYPlotFormat(data, sampleSize, dim, 2, 3, coreSize, dataResult, mat);
        toXYPlotFormat(vecCore, coreSize, dim, 2, 3, coreSize, coreResult, coreMat);
        Gnuprint::printGroup(mat, coreMat, coreSize, "dim3", "dim4", gp2);
        Sleep(waitTime);
        gp1.clearTmpfiles();
        gp2.clearTmpfiles();
    }

    return 0;
}

//將傳入的data轉換成適合GnuPlot繪製的資料結構, 結果輸出到傳入的mat參數中
int Kmeans::toXYPlotFormat(const std::vector<double> &data,  int sampleSize, int dim, int plotDim1, int plotDim2, int coreSize,
                           const std::vector<int> &result, std::vector<std::vector<boost::tuple<double, double> > > &mat){

    int isFirstTime;
    if(mat.size()==0) isFirstTime = 1;
    else isFirstTime = 0;

    for(int i=0;i<coreSize;i++){

        std::vector<boost::tuple<double, double> > groupList;

        for(int j=0;j<sampleSize;j++){
            if(result[j]==i)    groupList.push_back(boost::make_tuple(data[j*dim+plotDim1], data[j*dim+plotDim2]));
        }

        if(isFirstTime==1)  mat.push_back(groupList);
        else    mat[i] = groupList;

        vec_clr(groupList);
    }
    return 0;
}
