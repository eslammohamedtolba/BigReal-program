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
    char signNumber;
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
    int sign();
    void setNumber(string num);
    string getNumber(){
        return number;
    }

    BigDecimalInt(){}
    BigDecimalInt(string num)
    {
        setNumber(num);
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
            signNumber = '+';
        }
        else if (number[0] == '-')
        {
            number.erase(0,1);
            signNumber = '-';
        }
        else
        {
            signNumber = '+';
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

    if(signNumber == '-' && anotherDec.signNumber == '+')
    {
        return true;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '-')
    {
        return false;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '+')
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

    if(signNumber == '-' && anotherDec.signNumber == '+')
    {
        return false;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '-')
    {
        return true;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '+')
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
    if (signNumber == anotherDec.signNumber && number == anotherDec.number)
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
    signNumber = anotherDec.signNumber;
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
    char signNumber1 = signNumber, signNumber2 = number2.signNumber;
    string num1 = number, num2 = number2.number;
    BigDecimalInt number1 = *this;

    while (num1.length() < num2.length()){
        num1 = '0' + num1;
    }
    while (num2.length() < num1.length()){
        num2 = '0' + num2;
    }

    if (signNumber1 == signNumber2){
        result.signNumber = signNumber1;
        result.number = addition(num1,num2);

    }else{

        if(number1.signNumber == '-')
        {
            number1.signNumber = '+';
            result = (number2 - number1);
        }
        else{
            number2.signNumber = '+';
            result = (number1 - number2);
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
    char sign1 = signNumber, sign2 = anotherDec.signNumber;

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
        if(signNumber == '-')
        {
            obj.signNumber = '-';
            is_determined = true;
        }
        else
        {
            obj.signNumber = '+';
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
        obj.signNumber = '-';
    }
    else if(!is_determined)
    {
        obj.signNumber = '+';
    }

    obj.number = res;
    return obj;
}

// function to return the size of number.
int BigDecimalInt :: size()
{
    return number.size();
}

// function returns the sign.
int BigDecimalInt :: sign()
{
    if (signNumber == '+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// operator << overloading function.
ostream &operator << (ostream &out, BigDecimalInt num)
{
    if(num.signNumber == '+')
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
            out << num.signNumber << num.number ;
        }
    }
    return out;
}
//----------------------------------------------------------------------------------------------------------------------
bool chValInpreal(string input)
{
    regex validInput("[-+]?[0-9]+[.][0-9]+");
    return regex_match(input, validInput);
}

// constructor that takes a string as an input.
void setNumberreal(string num)
{
    bool validNumber = chValInpreal(num);
    if(!validNumber)
    {
        cout << "Invalid" << "\n";
        exit(1);
    }
}

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
//----------------------------------------------------------------------------------------------------------------------
void fillbigreal(string str,string &integer,string &fraction)
{
    int index=str.find('.');
    integer=str.substr(0,index);
    fraction=str.substr(index+1,str.size()-index-1);
    fraction=(str[0]=='-'?"-":"+")+fraction;
}
//----------------------------------------------------------------------------------------------------------------------
BigReal::BigReal (double realNumber) // Default constructor
{
    //Ahmed
    string str= to_string(realNumber),myinteger,myfraction;
    setNumberreal(str);
    fillbigreal(str,myinteger,myfraction);
    integer=BigDecimalInt(myinteger);
    fraction=BigDecimalInt(myfraction);
}
//----------------------------------------------------------------------------------------------------------------------
BigReal::BigReal (string realNumber)
{
    //Ahmed
    setNumberreal(realNumber);
    string myinteger,myfraction;
    fillbigreal(realNumber,myinteger,myfraction);
    integer=BigDecimalInt(myinteger);
    fraction=BigDecimalInt(myfraction);
}
//----------------------------------------------------------------------------------------------------------------------
BigReal::BigReal (BigDecimalInt bigInteger)
{
    //Ahmed
    integer=bigInteger;
    fraction=BigDecimalInt("0");
}
//----------------------------------------------------------------------------------------------------------------------
BigReal::BigReal (const BigReal& other)
{
    //Ahmed
    //Copy constructor
    integer=other.integer;
    fraction=other.fraction;
}
//----------------------------------------------------------------------------------------------------------------------
BigReal::BigReal (BigReal&& other)
{
    //Ahmed
    //Move constructor
    integer=other.integer;
    fraction=other.fraction;
}
//----------------------------------------------------------------------------------------------------------------------
BigReal& BigReal::operator= (BigReal& other)
{
    //Ahmed
    // Assignment operator
    integer=other.integer;
    fraction=other.fraction;
    return *this;
}
//----------------------------------------------------------------------------------------------------------------------
BigReal& BigReal::operator= (BigReal&& other)
{
    //Ahmed
    // Move assignment
    integer=other.integer;
    fraction=other.fraction;
    return *this;
}
//----------------------------------------------------------------------------------------------------------------------
void equalfracs(BigDecimalInt &frac1,BigDecimalInt &frac2)
{
    int sf1=frac1.size(),
    sf2=frac2.size();string str="";
    while(sf1<sf2){
        sf2--;
        str+='0';
        if(sf1==sf2){
            str=(frac1.sign()==0?'-':'+')+frac1.getNumber()+str;
            frac1=BigDecimalInt(str);
        }
    }
    while(sf2<sf1){
        sf1--;
        str+='0';
        if(sf1==sf2){
            str=(frac2.sign()==0?'-':'+')+frac2.getNumber()+str;
            frac2=BigDecimalInt(str);
        }
    }
}
//-----------------------------------------------------------------------------------
void equalint(BigDecimalInt &int1,BigDecimalInt &int2)
{
    int sf1=int1.size(),
    sf2=int2.size();string str="";
    while(sf1<sf2){
        sf2--;
        str+='0';
        if(sf1==sf2){
            str=(int1.sign()==0?'-':'+')+int1.getNumber()+str;
            int1=BigDecimalInt(str);
        }
    }
    while(sf2<sf1){
        sf1--;
        str+='0';
        if(sf1==sf2){
            str=(int2.sign()==0?'-':'+')+int2.getNumber()+str;
            int2=BigDecimalInt(str);
        }
    }
}
//-----------------------------------------------------------------------------------
void rightSfract(BigDecimalInt &fractionnum3,BigDecimalInt frac1,BigDecimalInt frac2)
{
    if(frac1.sign()!=frac2.sign()){
        int i=0;string str="";
        while(frac1.getNumber()[i]==frac2.getNumber()[i] && i<frac1.size()-1){
            str+='0';
            i++;
        }
        str=(fractionnum3.sign()==0?"-":"+")+str+fractionnum3.getNumber();
        fractionnum3=BigDecimalInt(str);
    }
}
//-----------------------------------------------------------------------------------
void sameBirsign(BigDecimalInt &integthi,BigDecimalInt &fracthi,BigDecimalInt fracfirst)
{
    string str;
    if(fracthi.size()>fracfirst.size()){
        str=fracthi.getNumber();
        str=str.substr(1,str.size()-1);
        fracthi=BigDecimalInt(str);
        integthi=integthi+BigDecimalInt("1");
    }
}
void diffBirsign(BigDecimalInt &integthi,BigDecimalInt &fracthi)
{
    string strinteger(integthi.size(),'0'),strfrac(fracthi.size(),'0');
    if(fracthi.getNumber()!=strfrac){
        if(integthi.getNumber()==strinteger){
            strinteger=(fracthi.sign()==1?"+":"-")+strinteger;
            integthi=BigDecimalInt(strinteger);
        }
        else{
            bool istrue=1;string strdifffr="";char ch;
            integthi=integthi+BigDecimalInt(integthi.sign()==0?"+1":"-1");
            for(int i=fracthi.size()-1;i>=0;i--){
                if(fracthi.getNumber()[i]!='0' && istrue==1){
                    istrue=0;
                    ch='9'-fracthi.getNumber()[i]+49;
                    strdifffr=ch;
                }
                else if(!istrue){
                    ch='9'-fracthi.getNumber()[i]+48;
                    strdifffr=ch+strdifffr;
                }
            }
            fracthi=BigDecimalInt(strdifffr);
        }
    }
}
//-----------------------------------------------------------------------------------
BigReal BigReal :: operator + (BigReal& other)
{
    //Eslam
    BigReal num3;
    num3.integer=integer+other.integer;
    equalfracs(fraction,other.fraction);
    num3.fraction=fraction+other.fraction;
    rightSfract(num3.fraction,fraction,other.fraction);
    if(num3.integer.sign()==num3.fraction.sign()){
        sameBirsign(num3.integer,num3.fraction,fraction);
    }
    else{
        diffBirsign(num3.integer,num3.fraction);
    }
//    if(num3.integer.sign()==0){
//        cout<<'-';
//    }
//    cout<<num3.integer.getNumber()<<"."<<num3.fraction.getNumber()<<endl;
    return num3;
}
//-----------------------------------------------------------------------------------
BigReal BigReal::operator- (BigReal& other)
{
    //Eslam
    string str1integ=(other.integer.sign()==0?"+":"-")+other.integer.getNumber(),
    str2frac=(other.fraction.sign()==0?"+":"-")+other.fraction.getNumber();
    other.integer=BigDecimalInt(str1integ);
    other.fraction=BigDecimalInt(str2frac);
    BigReal num3;
    num3.integer=integer+other.integer;
    equalfracs(fraction,other.fraction);
    num3.fraction=fraction+other.fraction;
    rightSfract(num3.fraction,fraction,other.fraction);
    if(num3.integer.sign()==num3.fraction.sign()){
        sameBirsign(num3.integer,num3.fraction,fraction);
    }
    else{
        diffBirsign(num3.integer,num3.fraction);
    }
//    if(num3.integer.sign()==0){
//        cout<<'-';
//    }
//    cout<<num3.integer.getNumber()<<"."<<num3.fraction.getNumber()<<endl;
    return num3;

}
//----------------------------------------------------------------------------------------------------------------------
bool BigReal::operator< (BigReal anotherReal)
{
    //abdelrahman
    equalint(integer,anotherReal.integer);
    equalfracs(fraction,anotherReal.fraction);
    if(integer<anotherReal.integer)
        return true;
    else if(integer==anotherReal.integer && fraction <anotherReal.fraction )
        return true;
    else
        return false;


}
//----------------------------------------------------------------------------------------------------------------------
bool BigReal::operator> (BigReal anotherReal)
{
    //abdelrahman
    equalint(integer,anotherReal.integer);
    equalfracs(fraction,anotherReal.fraction);
    if(integer>anotherReal.integer)
        return true;
    else if(integer==anotherReal.integer && fraction > anotherReal.fraction )
        return true;
    else
        return false;

}
//----------------------------------------------------------------------------------------------------------------------
bool BigReal::operator== (BigReal anotherReal)
{
    //abdelrahman
    equalint(integer,anotherReal.integer);
    equalfracs(fraction,anotherReal.fraction);
    if(integer==anotherReal.integer && fraction==anotherReal.fraction)
        return true;
    else
        return false;

}
//----------------------------------------------------------------------------------------------------------------------
int BigReal::size()
{
    //abdelrahman
    return (integer.size()+fraction.size());

}
//----------------------------------------------------------------------------------------------------------------------
int BigReal::sign()
{
    //abdelrahman
    return (integer.sign());

}
//----------------------------------------------------------------------------------------------------------------------
ostream &operator << (ostream &out,BigReal num)
{
    //abdelrahman
    if(num.integer.sign()==0)
        cout<<'-';
    cout<<num.integer.getNumber()<<'.'<<num.fraction.getNumber();
    return out;

}
//----------------------------------------------------------------------------------------------------------------------
istream& operator>> (istream& in, BigReal &num)
{
    //abdelrahman adel
    string intstr,frastr,str;
    cin>>str;
    fillbigreal(str,intstr,frastr);
    num.integer=BigDecimalInt(intstr);
    num.fraction=BigDecimalInt(frastr);
    return in;

}
//----------------------------------------------------------------------------------------------------------------------
int main() {
    BigReal n,m;
    cin>>n;
    cin>>m;
    cout<<n<<endl;
    cout<<m<<endl;
}
