#include <iostream>
#include <locale>
#include <iomanip>

const int N = 50;
using namespace std;

struct studentas
{
    string vardas;
    string pavarde;
    double namudarburez[N];
    double egzaminorez;
    double namudarburezsuma;
    double vidurkis;
    double galutinisbalas;
};
void NetinkamaIvestis()
{
    cout << "Netinkama ávestis. Programa iðjungiama...";
}

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int studentukiekis;
    cout << "Kiek bus studentø?: " << endl;
    cin >> studentukiekis;
    if (studentukiekis > 0)
    {
        cout << "kiek bus namu darbø?: " << endl;
        double namudarbai;
        cin >> namudarbai;
        studentas stud[N];
        if (namudarbai > 0)
        {
            for (int i = 0; i < studentukiekis; i++)
            {
                cout << "Iveskite studento vardà ir pavaradæ: " << endl;
                cin >> stud[i].vardas;
                cin >> stud[i].pavarde;
                stud[i].namudarburezsuma = 0;
                for (int j = 0; j < namudarbai; j++)
                {
                    while (true)
                    {
                        cout << "Iveskite " << j + 1 << "-ojo namø darbo rezultatà (turi bûti tarp 0 ir 10): " << endl;
                        if (cin >> stud[i].namudarburez[j] && stud[i].namudarburez[j] >= 0 && stud[i].namudarburez[j] <= 10)
                        {
                            break;
                        }
                        else
                        {
                            cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                        }
                    }
                    stud[i].namudarburezsuma += stud[i].namudarburez[j];
                }
                cout << "Iveskite egzamino rezultatà: " << endl;
                cin >> stud[i].egzaminorez;
                stud[i].vidurkis = stud[i].namudarburezsuma / namudarbai;
                stud[i].galutinisbalas = stud[i].vidurkis * 0.4 + stud[i].egzaminorez * 0.6;
            }

            cout << "Pavarde" << setw(15) << "Vardas" << setw(30) << "Galutinis balas (vid.)" << setw(30) << endl;
            cout << "-----------------------------------------------------------" << endl;
            for (int i = 0; i < studentukiekis; i++)
            {
                cout << stud[i].pavarde << "         " << stud[i].vardas << "                " << stud[i].galutinisbalas << fixed << setprecision(3) << endl;
            }
        }
        else NetinkamaIvestis();
    }
    else NetinkamaIvestis();
}


