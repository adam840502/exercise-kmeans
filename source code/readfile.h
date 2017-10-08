#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "basicfunc.h"  //<string>, <vector>

class Readfile{

    public:

        /**
        Ū���ɮפ������
        fileName: ��Ū�����ɦW
        data: �ӱ�Ū�쪺double���O���
        stringData: �ӱ�Ū�쪺��r�����
        sampleSize: �˥���
        dim: �ƭȫ�����ƺ���, �ܼƶq
        stringDim: ���O��(��r��, �r�ꫬ)����ƺ���, �ܼƶq
        */
        static int read(const std::string &fileName, std::vector<double> &data, std::vector<std::string> &stringData, int &sampleSize, int &dim, int &stringDim);

        /**
        �NŪ�쪺string���O��vector�ഫ��int���O��vector
        stringData: string���O���
        sampleSize: �˥���
        dim: ����
        */
        static std::vector<std::vector<int> > stringtoint(const std::vector<std::string> &stringData, int sampleSize, int dim);

    protected:

    private:
};

#endif // READFILE_H
