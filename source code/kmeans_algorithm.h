#ifndef KMEANS_ALGORITHM_H
#define KMEANS_ALGORITHM_H

#include <iostream> //cout, endl
#include <math.h> //pow()

#include "basicfunc.h"  //<vector>

class Kmeans_algorithm{

    public:

        //statics

        /**
        ���o�Τ߰_�l�I
        data: �ƾڸ��, �ΥH�o��Τߪ�l�I���H���d��
        sampleSize: �˥���
        coreSize: �n�H�����Τ߼�
        dim: ����
        */
        static std::vector<double> getCore(std::vector<double> data, int sampleSize, int coreSize, int dim);

        //constructors

        /**
        �����O�������N���ƻPSSE
        */
        Kmeans_algorithm();

        //gets

        //���o�w���N����
        int getItrTimes();
        //���o�̫�@����SSE
        double getSSE();

        //member functions

        /**
        ����@��assign�M�@��update
        data: �ƾڸ��
        sampleSize: �˥���
        core: �Τߦ�m
        coreSize: �Τ߼�
        dim: ����
        result: ����assign���G
        */
        int runOne(const std::vector<double> &data, int sampleSize, std::vector<double> &core, int coreSize,
                    int dim, std::vector<int> &result);

    protected:

        //statics

        /**
        �Ndata���C���ƾڤ��t�����ݪ��Τߤ�, ���t���G���result��, �^�ǭȦ^sse
        data: ��Ƽƾ�
        sampleSize: �˥���
        core: �Τߦ�m
        coreSize: �Τ߼�
        dim: ����
        result: �ӱ����t���G
        return sse: �Ҧ���SquareOfDistance���`�M(�~�t����M)
        */
        static double dataAssign(const std::vector<double> &data, int sampleSize, const std::vector<double> &core, int coreSize,
                                 int dim, std::vector<int> &result);

        /**
        �p���(dataIndex)�Ӽ˥��P��(coreIndex)�ӧΤߤ������Z��
        data: ��Ƽƾ�
        dataIndex: ���p�⪺�˥�index
        core: �Τߦ�m
        coreIndex: ���p�⪺�Τ�index
        dim: ����
        return squareOfDistance: �Z��������
        */
        static double squareOfDistance(const std::vector<double> &data, int dataIndex,
                                       std::vector<double> core, int coreIndex, int dim);

        /**
        �N���ݩ��i���֪�data push�igroupList���A�Q��updateSingleCore()��X�s�֤ߦ�m�A�ç�s�U�֤�
        data: ��Ƽƾ�
        sampleSize: �˥���
        core: �Τߦ�m
        coreSize: �Τ߼�
        dim: ����
        result: �̫�@��assign�����ݸs�յ��G
        */
        static void update(const std::vector<double> &data, int sampleSize, std::vector<double> &core, int coreSize,
                           int dim, const std::vector<int> &result);

        /**
        ��s�Y�@�ժ��֤ߦ�m(��X�Ӳժ�������m, �Y���Τ߷s��m)
        data: ��Ƽƾ�
        sampleSize: �˥���
        core: �Τߦ�m
        dim: ����
        coreIndex: ����s���Τ�Index
        */
        static void updateSingleCore(const std::vector<double> &data, int sampleSize, std::vector<double> &core,
                                    int dim, int coreIndex);

        /**
        �o��data���U�����̤p�P�̤j�[���ȡA��X��(range, min), ...
        data: ��Ƽƾ�
        sampleSize: �˥���
        dim: ����
        return vector: (range, min) of core1, (range, min) of core2, (range, min) of core3, ...
        */
        static std::vector<double> getRange(const std::vector<double> &data, int sampleSize, int dim);

    private:

        //member variables

        int itrTimes;
        double sse;
};


#endif // KMEANS_ALGORITHM_H
