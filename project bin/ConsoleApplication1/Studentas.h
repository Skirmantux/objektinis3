#pragma once

#include <string>
#include <vector>

/**
 * @brief Abstract class representing a person.
 *
 * This class defines the basic interface for a person, providing methods to retrieve
 * information such as name and exam grades.
 */
class Zmogus {
public:
    virtual ~Zmogus() = default;
    // Getters
     /**
     * @brief Get the first name of the person.
     *
     * @return The first name of the person.
     */
    virtual std::string getVardas() const = 0;
    /**
    * @brief Get the last name of the person.
    *
    * @return The last name of the person.
    */
    virtual std::string getPavarde() const = 0;
    /**
    * @brief Get the exam grade of the person.
    *
    * @return The exam grade of the person.
    */
    virtual double getEgzaminoRez() const = 0;
    /**
    * @brief Get the grades of homework for the person.
    *
    * @return A reference to the vector containing homework grades of the person.
    */
    virtual std::vector<double>& getNamudarbuRez() = 0;
};
/**
 * @brief Class representing a student.
 *
 * This class stores information about a student, including their name,
 * grades for homework and exams, and calculated final grades.
 */
class Studentas : public Zmogus {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<double> namudarburez_;
    double egzaminorez_;

public:
    double namudarburezsuma_; /**< Sum of homework grades. */
    double vidurkis_; /**< Average final grade. */
    double galutinisbalasvidurkis_; /**< Final grade calculated using average method. */
    double mediana_; /**< Median final grade. */
    double galutinisbalasmediana_; /**< Final grade calculated using median method. */

    // Constructors
    Studentas(); /**< Default constructor. */
    Studentas(std::istream& is); /**< Constructor to initialize a student with input stream. */

    // Getters
    std::string getVardas() const { return vardas_; } /**< Get the first name of the student. */
    std::string getPavarde() const { return pavarde_; } /**< Get the last name of the student. */
    double getEgzaminoRez() const { return egzaminorez_; } /**< Get the exam grade of the student. */
    std::vector<double>& getNamudarbuRez() { return namudarburez_; } /**< Get the grades of homework for the student. */

    // Setters
    void setVardas(const std::string& vardas) { vardas_ = vardas; } /**< Set the first name of the student. */
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; } /**< Set the last name of the student. */
    void setEgzaminoRez(double egzaminorez) { egzaminorez_ = egzaminorez; } /**< Set the exam grade of the student. */
    void addGrade(double grade) { namudarburez_.push_back(grade); } /**< Add a grade to the homework grades of the student. */

    // Other member functions
    std::istream& readStudent(std::istream&); /**< Read student data from an input stream. */
    void calculateFinalGrades(); /**< Calculate final grades for the student. */

    //Destructor
    ~Studentas(); /**< Destructor. */
    Studentas(const Studentas& other); /**< Copy constructor. */
    Studentas& operator=(const Studentas& other); /**< Copy assignment operator. */
    Studentas(Studentas&& other) noexcept; /**< Move constructor. */
    Studentas& operator=(Studentas&& other) noexcept; /**< Move assignment operator. */

};
// Negalima kurti zmogus objekto - 
// Zmogus a;

// Comparison functions
bool vardolyginimas(const Studentas& a, const Studentas& b); /**< Compare students by first name. */
bool pavardeslyginimas(const Studentas& a, const Studentas& b); /**< Compare students by last name. */
bool vidurkiolyginimas(const Studentas& a, const Studentas& b); /**< Compare students by average final grade. */
bool medianoslyginimas(const Studentas& a, const Studentas& b); /**< Compare students by median final grade. */

// Utility functions
void PrintStudents(const std::vector<Studentas>& studentai); /**< Print a list of students. */
void readAndProcessData(const std::string& filename, std::vector<Studentas>& studentai, int& namudarbai, int studentuskaicius); /**< Read and process student data from a file. */
void sortStudents(std::vector<Studentas>& studentai, int sortpasirinkimas); /**< Sort students based on specified criteria. */
void partitionStudents1(const std::vector<Studentas>& studentai, std::vector<Studentas>& normalus, std::vector<Studentas>& nenormalus); /**< Partition students into normal and weird categories (method 1). */
void partitionStudents2(std::vector<Studentas>& studentai, std::vector<Studentas>& nenormalus); /**< Partition students into normal and weird categories (method 2). */
void partitionStudents3(std::vector<Studentas>& studentai, std::vector<Studentas>& normalus, std::vector<Studentas>& nenormalus); /**< Partition students into normal and weird categories (method 3). */
void WriteWeirdStudents(std::vector<Studentas>& nenormalus); /**< Write weird students to a file. */
void WriteNormalStudents(std::vector<Studentas>& normalus); /**< Write normal students to a file. */
void testConstructors(); /**< Test constructors of the Studentas class. */
