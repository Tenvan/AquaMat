;
; AQUAMA T00 BIGCASE
;
; BREITE: 22CM
; TIEFE: 15CM
;
G21(UNITS IN MILLIMETERS) 
G90(ABSOLUTE PROGRAMMING) 
G17(XY PLANE) 


; Home Position
; SPINDEL AUS
M05
F1200
G00 X0 Y0 Z10

;#################################
;
; USB Buchse
;
;#################################
; Position anfahren
G90
G00 X50 Y40
; Buchse abfahren
M03
G91
G01 Z-10
G02 X0 Y0 I8 Z-1
G02 X0 Y0 I8 Z-1
G02 X0 Y0 I8 Z-1
G02 X0 Y0 I8 Z-1
G02 X0 Y0 I8 Z-1
G01 Z15
M05

;#################################
;
; Strom Buchse
;
;#################################
; Position anfahren
G90
G00 X35 Y40
; Buchse abfahren
M03
G91
G01 Z-10
G02 X0 Y0 I5 Z-1
G02 X0 Y0 I5 Z-1
G02 X0 Y0 I5 Z-1
G02 X0 Y0 I5 Z-1
G02 X0 Y0 I5 Z-1
G01 Z15
M05

;#################################
;
; Display ssd1306
;
;#################################
; Size: 2.3cm  x 3.4cm
; Position anfahren
G90
G00 X60 Y145
(Umriss abfahren)
M03
G91
(Start Position)
G00 Y18
G01 Z-10

(Ebene 1)
G01 Y-36 Z-0.25
G01 X-25 Z-0.25
G01 Y36 Z-0.25
G01 X25 Z-0.25
(Ebene 2)
G01 Y-36 Z-0.25
G01 X-25 Z-0.25
G01 Y36 Z-0.25
G01 X25 Z-0.25
(Ebene 3)
G01 Y-36 Z-0.25
G01 X-25 Z-0.25
G01 Y36 Z-0.25
G01 X25 Z-0.25
(Ebene 4)
G01 Y-36 Z-0.25
G01 X-25 Z-0.25
G01 Y36 Z-0.25
G01 X25 Z-0.25
(Ebene 5)
G01 Y-36 Z-0.25
G01 X-25 Z-0.25
G01 Y36 Z-0.25
G01 X25 Z-0.25

G01 Z15
M05

M30

;#################################
;
; Case mit Kopf abfahren
;
;#################################
;
; Position anfahren
;
G90
G00 X0 Y0 Z10

; Case abfahren
G91
G00 X150
G00 Y220
G00 X-150
G00 Y-220
G90

; Home
G90
G00 X0 Y0 Z10
G91

; Home
G90
G00 X0 Y0

; Programmende
; M02

; SPINDEL LANGSAM
; S100 M03
; G03 X0 Y0 I20 J0
; G03 X0 Y0 Z20 I20 J0
; G03 X0 Y0 I20 J0

; SPINDEL AUS
; S000 M03
; G01 Z0

; SPINDEL SCHNELL
; S900 M03

; G02 X0 Y0 I-20 J0
; G02 X0 Y0 Z -20 I-20 J0
; G02 X0 Y0 I-20 J0
; G01 Z0

; G-Befehle (Wegfunktionen)
;
; G00: Im Eilgang eine Position mit den Vorschub Achsen anfahren
; G01: In normaler Geschwindigkeit eine Position anfahren (lineare Interpolation)
; G02: Vorschub mit Kreisbogen, im Uhrzeigersinn (Kreis Interpolation)
; G03: Vorschub mit Kreisbogen, gegen den Uhrzeigersinn
; G04: Verweilzeit
; G05: Spline Definition
; G06: Spline Interpolation
; G09: Genauhalt
; G14: Polarkoordinatensystem, absolut
; G15: Polarkoordinatensystem, relativ
; G17: X-Y Ebene wählen
; G18: Z-X Ebene wählen
; G19: Y-Z Ebene wählen
; G20: Frei definierbare Ebene wählen
; G28: HOME Position anfahren
; G33: Gewindeschneiden mit konstanter Steigung
; G34: Gewindeschneiden mit zunehmender Steigung
; G35: Gewindeschneiden mit abnehmender Steigung
; G40: Aufheben aller Werkzeugbahnkorrekturen
; G41: Werkzeugbahnkorrektur in Vorschubrichtung links
; G42: Werkzeugbahnkorrektur in Vorschubrichtung rechts
; G43: Werkzeugkorrektur positiv
; G44: Werkzeugkorrektur negativ
; G53: Löschen der Nullpunktverschiebung
; G54-G59: Nullpunktverschiebungen 1-6
; G80: Zyklen Lölschen
; G81-G89: Bohrzyklen
; G90: Absolute Koordinatenangaben im aktuellen Koordinatensystem
; G91: Relative Koordinatenangaben im aktuellen Koordinatensystem
; G92: Bezugspunktverschiebung – Speicher setzen
; G94: Vorschub in mm/min
; G95: Vorschub in mm/U
; G96: Konstante Schnittgeschwindigkeit (Bitte G92 Spindeldrehzahlbegrenzung setzen)
; G97: Konstante Spindeldrehzahl in U/min

; M-Befehle (Schaltfunktionen):
; M-Befehle, auch M-Funktionen (Miscellaneous Functions) genannt dienen zum Zu- und Abschalten von Maschinenfunktionen.
;
; M00: Programmhalt (Spindel, Kühlmittel, Vorschub aus)
; M01: Wahlweiser Halt
; M02: Programm Ende
; M03: Spindel Ein: Im Uhrzeigersinn (Rechtslauf)
; M04: Spindel Ein: Gegen den Uhrzeigersinn (Linkslauf)
; M05: Spindel Stop
; M06: Werkzeugwechsel durchführen (Werkzeug muss vorher eingemessen worden sein)
; M07: Kühlmittel 2 Ein
; M08: Kühlmittel 1 Ein
; M09: Kühlmittel Aus
; M10: Klemmung Ein
; M11: Klemmung Aus
; M13: Spindel Ein, Rechtslauf und Kühlmittel Ein
; M14: Spindel Ein, Linkslauf und Kühlmittel Ein
; M19: Spindel Stop bei bestimmter Winkellage
; M030: Programm-Ende, Zurück zum Programm-Anfang
; M031: Verriegelung aus
; M40 – M45: Getriebestufen Wahl
; M60: Werkstückwechsel
; M68: Werkstück spannen
; M69: Werkstück ausspannen

; Überblick über alle Adressbefehle:
; Nach der Norm DIN 66025 / ISO 6983 gibt es folgende Addressbuchstaben:
;
; A	Absolut oder Inkrementposition um die X-Achse (Drehen um X)
; B	Absolut oder Inkrementposition um die Y-Achse (Drehen um Y)
; C	Absolut oder Inkrementposition um die Z-Achse (Drehen um Z)
; D	Werkzeugkorrekturfaktor
; E	Zweiter Vorschub
; F	Vorschub
; G	Verfahrbefehle (G0)
; H	Werkzeuglängenkorrektur
; I	Definiert den Kreisbogenmittelpunkt auf der x-Achse bei den Befehlen G02 und G03
; J	Definiert den Kreisbogenmittelpunkt auf der y-Achse bei den Befehlen G02 und G03
; K	Definiert den Kreisbogenmittelpunkt auf der z-Achse bei den Befehlen G02 und G03
; L	Fixed Cycle Loop Count
; M	Zusatzfunktionen (Miscellaneous) (z.B. Kühlmittel an/aus, Motorspindel an/aus… )
; N	Satznummer
; O	Programmname
; P	Zusätzlicher Parameter für manche G und M Befehle
; Q	Zusätzlicher Parameter für manche G Befehlen
; R	Parameter, z.B. Radius bei Kreisbahn (Radius)
; S	Spindeldrehzahl
; T	Werkzeugauswahl
; U	Inkrement X
; V	Inkrement Y
; W	Inkrement Z
; X	Absolut oder Inkrementposition in Richtung der X-Achse
; Y	Absolut oder Inkrementposition in Richtung der Y-Achse
; Z	Absolut oder Inkrementposition in Richtung der Z-Achse
; $	Satzende