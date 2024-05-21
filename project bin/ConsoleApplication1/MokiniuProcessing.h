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
void PatikrintiTeigiamajiSkaiciu(double skaicius);
bool ContainsNumbers(const string& str);