#include <iostream>
#include <locale>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

struct studentas {
    string vardas;
    string pavarde;
    double* namudarburez;
    int namudarbai;
    double egzaminorez;
    double namudarburezsuma;
    double vidurkis;
    double galutinisbalasvidurkis;
    double mediana;
    double galutinisbalasmediana;
};

void NetinkamaIvestis() {
    cout << "Netinkama ávestis. Programa iğjungiama..." << endl;
}

void Rikiavimas(double mas[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (mas[j] > mas[j + 1]) {
                double temp = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = temp;
            }
        }
    }
}

double mediana(double mas[], int namudarbai) {
    double mediana = 0.0;
    if (namudarbai % 2 == 0) {
        mediana = (mas[namudarbai / 2] + mas[namudarbai / 2 - 1]) / 2.0;
    }
    else {
        mediana = mas[namudarbai / 2];
    }
    return mediana;
}

int main() {
    setlocale(LC_ALL, "Lithuanian");
    const int N = 50;
    int studentukiekis = 0;
    studentas stud[N];
    int namudarbai = 0;
    while (studentukiekis < N) {
        cout << "Iveskite studento vardus ir pavardes. Norëdami baigti ávedimà, áveskite skaitmená -1: " << endl;
        if (!(cin >> stud[studentukiekis].vardas) || stud[studentukiekis].vardas == "-1" || !(cin >> stud[studentukiekis].pavarde) || stud[studentukiekis].pavarde == "-1") {
            break;
        }
        stud[studentukiekis].namudarburezsuma = 0;
        namudarbai = 0;
        cout << "Áveskite namø darbø rezultatus (baigti ávedimà áveskite -1): \n";
        stud[studentukiekis].namudarburez = new double[N];
        while (true) {
            double pazymys;
            if (!(cin >> pazymys) || pazymys == -1 || (pazymys >= 0 || pazymys <= 10)) {
                if (pazymys == -1) break;
                stud[studentukiekis].namudarburez[namudarbai++] = pazymys;
                stud[studentukiekis].namudarburezsuma += pazymys;
            }
            else {
                cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        stud[studentukiekis].namudarbai = namudarbai;
        Rikiavimas(stud[studentukiekis].namudarburez, namudarbai);
        stud[studentukiekis].mediana = mediana(stud[studentukiekis].namudarburez, namudarbai);
        cout << "Iveskite egzamino rezultatà (turi bûti tarp 0 ir 10): " << endl;
        while (true) {
            if (!(cin >> stud[studentukiekis].egzaminorez) || (stud[studentukiekis].egzaminorez >= 0 || stud[studentukiekis].egzaminorez <= 10)) {
                break;
            }
            else {
                cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        stud[studentukiekis].vidurkis = stud[studentukiekis].namudarburezsuma / namudarbai;
        stud[studentukiekis].galutinisbalasvidurkis = stud[studentukiekis].vidurkis * 0.4 + stud[studentukiekis].egzaminorez * 0.6;
        stud[studentukiekis].galutinisbalasmediana = stud[studentukiekis].mediana * 0.4 + stud[studentukiekis].egzaminorez * 0.6;
        studentukiekis++;
    }
    if (studentukiekis >= 1) {
        cout << "Kurá galutinio balo skaièiavimo bûdà renkatës? (1 - vidurkis; 2 - mediana)" << endl;
        int skaicbudas;
        if (cin >> skaicbudas) {
            if (skaicbudas == 1) {
                cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(30) << "Galutinis balas (vid.)" << endl;
                cout << "---------------------------------------------------------------------------------------------------" << endl;

                for (int i = 0; i < studentukiekis; i++) {
                    cout << setw(15) << stud[i].pavarde << setw(15) << stud[i].vardas << setw(30) << fixed << setprecision(2) << stud[i].galutinisbalasvidurkis << endl;
                }
            }
            else if (skaicbudas == 2) {
                cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(30) << "Galutinis balas (med.)" << endl;
                cout << "---------------------------------------------------------------------------------------------------" << endl;

                for (int i = 0; i < studentukiekis; i++) {
                    cout << setw(15) << stud[i].pavarde << setw(15) << stud[i].vardas << setw(30) << fixed << setprecision(2) << stud[i].galutinisbalasmediana << endl;
                }
            }
            else {
                NetinkamaIvestis();
            }
        }
        else {
            NetinkamaIvestis();
        }
    }
    else {
        NetinkamaIvestis();
    }

    for (int i = 0; i < studentukiekis; i++) {
        delete[] stud[i].namudarburez;
    }

    return 0;
}
