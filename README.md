# ImP_Pruefungsleistung

## Berechnung der Paketwahrscheinlichkeit

Es wird jede Minute berechnet, ob ein Kunde ein Paket erhält oder nicht.
Diese Chance wird pro Kunde für jede Minute berechnet.
Der Wahrscheinlichkeitsparameter entsteht aus folgender Rechnung:
> 500 / 2520000 = 0,000198\
> Berechnet wurde dieser aus Angaben der Aufgabenstellung:
> * Jeder der 250 Kunden erhält durchschnittlich 2 Pakete die Woche (500 = 250 * 2)
> * Es gibt 7 Tage die Woche, unterteilt in 24 Stunden, unterteilt in 60 Minuten für jeden Kunden des Paketshops (2520000 = 7 * 24 * 60 * 250)

* Diese Berechnung wird im Hintergrund zwei mal durchgeführt, einmal für die Chance, dass ein Kunde etwas in die Paketstation hereinlegt, ein weiteres Mal, ob der Mitarbeiter ein Paket in die Paketstation legt.

## Entscheidung Externer Empfänger vs Interner Empfänger
* 80% Externer - 20% Interner

## Module

* []DEBUG: Generierte Paket-Interaktionen in eine TXT-File (S)
* []Turbo-Knopf (P)
* []Pause-Knopf (P/S)
* []Initialisierung (P)
* []1-4 Uhr Time-Skip (P)
* []Kunden müssen warten (P)
* [x]Entnahme (S)
* [x]Einlage (S)
> * Zuweisung des Paketfachs
* []Mitarbeiter (S)
> * Entnahme_Mitarbeiter
> * Spezialfall - Paket ist intern
> * Einlage_Mitarbeiter
* [x]Paket-MHD (S)
* []Aktualisierung der Oberfläche (Ausgabe in eine txt-file) (P)
* []Ausgabe der Oberfläche (Auslesung der txt-file) (P)
* []Zusammenführung (P)

## ZUSATZ - Module
* []Pakete, wenn sie passen, noch in gleiche Fächer legen

## ZUSATZ
* [x]Fachgrößen nach Fibonacci-Folge:
> XS = 1 \
> S = 2 \
> M = 3 \
> L = 5 \
> XL = 8

* [x]Mitarbeiter/Externer recipientID
> 300
