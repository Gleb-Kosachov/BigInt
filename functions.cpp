//
//  functions.cpp
//  C++
//
//  Created by Глеб Косачёв on 20.03.21.
//

#include "BigInt.hpp"
#include <string>

std::deque<char> BigInt::multiply_by_digit(std::deque<char> op, int digit)
{
    std::deque<char> result;
    int buf = 0;
    for (int i = 0; i < op.size() || buf; i++)
    {
        int d = 0;
        if (static_cast<signed int>(op.size()) - i - 1 >= 0) d = digit * (op[op.size() - i - 1] - 48);
        d += buf;
        buf = 0;
        while (d > 9)
        {
            d -= 10;
            buf++;
        }
        result.push_front(d + 48);
    }
    return result;
}

BigInt BigInt::fact() const
{
    BigInt result = 1;
    for (BigInt n = 2; n <= *this; n++) result *= n;
    return result;
}

long long int BigInt::to_int() const
{
    long long int result = 0;
    for (int i = 0; i < this->number.size(); i++)
    {
        result *= 10;
        result += this->number[i] - 48;
    }
    return result;
}

BigInt BigInt::power(BigInt p) const
{
    if (p.has_minus) return 0;
    BigInt result = 1;
    while (!!p--)
    {
        result *= *this;
    }
    return result;
}

BigInt BigInt::abs() const
{
    if (this->has_minus) return -*this;
    else return *this;
}

bool BigInt::is_prime() const
{
    if (!(*this % 2) || this->operator<(2)) return false;
    for (BigInt i = 3; i < this->abs(); i += 2)
    {
        if (!(*this % i)) return false;
    }
    return true;
}

BigInt BigInt::sqrt() const
{
    if (*this < 0) throw std::invalid_argument("Square root of negative number!" + std::to_string(__LINE__));
    BigInt result = *this - 1;
    if (!*this) result = 0;
    else if (*this < 4) result = 1;
    else if (*this < 9) result = 2;
    else if (*this < 16) result = 3;
    else if (*this < 25) result = 4;
    else if (*this < 36) result = 5;
    else if (*this < 49) result = 6;
    else if (*this < 64) result = 7;
    else if (*this < 81) result = 8;
    else if (*this < 100) result = 9;
    else if (*this == 100) result = 10;
    else while (result * result > (*this)) result = ((*this / result) + result) / 2;
    return result;
}
