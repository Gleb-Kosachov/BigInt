//
//  constructors.cpp
//  C++
//
//  Created by Глеб Косачёв on 20.03.21.
//

#include "BigInt.hpp"
#include <cstring>

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

BigInt::BigInt(const char *str)
{
    int i = 0;
    if (str[i] == '-')
    {
        this->has_minus = true;
        i++;
    }
    else this->has_minus = false;
    std::deque<char> deq;
    for (int i = 0; i < strlen(str); i++)
    {
        deq.push_back(str[i]);
    }
    this->number = deq;
}

BigInt::BigInt(const BigInt &arg): number(arg.number), has_minus(arg.has_minus) {}

BigInt::BigInt(const std::deque<char> &arg): number(arg), has_minus(false) {}
