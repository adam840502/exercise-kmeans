#include "basicfunc.h"

using namespace std;

/**
ÄÀ©ñvectorªÅ¶¡( vector.swap() )
*/
template<typename T>
void vec_clr(std::vector<T> & v){
    std::vector<T> t;
    v.swap(t);
}

//explicit template instantiation

    //1dim
template void vec_clr<int>(std::vector<int> &v);
template void vec_clr<double>(std::vector<double> &v);
template void vec_clr<std::string>(std::vector<std::string> &v);
template void vec_clr<boost::tuple<double, double> >(std::vector<boost::tuple<double, double > > &v);

    //2dim
template void vec_clr<std::vector<int> >(std::vector<std::vector<int> > &v);
template void vec_clr<std::vector<double> >(std::vector<std::vector<double> > &v);
template void vec_clr<std::vector<std::string> >(std::vector<std::vector<std::string> > &v);
template void vec_clr<std::vector<boost::tuple<double, double> > >(std::vector<std::vector<boost::tuple<double, double> > > &v);
