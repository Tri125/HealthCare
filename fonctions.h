enum class typeVision
{
   CITOYEN, PROFESSIONNEL
};

//Un peu �trange de d�finir un attribut directement ici, mais n�cessaire pour l'utilisation de param�tre optionnelle avec valeur par d�fault.
Citoyen* Trouver(string, typeVision, bool indexation = 1);
Citoyen* ChargementCitoyen(vector<string> citoyen, typeVision);
list<RendezVous*> ChargementUtilisation(const string, string, typeVision);
list<Probleme*> ChargementProbleme(const string, string);
void ChargementPatient(const string, Professionnel*, list<RendezVous*>);