# v1.0 Veikimo Įvertinimas

## Kompiuterio Specifikacijos:
- CPU: Intel Core i5-12450H
- GPU: NVIDIA RTX 4060 Laptop GPU
- RAM: 16 GB DDR5
- SSD: 2TB NVMe KINGSTON SKC3000

## Testavimo Duomenys ir Rezultatai

### Testas Nr. 1 - Vektoriai

| Vektoriai | # Studentų | Skaitymas (s) | Rūšiavimas (s) | Skaidymas (s) |
|-----------|-------------|---------------|----------------|---------------|
| 1000      | 0.0022777   | 0.0001363     | 0.0001160      |
| 10000     | 0.0236244   | 0.0012293     | 0.0010826      |
| 100000    | 0.2216030   | 0.0161473     | 0.0010826      |
| 1000000   | 2.2053800   | 0.1892920     | 0.2374710      |
| 10000000  | 22.8862000  | 2.3103800     | 2.7045500      |

### Testas Nr. 1 - Deque

| Deque     | # Studentų | Skaitymas (s) | Rūšiavimas (s) | Skaidymas (s) |
|-----------|-------------|---------------|----------------|---------------|
| 1000      | 0.0037541   | 0.0001979     | 0.0001114      |
| 10000     | 0.223408    | 0.0011828     | 0.0008896      |
| 100000    | 0.2275090   | 0.0148839     | 0.0270712      |
| 1000000   | 2.2069500   | 0.1862820     | 0.1672080      |
| 10000000  | 22.5660000  | 2.2550900     | 2.2518800      |

### Testas Nr. 1 - List

| List      | # Studentų | Skaitymas (s) | Rūšiavimas (s) | Skaidymas (s) |
|-----------|-------------|---------------|----------------|---------------|
| 1000      | 0.0022424   | 0.0001336     | 0.0001521      |
| 10000     | 0.0219628   | 0.0011320     | 0.0031113      |
| 100000    | 0.2220000   | 0.0150706     | 0.0131362      |
| 1000000   | 2.2095000   | 0.1879120     | 0.1137770      |
| 10000000  | 22.6014000  | 2.2339300     | 1.2377700      |

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

## Perspėjimas
(WARNING GitHub Syntax)
Jei atliksite benchmark'us patys, prašome kartoti testus kuo daugiau ir imti vidurkį, nes dauguma laiko skirtumo atidarant/uždarant ir modifikuojant elementus failuose užima operacinė sistema, taip pat ji užima resursus, kuriuos galima būtų naudoti atidarant failus, todėl tai yra nenuspėjama. Testuojant pirmą kart buvo išrinkta greičiausia universali strategija ir su ja testuojami skirtingi konteineriai!!!

## Konteinerių Palyginimas
Remiantis vidutiniais laikais, pastebima, kad vektorius yra labiausiai efektyvus skaitymo procesas, tačiau jis reikalauja daugiau laiko rūšiuojant palyginus su list ir deque. List, priešingai, rūšiuojasi greičiau, bet skaitymo procesas užtrunka ilgiau lyginant su vektoriumi ir dvipusiu sąrašu. Dvipusis sąrašas pasižymi tarpiniu elgesiu, kai skirstymas į "nenormalius" ir "normalius" nevyksta dažnai. Studentų klasifikavimas į nenormalius trunka trumpiausiai naudojant deque, o ilgiausiai naudojant list. Padidėjus duomenų kiekiui, studentų klasifikavimas į nenormalius trunka ilgiau visuose konteineriuose, tačiau dvipusis sąrašas pasirodo greitesnis nei vektorius ir list. Didžiausias studentų skaidymo laikas yra su 100 000 00 duomenų, o mažiausias su 1000 duomenų. Vektorius gali patirti didelį veikimo spartos sumažėjimą dė
