// FCAI – Object-Oriented Programming 1 – 2022 - Assignment 1
// Program Name: BigDecimalInt
// Last Modification Date: 27/10/2022
// Author1 and ID and Group: Eslam Mohamed Abdul azim Ali Tolba  ID: 20211013
// Author2 and ID and Group: Aya Ali Hassan  ID: 20210083 (d, e)
// Author3 and ID and Group: Mohamed Ashraf Fahim  ID: 20210329 (f, i, j , k)
/*
description:

 */
#include <iostream>
#include <deque>
#include <regex>
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
class BigDecimalInt{
private:
    string number;
    char sign;
    void setNumber(string num);
    bool checkValidInput(string input);
public:
    bool operator < (const BigDecimalInt& anotherDec);
    bool operator > (const BigDecimalInt& anotherDec);
    bool operator == (const BigDecimalInt anotherDec);
    BigDecimalInt& operator = (BigDecimalInt anotherDec);
    BigDecimalInt operator + (BigDecimalInt number2);
    BigDecimalInt operator - (BigDecimalInt anotherDec);
    friend ostream &operator << (ostream &out, BigDecimalInt num);
    int size();
    int Sign();
    void push_back(char ch);
    void push_front(char ch);
    BigDecimalInt(){}
    BigDecimalInt(string num)
    {
        setNumber(num);
    }
    string getnum(){
        return number;
    }
};
//----------------------------------------------------------------------------------------------------------------------
// regex function that checks the validation of the input.
bool BigDecimalInt :: checkValidInput(string input)
{
    regex validInput("[-+]?[0-9]+");
    return regex_match(input, validInput);
}

// constructor that takes a string as an input.
void BigDecimalInt :: setNumber(string num)
{
    bool validNumber = checkValidInput(num);
    if(validNumber)
    {
        number = num;
        if(number[0] == '+')
        {
            number.erase(0,1);
            sign = '+';
        }
        else if (number[0] == '-')
        {
            number.erase(0,1);
            sign = '-';
        }
        else
        {
            sign = '+';
        }
    }
    else
    {
        cout << "Invalid" << "\n";
        exit(1);
    }
}

// operator < overloading function.
bool BigDecimalInt :: operator < (const BigDecimalInt& anotherDec)
{
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2){
        comp1 += '0';
        len1++;
    }
    while (len2 < len1){
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if(sign == '-' && anotherDec.sign == '+')
    {
        return true;
    }
    else if(sign == '+' && anotherDec.sign == '-')
    {
        return false;
    }
    else if(sign == '+' && anotherDec.sign == '+')
    {
        return comp1 < comp2;
    }
    else
    {
        return comp1 > comp2;
    }
}

// operator > overloading function.
bool BigDecimalInt :: operator > (const BigDecimalInt &anotherDec)
{
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2){
        comp1 += '0';
        len1++;
    }
    while (len2 < len1){
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if(sign == '-' && anotherDec.sign == '+')
    {
        return false;
    }
    else if(sign == '+' && anotherDec.sign == '-')
    {
        return true;
    }
    else if(sign == '+' && anotherDec.sign == '+')
    {
        return comp1 > comp2;
    }
    else
    {
        return comp1 < comp2;
    }
}

// operator == overloading function.
bool BigDecimalInt :: operator == (const BigDecimalInt anotherDec)
{
    if (sign == anotherDec.sign && number == anotherDec.number)
    {
        return true;

    }
    else
    {
        return false;
    }
}

// operator = overloading function.
BigDecimalInt& BigDecimalInt :: operator = (BigDecimalInt anotherDec)
{
    sign = anotherDec.sign;
    number = anotherDec.number;
    return *this;
}

//addition implementation.
string addition(string num1,string num2)
{
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    string res = "";
    int carry = 0;
    while (it1 != num1.rend())
    {
        int twoDigitsSum;
        carry = 0;
        twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
        if (twoDigitsSum >= 10)
        {
            carry = 1;
        }
        res = char((twoDigitsSum % 10) + '0') + res;
        *(it1 + 1) = char(((*(it1 + 1) - '0') + carry) + '0');
        it1++;
        it2++;
    }
    if (carry)
    {
        res = char((carry) + '0') + res;
    }
    return res;
}

//subtraction implementation
string subtraction(string num1,string num2){
    deque<long long>d;
    string res;

    for (long long i = num1.length() - 1; i >= 0; i--)
    {
        if (num1[i] < num2[i])
        {
            num1[i] = char (((num1[i] - '0') + 10) + '0');
            num1[i - 1] = char (((num1[i - 1] - '0') - 1) + '0');
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
        else
        {
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
    }

    for (auto i : d)
    {
        res += to_string(i);
    }
    return res;
}

// // operator + overloading function.
BigDecimalInt BigDecimalInt :: operator + (BigDecimalInt number2)
{
    BigDecimalInt result;
    char signNumber1 = sign, signNumber2 = number2.sign;
    string num1 = number, num2 = number2.number;
    BigDecimalInt number1 = *this;

    while (num1.length() < num2.length()){
        num1 = '0' + num1;
    }
    while (num2.length() < num1.length()){
        num2 = '0' + num2;
    }

    if (signNumber1 == signNumber2){
        result.sign = signNumber1;
        result.number = addition(num1,num2);

    }else{

        if(number1.sign=='-')
        {
            number1.sign = '+';
            result = (number2-number1);
        }
        else{
            number2.sign = '+';
            result = (number1-number2);
        }
    }
    return result;
}

// operator - overloading function.
BigDecimalInt BigDecimalInt :: operator - (BigDecimalInt anotherDec)
{
    BigDecimalInt obj;
    deque<long long> d;
    string strmin = "", res = "";
    string num1 = number, num2 = anotherDec.number;
    char sign1 = sign, sign2 = anotherDec.sign;

    if (number.length() > anotherDec.number.length())
    {
        for (long long i = 0; i < number.length() - anotherDec.number.length(); i++)
        {
            strmin += '0';
        }
        strmin += anotherDec.number;
        num2 = strmin;
    }
    else if (number.length() < anotherDec.number.length())
    {
        for (long long i = 0; i < anotherDec.number.length() - number.length(); i++)
        {
            strmin += '0';
        }
        strmin += number;
        num1 = strmin;
    }

    bool ok = false, is_determined = false;
    if (num1 < num2)
    {
        swap(num1, num2);
        swap(sign1, sign2);
        ok = true;
    }

    if (sign1 == sign2 )
    {
        res = subtraction(num1,num2);

        if(sign1=='-')ok = !ok;
    }
    else
    {
        res = addition(num1,num2);
        if(sign == '-')
        {
            obj.sign = '-';
            is_determined = true;
        }
        else
        {
            obj.sign = '+';
            is_determined = true;
        }

    }

    bool right = false;
    for (long long i = 0; i < res.length(); i++)
    {
        if (res[i] != '-' && res[i] != '0')
        {
            right = true;
        }
        if (!right && res[i] == '0')
        {
            res.erase(i, 1);
            i--;
        }
    }

    if(res.empty()) res = "0";
    if (!is_determined && (ok))
    {
        obj.sign = '-';
    }
    else if(!is_determined)
    {
        obj.sign = '+';
    }

    obj.number=res;
    return obj;
}

// function to return the size of number.
int BigDecimalInt :: size()
{
    return number.size();
}

// function returns the sign.
int BigDecimalInt :: Sign()
{
    if (sign == '+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// function to push a character.
void BigDecimalInt ::push_back(char ch)
{
    number.push_back(ch);
}

// function to push a character in the front.
void BigDecimalInt ::push_front(char ch)
{
    string temp;
    temp = ch + number;
    number = temp;
}

// operator << overloading function.
ostream &operator << (ostream &out, BigDecimalInt num)
{
    if(num.sign == '+')
    {
        out << num.number ;
    }
    else
    {
        if(num.number == "0")
        {
            out << num.number ;
        }
        else
        {
            out << num.sign << num.number ;
        }
    }
    return out;
}
//----------------------------------------------------------------------------------------------------------------------------------
class BigReal {
private:
    BigDecimalInt integer,fraction;
public:
    BigReal (double realNumber = 0.0) // Default constructor
    {
        //Ahmed
    }
    BigReal (string realNumber)
    {
        //Ahmed
    }
    BigReal (BigDecimalInt bigInteger)
    {
        //Ahmed
    }
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
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
    friend istream& operator >> (istream& in, BigReal num);
};
//----------------------------------------------------------------------------------------------------------------------
BigReal BigReal::operator+ (BigReal& other)
{
    //Eslam
}
//----------------------------------------------------------------------------------------------------------------------
BigReal BigReal::operator- (BigReal& other)
{
    //Eslam
}
//----------------------------------------------------------------------------------------------------------------------
bool BigReal::operator< (BigReal anotherReal)
{
    //abdelrahman
}
//----------------------------------------------------------------------------------------------------------------------
bool BigReal::operator> (BigReal anotherReal)
{
    //abdelrahman
}
//----------------------------------------------------------------------------------------------------------------------
bool BigReal::operator== (BigReal anotherReal)
{
    //abdelrahman
}
//----------------------------------------------------------------------------------------------------------------------
int BigReal::size()
{
    //abdelrahman
}
//----------------------------------------------------------------------------------------------------------------------
int BigReal::sign()
{
    //abdelrahman
}
//----------------------------------------------------------------------------------------------------------------------
ostream& operator << (ostream& out, BigReal num)
{
    //abdelrahman
}
//----------------------------------------------------------------------------------------------------------------------
istream& operator >> (istream& in, BigReal num)
{
    //abdelrahman
}
//----------------------------------------------------------------------------------------------------------------------
int main() {
    BigReal n("123456767.23748974");
    BigReal m("8978972342.238800831");
}
