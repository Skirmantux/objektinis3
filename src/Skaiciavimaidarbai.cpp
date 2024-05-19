#include "Skaiciavimaidarbai.h"
#include "MokiniuProcessing.h"
#include "Studentas.h"
void NetinkamaIvestis()
{
    cout << "Netinkama įvestis. Programa išjungiama...";
}

void NeraFailo()
{
    cout << "Failas nerastas. Programa išjungiama...";
}

double Mediana(vector<double>& vec) {
    size_t size = vec.size();
    if (size == 0) {
        return 0;
    }
    sort(vec.begin(), vec.end());
    if (size % 2 == 0) {
        return (vec[size / 2 - 1] + vec[size / 2]) / 2;
    }
    else {
        return vec[size / 2];
    }
}

double GenerateRandomGrade()
{
    return rand() % 11;
} 

void GeneruotiFaila(const string& pavadinimas, int studentuskaicius) {
    ofstream file(pavadinimas);
    if (!file.is_open()) {
        cerr << "Negalima atidaryti failo pavadinimu: " << pavadinimas << endl;
        return;
    }
    srand(time(nullptr));
    for (int i = 0; i < studentuskaicius; ++i) {
        file << "Vardas" << i + 1 << " Pavarde" << i + 1;
        for (int j = 0; j < 5; ++j) {
            file << " " << rand() % 10; 
        }
        file << " " << rand() % 10; 
        file << endl;
    }
    file.close();
}

bool compareByGalutinisVid(const Studentas& a, const Studentas& b) {
    return a.galutinisbalasvidurkis_ < b.galutinisbalasvidurkis_;
}

bool compareByGalutinisMed(const Studentas& a, const Studentas& b) {
    return a.galutinisbalasmediana_ < b.galutinisbalasmediana_;
}
