#pragma once
#include "MokiniuProcessing.h"

void NetinkamaIvestis();
void NeraFailo();
double Mediana(vector<double>& vec);
double GenerateRandomGrade();
void PrintStudents(const vector<Studentas>& studentai);
void GeneruotiFaila(const string& pavadinimas, int studentuskaicius);
bool compareByGalutinisVid(const Studentas& a, const Studentas& b);
bool compareByGalutinisMed(const Studentas& a, const Studentas& b);
void readAndProcessData(const string& filename, vector<Studentas>& studentai, int namudarbai);
void sortStudents(vector<Studentas>& studentai, int sortpasirinkimas);
void partitionStudents1(const vector<Studentas>& studentai, vector<Studentas>& normalus, vector<Studentas>& nenormalus);
void partitionStudents2(vector<Studentas>& studentai, vector<Studentas>& nenormalus);
void partitionStudents3(vector<Studentas>& studentai, vector<Studentas>& normalus, vector<Studentas>& nenormalus);