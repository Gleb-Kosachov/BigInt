//
//  BigInt.hpp
//  C++
//
//  Created by Глеб Косачёв on 25.02.21.
//

#ifndef BigInt_hpp
#define BigInt_hpp

#include <deque>
#include <string>

class BigInt final //integer type with no size limits
{
    std::deque<char> number;
    bool has_minus; //if true, the number is less than 0
    static std::deque<char> multiply_by_digit(std::deque<char>, int);
public:
    //constructors
    BigInt();
    BigInt(long long int);
    BigInt(const BigInt &);
    BigInt(const std::deque<char> &);
    explicit BigInt(const char *str);
    
    friend std::ostream &operator<<(std::ostream &, const BigInt &);
    friend std::istream &operator>>(std::istream &, BigInt &);
    
    BigInt operator=(const BigInt &);
    
    BigInt operator+(const BigInt &) const; //addition
    
    BigInt operator-(const BigInt &) const;  //subtraction
    
    BigInt operator*(const BigInt &) const; //multiplication

    BigInt operator/(const BigInt &) const; //division
    
    BigInt operator%(const BigInt &) const; //modulo
    
    //increment
    friend BigInt operator++(BigInt &);
    friend BigInt operator++(BigInt &, int);
    
    //decrement
    friend BigInt operator--(BigInt &);
    friend BigInt operator--(BigInt &, int);
    
    //logical operators
    bool operator>(const BigInt &) const;
    bool operator<(const BigInt &) const;
    bool operator==(const BigInt &) const;
    bool operator!=(const BigInt &) const;
    bool operator>=(const BigInt &) const;
    bool operator<=(const BigInt &) const;
    
    void operator+=(const BigInt &);
    
    void operator-=(const BigInt &);
    
    void operator*=(const BigInt &);
    
    void operator/=(const BigInt &);
    
    void operator%=(const BigInt &);
    
    BigInt operator-() const; //unary minus
    
    BigInt fact() const; //returns factorial
    
    long long int to_int() const; //converts BigInt to usual int.
    
    bool to_bool() const;
    
    explicit operator bool() const;
    
    BigInt power(BigInt) const;
    
    BigInt abs() const;
    
    bool is_prime() const; //returns true if the number is prime. works slowly with big numbers.
    
    BigInt sqrt() const; //returns square root.
};

std::ostream &operator<<(std::ostream &, const BigInt &);
std::istream &operator>>(std::istream &, BigInt &);
//
BigInt operator+(const int &, const BigInt &);
BigInt operator-(const int &, const BigInt &);
BigInt operator*(const int &, const BigInt &);
BigInt operator/(const int &, const BigInt &);
BigInt operator%(const int &, const BigInt &);

BigInt operator++(BigInt &);
BigInt operator++(BigInt &, int);

BigInt operator--(BigInt &);
BigInt operator--(BigInt &, int);

bool operator>(const int &, const BigInt &);
bool operator<(const int &, const BigInt &);
bool operator==(const int &, const BigInt &);
bool operator>=(const int &, const BigInt &);
bool operator<=(const int &, const BigInt &);
bool operator!=(const int &, const BigInt &);

#endif /* BigInt_hpp */
