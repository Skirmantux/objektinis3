#include <iostream>
#include <locale>
#include <iomanip>

const int N = 50;
using namespace std;

struct studentas
{
    string vardas;
    string pavarde;
    int namudarburez[N];
    int egzaminorez;
    double namudarburezsuma;
    double vidurkis;
    double galutinisbalas;
};

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int studentukiekis; 
    cout << "Kiek bus studentø?: " << endl;
    cin >> studentukiekis;
    cout << "kiek bus namu darbø?: " << endl;
    double namudarbai;
    cin >> namudarbai;
    studentas stud[N];
    int galutinisvertinimas[N];
    for (int i = 0; i < studentukiekis; i++)
    {
        cout << "Iveskite studento vardà ir pavaradæ: " << endl;
        cin >> stud[i].vardas;
        cin >> stud[i].pavarde;
        if (namudarbai > 0)
        {
        for (int j = 0; j < namudarbai; j++) {
            cout << "Iveskite " << j+1 << "-ojo namø darbo rezultatà : " << endl;
            cin >> stud[i].namudarburez[j];
            stud[i].namudarburezsuma = 0;
            stud[i].namudarburezsuma += stud[i].namudarburez[j];
        }
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
        cout << stud[i].pavarde << "         " << stud[i].vardas << "                " << stud[i].galutinisbalas << endl;
    }
}

