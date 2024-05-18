#include "Studentas.h"
#include "Skaiciavimaidarbai.h"
#include <fstream> 
#include <chrono>  
#include <algorithm> 

using namespace std; // For brevity

// Constructor implementation
Studentas::Studentas() {
    vardas_ = "";
	pavarde_ = "";
	namudarburezsuma_ = 0.0;
	vidurkis_ = 0.0;
	galutinisbalasvidurkis_ = 0.0;
	mediana_ = 0.0;
	galutinisbalasmediana_ = 0.0;
    egzaminorez_ = 0.0;
}

Studentas::Studentas(std::istream& is)
{
	readStudent(is);
}

// Function to calculate final grades
void Studentas::calculateFinalGrades() {
    namudarburezsuma_ = accumulate(namudarburez_.begin(), namudarburez_.end(), 0.0);
    vidurkis_ = namudarburezsuma_ / namudarburez_.size();
    galutinisbalasvidurkis_ = vidurkis_ * 0.4 + egzaminorez_ * 0.6;
    mediana_ = Mediana(namudarburez_);
    galutinisbalasmediana_ = mediana_ * 0.4 + egzaminorez_ * 0.6;
}

std::string Studentas::getVardas() const
{
    return std::string();
}

std::string Studentas::getPavarde() const
{
    return std::string();
}

double Studentas::getGalBalasVidurkis() const
{
    return 0.0;
}

double Studentas::getGalBalasMediana() const
{
    return 0.0;
}

// Member function to read student data from input stream
istream& Studentas::readStudent(istream& is) {
    is >> vardas_ >> pavarde_;
    double grade;
    while (is >> grade) {
        namudarburez_.push_back(grade);
    }
    is.clear();
    is >> egzaminorez_;
    return is;
}

// Comparison functions
bool vardolyginimas(const Studentas& a, const Studentas& b) {
    return a.vardas_ < b.vardas_;
}

bool pavardeslyginimas(const Studentas& a, const Studentas& b) {
    return a.pavarde_ < b.pavarde_;
}

bool vidurkiolyginimas(const Studentas& a, const Studentas& b) {
    return a.galutinisbalasvidurkis_ < b.galutinisbalasvidurkis_;
}

bool medianoslyginimas(const Studentas& a, const Studentas& b) {
    return a.galutinisbalasmediana_ < b.galutinisbalasmediana_;
}

// Print students function
void PrintStudents(const vector<Studentas>& studentai) {
    auto start_print = chrono::high_resolution_clock::now();
    cout << setw(15) << "Pavarde" << setw(15) << "Vardas"
        << setw(30) << "Galutinis balas (vid.)"
        << setw(30) << "Galutinis balas (med.)" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    for (const auto& stud : studentai) {
        cout << setw(15) << stud.pavarde_ << setw(15) << stud.vardas_
            << setw(30) << fixed << setprecision(2) << stud.galutinisbalasvidurkis_
            << setw(30) << fixed << setprecision(2) << stud.galutinisbalasmediana_ << endl;
    }
    auto end_print = chrono::high_resolution_clock::now();
    chrono::duration<double> write_time = end_print - start_print;
    cout << "Rasymo i ekrana trukme: " << write_time.count() << " sekundes" << endl;
}
void WriteNormalStudents(std::vector<Studentas>& normalus)
{
    cout << "Normalus studentai spausdinami á failà 'normalûs.txt'." << endl;
    ofstream failas2("normalûs.txt");
    failas2 << fixed << setprecision(2);
    failas2 << left << setw(15) << "Pavarde" << setw(15) << "Vardas";
    failas2 << setw(30) << "Galutinis balas (vid.)" << endl;
    for (const auto& stud : normalus) {
        failas2 << left << setw(15) << stud.pavarde_ << setw(15) << stud.vardas_;
        failas2 << setw(30) << stud.galutinisbalasvidurkis_ << endl;
    }
}
void WriteWeirdStudents(std::vector<Studentas>& nenormalus)
{
    cout << "Nenormalus studentai spausdinami á failà 'nenormalûs.txt'." << endl;
    std::ofstream nenormalus1("nenormalûs.txt");
    nenormalus1 << std::fixed << std::setprecision(2);
    nenormalus1 << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas";
    nenormalus1 << std::setw(30) << "Galutinis balas (vid.)" << std::endl;
    for (const auto& stud : nenormalus) {
        nenormalus1 << std::left << std::setw(15) << stud.pavarde_ << std::setw(15) << stud.vardas_;
        nenormalus1 << std::setw(30) << stud.galutinisbalasvidurkis_ << std::endl;
    }
}
// Function to read and process data
void readAndProcessData(const std::string& filename, std::vector<Studentas>& studentai, int& namudarbai, int studentuskaicius) {
    std::ifstream failas1;
    failas1.open(filename);
    if (!failas1.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    std::chrono::high_resolution_clock::time_point atidarymo_pradzia = std::chrono::high_resolution_clock::now();
    studentai.reserve(studentuskaicius); 
    while (failas1 >> std::ws && getline(failas1, line)) {
        Studentas stud;
        std::istringstream iss(line);
        if (!(iss >> stud.vardas_ >> stud.pavarde_)) {
            break;
        }
        double grade;
        for (int i = 0; i < namudarbai; i++) {
            if (!(iss >> grade)) {
                std::cerr << "Error reading grades." << std::endl;
                return;
            }
            stud.namudarburez_.push_back(grade);
        }
        if (!(iss >> stud.egzaminorez_)) {
            std::cerr << "Error reading exam grade." << std::endl;
            return;
        }
        stud.calculateFinalGrades();
        studentai.emplace_back(std::move(stud));
    }
    std::chrono::high_resolution_clock::time_point atidarymo_pabaiga = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> read_time = atidarymo_pabaiga - atidarymo_pradzia;
    std::cout << "Duomenu nuskaitymas ið failo á konteinerá ir galutiniø balø skaièiavimas uþtruko: " << read_time.count() << " sekundes" << std::endl;
    failas1.close();
}

// Function to sort students
void sortStudents(vector<Studentas>& studentai, int sortpasirinkimas) {
    auto sort_pradzia = chrono::high_resolution_clock::now();
    switch (sortpasirinkimas) {
    case 1: sort(studentai.begin(), studentai.end(), vidurkiolyginimas); break;
    case 2: sort(studentai.begin(), studentai.end(), medianoslyginimas); break;
    default: cout << "Netinkamas pasirinkimas. Pasirinkite ið naujo." << endl; return;
    }
    auto sort_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> sort_time = sort_pabaiga - sort_pradzia;
    cout << "Mokiniu rusiavimas naudojant sort funkcija uztruko " << sort_time.count() << " sekundes" << endl;
}

// Function to partition students (method 1)
void partitionStudents1(const vector<Studentas>& studentai, vector<Studentas>& normalus, vector<Studentas>& nenormalus) {
    cout << "Studentai dalinami á normalius ir nenormalius." << endl;
    auto normnenorm_pradzia = chrono::high_resolution_clock::now();
    for (const auto& stud : studentai) {
        if (stud.galutinisbalasvidurkis_ >= 5.0) normalus.push_back(stud);
        else nenormalus.push_back(stud);
    }
    auto normnenorm_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> normnenorm_time = normnenorm_pabaiga - normnenorm_pradzia;
    cout << "Studentø rûðiavimas á normalius ir nenormalius uþtruko " << normnenorm_time.count() << " sekundes" << endl;
}

// Function to partition students (method 2)
void partitionStudents2(vector<Studentas>& studentai, vector<Studentas>& nenormalus) {
    cout << "Studentai dalinami á normalius ir nenormalius." << endl;
    auto normnenorm_pradzia = chrono::high_resolution_clock::now();
    auto iter = remove_if(studentai.begin(), studentai.end(),
        [&nenormalus](const Studentas& s) {
            if (s.galutinisbalasvidurkis_ < 5.0) {
                nenormalus.push_back(s);
                return true; 
            }
            return false; 
        });
    studentai.clear();
    auto normnenorm_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> normnenorm_time = normnenorm_pabaiga - normnenorm_pradzia;
    cout << "Studentø rûðiavimas á normalius ir nenormalius uþtruko " << normnenorm_time.count() << " sekundes" << endl;
}

// Function to partition students (method 3)
void partitionStudents3(vector<Studentas>& studentai, vector<Studentas>& normalus, vector<Studentas>& nenormalus) {
    cout << "Studentai dalinami á normalius ir nenormalius." << endl;
    auto normnenorm_pradzia = chrono::high_resolution_clock::now();
    auto partition_point = partition(studentai.begin(), studentai.end(),
        [](const Studentas& stud) {
            return stud.galutinisbalasvidurkis_ >= 5.0;
        });
    move(studentai.begin(), partition_point, back_inserter(normalus));
    move(partition_point, studentai.end(), back_inserter(nenormalus));
    auto normnenorm_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> normnenorm_time = normnenorm_pabaiga - normnenorm_pradzia;
    cout << "Studentø rûðiavimas á normalius ir nenormalius uþtruko " << normnenorm_time.count() << " sekundes" << endl;
}
