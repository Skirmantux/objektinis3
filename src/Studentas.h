#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <chrono>

class Studentas {
public:
    std::string vardas_;
    std::string pavarde_;
    std::vector<double> namudarburez_;
    double egzaminorez_;
    double namudarburezsuma_;
    double vidurkis_;
    double galutinisbalasvidurkis_;
    double mediana_;
    double galutinisbalasmediana_;

    // Constructors
    Studentas();
    Studentas(std::istream& is);

    // Getters
    std::string getVardas() const;
    std::string getPavarde() const;
    double getGalBalasVidurkis() const;
    double getGalBalasMediana() const;

    // Setters
    std::istream& readStudent(std::istream&);

    // Other member functions
    void calculateFinalGrades();
};

// Non-member functions
bool vardolyginimas(const Studentas& a, const Studentas& b);
bool pavardeslyginimas(const Studentas& a, const Studentas& b);
bool vidurkiolyginimas(const Studentas& a, const Studentas& b);
bool medianoslyginimas(const Studentas& a, const Studentas& b);

// Utility functions
void PrintStudents(const std::vector<Studentas>& studentai);
void readAndProcessData(const std::string& filename, std::vector<Studentas>& studentai, int& namudarbai, int studentuskaicius);
void sortStudents(std::vector<Studentas>& studentai, int sortpasirinkimas);
void partitionStudents1(const std::vector<Studentas>& studentai, std::vector<Studentas>& normalus, std::vector<Studentas>& nenormalus);
void partitionStudents2(std::vector<Studentas>& studentai, std::vector<Studentas>& nenormalus);
void partitionStudents3(std::vector<Studentas>& studentai, std::vector<Studentas>& normalus, std::vector<Studentas>& nenormalus);
void WriteWeirdStudents(std::vector<Studentas>& nenormalus);
void WriteNormalStudents(std::vector<Studentas>& normalus);
