#include "biblio.h"

void Trouver(string id, typeVision vue)
{
   const char SEPARATING_SYMBOL = ';';
   const string FICHIER_POPULATION = "population.txt";
   const string FICHIER_PROBLEME = "problèmes.txt";
   const string FICHIER_UTILISATION = "utilisations.txt";
   bool isFound = false;
   //const int NOMBRE_CHAMPS = 3;
   string nomFichier = FICHIER_POPULATION;
   string ligneCourante;
   ifstream ficIn;
   vector<string> human;
   stringstream ss;
   string data;

   ficIn.open(FICHIER_POPULATION);
   while (!ficIn.is_open())
   {
      cout << "Erreur de lecture.\n";
      cout << "Veuillez entrer le nom du fichier contenant la population : ";
      cin >> nomFichier;
      ficIn.open(nomFichier);
   }
   while (ficIn.good())
   {
      getline(ficIn, ligneCourante);
      ss << ligneCourante;
      while (getline(ss, data, SEPARATING_SYMBOL))
      {
         human.push_back(data);
      }
      if (vue == typeVision::CITOYEN)
      {
         if (human.size() >= 3 && human.front() == id)
         {
            isFound = true;
            break;
         }
      }
      else
      {
         if (vue == typeVision::PROFESSIONNEL)
         {
            if (human.size() == 5 && human[3] == id)
            {
               isFound = true;
               break;
            }
         }
      }
      human.clear();
      ss.str(std::string());
      ss.clear();
   }
   ficIn.close();
   //Aucun resultat ou bon resultat ici
   cout << endl;
   system("pause");
   if (!isFound)
   {
      throw runtime_error("Code non trouvé");
   }
   cout << isFound << endl;
   for (string s : human)
   {
      cout << s << ";";
   }
   Citoyen* citoyen = ChargementCitoyen(human, vue);
}


Citoyen* ChargementCitoyen(vector<string> data, typeVision vue)
{
	Citoyen* citoyen;
   switch (vue)
   {
   case typeVision::CITOYEN:
	   //stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
	   citoyen = new Citoyen(stoi(data[0]), data[1], data[2]);
      break;

   case typeVision::PROFESSIONNEL:
	   //stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
	   citoyen = new Professionnel(stoi(data[0]), data[1], data[2], data[3], data[4]);
      break;
   default:
      throw runtime_error("Chargement: typeVision non implémenté");
   }
   return citoyen;
}


list<RendezVous*> ChargementRendezVous(vector<string> citoyen)
{
	list<RendezVous*> liste;
	return liste;
}


list<Probleme*> ChargementProbleme(vector<string> citoyen)
{
	list<Probleme*> liste;
	return liste;
}