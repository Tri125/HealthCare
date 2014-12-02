enum class typeVision
{
   CITOYEN, PROFESSIONNEL
};

void Trouver(string, typeVision);
Citoyen* ChargementCitoyen(vector<string> citoyen, typeVision);
list<RendezVous*> ChargementUtilisation(const string, string, typeVision);
list<Probleme*> ChargementProbleme(const string, string);