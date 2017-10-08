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
        fileName: �ɦW
        multiTimes: Kmeans���榸��
        waitTime: �⦸ø�Ϥ��������j�ɶ�(Sleep(waitTime);)
        data: �˥��ƾ�, ex: {sample1dim1, sample1dim2, sample1dim3, sample2dim1, sample2dim2, ...}
        sampleSize: �˥���
        coreSize: �Τ߼�
        */

        //Ū���ɮ�, ����Kmeans
        static int doKmeans(std::string fileName, int coreSize, int multiTimes, int waitTime);

        //����h��Kmeans, getCore�����I�s�Lsrand()
        static int runMulti(const std::vector<double> &data, int sampleSize, int dim, int coreSize, int multiTimes, int waitTime);

        //����@��Kmeans, getCore�����I�s�Lsrand()
        static int runOne(const std::vector<double> &data, int sampleSize, int dim, int coreSize, int waitTime);

    private:

        /**
        �N����ഫ���iø�s�����c
        data: �˥��ƾ�, ex: {sample1dim1, sample1dim2, sample1dim3, sample2dim1, sample2dim2, ...}
        sampleSize: �˥���
        dim: ���׼�
        plotDim1: �nø�s���Ĥ@������ƪ��ĴX��
        plotDim2: �nø�s���ĤG������ƪ��ĴX��
        coreSize: �Τ߼�
        result: �˥���assign���G
        mat: �ӱ��iø�s����Ƶ��c, ���T�h, �Ĥ@�h����i�s, �ĤG�h���s����j���I, �ĤT�h�����I��x, y�y��
        */
        static int toXYPlotFormat(const std::vector<double> &data, int sampleSize, int dim,
                                int plotDim1, int plotDim2, int coreSize, const std::vector<int> &result, std::vector<std::vector<boost::tuple<double, double> > > &mat);

};


#endif // KMEANS_H
