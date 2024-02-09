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
};

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int studentukiekis; 
    cout << "Kiek bus studentu?";
    cin >> studentukiekis;
    cout << "kiek bus namu darbu?: ";
    int namudarbai;
    cin >> namudarbai;
    studentas stud[N];
    int galutinisvertinimas[N];
    for (int i = 0; i < studentukiekis; i++)
    {
        cout << "Iveskite studento vardà ir pavaradæ: " << endl;
        cin >> stud[i].vardas;
        cin >> stud[i].pavarde;
        cout << "Iveskite namø darbø rezultatus: ";
        for (int i = 0; i < namudarbai; i++) {
            cin >> stud[i].namudarburez;
        }
        cout << "Iveskite egzamino rezultatus";
        cin >> stud[i].egzaminorez;

    }
    cout << "Pavardë          Vardas           Galutinis (vid.)" << endl;
    cout << "-----------------------------------------------------------" << endl;
}

