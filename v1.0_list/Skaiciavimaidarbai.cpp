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

double Mediana(list<double>& lst) {
    if (lst.empty()) return 0;
    lst.sort();
    auto it = lst.begin();
    advance(it, lst.size() / 2);
    if (lst.size() % 2 == 0) {
        auto it_prev = prev(it);
        return (*it + *it_prev) / 2.0;
    }
    else {
        return *it;
    }
}

double GenerateRandomGrade()
{
    return rand() % 11;
}

void PrintStudents(const list<Studentas>& studentai)
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
void GeneruotiFaila(const string& pavadinimas, int studentuskaicius) {
    ofstream failas(pavadinimas);
    if (failas.is_open()) {
        failas << left << setw(20) << "Vardas" << setw(24) << "Pavarde" << setw(6) << "ND1" << setw(6) << "ND2" << setw(6) << "ND3" << setw(6) << "ND4" << setw(6) << "ND5" << setw(6) << "Egz." << endl;
        for (int i = 1; i <= studentuskaicius; i++) {
            failas << left << setw(20) << ("Vardas" + to_string(i)) << setw(20) << ("Pavarde" + to_string(i)) << right;
            for (int j = 0; j < 5; j++) {
                int pazymys = GenerateRandomGrade();
                failas << setw(6) << pazymys;
            }
            failas << setw(6) << GenerateRandomGrade() << endl;
        }
        failas.close();
        cout << "Failas sugeneruotas." << endl;
    }
    else {
        cout << "Neámanoma atidaryti failo." << endl;
    }

}
bool compareByGalutinisVid(const Studentas& a, const Studentas& b) {
    return a.galutinisbalasvidurkis < b.galutinisbalasvidurkis;
}
bool compareByGalutinisMed(const Studentas& a, const Studentas& b) {
	return a.galutinisbalasmediana < b.galutinisbalasmediana;
}
void readAndProcessData(const string& filename, list<Studentas>& studentai, int namudarbai) {
    ifstream failas1(filename);
    string line;
    getline(failas1, line);
    auto atidarymo_pradzia = chrono::high_resolution_clock::now();
    while (failas1.good()) {
        Studentas stud;
        if (!(failas1 >> stud.vardas >> stud.pavarde)) break;
        double grade;
        for (int i = 0; i < namudarbai; i++) {
            failas1 >> grade;
            stud.namudarburez.push_back(grade);
        }
        failas1 >> stud.egzaminorez;
        stud.namudarburezsuma = accumulate(stud.namudarburez.begin(), stud.namudarburez.end(), 0.0);
        stud.vidurkis = stud.namudarburezsuma / stud.namudarburez.size();
        stud.galutinisbalasvidurkis = stud.vidurkis * 0.4 + stud.egzaminorez * 0.6;
        stud.mediana = Mediana(stud.namudarburez);
        stud.galutinisbalasmediana = stud.mediana * 0.4 + stud.egzaminorez * 0.6;
        studentai.push_back(stud);
    }
    auto atidarymo_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> read_time = atidarymo_pabaiga - atidarymo_pradzia;
    cout << "Duomenu nuskaitymas ið failo á konteinerá uþtruko: " << read_time.count() << " sekundþiø" << endl;
}
void sortStudents(list<Studentas>& studentai, int sortpasirinkimas) {
    auto sort_pradzia = chrono::high_resolution_clock::now();
    switch (sortpasirinkimas) {
    case 1: studentai.sort(compareByGalutinisVid); break;
    case 2: studentai.sort(compareByGalutinisMed); break;
    default: cout << "Netinkamas pasirinkimas. Pasirinkite ið naujo." << endl; return;
    }
    auto sort_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> sort_time = sort_pabaiga - sort_pradzia;
    cout << "Mokiniu rusiavimas naudojant sort funkcija uztruko " << sort_time.count() << " sekundþiø" << endl;
}

void partitionStudents1(const list<Studentas>& studentai, list<Studentas>& normalus, list<Studentas>& nenormalus) {
    cout << "Studentai dalinami á normalius ir nenormalius." << endl;
    auto normnenorm_pradzia = chrono::high_resolution_clock::now();
    for (const auto& stud : studentai) {
        if (stud.galutinisbalasvidurkis >= 5.0) normalus.push_back(stud);
        else nenormalus.push_back(stud);
    }
    auto normnenorm_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> normnenorm_time = normnenorm_pabaiga - normnenorm_pradzia;
    cout << "Studentu rusiavimas i normalius ir nenormalius uztruko " << normnenorm_time.count() << " sekundþiø" << endl;
}
void partitionStudents2(list<Studentas>& studentai, list<Studentas>& nenormalus) {
    cout << "Studentai dalinami á normalius ir nenormalius." << endl;
    auto normnenorm_pradzia = chrono::high_resolution_clock::now();
    auto it = studentai.begin();
    while (it != studentai.end()) {
        if (it->galutinisbalasvidurkis < 5.0) {
            nenormalus.push_back(*it);
            it = studentai.erase(it);
        }
        else {
            ++it;
        }
    }
    auto normnenorm_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> normnenorm_time = normnenorm_pabaiga - normnenorm_pradzia;
    cout << "Studentu rusiavimas i normalius ir nenormalius uztruko " << normnenorm_time.count() << " sekundþiø" << endl;
}
void partitionStudents3(list<Studentas>& studentai, list<Studentas>& normalus, list<Studentas>& nenormalus) {
    cout << "Studentai dalinami á normalius ir nenormalius." << endl;
    auto normnenorm_pradzia = chrono::high_resolution_clock::now();
    auto partition_point = partition(studentai.begin(), studentai.end(),
        [](const Studentas& stud) {
            return stud.galutinisbalasvidurkis >= 5.0;
        });
    normalus.insert(normalus.end(), studentai.begin(), partition_point);
    nenormalus.insert(nenormalus.end(), partition_point, studentai.end());
    studentai.erase(partition_point, studentai.end());
    auto normnenorm_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> normnenorm_time = normnenorm_pabaiga - normnenorm_pradzia;
    cout << "Studentu rusiavimas i normalius ir nenormalius uztruko " << normnenorm_time.count() << " sekundþiø" << endl;
}