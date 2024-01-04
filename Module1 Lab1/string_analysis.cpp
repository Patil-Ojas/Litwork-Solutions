#include <iostream>
#include <cstdio> //who even uses this?
#include <string>
#include <iomanip>
using namespace std;

void get_percentages(string str)
{
    float leng = str.length();
    float uppercase_characters = 0;
    float lowercase_characters = 0;
    float digits = 0;
    float other_characters = 0;
    
    for(int i=0; i<leng; i++)
    {
        if (str[i]>='A' and str[i]<='Z')
        {
            uppercase_characters++;
        }
        else if (str[i]>='a' and str[i]<='z')
        {
            lowercase_characters++;
        }
        else if (str[i]>='0' and str[i]<='9')
        {
            digits++;
        }
        else
        {
            other_characters++;
        }
    }
    float upc = (uppercase_characters/leng)*100;
    float lwc = (lowercase_characters/leng)*100;
    float dg = (digits/leng)*100;
    float oc = (other_characters/leng)*100;
    
    printf("%.3f", upc);
    cout<<"% ";
    printf("%.3f", lwc);
    cout<<"% ";
    printf("%.3f", dg);
    cout<<"% ";
    printf("%.3f", oc);
    cout<<"%";
}

int main() 
{
    string str;
    getline(cin, str);
    
    get_percentages(str);
    
    return 0;
}
                                                                                                                            