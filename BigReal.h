#ifndef MAIN_CPP_BIGREAL_H
#define MAIN_CPP_BIGREAL_H
#include "BigDecimalInt.h"
class BigReal {
private:
    BigDecimalInt integer,fraction;
public:
    BigReal (double realNumber = 0.0); // Default constructor
    BigReal (string realNumber);
    BigReal (BigDecimalInt bigInteger);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other);      // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal& other);
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    int size();
    int sign();
    friend ostream& operator << (ostream& out, BigReal num);
    friend istream& operator >> (istream& in, BigReal &num);
};

#endif //MAIN_CPP_BIGREAL_H
//---------------------------------------------------------------------
