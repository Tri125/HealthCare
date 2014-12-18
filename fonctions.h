enum class typeVision
{
   CITOYEN, PROFESSIONNEL
};

//Un peu étrange de définir un attribut directement ici, mais nécessaire pour l'utilisation de paramêtre optionnelle avec valeur par défault.
Citoyen* Trouver(string, typeVision, bool indexation = 1);
Citoyen* ChargementCitoyen(vector<string> citoyen, typeVision);
list<RendezVous*> ChargementUtilisation(const string, string, typeVision);
list<Probleme*> ChargementProbleme(const string, string);
void ChargementPatient(const string, Professionnel*, list<RendezVous*>);