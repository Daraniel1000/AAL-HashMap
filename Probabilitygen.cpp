#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

/*
amounts 0-25  - A-Z
amounts 26-51 - a-z
amounts 52    - end of word
amounts 53    - n of entries in current letter
*/

int amain(char argc, char** argv)
{
    string fname;
    if(argc<2) fname = "in.txt";
    else fname = argv[1];
	ifstream fin(fname);
	if(!fin.is_open())
    {
        cout<<"Blad otwarcia pliku\n";
        return -1;
    }
	vector<vector<int> > amounts;                   //wektor wektorów liter na miejscu x
	vector<int> tocopy;
	for(int i=0; i<54; ++i) tocopy.push_back(0);    //wektor zer do kopiowania jako tablica liter na miejscu x
    amounts.push_back(tocopy);
    char c;
    size_t lword;
    while(fin.get(c))
    {
        lword = 0;
        if(c>96&&c<123) amounts[0][c-71]++;         //male litery
        else if (c>64&&c<91) amounts[0][c-65]++;    //duze litery
        else continue;                              //nie litera na pierwszym miejscu -> pominiecie
        ++lword;                                    //dlugosc slowa - miejsce w slowie
        ++amounts[0][53];                           //ilosc do pozniejszego wyliczania prawdopodobienstw
        //cout<<c<<" "<<amounts[0][53]<<endl;
        while(fin.get(c))
        {
            if(lword>=amounts.size())
            {
                amounts.push_back(tocopy);
            }
            if(c>96&&c<123) amounts[lword][c-71]++;
            else if (c>64&&c<91) amounts[lword][c-65]++;
            else
            {
                ++amounts[lword][52];
                ++amounts[lword][53];
                break;
            }
            ++amounts[lword][53];
            ++lword;
        }
    }
    ofstream fout("prob_table");
    fout<<amounts.size()<<endl;
    for(size_t i=0; i<amounts.size(); ++i)
    {
        for(int a=0; a<53; ++a)
        {
            fout<<amounts[i][a]<<" ";
        }
        fout<<endl;
    }
    return 0;

}
