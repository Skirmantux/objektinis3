#include "Studentas.h"
#include "Skaiciavimaidarbai.h"
#include <fstream> 
#include <chrono>  
#include <algorithm> 

using namespace std;

// Constructor implementation
Studentas::Studentas() : egzaminorez_(0.0) {
    vardas_ = "";
    pavarde_ = "";
    namudarburezsuma_ = 0.0;
    vidurkis_ = 0.0;
    galutinisbalasvidurkis_ = 0.0;
    mediana_ = 0.0;
    galutinisbalasmediana_ = 0.0;
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
    return a.getVardas() < b.getVardas();
}

bool pavardeslyginimas(const Studentas& a, const Studentas& b) {
    return a.getPavarde() < b.getPavarde();
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
        cout << setw(15) << stud.getPavarde() << setw(15) << stud.getVardas()
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
        failas2 << left << setw(15) << stud.getPavarde() << setw(15) << stud.getVardas();
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
        nenormalus1 << std::left << std::setw(15) << stud.getPavarde() << std::setw(15) << stud.getVardas();
        nenormalus1 << std::setw(30) << stud.galutinisbalasvidurkis_ << std::endl;
    }
}

// Function to read and process data
void readAndProcessData(const std::string& filename, std::vector<Studentas>& studentai, int& namudarbai, int studentuskaicius) {
    std::ifstream failas1(filename);
    if (!failas1.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(failas1, line); // Skip the header line
    std::chrono::high_resolution_clock::time_point atidarymo_pradzia = std::chrono::high_resolution_clock::now();
    studentai.reserve(studentuskaicius);
    while (std::getline(failas1, line)) {
        if (line.empty()) {
            continue; // Skip empty lines
        }
        Studentas stud;
        std::istringstream iss(line);
        std::string vardas, pavarde;
        if (!(iss >> vardas >> pavarde)) {
            std::cerr << "Error reading name and surname." << std::endl;
            break;
        }
        stud.setVardas(vardas);
        stud.setPavarde(pavarde);
        double grade;
        for (int i = 0; i < namudarbai; ++i) {
            if (!(iss >> grade)) {
                std::cerr << "Error reading grade " << (i + 1) << "." << std::endl;
                return;
            }
            stud.addGrade(grade);
        }
        double egzaminorez;
        if (!(iss >> egzaminorez)) {
            std::cerr << "Error reading exam grade." << std::endl;
            return;
        }
        stud.setEgzaminoRez(egzaminorez);
        stud.calculateFinalGrades();
        studentai.emplace_back(std::move(stud));
    }
    std::chrono::high_resolution_clock::time_point atidarymo_pabaiga = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> read_time = atidarymo_pabaiga - atidarymo_pradzia;
    std::cout << "Duomenu nuskaitymas ið failo á konteinerá ir galutiniø balø skaièiavimas uþtruko: " << read_time.count() << " sekundes" << std::endl;
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
    studentai.erase(iter, studentai.end());
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
    studentai.clear();
    auto normnenorm_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> normnenorm_time = normnenorm_pabaiga - normnenorm_pradzia;
    cout << "Studentø rûðiavimas á normalius ir nenormalius uþtruko " << normnenorm_time.count() << " sekundes" << endl;
}
//bomberis
Studentas::~Studentas() {
    vardas_ = "";
    pavarde_ = "";
    namudarburez_.clear();
    egzaminorez_ = 0.0;
}

// Copy constructor implementation
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_),
    namudarburez_(other.namudarburez_), egzaminorez_(other.egzaminorez_),
    namudarburezsuma_(other.namudarburezsuma_), vidurkis_(other.vidurkis_),
    galutinisbalasvidurkis_(other.galutinisbalasvidurkis_),
    mediana_(other.mediana_), galutinisbalasmediana_(other.galutinisbalasmediana_) {}

// Copy assignment operator implementation
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        namudarburez_ = other.namudarburez_;
        egzaminorez_ = other.egzaminorez_;
        namudarburezsuma_ = other.namudarburezsuma_;
        vidurkis_ = other.vidurkis_;
        galutinisbalasvidurkis_ = other.galutinisbalasvidurkis_;
        mediana_ = other.mediana_;
        galutinisbalasmediana_ = other.galutinisbalasmediana_;
    }
    return *this;
}

// Move constructor implementation
Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(std::move(other.vardas_)), pavarde_(std::move(other.pavarde_)),
    namudarburez_(std::move(other.namudarburez_)), egzaminorez_(other.egzaminorez_),
    namudarburezsuma_(other.namudarburezsuma_), vidurkis_(other.vidurkis_),
    galutinisbalasvidurkis_(other.galutinisbalasvidurkis_),
    mediana_(other.mediana_), galutinisbalasmediana_(other.galutinisbalasmediana_) {
    // Resetting the moved object
    other.namudarburezsuma_ = 0.0;
    other.vidurkis_ = 0.0;
    other.galutinisbalasvidurkis_ = 0.0;
    other.mediana_ = 0.0;
    other.galutinisbalasmediana_ = 0.0;
}

// Move assignment operator implementation
Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        namudarburez_ = std::move(other.namudarburez_);
        egzaminorez_ = other.egzaminorez_;
        namudarburezsuma_ = other.namudarburezsuma_;
        vidurkis_ = other.vidurkis_;
        galutinisbalasvidurkis_ = other.galutinisbalasvidurkis_;
        mediana_ = other.mediana_;
        galutinisbalasmediana_ = other.galutinisbalasmediana_;

        // Resetting the moved object
        other.namudarburezsuma_ = 0.0;
        other.vidurkis_ = 0.0;
        other.galutinisbalasvidurkis_ = 0.0;
        other.mediana_ = 0.0;
        other.galutinisbalasmediana_ = 0.0;
    }
    return *this;
}
// Output Operator (Serialization)
std::ostream& operator<<(std::ostream& os, Studentas& studentas) {
    os << studentas.getVardas() << " " << studentas.getPavarde() << " " << studentas.getEgzaminoRez() << " ";
    for (double pazymys : studentas.getNamudarbuRez()) {
        os << pazymys << " ";
    }
    return os;
}

// Input Operator (Deserialization)
std::istream& operator>>(std::istream& is, Studentas& studentas) {
    std::string vardas, pavarde;
    double egzaminas;
    is >> vardas >> pavarde >> egzaminas;
    studentas.setVardas(vardas);
    studentas.setPavarde(pavarde);
    studentas.setEgzaminoRez(egzaminas);
    studentas.getNamudarbuRez().clear();
    double pazymys;
    while (is >> pazymys) {
        studentas.addGrade(pazymys);
    }
    return is;
}
void testConstructors() {
    std::vector<double> grades = { 5, 6, 7, 8, 9 };
    // Test parameterized constructor
    Studentas s1;
    s1.setVardas("Skirmantas");
    s1.setPavarde("Strasinskas");
    s1.setEgzaminoRez(8);
    for (double grade : grades) {
        s1.addGrade(grade);
    }
    s1.calculateFinalGrades();
    std::cout << "Parameterized Constructor (s1): " << s1.getVardas() << " " << s1.getPavarde() << std::endl;

    // Test copy constructor
    Studentas s2(s1);
    std::cout << "Copy Constructor (s1 copy - > s2): " << s2.getVardas() << " " << s2.getPavarde() << std::endl;

    // Test move constructor
    Studentas s3(std::move(s2));
    std::cout << "Move Constructor (s2 move -> s3): " << s3.getVardas() << " " << s3.getPavarde() << std::endl;
    cout << "s2 liekana: " << s2.getVardas() << " " << s2.getPavarde() << endl;

    // Test default constructor
    Studentas s4;
    std::cout << "Default Constructor: " << s4.getVardas() << " " << s4.getPavarde() << std::endl;
}
