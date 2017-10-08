#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "basicfunc.h"  //<string>, <vector>

class Readfile{

    public:

        /**
        讀取檔案中的資料
        fileName: 欲讀取的檔名
        data: 承接讀到的double型別資料
        stringData: 承接讀到的文字類資料
        sampleSize: 樣本數
        dim: 數值型的資料維度, 變數量
        stringDim: 類別型(文字型, 字串型)的資料維度, 變數量
        */
        static int read(const std::string &fileName, std::vector<double> &data, std::vector<std::string> &stringData, int &sampleSize, int &dim, int &stringDim);

        /**
        將讀到的string型別的vector轉換成int型別的vector
        stringData: string型別資料
        sampleSize: 樣本數
        dim: 維度
        */
        static std::vector<std::vector<int> > stringtoint(const std::vector<std::string> &stringData, int sampleSize, int dim);

    protected:

    private:
};

#endif // READFILE_H
