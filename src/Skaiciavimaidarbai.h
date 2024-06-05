#pragma once
#include "MokiniuProcessing.h"

/**
 * @brief Prints a message indicating invalid input and terminates the program.
 *
 * This function outputs a message to the console indicating that the input was invalid
 * and then terminates the program.
 */
void NetinkamaIvestis();

/**
 * @brief Prints a message indicating that a file was not found and terminates the program.
 *
 * This function outputs a message to the console indicating that the specified file was not found
 * and then terminates the program.
 */
void NeraFailo();

/**
 * @brief Calculates the median of a vector of doubles.
 *
 * This function sorts the provided vector and calculates the median value.
 * If the vector size is even, it returns the average of the two middle elements.
 * If the vector size is odd, it returns the middle element.
 *
 * @param vec The vector of doubles to calculate the median for.
 * @return double The median value of the vector.
 */
double Mediana(std::vector<double>& vec);

/**
 * @brief Generates a random grade between 0 and 10.
 *
 * This function returns a random grade in the range of 0 to 10.
 *
 * @return double A randomly generated grade between 0 and 10.
 */
double GenerateRandomGrade();

/**
 * @brief Generates a file with random student data.
 *
 * This function creates a file with the specified name and populates it with
 * a specified number of students. Each student will have a generated name, surname,
 * and a set of random grades.
 *
 * @param pavadinimas The name of the file to generate.
 * @param studentuskaicius The number of students to generate data for.
 */
void GeneruotiFaila(const string& pavadinimas, int studentuskaicius);

/**
 * @brief Comparator function to compare students by their final average grade.
 *
 * This function compares two students based on their final average grade
 * and returns true if the first student's grade is less than the second student's grade.
 *
 * @param a The first student to compare.
 * @param b The second student to compare.
 * @return bool True if the first student's final average grade is less than the second student's grade.
 */
bool compareByGalutinisVid(const Studentas& a, const Studentas& b);

/**
 * @brief Comparator function to compare students by their final median grade.
 *
 * This function compares two students based on their final median grade
 * and returns true if the first student's grade is less than the second student's grade.
 *
 * @param a The first student to compare.
 * @param b The second student to compare.
 * @return bool True if the first student's final median grade is less than the second student's grade.
 */
bool compareByGalutinisMed(const Studentas& a, const Studentas& b);
