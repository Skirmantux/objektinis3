#include "Studentas.h"
#include "Skaiciavimaidarbai.h"
#include <fstream> 
#include <chrono>  
#include <algorithm> 

using namespace std;

// Constructor implementation

/**
 * @brief Default constructor for Studentas class.
 *
 * Initializes a new Studentas object with default values.
 */
Studentas::Studentas() : egzaminorez_(0.0) {
    vardas_ = "";
    pavarde_ = "";
    namudarburezsuma_ = 0.0;
    vidurkis_ = 0.0;
    galutinisbalasvidurkis_ = 0.0;
    mediana_ = 0.0;
    galutinisbalasmediana_ = 0.0;
}
/**
 * @brief Constructor that reads student data from an input stream.
 *
 * @param is The input stream to read from.
 */
Studentas::Studentas(std::istream& is)
{
    readStudent(is);
}

// Function to calculate final grades

/**
 * @brief Calculates the final grades for the student.
 *
 * This function calculates both the final average grade and the final median grade
 * based on the student's homework and exam results.
 */
void Studentas::calculateFinalGrades() {
    namudarburezsuma_ = accumulate(namudarburez_.begin(), namudarburez_.end(), 0.0);
    vidurkis_ = namudarburezsuma_ / namudarburez_.size();
    galutinisbalasvidurkis_ = vidurkis_ * 0.4 + egzaminorez_ * 0.6;
    mediana_ = Mediana(namudarburez_);
    galutinisbalasmediana_ = mediana_ * 0.4 + egzaminorez_ * 0.6;
}

// Member function to read student data from input stream

/**
 * @brief Reads student data from an input stream.
 *
 * @param is The input stream to read from.
 * @return istream& The input stream after reading the student data.
 */
std::istream& Studentas::readStudent(std::istream& is) {
    is >> vardas_ >> pavarde_;
    double grade;
    while (is >> grade) {
        namudarburez_.push_back(grade);
    }
    egzaminorez_ = namudarburez_.back();
    namudarburez_.pop_back();
    return is;
}

// Comparison functions

/**
 * @brief Compares two students by their first name.
 *
 * @param a The first student.
 * @param b The second student.
 * @return bool True if the first student's name is less than the second student's name.
 */
bool vardolyginimas(const Studentas& a, const Studentas& b) {
    return a.getVardas() < b.getVardas();
}
/**
 * @brief Compares two students by their last name.
 *
 * @param a The first student.
 * @param b The second student.
 * @return bool True if the first student's last name is less than the second student's last name.
 */
bool pavardeslyginimas(const Studentas& a, const Studentas& b) {
    return a.getPavarde() < b.getPavarde();
}
/**
 * @brief Compares two students by their final average grade.
 *
 * @param a The first student.
 * @param b The second student.
 * @return bool True if the first student's final average grade is less than the second student's final average grade.
 */
bool vidurkiolyginimas(const Studentas& a, const Studentas& b) {
    return a.galutinisbalasvidurkis_ < b.galutinisbalasvidurkis_;
}
/**
 * @brief Compares two students by their final median grade.
 *
 * @param a The first student.
 * @param b The second student.
 * @return bool True if the first student's final median grade is less than the second student's final median grade.
 */
bool medianoslyginimas(const Studentas& a, const Studentas& b) {
    return a.galutinisbalasmediana_ < b.galutinisbalasmediana_;
}

// Print students function

/**
 * @brief Prints a list of students to the console.
 *
 * @param studentai The vector of students to print.
 */
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
/**
 * @brief Writes normal students to a file.
 *
 * @param normalus The vector of normal students.
 */
void WriteNormalStudents(std::vector<Studentas>& normalus)
{
    cout << "Normalus studentai spausdinami   fail  'normal s.txt'." << endl;
    ofstream failas2("normal s.txt");
    failas2 << fixed << setprecision(2);
    failas2 << left << setw(15) << "Pavarde" << setw(15) << "Vardas";
    failas2 << setw(30) << "Galutinis balas (vid.)" << endl;
    for (const auto& stud : normalus) {
        failas2 << left << setw(15) << stud.getPavarde() << setw(15) << stud.getVardas();
        failas2 << setw(30) << stud.galutinisbalasvidurkis_ << endl;
    }
}
/**
 * @brief Writes weird students to a file.
 *
 * @param nenormalus The vector of weird students.
 */
void WriteWeirdStudents(std::vector<Studentas>& nenormalus)
{
    cout << "Nenormalus studentai spausdinami   fail  'nenormal s.txt'." << endl;
    std::ofstream nenormalus1("nenormal s.txt");
    nenormalus1 << std::fixed << std::setprecision(2);
    nenormalus1 << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas";
    nenormalus1 << std::setw(30) << "Galutinis balas (vid.)" << std::endl;
    for (const auto& stud : nenormalus) {
        nenormalus1 << std::left << std::setw(15) << stud.getPavarde() << std::setw(15) << stud.getVardas();
        nenormalus1 << std::setw(30) << stud.galutinisbalasvidurkis_ << std::endl;
    }
}

// Function to read and process data

/**
 * @brief Reads and processes student data from a file.
 *
 * @param filename The name of the file to read from.
 * @param studentai The vector to store the read students.
 * @param namudarbai The number of homework grades.
 * @param studentuskaicius The number of students.
 */
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
    std::cout << "Duomenu nuskaitymas i  failo   konteiner  ir galutini  bal  skai iavimas u truko: " << read_time.count() << " sekundes" << std::endl;
}


// Function to sort students

/**
 * @brief Sorts students using the STL sort function.
 *
 * @param studentai The vector to store the read students.
 * @param sortpasirinkimas The sorting option to use.
 */
void sortStudents(vector<Studentas>& studentai, int sortpasirinkimas) {
    auto sort_pradzia = chrono::high_resolution_clock::now();
    switch (sortpasirinkimas) {
    case 1: sort(studentai.begin(), studentai.end(), vidurkiolyginimas); break;
    case 2: sort(studentai.begin(), studentai.end(), medianoslyginimas); break;
    default: cout << "Netinkamas pasirinkimas. Pasirinkite i  naujo." << endl; return;
    }
    auto sort_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> sort_time = sort_pabaiga - sort_pradzia;
    cout << "Mokiniu rusiavimas naudojant sort funkcija uztruko " << sort_time.count() << " sekundes" << endl;
}

// Function to partition students (method 1)
/**
 * @brief Partitions students into normal and not normal students using method 1
 *
 * @param studentai The vector to store the read students.
 * @param normalus The vector to store normal students.
 * @param nenormalus The vector to store not normal students.
 */
void partitionStudents1(const vector<Studentas>& studentai, vector<Studentas>& normalus, vector<Studentas>& nenormalus) {
    cout << "Studentai dalinami   normalius ir nenormalius." << endl;
    auto normnenorm_pradzia = chrono::high_resolution_clock::now();
    for (const auto& stud : studentai) {
        if (stud.galutinisbalasvidurkis_ >= 5.0) normalus.push_back(stud);
        else nenormalus.push_back(stud);
    }
    auto normnenorm_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> normnenorm_time = normnenorm_pabaiga - normnenorm_pradzia;
    cout << "Student  r  iavimas   normalius ir nenormalius u truko " << normnenorm_time.count() << " sekundes" << endl;
}

// Function to partition students (method 2)
/**
 * @brief Partitions students into normal and not normal students using method 2
 *
 * @param studentai The vector to store the read students.
 * @param nenormalus The vector to store not normal students.
 */
void partitionStudents2(vector<Studentas>& studentai, vector<Studentas>& nenormalus) {
    cout << "Studentai dalinami   normalius ir nenormalius." << endl;
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
    cout << "Student  r  iavimas   normalius ir nenormalius u truko " << normnenorm_time.count() << " sekundes" << endl;
}

// Function to partition students (method 3)
/**
 * @brief Partitions students into normal and not normal students using method 3
 *
 * @param studentai The vector to store the read students.
 * @param normalus The vector to store normal students.
 * @param nenormalus The vector to store not normal students.
 */
void partitionStudents3(vector<Studentas>& studentai, vector<Studentas>& normalus, vector<Studentas>& nenormalus) {
    cout << "Studentai dalinami   normalius ir nenormalius." << endl;
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
    cout << "Student  r  iavimas   normalius ir nenormalius u truko " << normnenorm_time.count() << " sekundes" << endl;
}
/**
 * @brief ClassDestructor for Studentas class.
 * 
 * Destructor for the Studentas class.
 */
Studentas::~Studentas() {
    vardas_ = "";
    pavarde_ = "";
    namudarburez_.clear();
    egzaminorez_ = 0.0;
}

// Copy constructor implementation
/**
 * @brief Copy constructor for Studentas class.
 *
 * Constructor for the Studentas class.
 */
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_),
    namudarburez_(other.namudarburez_), egzaminorez_(other.egzaminorez_),
    namudarburezsuma_(other.namudarburezsuma_), vidurkis_(other.vidurkis_),
    galutinisbalasvidurkis_(other.galutinisbalasvidurkis_),
    mediana_(other.mediana_), galutinisbalasmediana_(other.galutinisbalasmediana_) {}

// Copy assignment operator implementation
/**
 * @brief Copy assignment operator implementation
 *
 * Copy assignment operator implementation.
 */
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
/**
 * @brief Move constructor implementation
 *
 * Move constructor implementation.
 */
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
/**
 * @brief Move assignment operator implementationconstructor implementation
 *
 * Move assignment operator implementation.
 */
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
/**
 * @brief Output operator implementation
 *
 * Output operator implementation.
 */
std::ostream& operator<<(std::ostream& os, Studentas& studentas) {
    os << studentas.getVardas() << " " << studentas.getPavarde() << " " << studentas.getEgzaminoRez() << " ";
    for (double pazymys : studentas.getNamudarbuRez()) {
        os << pazymys << " ";
    }
    return os;
}

// Input Operator (Deserialization)
/**
 * @brief Input operator implementation
 *
 * Input operator implementation.
 */
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
// Test constructors
/**
 * @brief Test constructors
 *
 * Test constructors.
 */
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
