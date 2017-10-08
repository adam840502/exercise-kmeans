#ifndef GNUPRINT_H
#define GNUPRINT_H

#include "gnuplot-iostream.h"   //<vector>, <string>, <boost/tuple/tuple.hpp>

class Gnuprint{

    public:

        /**
        將樣本點與形心用GNUPlot_Interface印出來
        mat: 樣本資料數據
        coreMat: 形心資料
        coreSize: 形心數(群組數), 為mat與coreMat最外層vector的size
        gp: Gnuplot實例, 類似視窗handle的概念
        xAxisName: x軸名稱
        yAxisName: y軸名稱
        */
        static void printGroup(const std::vector<std::vector<boost::tuple<double, double> > > &mat,
                               const std::vector<std::vector<boost::tuple<double, double> > > &coreMat,
                               int coreSize, std::string xAxisName, std::string yAxisName, Gnuplot &gp);

};

#endif
