#include <iostream>
#include <vector>
#include <locale>
#include <iomanip>
#include <numeric>   
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Studentas
{
    string vardas;
    string pavarde;
    vector<double> namudarburez;
    double egzaminorez = 0.0;
    double namudarburezsuma = 0.0;
    double vidurkis = 0.0;
    double galutinisbalasvidurkis = 0.0;
    double mediana = 0.0;
    double galutinisbalasmediana = 0.0;
};

void NetinkamaIvestis()
{
    cout << "Netinkama ávestis. Programa iğjungiama...";
}

void Rikiavimas(vector<double>& mas)
{
    sort(mas.begin(), mas.end());
}

double Mediana(const vector<double>& namudarburez)
{
    double mediana = 0.0;
    int namudarbai = namudarburez.size();
    if (namudarbai % 2 == 0)
    {
        mediana = (namudarburez[namudarbai / 2] + namudarburez[namudarbai / 2 - 1]) / 2.0;
    }
    else
    {
        mediana = namudarburez[namudarbai / 2];
    }
    return mediana;
}

double GenerateRandomGrade()
{
    return rand() % 11;
}

string GeneruotiVardus()
{
    vector<string> vardai = { "Jonas", "Petras", "Antanas", "Marius", "Tomas" };
    return vardai[rand() % vardai.size()];
}

string GeneruotiPavardes()
{
    vector<string> pavardes = { "Kazlauskas", "Petrauskas", "Stankevièius", "Gudelis", "Lukğys" };
    return pavardes[rand() % pavardes.size()];
}

bool vardolyginimas(const Studentas& a, const Studentas& b)
{
    return a.vardas < b.vardas;
}

bool pavardeslyginimas(const Studentas& a, const Studentas& b)
{
    return a.pavarde < b.pavarde;
}

bool vidurkiolyginimas(const Studentas& a, const Studentas& b)
{
    return a.galutinisbalasvidurkis < b.galutinisbalasvidurkis;
}

bool medianoslyginimas(const Studentas& a, const Studentas& b)
{
    return a.galutinisbalasmediana < b.galutinisbalasmediana;
}

void PrintStudents(const vector<Studentas>& studentai)
{
    cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(30) << "Galutinis balas (vid.)" << setw(30) << "Galutinis balas (med.)" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    for (const auto& stud : studentai)
    {
        cout << setw(15) << stud.pavarde << setw(15) << stud.vardas << setw(30) << fixed << setprecision(2) << stud.galutinisbalasvidurkis << setw(30) << fixed << setprecision(2) << stud.galutinisbalasmediana << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    srand(time(NULL));
    vector<Studentas> studentai;
    int pasirinkimas;
    cout << "Pasirinkite bûdà ávesti balus:\n1. Ávesti rankiniu bûdu\n2. Sugeneruoti atsitiktinius balus\n3. Sugeneruoti balus, vardus ir pavardes\n4. Skaitymas iğ failo.\n5. Baigti programà.\nPasirinkimas: ";
    while (true) {
        if (cin >> pasirinkimas && (pasirinkimas == 1 || pasirinkimas == 2 || pasirinkimas == 3 || pasirinkimas == 4)) {
            break;
        }
        else if (pasirinkimas == 5) {
            cout << "Programa iğjungiama...";
            return 0;
        }
        else {
            cout << "Netinkama ávestis. Pasirinkite bûdà ávesti balus:\n1. Ávesti rankiniu bûdu\n2. Sugeneruoti atsitiktinius balus\n3. Sugeneruoti balus, vardus ir pavardes\n4. Skaitymas iğ failo.\n5. Baigti programà.\nPasirinkimas: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (true)
    {
        Studentas stud;
        if (pasirinkimas == 1 || pasirinkimas == 2)
        {
            cout << "Áveskite studento vardà ir pavardæ. Norëdami baigti ávedimà, áveskite -1: ";
            cin >> stud.vardas;
            if (stud.vardas == "-1")
                break;
            cin >> stud.pavarde;
        }
        if (pasirinkimas == 1) {
            cout << "Áveskite namø darbø rezultatus. Norëdami baigti ávedimà, áveskite -1: ";
            double namudarburez;
            while (true)
            {
                if (!(cin >> namudarburez)) {
                    cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (namudarburez == -1)
                    break;
                if (namudarburez >= 0 && namudarburez <= 10)
                {
                    stud.namudarburez.push_back(namudarburez);
                }
                else
                {
                    cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                }
            }
        }
        else if (pasirinkimas == 2) {
            cout << "Generuojami atsitiktiniai balai uş namø darbus..." << endl;
            for (int i = 0; i < 5; ++i)
            {
                stud.namudarburez.push_back(GenerateRandomGrade());
            }
        }
        else if (pasirinkimas == 3) {
            cout << "Generuojami balai, vardai ir pavardës spausdinimui" << endl;
            int studentukiekis = rand() % 10;
            for (int i = 0; i < studentukiekis; i++) {
                for (int j = 0; j < 5; j++) {
                    stud.namudarburez.push_back(GenerateRandomGrade());
                }
                stud.egzaminorez = GenerateRandomGrade();
                stud.vardas = GeneruotiVardus();
                stud.pavarde = GeneruotiPavardes();
                stud.namudarburezsuma = accumulate(stud.namudarburez.begin(), stud.namudarburez.end(), 0.0);
                stud.vidurkis = stud.namudarburezsuma / stud.namudarburez.size();
                stud.galutinisbalasvidurkis = stud.vidurkis * 0.4 + stud.egzaminorez * 0.6;
                stud.mediana = Mediana(stud.namudarburez);
                stud.galutinisbalasmediana = stud.mediana * 0.4 + stud.egzaminorez * 0.6;
                studentai.push_back(stud);
                stud.namudarburez.clear();
            }
            break;
        }
        else if (pasirinkimas == 4)
        {
            cout << "Kuri faila norite atidaryti:\n1 - studentai10000.txt\n2 - studentai100000.txt\n3 - studentai1000000.txt\nPasirinkimas: ";
            int failopasirinkimas;
            cin >> failopasirinkimas;
            ifstream failas;
            switch (failopasirinkimas)
            {
            case 1:
                failas.open("studentai10000.txt");
                break;
            case 2:
                failas.open("studentai100000.txt");
                break;
            case 3:
                failas.open("studentai1000000.txt");
                break;
            default:
                cout << "Netinkama ávestis. Programa iğjungiama...";
                return -1;
            }
            if (!failas.is_open())
            {
                cout << "Failas nerastas. Programa iğjungiama...";
                return -1;
            }
            string line;
            getline(failas, line);
            istringstream iss(line);
            int stulpeliai = 0;
            string zodziai;
            while (iss >> zodziai)
            {
                stulpeliai++;
            }
            int namudarbai = stulpeliai - 3;
            while (failas.good())
            {
                Studentas stud;
                if (!(failas >> stud.vardas >> stud.pavarde))
                    break;
                double grade;
                for (int i = 0; i < namudarbai; i++)
                {
                    failas >> grade;
                    stud.namudarburez.push_back(grade);
                }
                failas >> stud.egzaminorez;
                stud.namudarburezsuma = accumulate(stud.namudarburez.begin(), stud.namudarburez.end(), 0.0);
                stud.vidurkis = stud.namudarburezsuma / stud.namudarburez.size();
                stud.galutinisbalasvidurkis = stud.vidurkis * 0.4 + stud.egzaminorez * 0.6;
                stud.mediana = Mediana(stud.namudarburez);
                stud.galutinisbalasmediana = stud.mediana * 0.4 + stud.egzaminorez * 0.6;
                studentai.push_back(stud);
                stud.namudarburez.clear();
            }
            failas.close();
        }
        if (!studentai.empty())
        {
            cout << "Norite árağyti duomenis atspausdinant á ekranà ar á failà?: 1 - ekranà; 2 - failà" << endl;
            int skaicbudas;
            cin >> skaicbudas;
            cout << "Pasirinkite rikiavimo bûdà:\n1 - pagal vardus\n2 - pagal pavardes\n3 - pagal galutiná balà (vid.)\n4 - pagal galutiná balà (med.)\nPasirinkimas: ";
            int sorting_choice;
            cin >> sorting_choice;
            switch (sorting_choice)
            {
            case 1:
                sort(studentai.begin(), studentai.end(), vardolyginimas);
                break;
            case 2:
                sort(studentai.begin(), studentai.end(), pavardeslyginimas);
                break;
            case 3:
                sort(studentai.begin(), studentai.end(), vidurkiolyginimas);
                break;
            case 4:
                sort(studentai.begin(), studentai.end(), medianoslyginimas);
                break;
            default:
                NetinkamaIvestis();
                break;
            }
            if (skaicbudas == 1)
            {
                PrintStudents(studentai);
            }
            if (skaicbudas == 2)
            {
                ofstream failasr("kursioku_duomenys.txt");
                failasr << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(30) << "Galutinis balas (vid.)" << setw(30) << "Galutinis balas (med.)" << endl;
                failasr << "---------------------------------------------------------------------------------------------------" << endl;
                for (const auto& stud : studentai)
                {
                    failasr << setw(15) << stud.pavarde << setw(15) << stud.vardas << setw(30) << fixed << setprecision(2) << stud.galutinisbalasvidurkis << setw(30) << fixed << setprecision(2) << stud.galutinisbalasmediana << endl;
                }
                cout << "Árağymas sëkmingas. Rezultatai iğsaugoti faile kursioku_duomenys.txt" << endl;
                failasr.close();
                break;
            }
            else
            {
                NetinkamaIvestis();
            }
        }
        else
        {
            NetinkamaIvestis();
        }
    }
    return 0;
}
