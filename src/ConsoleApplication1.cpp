#include "MokiniuProcessing.h"
#include "Skaiciavimaidarbai.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    srand(time(NULL));
    vector<Studentas> studentai;
    vector<Studentas> normalus;
    vector<Studentas> nenormalus;
    int pasirinkimas;
    chrono::duration<double> process_time;
    chrono::duration<double> read_time;

    cout << "Pasirinkite balų įvedimo metodą/generavimo funkciją:\n"
        << "1. Įvesti rankiniu būdu\n"
        << "2. Sugeneruoti atsitiktinius balus\n"
        << "3. Sugeneruoti balus, vardus ir pavardes\n"
        << "4. Skaitymas iš failo\n"
        << "5. Baigti programą\n"
        << "6. Generuoti studentų failą\n"
        << "7. Strategijų testavimas\n"
        << "Pasirinkimas: ";

    while (true) {
        try {
            cin >> pasirinkimas;
            if (pasirinkimas < 1 || pasirinkimas > 7) {
                throw invalid_argument("Netinkama įvestis.");
            }
            break;
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            cout << "Pasirinkimas: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        Studentas stud;
        string vardas;
        string pavarde;
        if (pasirinkimas == 1) {
            while (true) {
                try {
                    cout << "Įveskite studento vardą ir pavardę. Norėdami baigti įvedimą, įveskite -1: ";
                    cin >> vardas;
                    stud.setVardas(vardas);
                    if (vardas == "-1")
                        break;
                    if (ContainsNumbers(vardas)) {
                        throw invalid_argument("Vardas negali turėti skaičių. Prašome įvesti vardą be skaičių.");
                    }
                    cin >> pavarde;
                    stud.setPavarde(pavarde);
                    if (pavarde == "-1")
                        break;
                    if (ContainsNumbers(pavarde)) {
                        throw invalid_argument("Pavardė negali turėti skaičių. Prašome įvesti pavardę be skaičių.");
                    }
                    cout << "Įveskite namų darbų rezultatus. Norėdami baigti įvedimą, įveskite -1: ";
                    while (true) {
                        double namudarburezultatas;
                        if (!(cin >> namudarburezultatas)) {
                            cout << "Netinkama įvestis. Įveskite skaičių tarp 0 ir 10." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (namudarburezultatas == -1)
                            break;
                        if (namudarburezultatas >= 0 && namudarburezultatas <= 10) {
                            stud.addGrade(namudarburezultatas);
                        }
                        else {
                            cout << "Netinkama įvestis. Įveskite skaičių tarp 0 ir 10." << endl;
                        }
                    }
                    double egzaminorezultatas;
                    cout << "Įveskite egzamino rezultatą: ";
                    cin >> egzaminorezultatas;
                    stud.setEgzaminoRez(egzaminorezultatas);
                    if (egzaminorezultatas < 0 || egzaminorezultatas > 10) {
                        throw out_of_range("Netinkama įvestis.");
                    }
                    stud.calculateFinalGrades();
                }
                catch (const exception& e) {
                    cerr << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
        else if (pasirinkimas == 2) {
            while (true) {
                Studentas stud;
                cout << "Įveskite studento vardą ir pavardę. Norėdami baigti įvedimą, įveskite -1: ";
                std::string vardas, pavarde;
                cin >> vardas;
                if (vardas == "-1")
                    break;
                cin >> pavarde;
                stud.setVardas(vardas);
                stud.setPavarde(pavarde);
                cout << "Generuojami atsitiktiniai balai už namų darbus..." << endl;
                for (int i = 0; i < 5; ++i) {
                    stud.addGrade(GenerateRandomGrade());
                }
                stud.setEgzaminoRez(GenerateRandomGrade());
                stud.calculateFinalGrades();
                studentai.push_back(stud);
            }
        }
        else if (pasirinkimas == 3) {
            cout << "Generuojami balai, vardai ir pavardės ir studentų kiekis spausdinimui" << endl;
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
            while (true) {
                try {
                    auto start_read = chrono::high_resolution_clock::now();
                    cout << "Kuri faila norite atidaryti:\n1 - studentai10000.txt\n2 - studentai100000.txt\n3 - studentai1000000.txt\nPasirinkimas: ";
                    int failopasirinkimas;
                    cin >> failopasirinkimas;
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
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
        else if (pasirinkimas == 5) {
            cout << "Programa baigia darbą." << endl;
            break;
        }
        else if (pasirinkimas == 6) {
            cout << "Ar norite generuoti studentų failą? (1 - taip, 2 - ne): ";
            int pasirinkimasgen;
            cin >> pasirinkimasgen;
            auto veikimo_pradzia = chrono::high_resolution_clock::now();
            if (pasirinkimasgen == 1) {
                cout << "Pasirinkite kiek studentų norite sugeneruoti:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:";
                int studentugen;
                cin >> studentugen;
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
                    cout << "Netinkamas pasirinkimas. Prašome įvesti tinkamą pasirinkimą: " << endl;
                    continue;
                }
                auto end_read = chrono::high_resolution_clock::now();
                read_time = end_read - start_read;
                cout << "Failo kurimas ir jo uzdarymas uztruko: " << read_time.count() << " sekundes" << endl;
            }
            cout << "Kurį failą norite skaityti?:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:" << endl;
            int failopasirinkimas;
            cin >> failopasirinkimas;
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
            vector<Studentas> studentai;
            int namudarbai = 5;
            readAndProcessData(readFilename, studentai, namudarbai, studentuskaicius);
            vector<Studentas> normalus;
            vector<Studentas> nenormalus;
            partitionStudents1(studentai, normalus, nenormalus);
            auto start_write = chrono::high_resolution_clock::now();
            WriteWeirdStudents(nenormalus);
            WriteNormalStudents(normalus);
            auto end_write = chrono::high_resolution_clock::now();
            chrono::duration<double> write_time = end_write - start_write;
            cout << "Rasymas i failus uztruko : " << write_time.count() << " sekundes" << endl;
            auto veikimo_pabaiga = chrono::high_resolution_clock::now();
            chrono::duration<double> process_time = veikimo_pabaiga - veikimo_pradzia;
            cout << "Programa viso uztruko " << process_time.count() << " sekundes" << endl;
            break;
            }
        else if (pasirinkimas == 7) {
            cout << "Bandoma pirma strategija..." << endl;
            cout << "Kurį failą norite skaityti?:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:" << endl;
            int failopasirinkimas;
            cin >> failopasirinkimas;
            string filename;
            int studentuskaicius;
            switch (failopasirinkimas) {
            case 1: filename = "studentaic1000.txt"; studentuskaicius = 1000; break;
            case 2: filename = "studentaic10000.txt"; studentuskaicius = 10000; break;
            case 3: filename = "studentaic100000.txt"; studentuskaicius = 100000; break;
            case 4: filename = "studentaic1000000.txt"; studentuskaicius = 1000000; break;
            case 5: filename = "studentaic10000000.txt"; studentuskaicius = 10000000; break;
            default:
                cout << "Netinkamas pasirinkimas. Prašome įvesti tinkamą pasirinkimą: " << endl;
                return 1;
            }
            vector<Studentas> studentai;
            int namudarbai = 5;
            readAndProcessData(filename, studentai, namudarbai, studentuskaicius);
            cout << "Kaip norite rusiuoti studentų vektorių?\n1. Pagal vidurkį\n2. Pagal medianą\nPasirinkimas: ";
            int sortpasirinkimas;
            cin >> sortpasirinkimas;
            sortStudents(studentai, sortpasirinkimas);
            vector<Studentas> normalus;
            vector<Studentas> nenormalus;
            partitionStudents1(studentai, normalus, nenormalus);
            studentai.clear();
            normalus.clear();
            nenormalus.clear();
            cout << "Bandoma antra strategija..." << endl;
            readAndProcessData(filename, studentai, namudarbai, studentuskaicius);
            sortStudents(studentai, sortpasirinkimas);
            partitionStudents2(studentai, nenormalus);
            studentai.clear();
            nenormalus.clear();
            cout << "Bandoma trečia strategija..." << endl;
            readAndProcessData(filename, studentai, namudarbai, studentuskaicius);
            sortStudents(studentai, sortpasirinkimas);
            partitionStudents3(studentai, normalus, nenormalus);
            studentai.clear();
            normalus.clear();
            nenormalus.clear();
            break;
        }
        if (!studentai.empty())
        {
            cout << "Norite įrašyti duomenis atspausdinant į ekraną ar į failą?: 1 - ekraną; 2 - failą" << endl;
            int skaicbudas;
            cin >> skaicbudas;
            cout << "Pasirinkite rikiavimo būdą:\n1 - pagal vardus\n2 - pagal pavardes\n3 - pagal galutinį balą (vid.)\n4 - pagal galutinį balą (med.)\nPasirinkimas: ";
            int sorting_choice;
            cin >> sorting_choice;
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
                cout << "Įrašymas sėkmingas. Rezultatai išsaugoti faile kursioku_duomenys.txt" << endl;
                failasr.close();
                auto end_writing = chrono::high_resolution_clock::now();
                chrono::duration<double> writeFile_time = end_writing - start_writing;
                cout << "Skaitymas iš failo truko: " << read_time.count() << " sekundes" << endl;
                cout << "Mokinių vidurkio/medianos skaičiavimas užtruko: " << process_time.count() << " sekundes" << endl;
                cout << "Įrašymas į failą truko: " << writeFile_time.count() << " sekundes" << endl;
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
            cout << "Studentų masyvas tuščias." << endl;
        }
    }
    cout << "Vector programos versija baigta. Paspauskite bet kokį mygtuką ir ENTER norint užbaigti programą..." << endl;
    int a;
    cin >> a;
    return 0;
}
