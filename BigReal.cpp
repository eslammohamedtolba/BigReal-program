#include "BigReal.h"
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
//----------------------------------------------------------------------------------------------------------------------
//ahmed
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
    //ahmed
    string str= to_string(realNumber),myinteger,myfraction;
    setNumberreal(str);
    fillbigreal(str,myinteger,myfraction);
    integer=BigDecimalInt(myinteger);
    fraction=BigDecimalInt(myfraction);
}
//----------------------------------------------------------------------------------------------------------------------
BigReal::BigReal (string realNumber)
{
    //ahmed
    setNumberreal(realNumber);
    string myinteger,myfraction;
    fillbigreal(realNumber,myinteger,myfraction);
    integer=BigDecimalInt(myinteger);
    fraction=BigDecimalInt(myfraction);
}
//----------------------------------------------------------------------------------------------------------------------
BigReal::BigReal (BigDecimalInt bigInteger)
{
    //ahmed
    integer=bigInteger;
    fraction=BigDecimalInt("0");
}
//----------------------------------------------------------------------------------------------------------------------
BigReal::BigReal (const BigReal& other)
{
    //ahmed
    //Copy constructor
    integer=other.integer;
    fraction=other.fraction;
}
//----------------------------------------------------------------------------------------------------------------------
BigReal::BigReal (BigReal&& other)
{
    //ahmed
    //Move constructor
    integer=other.integer;
    fraction=other.fraction;
}
//----------------------------------------------------------------------------------------------------------------------
BigReal& BigReal::operator= (BigReal& other)
{
    //ahmed
    // Assignment operator
    integer=other.integer;
    fraction=other.fraction;
    return *this;
}
//----------------------------------------------------------------------------------------------------------------------
BigReal& BigReal::operator= (BigReal&& other)
{
    //ahmed
    // Move assignment
    integer=other.integer;
    fraction=other.fraction;
    return *this;
}
//----------------------------------------------------------------------------------------------------------------------
//ahmed
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
//ahmed
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
//ahmed
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
//ahmed
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
//------------------------------------------------------------------------------------
//ahmed
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
