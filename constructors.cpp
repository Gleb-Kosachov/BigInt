//
//  constructors.cpp
//  C++
//
//  Created by Глеб Косачёв on 20.03.21.
//

#include "BigInt.hpp"

BigInt::BigInt() : number({}), has_minus(false) {}

BigInt::BigInt(long long int arg): has_minus(arg < 0)
{
    arg = std::abs(arg);
    do
    {
        number.push_front(arg % 10 + 48);
        arg /= 10;
    } while(arg);
}

BigInt::BigInt(const BigInt &arg): number(arg.number), has_minus(arg.has_minus) {}

BigInt::BigInt(const std::deque<char> &arg): number(arg), has_minus(false) {}
