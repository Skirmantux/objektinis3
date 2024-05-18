#pragma once
#include "MokiniuProcessing.h"

void NetinkamaIvestis();
void NeraFailo();
double Mediana(deque<double>& dq);
double GenerateRandomGrade();
void PrintStudents(const deque<Studentas>& studentai);
void GeneruotiFaila(const string& pavadinimas, int kiekis);
bool compareByGalutinisVid(const Studentas& a, const Studentas& b);
bool compareByGalutinisMed(const Studentas& a, const Studentas& b);
void readAndProcessData(const string& filename, deque<Studentas>& studentai, int namudarbai);
void sortStudents(deque<Studentas>& studentai, int sortpasirinkimas);
void partitionStudents1(const deque<Studentas>& studentai, deque<Studentas>& normalus, deque<Studentas>& nenormalus);
void partitionStudents2(deque<Studentas>& studentai, deque<Studentas>& nenormalus);
void partitionStudents3(deque<Studentas>& studentai, deque<Studentas>& normalus, deque<Studentas>& nenormalus);