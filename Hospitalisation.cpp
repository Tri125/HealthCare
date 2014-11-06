#include "biblio.h"


Hospitalisation::Hospitalisation()
{
}

Hospitalisation::Hospitalisation(int n, string code, string etab, string dDebut, string dFin, int chamb) : RendezVous(n, code, etab, dDebut), dateFin(dFin), chambre(chamb){}