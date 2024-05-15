#pragma once
#include "MokiniuProcessing.h"
class Studentas {
public:
    Studentas() : vardas(""), pavarde(""), egzaminorez(0.0), namudarburezsuma(0.0), vidurkis(0.0), galutinisbalasvidurkis(0.0), mediana(0.0), galutinisbalasmediana(0.0) {}
    string vardas;
    string pavarde;
    vector<double> namudarburez;
    double egzaminorez;
    double namudarburezsuma;
    double vidurkis;
    double galutinisbalasvidurkis;
    double mediana;
    double galutinisbalasmediana;
    // Constructor
    Studentas(const string& vardas_, const string& pavarde_, const vector<double>& namudarburez_, double egzaminorez_) :
        vardas(vardas_), pavarde(pavarde_), namudarburez(namudarburez_), egzaminorez(egzaminorez_) {}
    // Destructor
    ~Studentas() {}