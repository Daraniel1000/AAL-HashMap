#include<iostream>
#include<fstream>
#include<vector>
#include<random>
using namespace std;

/*
amounts 0-25  - A-Z
amounts 26-51 - a-z
amounts 52    - end of word
amounts 53    - n of entries in current letter
*/

int bmain(char argc, char** argv)
{
    int nwords;
    string fname;
    if(argc > 1) nwords = atoi(argv[1]);
    else nwords = 100;
    if(argc > 2) fname = argv[2];
    else fname = "out.txt";
    ifstream fin("prob_table");
    if(!fin.is_open())
    {
        cout<<"Blad otwarcia pliku tablicy prawdopodobienstwa\n";
        return -1;
    }
    size_t n, i;
    int temp;
    vector<int> amounts;
    vector<std::discrete_distribution<int>> distribution;
    char letter;
    fin>>n;
    for(size_t a=0; a<n; ++a)
    {
        amounts.clear();
        for(i=0; i<53; ++i)
        {
            fin>>temp;
            amounts.push_back(temp);
        }
        distribution.push_back(*new std::discrete_distribution<int>(amounts.begin(), amounts.end()));
    }
    fin.close();

    //std::random_device rd;
    //std::mt19937 gen(rd());
    std::default_random_engine gen;
    ofstream fout(fname);
    if(!fout.is_open())
    {
        cout<<"Blad otwarcia pliku wyjsciowego\n";
        return -1;
    }
    for(int t=0; t<nwords; ++t)
    {
        i=0;
        while(true)
        {
            letter = distribution[i](gen);
            if(letter<26) letter += 65;
            else if(letter<52) letter += 71;
            else break;
            fout<<letter;
            ++i;
            if(i>=n)
            {
                return -1;
            }
        }
        fout<<endl;
    }
    fout.close();
}
