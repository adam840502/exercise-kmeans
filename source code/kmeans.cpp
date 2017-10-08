#include "kmeans.h"

/**
Ū��, ����h��kmeans, �̫�@���G���, ��ø�̨Τ@�������G
return 1: Ū�ɿ��~
*/
int Kmeans::doKmeans(std::string fileName, int coreSize, int multiTimes, int waitTime){

    std::vector<double> data;       //�ƭȫ��ܼ�
    std::vector<std::string> stringData;        //���O���ܼ�
    std::vector<std::vector<int> > stringDataint;       //�ഫ��int��stringData
    int sampleSize, dim, stringDim;         //sampleSize:�˥���, dim:�ƭȫ�(double)���׼�, stringDim:���O�����׼�

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

//��P�@��data����h��kmeans, �U���Τߪ��_�l�I���@��
int Kmeans::runMulti(const std::vector<double> &data, int sampleSize, int dim, int coreSize, int multiTimes, int waitTime){

    if(multiTimes<=0) return 1;

    /**
    Todo: ��gp1, gp2�令�ʺA, �]�N�Oø�s���ϼƨ㦳�u��, ���A�u����T
    */

    int finished;       //�s�񦹦��O�_���ħ������ܼ�, �C��update��s�@��
    Gnuplot gp1, gp2;       //��ӵ�����session
    std::vector<double> vecCore, vecSSE;        //vecCore:�s��Τ߮y��, vecSSE:�s��C�@���������ī᪺SSE
    std::vector<int> dataResult, coreResult;        //dataResult:��assign���G��, coreResult:ø�s�ΤߥΪ�dummy vector
    std::vector<std::vector<boost::tuple<double, double> > > mat, coreMat;      //�iø�s���c, ���T�h, �Ĥ@�h����i�s, �ĤG�h���s����j���I, �ĤT�h�����I��x, y�y��
    std::vector<std::vector<int> > vecResult;       //�s��C�@�����ħ����᪺assign���G, �~�h����i��, ���h���Ӧ�����j�Ӽ˥���assign���G
    std::vector<std::vector<double> > vecVecCore;       //�s��C�@�����ħ����᪺�Τߦ�m, �~�h����i��, ���h���Ӧ����Τߦ�m��vector


    for(int i=0;i<coreSize;i++) coreResult.push_back(i);        //�ǳƧΤߩ��ݸs�ժ�vector(�Τ�i���ݩ�s��i)�A�H�K�ϥ�ø�sdata�����ø�s�Τ�

    for(int i=0;i<multiTimes;i++){
        std::cout << "�}�l��" << i+1 << "��" << std::endl;

        finished = 0;
        Kmeans_algorithm kmnAl;     //��class�ΨӬ���SSE�P���N����
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

            if(finished){                           //�N���ĵ��G�s�_��, �������]���A�����
                vecSSE.push_back(kmnAl.getSSE());   //��������SSE
                vecResult.push_back(dataResult);    //��������assign���G
                vecVecCore.push_back(vecCore);      //���������Τ̲߳צ�m
            }
        }
    }

    int minIndex = 0;   //���ĵ�����s��̤pSSE������
    double minSSE, averageSSE = 0;  //minSSE: �̤pSSE����, averageSSE:, ����SSE

    for(int i=0;i<multiTimes;i++){          //��X�̨Ϊ��@�����G
        if(i==0)    minSSE = vecSSE[0];
        else if(vecSSE[i]<minSSE){
            minIndex = i;
            minSSE = vecSSE[i];
        }
        averageSSE += vecSSE[i];
        std::cout << "��" << i+1 << "��, SSE: " << vecSSE[i] << std::endl;
    }

    std::cout << "�̨ά���" << minIndex+1 << "��, SSE: " << minSSE << std::endl;
    std::cout << "����SSE: " << (averageSSE/multiTimes) << std::endl;

    //��ø�̨ε��G
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

//����@��kmeans
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

//�N�ǤJ��data�ഫ���A�XGnuPlotø�s����Ƶ��c, ���G��X��ǤJ��mat�ѼƤ�
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
