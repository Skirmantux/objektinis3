#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <list>
#include <vector>
#include "MokiniuProcessing.h"

void NetinkamaIvestis();
void NeraFailo();
double Mediana(list<double>& lst);
double GenerateRandomGrade();
void PrintStudents(const list<Studentas>& studentai);
void GeneruotiFaila(const string& pavadinimas, int kiekis);
bool compareByGalutinisVid(const Studentas& a, const Studentas& b);
bool compareByGalutinisMed(const Studentas& a, const Studentas& b);
void readAndProcessData(const string& filename, list<Studentas>& studentai, int namudarbai);
void sortStudents(list<Studentas>& studentai, int sortpasirinkimas);
void partitionStudents1(const list<Studentas>& studentai, list<Studentas>& normalus, list<Studentas>& nenormalus);
void partitionStudents2(list<Studentas>& studentai, list<Studentas>& nenormalus);
void partitionStudents3(list<Studentas>& studentai, list<Studentas>& normalus, list<Studentas>& nenormalus);