#ifndef GNUPRINT_H
#define GNUPRINT_H

#include "gnuplot-iostream.h"   //<vector>, <string>, <boost/tuple/tuple.hpp>

class Gnuprint{

    public:

        /**
        �N�˥��I�P�Τߥ�GNUPlot_Interface�L�X��
        mat: �˥���Ƽƾ�
        coreMat: �Τ߸��
        coreSize: �Τ߼�(�s�ռ�), ��mat�PcoreMat�̥~�hvector��size
        gp: Gnuplot���, ��������handle������
        xAxisName: x�b�W��
        yAxisName: y�b�W��
        */
        static void printGroup(const std::vector<std::vector<boost::tuple<double, double> > > &mat,
                               const std::vector<std::vector<boost::tuple<double, double> > > &coreMat,
                               int coreSize, std::string xAxisName, std::string yAxisName, Gnuplot &gp);

};

#endif
