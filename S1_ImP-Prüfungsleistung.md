---
title: Notizen - Pruefungsleistung Imperative Programmierung - BA Medieninformatik Semester 1
author: Paul Weibbrecht, Sebastian Schöneich
version: 1.0
date: 2024-01-15
---
# S1_ImP-Prüfungsleistung

## Grundaufgabe
Simulation einer Paketstation über 2 Wochen hinweg
* Es sollen pro Echtzeitsekunde 10 Minuten in der Simulation vergehen
> 1-4 Uhr sollen jedoch in einer Echtzeitsekunde vergehen
* Zusätzlich hierzu soll es einen "Turbo-Knopf" geben, der die Geschwindigkeit auf 100 Minuten erhöht
* Montag bis Freitag Entleerungen 10:30 und 18:30
* Samstag Entleerungen 14:00
* Sonntags KEINE Entleerung
* Entleerung selbst dauert 10 Minuten (also eine Echtzeitsekunde)
> -> Innerhalb dieser Zeit können die Kunden die Paketstation NICHT benutzen!
* 
* Pro Echtzeitsekunde können 2 bis 10 Paket-Interaktionen geschehen
> -> Median sind 5 Pakete

* Pakete sollen ihrer entsprechenden Größe ein Fach bekommen
* Ist die Größe vollständig belegt, wird das nächstgrößere Fach belegt
* Sind alle passenden belegt, wird der Kunde weggeschickt
* Kunden sind bereit bis zu 20 Minuten warten, wenn ein Entleerungstermin bevor steht.
> -> die Entleerungszeit wird dann auch noch gewartet wenn das der Fall ist

* Mitarbeiter führt erst die Entleerung aus, dann befüllt er
* Befüllt genau so wie die Kunden
* Wenn die Paketstation voll ist, nimmt der Mitarbeiter die zu befüllenden Pakete für das nächste Mal mit
* Pakete werden innerhalb von 4 Werktagen entweder abgeholt oder durch Mitarbeiter zurückgesendet
* Möglichkeit, dass Kunden an Kunden, die dieselbe Station benutzen versenden
> -> in diesem Fall muss aber erst ein Mitabeiter kommen, danach ist das Paket zur Abholung geflagt

* 250 Kunden
* Durchschnittlich erhält jeder Kunde 2 PAKETE PRO WOCHE

Trafficzeiten:
Zeit | Traffic-Modifikator
:---:|:------------------:
0    | 1%
1-4  | 1%
5    | 1%
6    | 15%
7    | 100%
8    | 150%
9    | 100%
10   | 50%
11   | 50%
12   | 100%
13   | 100%
14   | 50%
15   | 50%
16   | 100%
17   | 150%
18   | 100%
19   | 50%
20   | 50%
21   | 15%
22   | 1%
23   | 1%

Fächer:
Fachgröße | Anzahl
:--------:|:-----:
XS        | 4
S         | 5
M         | 21
L         | 10
XL        | 2

* Pseudo-Graphishe Konsolenausgabe