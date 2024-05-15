#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <locale>
#include <numeric>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include "Studentas.h"
using namespace std;
string GeneruotiVardus();
string GeneruotiPavardes();
bool vardolyginimas(const Studentas& a, const Studentas& b);
bool pavardeslyginimas(const Studentas& a, const Studentas& b);
bool vidurkiolyginimas(const Studentas& a, const Studentas& b);
bool medianoslyginimas(const Studentas& a, const Studentas& b);
void PatikrintiTeigiamajiSkaiciu(int skaicius);
bool ContainsNumbers(const string& str);