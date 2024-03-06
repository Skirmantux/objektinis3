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
    vector<double> namudarburez; // vektorius dinaminiam namu darbu rezultatu saugojimui
    double egzaminorez = 0.0;
    double namudarburezsuma = 0.0;
    double vidurkis = 0.0;
    double galutinisbalasvidurkis = 0.0;
    double mediana = 0.0;
    double galutinisbalasmediana = 0.0;
};

void NetinkamaIvestis()
{
    cout << "Netinkama ávestis. Programa iðjungiama...";
}

void Rikiavimas(vector<double>& mas)
{
    sort(mas.begin(), mas.end()); // std::sort sortinimui
}

double Mediana(const vector<double>& namudarburez) // perduodame vektoriu kaip konstanta, kad nebutu galima jo pakeisti
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
    vector<string> pavardes = { "Kazlauskas", "Petrauskas", "Stankevièius", "Gudelis", "Lukðys" };
    return pavardes[rand() % pavardes.size()];
}

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    srand(time(NULL));
    vector<Studentas> studentai; // studentø vektorius
    int pasirinkimas;
    cout << "Pasirinkite bûdà ávesti balus:\n1. Ávesti rankiniu bûdu\n2. Sugeneruoti atsitiktinius balus\n3. Sugeneruoti balus, vardus ir pavardes\n4. Skaitymas ið failo.\nPasirinkimas:";
    while (true) {
        if (cin >> pasirinkimas && (pasirinkimas == 1 || pasirinkimas == 2 || pasirinkimas == 3 || pasirinkimas == 4)) {
            break;
        }
        else {
            cout << "Netinkama ávestis. Pasirinkite bûdà ávesti balus:\n1. Ávesti rankiniu bûdu\n2. Sugeneruoti atsitiktinius balus\n3. Sugeneruoti balus, vardus ir pavardes\n4. Skaitymas ið failo.\nPasirinkimas: ";
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
                    stud.namudarburez.push_back(namudarburez); // kisame rezultata i vektoriu
                }
                else
                {
                    cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                }
            }
        }
        else if (pasirinkimas == 2) {
            cout << "Generuojami atsitiktiniai balai uþ namø darbus..." << endl;
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
                stud.mediana = Mediana(stud.namudarburez); // mediana skaiciuojama is rikiuoto vektoriaus
                stud.galutinisbalasmediana = stud.mediana * 0.4 + stud.egzaminorez * 0.6;
                studentai.push_back(stud); // Add the student to the vector
                stud.namudarburez.clear(); // Clear the grades for the next student
            }
            break;
        }
        else if (pasirinkimas == 4)
        {
            ifstream failas("studentai10000.txt");
            if (!failas.is_open())
            {
                cout << "Failas nerastas. Programa iðjungiama...";
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
            while (true)
            {
                Studentas stud;
                if (!(failas >> stud.vardas >> stud.pavarde)) // Read student's name and surname
                    break; // If unable to read, break out of the loop
                double grade;
                    for(int i = 0; i < namudarbai; i++)
                    {
                        failas >> grade; // Read grade
                        stud.namudarburez.push_back(grade);
                }
                failas >> stud.egzaminorez; // Read exam grade
                stud.namudarburezsuma = accumulate(stud.namudarburez.begin(), stud.namudarburez.end(), 0.0);
                stud.vidurkis = stud.namudarburezsuma / stud.namudarburez.size();
                stud.galutinisbalasvidurkis = stud.vidurkis * 0.4 + stud.egzaminorez * 0.6;
                stud.mediana = Mediana(stud.namudarburez); // Calculate median
                stud.galutinisbalasmediana = stud.mediana * 0.4 + stud.egzaminorez * 0.6;
                studentai.push_back(stud); // Add the student to the vector
            }
        }

        if (!studentai.empty())
        {
            cout << "Kurá galutinio balo skaièiavimo bûdà renkatës? (1 - vidurkis; 2 - mediana)" << endl;
            int skaicbudas;
            cin >> skaicbudas;
            if (skaicbudas == 1)
            {
                cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(30) << "Galutinis balas (vid.)" << endl;
                cout << "---------------------------------------------------------------------------------------------------" << endl;
                for (const auto& stud : studentai)
                {
                    cout << setw(15) << stud.pavarde << setw(15) << stud.vardas << setw(30) << fixed << setprecision(2) << stud.galutinisbalasvidurkis << endl;
                }
            }
            else if (skaicbudas == 2)
            {
                cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(30) << "Galutinis balas (med.)" << endl;
                cout << "---------------------------------------------------------------------------------------------------" << endl;
                for (const auto& stud : studentai)
                {
                    cout << setw(15) << stud.pavarde << setw(15) << stud.vardas << setw(30) << fixed << setprecision(2) << stud.galutinisbalasmediana << endl;
                }
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
        return 0;
    }
}