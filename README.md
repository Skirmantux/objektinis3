# v1.0

## Pakeitimai:
- Optimizavimo strategijų testavimas
- Konteinerių studentams testavimas (deque, vector, list)
- Dauguma strategijų testavimo kodo sudėtos į funkcijas, dėl optimizavimo
- Makefile
- Paleidžiami .exe failai
- Apvalyta repozitorija

## Kompiuterio Specifikacijos:
- CPU: Intel Core i5-12450H
- GPU: NVIDIA RTX 4060 Laptop GPU
- RAM: 16 GB DDR5
- SSD: 2TB NVMe KINGSTON SKC3000

## Ankstesnių versijų aprašymai:
### v0.4.1 naujienos:
- Galimybė generuoti atsitiktinius studentų failus.
- Galimybė pasirinkti kokio dydžio studentų failų norite.
- Galimybė sugeneruotus failus atidaryti.
- Galimybė sugeneruotus failus skirstyti į "normalius" ir "nenormalius" studentus, t.y studentus kurių vidurkiai yra daugiau arba lygūs 5 arba mažesni nei 5.
- Galimybė skirstytus studentus išspausdinti į atskirus failus.
- Galimybė matuoti programos veikimo ir procesų trukmę.

### v0.3

- Kodas perkeltas į header ir .cpp implementavimo failus;
- Naudojamas exception handling neteisingų įvesčių atveju; 
- Teksto failų tikrinimas;

Source failas - ConsoleApplication1, jį turime atidaryti norint pažiūrėti kodą. Norint kompiliuoti kodą per Visual Studio, reikia atidaryti .sln failą /ConsoleApplication1 aplanke ir paspausti "Local Windows Debugger" mygtuką viršuje. Tada tereikia sekti instrukcijas ekrane norint naudoti programą.

DĖMĖSIO!!! - studentų (studentai10000.txt...) iš ankščiau sugeneruoti failai nėra įkeliami į repozitoriją, nes jų dydžiai yra per dideli. Prašome juos užsipildyti patiems arba atsisiųsti iš interneto.

### v0.2.1 - tai dar labiau patobulinta mokinių galutinio pažymio skaičiuoklė. v0.2 naujienos:
- Skaitymas/rašymas į failus;
- Chronometras matuojantis, kiek laiko užima kiekviena operacija (read/write, process);
- Optimizuotas kodas;
- Galimybė užbaigti darbą per meniu;
- Mokinių rikiavimas pagal balus, vardus, pavardes;

### v0.1.1 - tai patobulinta v0.1 vektorių implementacija.
- Pridėta naujų random skaičių generavimo funkcija.
- Pridėtas vektoriaus patikrinimas, neišeis vietoj skaičiaus įrašyti raidės ir užcrashinti programą.
- Vietoj bubble sort naudojama sort() funkcija.
- Vietoj for ciklo naudojama accumulate() funkcija.
- Pakeistos ciklo ribos, dabar ciklas baigsis tik tada, kai vartotojas įves -1. Neprašoma vartotojo įvesti namų darbų ir studentų skaičiaus.

### v.pradinė
pirmoji prototipinė mokinių įvertinimo skaičiavimo ir spausdinimo versija. Ji ateityje bus tobulinama ir naudojama kaip pagrindas kitoms versijoms. Kaip atidaryti programą ir ją kompiliuoti yra aprašyta readme.md faile.

## Testavimo Duomenys ir Rezultatai

### Testas Nr. 1 - Vektoriai

| # Studentų| Skaitymas (s)| Rūšiavimas (s) | Skaidymas (s) 
|-----------|--------------|----------------|----------------
| 1000      | 0.0022777    | 0.0001363      | 0.0001160      
| 10000     | 0.0236244    | 0.0012293      | 0.0010826      
| 100000    | 0.2216030    | 0.0161473      | 0.0010826      
| 1000000   | 2.2053800    | 0.1892920      | 0.2374710      
| 10000000  | 22.8862000   | 2.3103800      | 2.7045500      

### Testas Nr. 1 - Deque

| # Studentų| Skaitymas (s)| Rūšiavimas (s)  | Skaidymas (s) 
|-----------|--------------|-----------------|-----------------
| 1000      | 0.0037541    | 0.0001979       | 0.0001114      
| 10000     | 0.223408     | 0.0011828       | 0.0008896      
| 100000    | 0.2275090    | 0.0148839       | 0.0270712      
| 1000000   | 2.2069500    | 0.1862820       | 0.1672080      
| 10000000  | 22.5660000   | 2.2550900       | 2.2518800      

### Testas Nr. 1 - List

| List      | # Studentų  | Skaitymas (s)  | Rūšiavimas (s) 
|-----------|-------------|----------------|---------------
| 1000      | 0.0022424   | 0.0001336      | 0.0001521      
| 10000     | 0.0219628   | 0.0011320      | 0.0031113      
| 100000    | 0.2220000   | 0.0150706      | 0.0131362      
| 1000000   | 2.2095000   | 0.1879120      | 0.1137770      
| 10000000  | 22.6014000  | 2.2339300      | 1.2377700      

## Veikimo Analizė

### Duomenų Skaitymas:
- Skaitymas naudojant list konteinerį yra greičiausias, tačiau mažesniuose failuose jo naudotojas neturėtų pastebėti skirtumo.

### Duomenų Rūšiavimas:
- Vektorių konteineris rūšiuoja studentus greičiausiai, nes jis gali prieiti įrašus atsitiktinai, kas yra labai padeda rūšiavimo algoritmui.
- List lėtesnis, nes jame elementus reikia prieiti iš eilės.
- Deque lėčiausias, nes nėra tam sukurtas.

### Studentų Skaidymas:
- List konteineris yra efektyviausias, nes gali įterpti ir pašalinti elementus be kitų perkėlimo.
- Deque yra antras, o vector konteineris yra lėčiausias, nes reikalauja daugiausia elementų perkėlimo.

> [!WARNING]  
>Jei atliksite benchmark'us patys, prašome kartoti testus kuo daugiau ir imti vidurkį, nes dauguma laiko skirtumo atidarant/uždarant ir modifikuojant elementus failuose užima operacinė sistema, taip pat ji užima resursus, kuriuos galima būtų naudoti atidarant failus, todėl tai yra nenuspėjama. Testuojant pirmą kart buvo išrinkta greičiausia universali strategija ir su ja testuojami skirtingi konteineriai!!!

## Konteinerių Palyginimas
Remiantis vidutiniais laikais, pastebima, kad vektorius yra labiausiai efektyvus skaitymo procesas, tačiau jis reikalauja daugiau laiko rūšiuojant palyginus su list ir deque. List, priešingai, rūšiuojasi greičiau, bet skaitymo procesas užtrunka ilgiau lyginant su vektoriumi ir dvipusiu sąrašu. Dvipusis sąrašas pasižymi tarpiniu elgesiu, kai skirstymas į "nenormalius" ir "normalius" nevyksta dažnai. Studentų klasifikavimas į nenormalius trunka trumpiausiai naudojant deque, o ilgiausiai naudojant list. Padidėjus duomenų kiekiui, studentų klasifikavimas į nenormalius trunka ilgiau visuose konteineriuose, tačiau dvipusis sąrašas pasirodo greitesnis nei vektorius ir list. Didžiausias studentų skaidymo laikas yra su 100 000 00 duomenų, o mažiausias su 1000 duomenų. Vektorius gali patirti didelį veikimo spartos sumažėjimą dėl papildomo atminties kopijavimo. List gali būti geriau tinkamas pasirinkimas, jei didelės atminties reikalavimai, bet veikimo greitis nėra kritiškai svarbus. Deque gali būti efektyvesnis pasirinkimas nei vektorius dėl jo efektyvaus atminties manipuliavimo.

# Kaip paleisti kodą?

> [!NOTE]  
> Šią instrukciją Windows OS reikia sekti tik tada, kai neturite iš repozitorijos atsiųstų .exe failų!

## Makefile

> [!WARNING]  
> Makefile nėra palaikomas Windows sistemose, todėl yra atskiri žingsniai kaip jį įsidiegti.

### Windows

1. Nueikite į šią svetainę: [GNU Make for Windows](https://sourceforge.net/projects/gnuwin32/files/make/3.81/)
2. Atsisiųskite naujausią versiją.
3. Susikonfigūruokite. Jei sunku suprasti, kaip ką daryti, gali padėti YouTube vaizdo įrašas: [Makefile Installation Tutorial](https://www.youtube.com/watch?v=taCJhnBXG_w)
4. Atsisiunčiame projekto .zip failą, jį išskleidžiame.
5. Atidarius projekto aplankalą, jame paspaudžiame dešinįjį pelės mygtuką ir paspaudžiame "Atidaryti terminalą" (CMD)
6. Parašome "make"
7. Atsiras .exe failai, kuriuos paleidus galite naudotis programa.

> [!WARNING]  
> Studentų failai nėra įdedami į GitHub repozitoriją. Prašome juos susigeneruoti naudojantis programa!

