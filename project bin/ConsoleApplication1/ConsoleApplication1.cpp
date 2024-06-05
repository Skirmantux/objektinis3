#include "MokiniuProcessing.h"
#include "Skaiciavimaidarbai.h"

/**
 * @brief Main function that serves as the entry point of the program.
 *
 * The main function initializes the necessary components, handles user input, and directs
 * the program flow based on the user's choices. It provides options for entering student data
 * manually, generating random data, reading from files, and testing different strategies.
 *
 * @return int Returns 0 on successful execution.
 */
int main()
{
    //main function
    setlocale(LC_ALL, "Lithuanian"); // Sets the locale to Lithuanian
    srand(time(NULL)); // Seeds the random number generator with the current time
    vector<Studentas> studentai; // Vector to store all students
    vector<Studentas> normalus; // Vector to store normal students
    vector<Studentas> nenormalus; // Vector to store abnormal students
    int pasirinkimas; // Variable to store the user's choice
    chrono::duration<double> process_time; // Variable to measure processing time
    chrono::duration<double> read_time; // Variable to measure reading time
    //menu selection
    cout << "Pasirinkite balø ávedimo metodà/generavimo funkcijà:\n"
        << "1. Ávesti rankiniu bûdu\n"
        << "2. Sugeneruoti atsitiktinius balus\n"
        << "3. Sugeneruoti balus, vardus ir pavardes\n"
        << "4. Skaitymas ið failo\n"
        << "5. Baigti programà\n"
        << "6. Generuoti studentø failà\n"
        << "7. Strategijø testavimas\n"
        << "8. Studento klasës operatoriø testavimas\n"
        << "Pasirinkimas: ";

    while (true) {
        //try selection
        try {
            std::cin >> pasirinkimas;
            if (pasirinkimas < 1 || pasirinkimas > 8) {
                throw invalid_argument("Netinkama ávestis.");
            }
            break;
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            std::cout << "Pasirinkimas: ";
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        Studentas stud;
        string vardas;
        string pavarde;
        if (pasirinkimas == 1) {
            while (true) {
                try {
                    std::cout << "Áveskite studento vardà ir pavardæ. Norëdami baigti ávedimà, áveskite -1: ";
                    std::cin >> vardas;
                    stud.setVardas(vardas);
                    if (vardas == "-1")
                        break;
                    if (ContainsNumbers(vardas)) {
                        throw invalid_argument("Vardas negali turëti skaièiø. Praðome ávesti vardà be skaièiø.");
                    }
                    std::cin >> pavarde;
                    stud.setPavarde(pavarde);
                    if (pavarde == "-1")
                        break;
                    if (ContainsNumbers(pavarde)) {
                        throw invalid_argument("Pavardë negali turëti skaièiø. Praðome ávesti pavardæ be skaièiø.");
                    }
                    std::cout << "Áveskite namø darbø rezultatus. Norëdami baigti ávedimà, áveskite -1: ";
                    while (true) {
                        double namudarburezultatas;
                        if (!(std::cin >> namudarburezultatas)) {
                            std::cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                            std::cin.clear();
                            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (namudarburezultatas == -1)
                            break;
                        if (namudarburezultatas >= 0 && namudarburezultatas <= 10) {
                            stud.addGrade(namudarburezultatas);
                        }
                        else {
                            std::cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                        }
                    }
                    double egzaminorezultatas;
                    std::cout << "Áveskite egzamino rezultatà: ";
                    std::cin >> egzaminorezultatas;
                    stud.setEgzaminoRez(egzaminorezultatas);
                    if (egzaminorezultatas < 0 || egzaminorezultatas > 10) {
                        throw out_of_range("Netinkama ávestis.");
                    }
                    stud.calculateFinalGrades();
                }
                catch (const exception& e) {
                    cerr << e.what() << endl;
                    std::cin.clear();
                    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
        else if (pasirinkimas == 2) {
            //Manual input with random grade generation
            while (true) {
                Studentas stud;
                std::cout << "Áveskite studento vardà ir pavardæ. Norëdami baigti ávedimà, áveskite -1: ";
                std::string vardas, pavarde;
                std::cin >> vardas;
                if (vardas == "-1")
                    break;
                std::cin >> pavarde;
                stud.setVardas(vardas);
                stud.setPavarde(pavarde);
                std::cout << "Generuojami atsitiktiniai balai uþ namø darbus..." << endl;
                for (int i = 0; i < 5; ++i) {
                    stud.addGrade(GenerateRandomGrade());
                }
                stud.setEgzaminoRez(GenerateRandomGrade());
                stud.calculateFinalGrades();
                studentai.push_back(stud);
            }
        }
        else if (pasirinkimas == 3) {
            //Grade, name and surname and student amount generation
            std::cout << "Generuojami balai, vardai ir pavardës ir studentø kiekis spausdinimui" << endl;
            int studentukiekis = rand() % 50;
            for (int i = 0; i < studentukiekis; ++i) {
                Studentas stud;
                for (int j = 0; j < 5; ++j) {
                    stud.addGrade(GenerateRandomGrade());
                }
                stud.setEgzaminoRez(GenerateRandomGrade());
                stud.setVardas(GeneruotiVardus());
                stud.setPavarde(GeneruotiPavardes());
                stud.calculateFinalGrades();
                studentai.push_back(stud);
            }
        }
        else if (pasirinkimas == 4) {
            // Student file reading and processing
            while (true) {
                try {
                    auto start_read = chrono::high_resolution_clock::now();
                    std::cout << "Kuri faila norite atidaryti:\n1 - studentai10000.txt\n2 - studentai100000.txt\n3 - studentai1000000.txt\nPasirinkimas: ";
                    int failopasirinkimas;
                    std::cin >> failopasirinkimas;
                    string failoPavadinimas;
                    switch (failopasirinkimas) {
                    case 1:
                        failoPavadinimas = "studentai10000.txt";
                        break;
                    case 2:
                        failoPavadinimas = "studentai100000.txt";
                        break;
                    case 3:
                        failoPavadinimas = "studentai1000000.txt";
                        break;
                    default:
                        throw invalid_argument("Neteisingas pasirinkimas.");
                    }
                    ifstream failas(failoPavadinimas);
                    if (!failas.is_open()) {
                        throw runtime_error("Nepavyko atidaryti failo.");
                    }
                    auto end_read = chrono::high_resolution_clock::now();
                    read_time = end_read - start_read;
                    auto start_process = chrono::high_resolution_clock::now();
                    string line;
                    getline(failas, line);
                    istringstream iss(line);
                    int stulpeliai = 0;
                    string zodziai;
                    while (iss >> zodziai) {
                        stulpeliai++;
                    }
                    int namudarbai = stulpeliai - 3;
                    while (failas.good()) {
                        Studentas stud;
                        string vardas, pavarde;
                        if (!(failas >> vardas >> pavarde))
                            break;
                        stud.setVardas(vardas);
                        stud.setPavarde(pavarde);
                        double grade;
                        for (int i = 0; i < namudarbai; i++) {
                            failas >> grade;
                            stud.addGrade(grade);
                        }
                        double egzaminoRez;
                        failas >> egzaminoRez;
                        stud.setEgzaminoRez(egzaminoRez);
                        stud.calculateFinalGrades();
                        studentai.push_back(stud);
                    }
                    auto end_process = chrono::high_resolution_clock::now();
                    process_time = end_process - start_process;
                    failas.close();
                    break;
                }
                catch (const exception& e) {
                    cerr << e.what() << endl;
                    std::cin.clear();
                    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
        else if (pasirinkimas == 5) {
            // Exit selection
            std::cout << "Programa baigia darbà." << endl;
            break;
        }
        else if (pasirinkimas == 6) {
            // Generate student file
            std::cout << "Ar norite generuoti studentø failà? (1 - taip, 2 - ne): ";
            int pasirinkimasgen;
            std::cin >> pasirinkimasgen;
            auto veikimo_pradzia = chrono::high_resolution_clock::now();
            if (pasirinkimasgen == 1) {
                std::cout << "Pasirinkite kiek studentø norite sugeneruoti:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:";
                int studentugen;
                std::cin >> studentugen;
                auto start_read = chrono::high_resolution_clock::now();
                switch (studentugen)
                {
                case 1:
                    GeneruotiFaila("studentaic1000.txt", 1000);
                    break;
                case 2:
                    GeneruotiFaila("studentaic10000.txt", 10000);
                    break;
                case 3:
                    GeneruotiFaila("studentaic100000.txt", 100000);
                    break;
                case 4:
                    GeneruotiFaila("studentaic1000000.txt", 1000000);
                    break;
                case 5:
                    GeneruotiFaila("studentaic10000000.txt", 10000000);
                    break;
                default:
                    std::cout << "Netinkamas pasirinkimas. Praðome ávesti tinkamà pasirinkimà: " << endl;
                    continue;
                }
                auto end_read = chrono::high_resolution_clock::now();
                read_time = end_read - start_read;
                std::cout << "Failo kurimas ir jo uzdarymas uztruko: " << read_time.count() << " sekundes" << endl;
            }
            std::cout << "Kurá failà norite skaityti?:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:" << endl;
            int failopasirinkimas;
            std::cin >> failopasirinkimas;
            string readFilename;
            int studentuskaicius;
            switch (failopasirinkimas) {
            case 1:
                readFilename = "studentaic1000.txt";
                studentuskaicius = 1000;
                break;
            case 2:
                readFilename = "studentaic10000.txt";
                studentuskaicius = 10000;
                break;
            case 3:
                readFilename = "studentaic100000.txt";
                studentuskaicius = 100000;
                break;
            case 4:
                readFilename = "studentaic1000000.txt";
                studentuskaicius = 1000000;
                break;
            case 5:
                readFilename = "studentaic10000000.txt";
                studentuskaicius = 10000000;
                break;
            default:
                NetinkamaIvestis();
                return 0;
            }
            int namudarbai = 5;
            readAndProcessData(readFilename, studentai, namudarbai, studentuskaicius);
            partitionStudents1(studentai, normalus, nenormalus);
            auto start_write = chrono::high_resolution_clock::now();
            WriteWeirdStudents(nenormalus);
            WriteNormalStudents(normalus);
            auto end_write = chrono::high_resolution_clock::now();
            chrono::duration<double> write_time = end_write - start_write;
            std::cout << "Rasymas i failus uztruko : " << write_time.count() << " sekundes" << endl;
            auto veikimo_pabaiga = chrono::high_resolution_clock::now();
            chrono::duration<double> process_time = veikimo_pabaiga - veikimo_pradzia;
            std::cout << "Programa viso uztruko " << process_time.count() << " sekundes" << endl;
            normalus.clear();
            nenormalus.clear();
            studentai.clear();
            break;
        }
        else if (pasirinkimas == 7) {
            // Reading strategy testing
            std::cout << "Bandoma pirma strategija..." << endl;
            std::cout << "Kurá failà norite skaityti?:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:" << endl;
            int failopasirinkimas;
            std::cin >> failopasirinkimas;
            string filename;
            int studentuskaicius;
            switch (failopasirinkimas) {
            case 1: filename = "studentaic1000.txt"; studentuskaicius = 1000; break;
            case 2: filename = "studentaic10000.txt"; studentuskaicius = 10000; break;
            case 3: filename = "studentaic100000.txt"; studentuskaicius = 100000; break;
            case 4: filename = "studentaic1000000.txt"; studentuskaicius = 1000000; break;
            case 5: filename = "studentaic10000000.txt"; studentuskaicius = 10000000; break;
            default:
                std::cout << "Netinkamas pasirinkimas. Praðome ávesti tinkamà pasirinkimà: " << endl;
                return 1;
            }
            int namudarbai = 5;
            readAndProcessData(filename, studentai, namudarbai, studentuskaicius);
            std::cout << "Kaip norite rusiuoti studentø vektoriø?\n1. Pagal vidurká\n2. Pagal medianà\nPasirinkimas: ";
            int sortpasirinkimas;
            std::cin >> sortpasirinkimas;
            sortStudents(studentai, sortpasirinkimas);
            partitionStudents1(studentai, normalus, nenormalus);
            studentai.clear();
            normalus.clear();
            nenormalus.clear();
            std::cout << "Bandoma antra strategija..." << endl;
            readAndProcessData(filename, studentai, namudarbai, studentuskaicius);
            sortStudents(studentai, sortpasirinkimas);
            partitionStudents2(studentai, nenormalus);
            studentai.clear();
            nenormalus.clear();
            std::cout << "Bandoma treèia strategija..." << endl;
            readAndProcessData(filename, studentai, namudarbai, studentuskaicius);
            sortStudents(studentai, sortpasirinkimas);
            partitionStudents3(studentai, normalus, nenormalus);
            studentai.clear();
            normalus.clear();
            nenormalus.clear();
            break;
        }
        else if (pasirinkimas == 8) {
            // Testing student class operators
            testConstructors();
        }
        if (!studentai.empty())
            // End screen for manual input
        {
            std::cout << "Norite áraðyti duomenis atspausdinant á ekranà ar á failà?: 1 - ekranà; 2 - failà" << endl;
            int skaicbudas;
            std::cin >> skaicbudas;
            std::cout << "Pasirinkite rikiavimo bûdà:\n1 - pagal vardus\n2 - pagal pavardes\n3 - pagal galutiná balà (vid.)\n4 - pagal galutiná balà (med.)\nPasirinkimas: ";
            int sorting_choice;
            std::cin >> sorting_choice;
            switch (sorting_choice)
            {
            case 1:
                sort(studentai.begin(), studentai.end(), vardolyginimas);
                break;
            case 2:
                sort(studentai.begin(), studentai.end(), pavardeslyginimas);
                break;
            case 3:
                sort(studentai.begin(), studentai.end(), vidurkiolyginimas);
                break;
            case 4:
                sort(studentai.begin(), studentai.end(), medianoslyginimas);
                break;
            default:
                NetinkamaIvestis();
                break;
            }
            if (skaicbudas == 1)
            {
                PrintStudents(studentai);
                break;
            }
            else if (skaicbudas == 2)
            {
                auto start_writing = chrono::high_resolution_clock::now();
                ofstream failasr("kursioku_duomenys.txt");
                failasr << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(30) << "Galutinis balas (vid.)" << setw(30) << "Galutinis balas (med.)" << endl;
                failasr << "---------------------------------------------------------------------------------------------------" << endl;
                int vardas, pavarde;
                for (const auto& stud : studentai)
                {
                    failasr << setw(15) << stud.getPavarde() << setw(15) << stud.getVardas() << setw(30) << fixed << setprecision(2) << stud.galutinisbalasvidurkis_ << setw(30) << fixed << setprecision(2) << stud.galutinisbalasmediana_ << endl;
                }
                std::cout << "Áraðymas sëkmingas. Rezultatai iðsaugoti faile kursioku_duomenys.txt" << endl;
                failasr.close();
                auto end_writing = chrono::high_resolution_clock::now();
                chrono::duration<double> writeFile_time = end_writing - start_writing;
                std::cout << "Skaitymas ið failo truko: " << read_time.count() << " sekundes" << endl;
                std::cout << "Mokiniø vidurkio/medianos skaièiavimas uþtruko: " << process_time.count() << " sekundes" << endl;
                std::cout << "Áraðymas á failà truko: " << writeFile_time.count() << " sekundes" << endl;
                break;
            }
            else
            {
                NetinkamaIvestis();
                break;
            }
        }
        else
        {
            std::cout << "Studentø masyvas tuðèias." << endl;
        }
    }
    std::cout << "Vector programos versija baigta. Paspauskite bet koká mygtukà ir ENTER norint uþbaigti programà..." << endl;
    int a;
    std::cin >> a;
    return 0;
}

