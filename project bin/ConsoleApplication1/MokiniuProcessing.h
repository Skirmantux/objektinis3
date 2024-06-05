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

/**
 * @brief Generates a random Lithuanian first name from a predefined list.
 *
 * This function selects a random first name from a vector of common Lithuanian names
 * and returns it as a string.
 *
 * @return string A randomly selected Lithuanian first name.
 */
string GeneruotiVardus();

/**
 * @brief Generates a random Lithuanian last name from a predefined list.
 *
 * This function selects a random last name from a vector of common Lithuanian surnames
 * and returns it as a string.
 *
 * @return string A randomly selected Lithuanian last name.
 */
string GeneruotiPavardes();

/**
 * @brief Checks if a given number is within a valid range (0 to 10).
 *
 * This function throws an invalid_argument exception if the provided number is
 * not within the range of 0 to 10.
 *
 * @param skaicius The number to check.
 * @throws invalid_argument If the number is not within the range 0 to 10.
 */
void PatikrintiTeigiamajiSkaiciu(double skaicius);

/**
 * @brief Checks if a string contains any numeric digits.
 *
 * This function returns true if the provided string contains at least one numeric digit,
 * and false otherwise.
 *
 * @param str The string to check.
 * @return bool True if the string contains numeric digits, false otherwise.
 */
bool ContainsNumbers(const string& str);
