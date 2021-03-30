//
//  operatorsForUsualInt.cpp
//  C++
//
//  Created by Глеб Косачёв on 20.03.21.
//

#include "BigInt.hpp"

BigInt operator+(const int &num, const BigInt &op)
{
    return op + num;
}

BigInt operator-(const int &num, const BigInt &op2)
{
    return -(op2 - num);
}

BigInt operator*(const int &num, const BigInt &op2)
{
    return op2 * num;
}

BigInt operator/(const int &num, const BigInt &op2)
{
    BigInt op1 = num;
    return op1 / op2;
}

BigInt operator%(const int &num, const BigInt &op2)
{
    BigInt op1 = num;
    return op1 % op2;
}

bool operator>(const int &num, const BigInt &op)
{
    return (op <= num);
}

bool operator<(const int &num, const BigInt &op)
{
    return (op >= num);
}

bool operator==(const int &num, const BigInt &op)
{
    return (op == num);
}

bool operator!=(const int &num, const BigInt &op)
{
    return !(op == num);
}

bool operator>=(const int &num, const BigInt &op)
{
    return num > op || num == op;
}

bool operator<=(const int &num, const BigInt &op)
{
    return num < op || num == op;
}
