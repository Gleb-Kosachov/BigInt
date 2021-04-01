//
//  operators.cpp
//  C++
//
//  Created by Глеб Косачёв on 20.03.21.
//

#include "BigInt.hpp"
#include <iostream>
#include <string>

std::ostream &operator<<(std::ostream &stream, const BigInt &val)
{
    if (val.has_minus) stream << '-';
    for (int i = 0; i < val.number.size(); i++)
    {
        stream << val.number[i];
    }
    return stream;
}

std::istream &operator>>(std::istream &stream, BigInt &val)
{
    val.number.clear();
    std::string str;
    stream >> str;
    for (int i = 0; i < str.size(); i++)
    {
        if ((str[i] < 48 || str[i] > 57) && str[i] != '-') throw std::invalid_argument("Invalid input! " + std::to_string(__LINE__));
        val.number.push_back(str[i]);
    }
    if (val.number.front() == '-')
    {
        val.has_minus = true;
        val.number.pop_front();
    }
    return stream;
}

BigInt BigInt::operator=(const BigInt &op)
{
    this->number = op.number;
    this->has_minus = op.has_minus;
    return *this;
}

BigInt BigInt::operator+(const BigInt &op2) const
{
    BigInt result;
    if (this->has_minus && op2.has_minus)
    {
        result.has_minus = true;
    }
    else if (op2.has_minus) return *this - (-op2);
    else if (this->has_minus) return op2 - (-*this);
    int buf = 0;
    for (int i = 0; i < this->number.size() || i < op2.number.size() || buf; i++)
    {
        int digit = buf;
        if (static_cast<signed int>(this->number.size()) - i - 1 >= 0) digit += this->number[static_cast<int>(this->number.size()) - i - 1] - 48;
        if (static_cast<signed int>(op2.number.size()) - i - 1 >= 0) digit += op2.number[static_cast<int>(op2.number.size()) - i - 1] - 48;
        buf = 0;
        while (digit > 9)
        {
            buf++;
            digit -= 10;
        }
        result.number.push_front(digit + 48);
    }
    return result;
}

BigInt BigInt::operator-(const BigInt &op2) const
{
    if (op2.has_minus) return *this + (-op2);
    if ((*this) < op2) return -(op2 - (*this));
    BigInt result;
    int buf = 0;
    for (int i = 0; i < this->number.size() || i < op2.number.size() || buf; i++)
    {
        int digit = 0;
        if (static_cast<signed int>(this->number.size()) - i - 1 >= 0) digit += this->number[this->number.size() - i - 1] - 48;
        if (static_cast<signed int>(op2.number.size()) - i - 1 >= 0) digit -= op2.number[op2.number.size() - i - 1] - 48;
        digit -= buf;
        buf = 0;
        while (digit < 0)
        {
            digit += 10;
            buf++;
        }
        result.number.push_front(digit + 48);
    }
    while (!result.number.empty() && result.number.front() == '0') result.number.pop_front();
    if (result.number.empty()) result = 0;
    return result;
}

BigInt BigInt::operator*(const BigInt &op2) const
{
    BigInt result = 0;
    bool result_has_minus = true;
    if ((this->has_minus && op2.has_minus) || (!this->has_minus && !op2.has_minus)) result_has_minus = false;
    for (int i = 0; i < op2.number.size(); i++)
    {
        std::deque<char> var = BigInt::multiply_by_digit(this->number, op2.number[op2.number.size() - i - 1] - 48);
        for (int j = 0; j < i; j++)
        {
            var.push_back('0');
        }
        result += var;
    }
    while (!result.number.empty() && result.number.front() == '0') result.number.pop_front();
    if (result.number.empty()) result = 0;
    result.has_minus = result_has_minus;
    return result;
}

BigInt BigInt::operator/(const BigInt &op) const
{
    if (op == 0) throw __LINE__;
    BigInt result;
    bool result_has_minus;
    if (this->has_minus == op.has_minus) result_has_minus = false;
    else result_has_minus = true;
#define op (op.abs())
    if (this->abs() < op)
    {
        result = 0;
        return result;
    }
    if (this->abs() == op)
    {
        result = 1;
        result.has_minus = result_has_minus;
        return result;
    }
    std::deque<char> buf = {};
    for (int i = 0, iterations = 0; i < this->number.size(); iterations++)
    {
        BigInt temp = buf;
        buf.clear();
        int inside_iterations = 0;
        if (temp.number.empty()) while (this->number[i] == '0' && i < this->number.size()) {result.number.push_back('0'); i++;}
        do
        {
            if (iterations && inside_iterations) result.number.push_back('0');
            if (i >= this->number.size()) return result;
            temp.number.push_back(this->number[i]);
            inside_iterations++;
            i++;
        } while (temp < op);
        int to_res = 1;
        while (op * to_res < temp) to_res++;
        if (op * to_res > temp) to_res--;
        result.number.push_back(static_cast<char>(to_res + 48));
        buf = (temp - (op * to_res)).number;
        if(!buf.empty() && buf.front() == '0') buf = {};
    }
    while (!result.number.empty() && result.number.front() == '0') result.number.pop_front();
//    if (result.number.empty()) result = 0;
    result.has_minus = result_has_minus;
    return result;
#undef op
}

BigInt BigInt::operator%(const BigInt &op) const
{
    return (*this) - (((*this) / op) * op);
}

bool BigInt::operator>(const BigInt &op2) const
{
    if (this->has_minus && !op2.has_minus) return false;
    if (!this->has_minus && op2.has_minus) return true;
    if (this->has_minus && op2.has_minus) return -*this < -op2;
    if (this->number.size() > op2.number.size()) return true;
    if (this->number.size() < op2.number.size()) return false;
    for (int i = 0; i < this->number.size(); i++)
    {
        if (this->number[i] > op2.number[i]) return true;
        if (this->number[i] < op2.number[i]) return false;
    }
    return false;
}

bool BigInt::operator<(const BigInt &op2) const
{
    if (this->has_minus && !op2.has_minus) return true;
    if (!this->has_minus && op2.has_minus) return false;
    if (this->has_minus && op2.has_minus) return -*this > -op2;
    if (this->number.size() < op2.number.size()) return true;
    if (this->number.size() > op2.number.size()) return false;
    for (int i = 0; i < this->number.size(); i++)
    {
        if (this->number[i] > op2.number[i]) return false;
        if (this->number[i] < op2.number[i]) return true;
    }
    return false;
}

bool BigInt::operator==(const BigInt &op2) const
{
    if (this->number.size() != op2.number.size()) return false;
    for (int i = 0; i < this->number.size(); i++)
    {
        if (this->number[i] != op2.number[i]) return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt &op2) const
{
    return !(*this == op2);
}

bool BigInt::operator>=(const BigInt &op2) const
{
    if ((*this > op2) || *this == op2) return true;
    return false;
}

bool BigInt::operator<=(const BigInt &op2) const
{
    if ((*this < op2) || *this == op2) return true;
    return false;
}

BigInt operator++(BigInt &arg)
{
    arg = arg + 1;
    return arg;
}

BigInt operator++(BigInt &arg, int unused)
{
    BigInt result = arg;
    ++arg;
    return result;
}

BigInt operator--(BigInt &arg)
{
    arg = arg - 1;
    return arg;
}

BigInt operator--(BigInt &arg, int unused)
{
    BigInt result = arg;
    --arg;
    return result;
}

BigInt BigInt::operator-() const
{
    BigInt result = *this;
    result.has_minus = result.has_minus ? false : true;
    return result;
}

void BigInt::operator+=(const BigInt &op)
{
    *this = *this + op;
}

void BigInt::operator-=(const BigInt &op)
{
    *this = *this - op;
}

void BigInt::operator*=(const BigInt &op)
{
    (*this) = (*this) * op;
}

void BigInt::operator/=(const BigInt &op2)
{
    *this = *this / op2;
}

void BigInt::operator%=(const BigInt &op)
{
    *this = *this % op;
}
