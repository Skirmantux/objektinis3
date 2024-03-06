v0.2.1 - tai dar labiau patobulinta mokinių galutinio pažymio skaičiuoklė. v0.2 naujienos:
-Skaitymas/rašymas į failus;
-Chronometras matuojantis, kiek laiko užima kiekviena operacija (read/write, process);
-Optimizuotas kodas;
-Galimybė užbaigti darbą per meniu;
-Mokinių rikiavimas pagal balus, vardus, pavardes;
-----------------------------------------------------------------------------------------------------------------------------
Benchmark'ų vidurkiai naudojant iš ankščiau sugeneruotus failus (naudojamas vidurkio galutinio balo skaičiavimo metodas):
1) studentai10000.txt:
Skaitymas - 0.793849 sekundės;
Rašymas - 0.0056045 sekundės;
Skaičiavimas - 0.085432 sekundės;
2) studentai100000.txt:
Skaitymas - 0.823045 sekundės;
Rašymas - 0.0209729 sekundės
Skaičiavimas - 0.729594 sekundės;
3) studentai1000000.txt:
Skaitymas - 0.860858 sekundės;
Rašymas - 0.163746 sekundės;
Skaičiavimas - 3.04418 sekundės;
Instrukcijos, kaip paleisti programą:

Source failas - ConsoleApplication1, jį turime atidaryti norint pažiūrėti kodą. Norint kompiliuoti kodą per Visual Studio, reikia atidaryti .sln failą /ConsoleApplication1 aplanke ir paspausti "Local Windows Debugger" mygtuką viršuje. Tada tereikia sekti instrukcijas ekrane norint naudoti programą.

DĖMĖSIO!!! - studentų (studentai10000.txt...) iš ankščiau sugeneruoti failai nėra įkeliami į repozitoriją, nes jų dydžiai yra per dideli. Prašome juos užsipildyti patiems arba atsisiųsti iš interneto.



