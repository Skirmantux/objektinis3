#include <iostream>
#include <locale>

const int N = 50;
using namespace std;

struct studentas
{
    string vardas;
    string pavarde;
    int namudarburez[N];
    int egzaminorez;
    int namudarburezsuma;
    double vidurkis;
};

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int studentukiekis; 
    cout << "Kiek bus studentø?: " << endl;
    cin >> studentukiekis;
    cout << "kiek bus namu darbø?: " << endl;
    int namudarbai;
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
            cin >> stud[j].namudarburez[j];
            stud[i].namudarburezsuma += stud[i].namudarburez[j];
        }
        }
        cout << "Iveskite egzamino rezultatà: " << endl;
        cin >> stud[i].egzaminorez;
        stud[i].vidurkis = stud[i].namudarburezsuma / namudarbai;


    }
    cout << "Pavardë          Vardas           Galutinis (vid.)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (int i = 0; i < studentukiekis; i++)
    {
        cout << stud[i].pavarde << "         " << stud[i].vardas << "         " << stud[i].vidurkis << endl;
    }
}

