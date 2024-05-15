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
    vector<Studentas> studentai1;
    vector<Studentas> studentai2;
    int pasirinkimas;
    chrono::duration<double> process_time;
    chrono::duration<double> read_time;
    cout << "Pasirinkite balø ávedimo metodà/generavimo funkcijà:\n1. Ávesti rankiniu bûdu\n2. Sugeneruoti atsitiktinius balus\n3. Sugeneruoti balus, vardus ir pavardes\n4. Skaitymas ið failo.\n5. Baigti programà.\n6. Generuoti studentø failà.\n7. Strategijø testavimas.\nPasirinkimas: ";
    while (true) {
        try {
            cin >> pasirinkimas;
            if (pasirinkimas < 1 || pasirinkimas > 7) {
                throw invalid_argument("Netinkama ávestis.");
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
        if (pasirinkimas == 1) {
            while (true) {
                try {
                    cout << "Áveskite studento vardà ir pavardæ. Norëdami baigti ávedimà, áveskite -1: ";
                    cin >> stud.vardas;
                    if (stud.vardas == "-1")
                        break;
                    if (ContainsNumbers(stud.vardas)) {
                        throw invalid_argument("Vardas negali turëti skaièiø. Praðome ávesti vardà be skaièiø.");
                    }
                    cin >> stud.pavarde;
                    if (stud.pavarde == "-1")
                        break;
                    if (ContainsNumbers(stud.pavarde)) {
                        throw invalid_argument("Pavardë negali turëti skaièiø. Praðome ávesti pavardæ be skaièiø.");
                    }
                    cout << "Áveskite namø darbø rezultatus. Norëdami baigti ávedimà, áveskite -1: ";
                    while (true) {
                        double namudarburez;
                        if (!(cin >> namudarburez)) {
                            cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (namudarburez == -1)
                            break;
                        if (namudarburez >= 0 && namudarburez <= 10) {
                            stud.namudarburez.push_back(namudarburez);
                        }
                        else {
                            cout << "Netinkama ávestis. Áveskite skaièiø tarp 0 ir 10." << endl;
                        }
                    }
                    double egzaminorez;
                    cout << "Áveskite egzamino rezultatà: ";
                    cin >> egzaminorez;
                    if (egzaminorez < 0 || egzaminorez > 10) {
                        throw out_of_range("Netinkama ávestis.");
                    }
                    stud.namudarburezsuma = accumulate(stud.namudarburez.begin(), stud.namudarburez.end(), 0.0);
                    stud.vidurkis = stud.namudarburezsuma / stud.namudarburez.size();
                    stud.galutinisbalasvidurkis = stud.vidurkis * 0.4 + egzaminorez * 0.6;
                    studentai.push_back(stud);
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
                cout << "Áveskite studento vardà ir pavardæ. Norëdami baigti ávedimà, áveskite -1: ";
                cin >> stud.vardas;
                if (stud.vardas == "-1")
                    break;
                cin >> stud.pavarde;
                cout << "Generuojami atsitiktiniai balai uþ namø darbus..." << endl;
                for (int i = 0; i < 5; ++i) {
                    stud.namudarburez.push_back(GenerateRandomGrade());
                }
                stud.egzaminorez = GenerateRandomGrade();
                stud.namudarburezsuma = accumulate(stud.namudarburez.begin(), stud.namudarburez.end(), 0.0);
                stud.vidurkis = stud.namudarburezsuma / stud.namudarburez.size();
                stud.galutinisbalasvidurkis = stud.vidurkis * 0.4 + stud.egzaminorez * 0.6;
                stud.mediana = Mediana(stud.namudarburez);
                stud.galutinisbalasmediana = stud.mediana * 0.4 + stud.egzaminorez * 0.6;
                studentai.push_back(stud);
                stud.namudarburez.clear();
            }
        }
        else if (pasirinkimas == 3) {
            cout << "Generuojami balai, vardai ir pavardës ir studentø kiekis spausdinimui" << endl;
            int studentukiekis;
            studentukiekis = rand() % 200;
            for (int i = 0; i < studentukiekis; ++i) {
                Studentas stud;
                for (int j = 0; j < 5; ++j) {
                    stud.namudarburez.push_back(GenerateRandomGrade());
                }
                stud.egzaminorez = GenerateRandomGrade();
                stud.vardas = GeneruotiVardus();
                stud.pavarde = GeneruotiPavardes();
                stud.namudarburezsuma = accumulate(stud.namudarburez.begin(), stud.namudarburez.end(), 0.0);
                stud.vidurkis = stud.namudarburezsuma / stud.namudarburez.size();
                stud.galutinisbalasvidurkis = stud.vidurkis * 0.4 + stud.egzaminorez * 0.6;
                stud.mediana = Mediana(stud.namudarburez);
                stud.galutinisbalasmediana = stud.mediana * 0.4 + stud.egzaminorez * 0.6;
                studentai.push_back(stud);
                stud.namudarburez.clear();
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
                        if (!(failas >> stud.vardas >> stud.pavarde))
                            break;
                        double grade;
                        for (int i = 0; i < namudarbai; i++) {
                            failas >> grade;
                            stud.namudarburez.push_back(grade);
                        }
                        failas >> stud.egzaminorez;
                        stud.namudarburezsuma = accumulate(stud.namudarburez.begin(), stud.namudarburez.end(), 0.0);
                        stud.vidurkis = stud.namudarburezsuma / stud.namudarburez.size();
                        stud.galutinisbalasvidurkis = stud.vidurkis * 0.4 + stud.egzaminorez * 0.6;
                        stud.mediana = Mediana(stud.namudarburez);
                        stud.galutinisbalasmediana = stud.mediana * 0.4 + stud.egzaminorez * 0.6;
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
            cout << "Programa baigia darbà." << endl;
            break;
        }
        else if (pasirinkimas == 6) {
            auto veikimo_pradzia = chrono::high_resolution_clock::now();
            cout << "Pasirinkite kiek studentø norite sugeneruoti:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:";
            int studentugen;
            cin >> studentugen;
            auto start_read = chrono::high_resolution_clock::now();
            string filename;
            int studentuskaicius;
            switch (studentugen) {
            case 1:
                filename = "studentaic1000.txt";
                studentuskaicius = 1000;
                break;
            case 2:
                filename = "studentaic10000.txt";
                studentuskaicius = 10000;
                break;
            case 3:
                filename = "studentaic100000.txt";
                studentuskaicius = 100000;
                break;
            case 4:
                filename = "studentaic1000000.txt";
                studentuskaicius = 1000000;
                break;
            case 5:
                filename = "studentaic10000000.txt";
                studentuskaicius = 10000000;
                break;
            default:
                NetinkamaIvestis();
                return;
            }
            GeneruotiFaila(filename, studentuskaicius);
            auto end_read = chrono::high_resolution_clock::now();
            chrono::duration<double> read_time = end_read - start_read;
            cout << "Failo kurimas ir jo uzdarymas uztruko: " << read_time.count() << " sekundes" << endl;
            cout << "Kurá failà norite skaityti?:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:" << endl;
            int failopasirinkimas;
            cin >> failopasirinkimas;
            string readFilename;
            switch (failopasirinkimas) {
            case 1:
                readFilename = "studentaic1000.txt";
                break;
            case 2:
                readFilename = "studentaic10000.txt";
                break;
            case 3:
                readFilename = "studentaic100000.txt";
                break;
            case 4:
                readFilename = "studentaic1000000.txt";
                break;
            case 5:
                readFilename = "studentaic10000000.txt";
                break;
            default:
                NetinkamaIvestis();
                return;
            }
            vector<Studentas> studentai;
            int namudarbai = 5;
            readAndProcessData(readFilename, studentai, namudarbai);
            vector<Studentas> normalus;
            vector<Studentas> nenormalus;
            partitionStudents3(studentai, normalus, nenormalus);
            auto veikimo_pabaiga = chrono::high_resolution_clock::now();
            chrono::duration<double> process_time = veikimo_pabaiga - veikimo_pradzia;
            cout << "Normalus studentai spausdinami á failà 'normalûs.txt'." << endl;
            PrintStudents(normalus);
            cout << "Nenormalûs studentai spausdinami á failà 'nenormalûs.txt'." << endl;
            PrintStudents(nenormalus);
            cout << "Programa viso uztruko " << process_time.count() << " sekundes" << endl;
        }
        else if (pasirinkimas == 7) {
            cout << "Bandoma pirma strategija..." << endl;
            cout << "Kurá failà norite skaityti?:\n1. 1 000\n2. 10 000\n3. 100 000\n4. 1 000 000\n5. 10 000 000\nPasirinkimas:" << endl;
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
                cout << "Netinkamas pasirinkimas. Praðome ávesti tinkamà pasirinkimà: " << endl;
                return 1;
            }
            vector<Studentas> studentai;
            int namudarbai = 5;
            readAndProcessData(filename, studentai, namudarbai);
            cout << "Kaip norite rusiuoti studentø vektoriø?\n1. Pagal vidurká\n2. Pagal medianà\nPasirinkimas: ";
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
            vector<Studentas> studentai2;
            readAndProcessData(filename, studentai2, namudarbai);
            sortStudents(studentai2, sortpasirinkimas);
            vector<Studentas> nenormalus2;
            partitionStudents2(studentai2, nenormalus2);
            studentai2.clear();
            nenormalus2.clear();
            cout << "Bandoma treèia strategija..." << endl;
            vector<Studentas> studentai3;
            readAndProcessData(filename, studentai3, namudarbai);
            sortStudents(studentai3, sortpasirinkimas);
            vector<Studentas> normalus3;
            vector<Studentas> nenormalus3;
            partitionStudents3(studentai3, normalus3, nenormalus3);
            break;
        }
        if (!studentai.empty())
        {
            cout << "Norite áraðyti duomenis atspausdinant á ekranà ar á failà?: 1 - ekranà; 2 - failà" << endl;
            int skaicbudas;
            cin >> skaicbudas;
            cout << "Pasirinkite rikiavimo bûdà:\n1 - pagal vardus\n2 - pagal pavardes\n3 - pagal galutiná balà (vid.)\n4 - pagal galutiná balà (med.)\nPasirinkimas: ";
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
                for (const auto& stud : studentai)
                {
                    failasr << setw(15) << stud.pavarde << setw(15) << stud.vardas << setw(30) << fixed << setprecision(2) << stud.galutinisbalasvidurkis << setw(30) << fixed << setprecision(2) << stud.galutinisbalasmediana << endl;
                }
                cout << "Áraðymas sëkmingas. Rezultatai iðsaugoti faile kursioku_duomenys.txt" << endl;
                failasr.close();
                auto end_writing = chrono::high_resolution_clock::now();
                chrono::duration<double> writeFile_time = end_writing - start_writing;
                cout << "Skaitymas ið failo truko: " << read_time.count() << " sekundes" << endl;
                cout << "Mokiniø vidurkio/medianos skaièiavimas uþtruko: " << process_time.count() << " sekundes" << endl;
                cout << "Áraðymas á failà truko: " << writeFile_time.count() << " sekundes" << endl;
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
            cout << "Studentø masyvas tuðèias." << endl;
        }
    }
    cout << "Vector programos versija baigta. Paspauskite bet koká mygtukà ir ENTER norint uþbaigti programà..." << endl;
    int a;
    cin >> a;
    return 0;
}
