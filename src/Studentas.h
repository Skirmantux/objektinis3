#pragma once

#include <string>
#include <vector>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<double> namudarburez_;
    double egzaminorez_;

public:
    double namudarburezsuma_;
    double vidurkis_;
    double galutinisbalasvidurkis_;
    double mediana_;
    double galutinisbalasmediana_;

    // Constructors
    Studentas();
    Studentas(std::istream& is);

    // Getters
    std::string getVardas() const { return vardas_; }
    std::string getPavarde() const { return pavarde_; }
    double getEgzaminoRez() const { return egzaminorez_; }
    std::vector<double>& getNamudarbuRez() { return namudarburez_; }

    // Setters
    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    void setEgzaminoRez(double egzaminorez) { egzaminorez_ = egzaminorez; }
    void addGrade(double grade) { namudarburez_.push_back(grade); }

    // Other member functions
    std::istream& readStudent(std::istream&);
    void calculateFinalGrades();

    //Destructor
    ~Studentas();
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    Studentas(Studentas&& other) noexcept;
    Studentas& operator=(Studentas&& other) noexcept;

};

bool vardolyginimas(const Studentas& a, const Studentas& b);
bool pavardeslyginimas(const Studentas& a, const Studentas& b);
bool vidurkiolyginimas(const Studentas& a, const Studentas& b);
bool medianoslyginimas(const Studentas& a, const Studentas& b);
void PrintStudents(const std::vector<Studentas>& studentai);
void readAndProcessData(const std::string& filename, std::vector<Studentas>& studentai, int& namudarbai, int studentuskaicius);
void sortStudents(std::vector<Studentas>& studentai, int sortpasirinkimas);
void partitionStudents1(const std::vector<Studentas>& studentai, std::vector<Studentas>& normalus, std::vector<Studentas>& nenormalus);
void partitionStudents2(std::vector<Studentas>& studentai, std::vector<Studentas>& nenormalus);
void partitionStudents3(std::vector<Studentas>& studentai, std::vector<Studentas>& normalus, std::vector<Studentas>& nenormalus);
void WriteWeirdStudents(std::vector<Studentas>& nenormalus);
void WriteNormalStudents(std::vector<Studentas>& normalus);
void testConstructors();
