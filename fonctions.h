enum class typeVision
{
   CITOYEN, PROFESSIONNEL
};

void Trouver(string, typeVision);
Citoyen* ChargementCitoyen(vector<string> citoyen, typeVision);
list<RendezVous*> ChargementRendezVous(vector<string> citoyen);
list<Probleme*> ChargementProbleme(vector<string> citoyen);