/*
Maciej Kapuscinski - Tablica mieszajaca AAL
*/
#include<iostream>
#include<chrono>
#include<fstream>
#include "HashMap.h"
using namespace std;
using namespace chrono;

int main(int argc, char** argv)
{
    if(argc > 1)
    {
        string s = argv[1];
        if(s == "-h")
        {
            cout<<"uzycie: ./hashmap filename_in n filename_del\nn - funkcja mieszajaca do uzycia (0 lub 1)"<<endl;
            cout<<"filename_in - nazwa pliku zawierajacego slowa do wczytania\nfilename_del - nazwa pliku zawierajacego slowa do usuniecia"<<endl;
            cout<<"pominiecie filename_out - brak usuwania\npominiecie n - funkcja nr 0\npominiecie filename_in - wczytywanie slow z wejscia standardowego"<<endl;
            return 0;
        }
    }
    time_point<system_clock> start , stop, allstop;
    int n = 0, ndel = 0, nerr = 0, nerr_del = 0;
    int hashf = argc>2? atoi(argv[2]) : 0;
    string s;
    if(argc < 2)
    {
        HashMap map;
        cout<<"aby zakończyć wprowadzanie, wprowadź dowolny znak nie bedacy litera na początku linii\n";
        start = system_clock::now();
        cin>>s;
        while((s[0]>64&&s[0]<91) || (s[0]>96&&s[0]<123))
        {
            try
            {
                map.add(s);
            }
            catch (std::overflow_error e)
            {
                cout<<"Blad: "<<e.what()<<endl;
            }
            ++n;
            cin>>s;
        }
        stop = system_clock::now();
    }
    else
    {
        string fname = argv[1];
        string outname = argc > 3? argv[3] : "";
        HashMap map(hashf);
        ifstream fin(fname, std::ifstream::in);
        if(!fin.is_open())
        {
            cout<<"Blad otwarcia pliku wejsciowego\n";
            return -1;
        }
        start = system_clock::now();
        while(fin>>s)
        {
            try
            {
                map.add(s);
            }
            catch (std::overflow_error e)
            {
                ++nerr;
            }
            ++n;
        }
        stop = system_clock::now();
        fin.close();
        if(!outname.empty())
        {
            fin.open(outname);
            while(fin>>s)
            {
                try
                {
                    map.remove(s);
                }
                catch (std::out_of_range e)
                {
                    ++nerr_del;
                }
                ++ndel;
            }
        }
        allstop = system_clock::now();
    }
    ofstream fout("times.txt", std::ofstream::app);
    fout<<"elementy dodane: "<<n<<" czas wykonania: "<<duration_cast<microseconds>(stop-start).count()<<" us ";
    if(ndel>0)
    {
        fout<<"elementy usuniete: "<<ndel<<" czas wykonania: "<<duration_cast<microseconds>(allstop - stop).count()<<" us ";
    }
    cout<<"Funkcja mieszajaca: "<<hashf<<endl;
}
