#include "Skaiciavimaidarbai.h"
#include "MokiniuProcessing.h"
void NetinkamaIvestis()
{
    cout << "Netinkama ávestis. Programa iðjungiama...";
}
void NeraFailo()
{
    cout << "Failas nerastas. Programa iðjungiama...";
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

void PrintStudents(const vector<Studentas>& studentai)
{
    auto start_print = chrono::high_resolution_clock::now();
    cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(30) << "Galutinis balas (vid.)" << setw(30) << "Galutinis balas (med.)" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    for (const auto& stud : studentai)
    {
        cout << setw(15) << stud.pavarde << setw(15) << stud.vardas << setw(30) << fixed << setprecision(2) << stud.galutinisbalasvidurkis << setw(30) << fixed << setprecision(2) << stud.galutinisbalasmediana << endl;
    }
    auto end_print = chrono::high_resolution_clock::now();
    chrono::duration<double> write_time = end_print - start_print;
    cout << "Rasymo i ekrana trukme: " << write_time.count() << " sekundes" << endl;
}
void GeneruotiFaila(const string& pavadinimas, int studentuskaicius)
{
	ofstream failas(pavadinimas);
    if (failas.is_open())
    {
        failas << "Vardas" << " " << setw(10) << "Pavarde" << " " << setw(10) << "ND1" << " " << setw(5) << "ND2" << " " << setw(5) << "ND3" << " " << setw(5) << "ND4" << " " << setw(5) << "ND5" << " " << setw(10) << "Egzaminas" << endl;
        for (int i = 1; i <= studentuskaicius; i++)
        {
			failas << "Vardas" << i << " " << setw(10) << "Pavarde" << i << " ";
            for (int j = 0; j < 5; j++)
            {
                int pazymys = GenerateRandomGrade();
                if (j == 0)
                    failas << setw(10) << pazymys << " ";
                else
                    failas << setw(5) << pazymys << " ";
			}
			failas << setw(10) << GenerateRandomGrade() << endl;
		}
		failas.close();
	}
    else
    {
		NeraFailo();
	}
}