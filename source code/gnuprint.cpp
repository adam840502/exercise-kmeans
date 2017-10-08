#include "gnuprint.h"

/**
�N�˥��I�P�Τߥ�GNUPlot_Interface�L�X��
mat: �˥���Ƽƾ�
coreMat: �Τ߸��
coreSize: �Τ߼�(�s�ռ�), ��mat�PcoreMat�̥~�hvector��size
xAxisName: x�b�W��
yAxisName: y�b�W��
gp: Gnuplot���, ��������handle������
*/
void Gnuprint::printGroup(const std::vector<std::vector<boost::tuple<double, double> > > &mat,
                          const std::vector<std::vector<boost::tuple<double, double> > > &coreMat,
                          int coreSize, std::string xAxisName, std::string yAxisName, Gnuplot &gp){

    std::string label;

    gp << "set xlabel \"" << xAxisName << "\"\n";
    gp << "set ylabel \"" << yAxisName << "\"\n";
    gp << "plot ";
    for(int i=0;i<(2*coreSize);i++){

        //�M�wlabel��data�٬O�Τ�
        if(i<coreSize)  label = "Group";
        else    label = "Core";

        //�P�_�O�_���̫�@����O
        if(i!=(2*coreSize-1)) gp << "'-' with points title '" << label << " " << (i%coreSize)+1 << "', ";
        else gp << "'-' with points title '" << label << " " << (i%coreSize)+1 << "'\n";
    }

    //�ǻ��˥��I���
    for(int i=0;i<coreSize;i++){
        gp.send1d(mat[i]);
    }

    //�ǻ��Τ߸��
    for(int i=0;i<coreSize;i++){
        gp.send1d(coreMat[i]);
    }
}
