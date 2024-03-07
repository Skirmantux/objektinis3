#include "MokiniuProcessing.h"
string GeneruotiVardus()
{
    vector<string> vardai = { "Jonas", "Petras", "Antanas", "Marius", "Tomas" };
    return vardai[rand() % vardai.size()];
}

string GeneruotiPavardes()
{
    vector<string> pavardes = { "Kazlauskas", "Petrauskas", "Stankevièius", "Gudelis", "Lukğys" };
    return pavardes[rand() % pavardes.size()];
}

bool vardolyginimas(const Studentas& a, const Studentas& b)
{
    return a.vardas < b.vardas;
}

bool pavardeslyginimas(const Studentas& a, const Studentas& b)
{
    return a.pavarde < b.pavarde;
}

bool vidurkiolyginimas(const Studentas& a, const Studentas& b)
{
    return a.galutinisbalasvidurkis < b.galutinisbalasvidurkis;
}

bool medianoslyginimas(const Studentas& a, const Studentas& b)
{
    return a.galutinisbalasmediana < b.galutinisbalasmediana;
}