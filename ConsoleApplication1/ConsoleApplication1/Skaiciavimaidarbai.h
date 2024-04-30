#pragma once
#include <iostream>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include "MokiniuProcessing.h"

void NetinkamaIvestis();
void NeraFailo();
double Mediana(const vector<double>& namudarburez);
double GenerateRandomGrade();
void PrintStudents(const vector<Studentas>& studentai);
void GeneruotiFaila(const string& pavadinimas, int kiekis);
bool compareByGalutinisVid(const Studentas& a, const Studentas& b);
bool compareByGalutinisMed(const Studentas& a, const Studentas& b);