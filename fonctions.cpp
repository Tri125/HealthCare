#include "biblio.h"

void Chargement(string id, typeVision vue)
{
   const char SEPARATING_SYMBOL = ';';
   const string FICHIER_POPULATION = "population.txt";
   const string FICHIER_PROBLEME = "problèmes.txt";
   const string FICHIER_UTILISATION = "utilisations.txt";
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
      ss << ligneCourante ;
      while (getline(ss, data, SEPARATING_SYMBOL))
      {
         human.push_back(data);
      }
      if (vue == typeVision::CITOYEN)
      {
         if (human.size() > 0 && human.front() != id)
         {
            human.clear();
            ss.str(std::string());
            ss.clear();
            continue;
            system("Pause");
         }
      }
      else
      {
         if (vue == typeVision::PROFESSIONNEL)
         {

         }
      }
   }
}

void ChargementCitoyen(vector<string> citoyen, typeVision);