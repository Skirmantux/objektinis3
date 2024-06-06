#include "MokiniuProcessing.h"
#include "Skaiciavimaidarbai.h"
#include "Vektorius.h"

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
    srand(time(NULL)); // Seeds the random number generator with the current time
    Vector<Studentas> studentai; // Vector to store all students
    Vector<Studentas> normalus; // Vector to store normal students
    Vector<Studentas> nenormalus; // Vector to store abnormal students
    int pasirinkimas; // Variable to store the user's choice
    chrono::duration<double> process_time; // Variable to measure processing time
    chrono::duration<double> read_time; // Variable to measure reading time
    //menu selection
    cout << "Pasirinkite balu ivedimo metoda/generavimo funkcija:\n"
        << "1. Ivesti rankiniu budu\n"
        << "2. Sugeneruoti atsitiktinius balus\n"
        << "3. Sugeneruoti balus, vardus ir pavardes\n"
        << "4. Skaitymas is failo\n"
        << "5. Baigti programa\n"
        << "6. Generuoti studentu faila\n"
        << "7. Strategiju testavimas\n"
        << "8. Studento klases operatoriu testavimas\n"
        << "9. Vektoriu klases testavimas\n"
        << "Pasirinkimas: ";

    while (true) {
        //try selection
        try {
            std::cin >> pasirinkimas;
            if (pasirinkimas < 1 || pasirinkimas > 9) {
                throw invalid_argument("Netinkama ivestis.");
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
                    std::cout << " veskite studento varda ir pavarde. Noredami baigti ivedima, iveskite -1: ";
                    std::cin >> vardas;
                    stud.setVardas(vardas);
                    if (vardas == "-1")
                        break;
                    if (ContainsNumbers(vardas)) {
                        throw invalid_argument("Vardas negali tureti skaiciu. Prasome ivesti varda be skaiciu.");
                    }
                    std::cin >> pavarde;
                    stud.setPavarde(pavarde);
                    if (pavarde == "-1")
                        break;
                    if (ContainsNumbers(pavarde)) {
                        throw invalid_argument("Pavarde negali tureti skaiciu. Prasome ivesti pavarde be skaiciu.");
                    }
                    std::cout << " veskite nam  darb  rezultatus. Nor dami baigti  vedim ,  veskite -1: ";
                    while (true) {
                        double namudarburezultatas;
                        if (!(std::cin >> namudarburezultatas)) {
                            std::cout << "Netinkama  vestis.  veskite skai i  tarp 0 ir 10." << endl;
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
                            std::cout << "Netinkama  vestis.  veskite skai i  tarp 0 ir 10." << endl;
                        }
                    }
                    double egzaminorezultatas;
                    std::cout << " veskite egzamino rezultat : ";
                    std::cin >> egzaminorezultatas;
                    stud.setEgzaminoRez(egzaminorezultatas);
                    if (egzaminorezultatas < 0 || egzaminorezultatas > 10) {
                        throw out_of_range("Netinkama  vestis.");
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
                std::cout << " veskite studento vard  ir pavard . Nor dami baigti  vedim ,  veskite -1: ";
                std::string vardas, pavarde;
                std::cin >> vardas;
                if (vardas == "-1")
                    break;
                std::cin >> pavarde;
                stud.setVardas(vardas);
                stud.setPavarde(pavarde);
                std::cout << "Generuojami atsitiktiniai balai u  nam  darbus..." << endl;
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
            std::cout << "Generuojami balai, vardai ir pavard s ir student  kiekis spausdinimui" << endl;
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
            std::cout << "Programa baigia darb ." << endl;
            break;
        }
        else if (pasirinkimas == 6) {
            // Generate student file
            std::cout << "Ar norite generuoti student  fail ? (1 - taip, 2 - ne): ";
            int pasirinkimasgen;
            std::cin >> pasirinkimasgen;
            auto veikimo_pradzia = chrono::high_resolution_clock::now();
            if (pasirinkimasgen == 1) {
                std::cout << "Pasirinkite kiek student  norite sugeneruoti:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:";
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
                    std::cout << "Netinkamas pasirinkimas. Pra ome  vesti tinkam  pasirinkim : " << endl;
                    continue;
                }
                auto end_read = chrono::high_resolution_clock::now();
                read_time = end_read - start_read;
                std::cout << "Failo kurimas ir jo uzdarymas uztruko: " << read_time.count() << " sekundes" << endl;
            }
            std::cout << "Kur  fail  norite skaityti?:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:" << endl;
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
            std::cout << "Kuri faila norite skaityti?:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:" << endl;
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
                std::cout << "Netinkamas pasirinkimas. Prasome ivesti tinkama pasirinkima: " << endl;
                return 1;
            }
            int namudarbai = 5;
            readAndProcessData(filename, studentai, namudarbai, studentuskaicius);
            std::cout << "Kaip norite rusiuoti studentu vektoriu?\n1. Pagal vidurki\n2. Pagal mediana\nPasirinkimas: ";
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
            std::cout << "Bandoma trecia strategija..." << endl;
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
	    break;
        }
        else if (pasirinkimas == 9) {
			// Testing vector class
            VectorExample();
            // Example vectors
            Vector<int> vec1 = { 1, 3, 5, 7, 9 };
            Vector<int> vec2 = { 2, 4, 6, 8, 10 };
            Vector<int> vec3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            Vector<int> vec4 = { 5, 2, 7, 2, 8, 5, 1, 9, 3, 7 };
            std::cout << "Pirmasis pavyzdinis vektorius:" << std::endl;
            for (int elem : vec1) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
            std::cout << "Antrasis pavyzdinis vektorius:" << std::endl;
            for (int elem1 : vec2) {
				std::cout << elem1 << " ";
			}
            std::cout << std::endl;
            std::cout << "Treciasis pavyzdinis vektorius:" << std::endl;
            for (int elem2 : vec3) {
				std::cout << elem2 << " ";
			}
            std::cout << std::endl;
            std::cout << "Ketvirtasis pavyzdinis vektorius:" << std::endl;
            for (int elem3 : vec4) {
                std::cout << elem3 << " ";
            }
            std::cout << std::endl;
            // Testing functions
            std::cout << "Pirmojo vektoriaus suma: " << sumVector(vec1) << std::endl;
            std::cout << "Ar pirmasis vektorius rusiuotas? " << (isSorted(vec1) ? "Yes" : "No") << std::endl;
            removeDuplicates(vec4);
            std::cout << "Ketvirtasis vektorius po tokiu paciu skaiciu istrinimo: ";
            for (int elem : vec4) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
            Vector<int> merged = mergeSortedVectors(vec1, vec2);
            std::cout << "Pirmasis ir antrasis vektorius sujungti: ";
            for (int elem : merged) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
            std::pair<int, int> maxElem = findMaxElement(vec3);
            std::cout << "Maksimalus elementas treciame vektoriuje: " << maxElem.second << " at index " << maxElem.first << std::endl;
            VectorUzpildymas();
            break;
        }
        if (!studentai.empty())
            // End screen for manual input
        {
            std::cout << "Norite irasyti duomenis atspausdinant i ekrana ar i faila?: 1 - ekrana; 2 - faila" << endl;
            int skaicbudas;
            std::cin >> skaicbudas;
            std::cout << "Pasirinkite rikiavimo buda:\n1 - pagal vardus\n2 - pagal pavardes\n3 - pagal galutini bala (vid.)\n4 - pagal galutini bala (med.)\nPasirinkimas: ";
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
                std::cout << "irasymas sekmingas. Rezultatai issaugoti faile kursioku_duomenys.txt" << endl;
                failasr.close();
                auto end_writing = chrono::high_resolution_clock::now();
                chrono::duration<double> writeFile_time = end_writing - start_writing;
                std::cout << "Skaitymas is failo truko: " << read_time.count() << " sekundes" << endl;
                std::cout << "Mokiniu vidurkio/medianos skaiciavimas uztruko: " << process_time.count() << " sekundes" << endl;
                std::cout << "irasymas i faila truko: " << writeFile_time.count() << " sekundes" << endl;
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
            std::cout << "Studentu masyvas tuscias." << endl;
        }
    }
    std::cout << "Vector programos versija baigta. Ar norite kartoti programa? 1 - taip; Bet kokia kita ivestis - ne." << endl;
    int a;
    std::cin >> a;
    if (a == 1)
    {
        system("cls");
		main();
	}
    else
    {
        std::cout << "Programa isjungiama...";
        return 0;
	}
}

