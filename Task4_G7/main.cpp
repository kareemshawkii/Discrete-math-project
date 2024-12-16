#include <iostream> 

using namespace std ; 
// A ==> 65 
// Z ==> 90 
// a ==> 97 
// z ==> 122

string encrypt (string text,int a,int b)
{
    for( int i =0 ; i<text.length(); i++)
    {
        if(text[i]>64 && text[i]<=90)
        {
            text[i]-=65 ; 
            text[i]= (int(text[i])*a +b)%26 ;
            text[i]+=65 ; 
             
        }
        else if(text[i]>=97 && text[i]<=122)
        {
            text[i]-=97 ; 
            text[i]= (int(text[i])*a +b)%26 ;
            text[i]+=97 ; 
        }
        else continue; 

    }
    return text ; 
}
int ainv(int a)
{ 
    for (int i =1 ; i<27 ; i++)
    {
        if (((i*a)%26) == 1)
        return i ; 
    }
    return 1 ;
}
string decrypt  (string text,int a,int b)
{
    // getting modulo multiplicate inverse 
    a = ainv(a); 
    for( int i =0 ; i<text.length(); i++)
    {
        if(text[i]>64 && text[i]<=90)
        {
            text[i]-=65 ; 
            text[i]= ((int(text[i])-b+26)*a)%26 ;
            while (text[i]<0)
            text[i]+=26; 
            text[i]%26;
            text[i]+=65 ; 
             
        }
        else if(text[i]>=97 && text[i]<=122)
        {
            text[i]-=97 ;
            text[i]= ((int(text[i])-b+26)*a)%26 ;
            text[i]+=97 ; 
        }
        else continue; 

    }
    return text ; 
}

int main ()
{
    //  c = ax+b 
    int a = 7 ; 
    int b =9 ; 
    string text = "WQICP QXULIX FSIN PMG" ; 
    cout << "original   text is "<< text <<endl ;
    string cipher = encrypt(text,a,b) ; 
    cout <<   "cipher     text is " <<cipher <<endl ; 
    cout << "decyphered text is " << decrypt(cipher,a,b) <<endl ; 

    cout << "=============================================================\n" ; 
    a=5 ; 
    b=8 ; 
    text = "HELLO" ; 
    cout << "original   text is "<< text <<endl ;
    cipher = encrypt(text,a,b) ; 
    cout <<   "cipher     text is " <<cipher <<endl ; 
    cout << "decyphered text is " << decrypt(cipher,a,b) <<endl ; 

    cout << "=============================================================\n" ; 
    a=5 ; 
    b=8 ; 
    text = "hello" ; 
    cout << "original   text is "<< text <<endl ;
    cipher = encrypt(text,a,b) ; 
    cout <<   "cipher     text is " <<cipher <<endl ; 
    cout << "decyphered text is " << decrypt(cipher,a,b) <<endl ; 

    cout << "=============================================================\n" ; 
    
    cout <<   "cipher     text is " <<text <<endl ; 
    cout << "decyphered text is " << decrypt(text,a,b) <<endl ; 
    // cout << (-5)%26 << endl ;
    // for (int m =0 ; m<26 ; m++)
    // { 
    //     cout <<"a= "<<m <<" ainv = "<< ainv(m) <<endl ; 
    // }



    return 0 ;
}