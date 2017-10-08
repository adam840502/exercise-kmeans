#ifndef BASICFUNC_H
#define BASICFUNC_H

#include <vector>
#include <string>

#include <boost/tuple/tuple.hpp>


/**
釋放vector空間( vector.swap() )
*/
template<typename T> void vec_clr(std::vector<T> & v);

#endif // BASICFUNC_H
