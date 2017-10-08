#include "gnuprint.h"

/**
將樣本點與形心用GNUPlot_Interface印出來
mat: 樣本資料數據
coreMat: 形心資料
coreSize: 形心數(群組數), 為mat與coreMat最外層vector的size
xAxisName: x軸名稱
yAxisName: y軸名稱
gp: Gnuplot實例, 類似視窗handle的概念
*/
void Gnuprint::printGroup(const std::vector<std::vector<boost::tuple<double, double> > > &mat,
                          const std::vector<std::vector<boost::tuple<double, double> > > &coreMat,
                          int coreSize, std::string xAxisName, std::string yAxisName, Gnuplot &gp){

    std::string label;

    gp << "set xlabel \"" << xAxisName << "\"\n";
    gp << "set ylabel \"" << yAxisName << "\"\n";
    gp << "plot ";
    for(int i=0;i<(2*coreSize);i++){

        //決定label為data還是形心
        if(i<coreSize)  label = "Group";
        else    label = "Core";

        //判斷是否為最後一行指令
        if(i!=(2*coreSize-1)) gp << "'-' with points title '" << label << " " << (i%coreSize)+1 << "', ";
        else gp << "'-' with points title '" << label << " " << (i%coreSize)+1 << "'\n";
    }

    //傳遞樣本點資料
    for(int i=0;i<coreSize;i++){
        gp.send1d(mat[i]);
    }

    //傳遞形心資料
    for(int i=0;i<coreSize;i++){
        gp.send1d(coreMat[i]);
    }
}
