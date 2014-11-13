#include "biblio.h"


Probleme::Probleme(int n, string debut, string fin, string desc) : nas(n), dateDebut(debut), dateFin(fin), description(desc){}

Probleme::Probleme() : nas(0), dateDebut("N/A"), dateFin("N/A"), description("N/A"){}