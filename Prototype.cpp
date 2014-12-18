/*------------------------------------------------
/   Hiver 2014 420-202
/   Prototype de d�part pour le TP 3
/   Squelette de la fonctionnalit�
/
/   par: Alain Martel
/------------------------------------------------*/


#include "biblio.h"

void EcranBienvenue();
char MenuPrincipal();

void VueDuCitoyen();
char MenuVueCitoyen();
void ConsulterProbleme();
void ConsulterRessource();

void VueDuProfessionnelSante();
char MenuVueProfessionnel();
void ConsulterPatients();
void ConsulterInterventions();
void Interv_date();
void Interv_DATE();
void Interv_etabli();
void Interv_ETABLI();
void Quitter();
void ErreurOption(char Choix);
char MenuErreurCode();

void Patient_sans();
void Interv_sans();

/*------------------------------------------------
/
/------------------------------------------------*/

Citoyen* citoyen;
Professionnel* pro;

int main()
{
   char Choix = MenuPrincipal();
   while (Choix != 'Q')
   {
      switch (toupper(Choix))
      {
      case 'C': VueDuCitoyen(); break;
      case 'P': VueDuProfessionnelSante(); break;
      case 'Q': Quitter(); break;
      default: ErreurOption(Choix); break;
      }
      Choix = MenuPrincipal();
   }
}

/*------------------------------------------------
/
/------------------------------------------------*/
char MenuPrincipal()
{
   char Choix;
   EcranBienvenue();
   cout << "\n\nProfils offerts:\n\n";
   cout << "\n\n";
   cout << "\tC-Citoyen\n";
   cout << "\tP-Professionnel de la sant�\n\n";
   cout << "\tQ-Quitter\n";

   cout << "\t\tVotre choix:";
   cin >> Choix;
   return toupper(Choix);
}

/*------------------------------------------------
/
/------------------------------------------------*/
void VueDuCitoyen()
{
   string strNAS;
   char Choix;
   bool erreur;
   do
   {
      erreur = false;
      EcranBienvenue();
      cout << "\nProfil citoyen\n";
      cout << "\n\tNum�ro d'assurance sociale du citoyen\n";
      cout << "\tNAS:";
      cin >> strNAS;
      try
      {
         citoyen = Trouver(strNAS, typeVision::CITOYEN);
      }
      catch (runtime_error& e)
      {
         erreur = true;
         cout << "Erreur: " << e.what() << endl;
         Choix = MenuErreurCode();
         switch (toupper(Choix))
         {
         case 'Q': return;
         case 'S': break;
         default: ErreurOption(Choix); break;
         }
      }
      if (!erreur)
      {

		 citoyen->Afficher();
         Choix = MenuVueCitoyen();
         switch (toupper(Choix))
         {
         case 'P': ConsulterProbleme(); break;
         case 'R': ConsulterRessource(); break;
         case 'Q': break;
         default: ErreurOption(Choix); break;
         }
      }
   } while (Choix != 'Q');
}


/*------------------------------------------------
/
/------------------------------------------------*/
char MenuErreurCode()
{
   char Choix;
   cout << "Proposition:" << endl;
   cout << "\t" << "Q-Quitter au menu principal\n";
   cout << "\t" << "S-Saisir un nouveau code\n";
   cout << "\t" << "\t\tVotre choix:";
   cin >> Choix;
   return toupper(Choix);
}

/*------------------------------------------------
/
/------------------------------------------------*/
char MenuVueCitoyen()
{
   char Choix;
   cout << "Consulter:" << endl;
   cout << "\t" << "P-probl�mes\n";
   cout << "\t" << "R-ressources\n";
   cout << "\t" << "\nQ-Quitter\n";
   cout << "\t" << "\t\tVotre choix:";
   cin >> Choix;
   return toupper(Choix);
}

/*------------------------------------------------
/
/------------------------------------------------*/
char MenuVueProfessionnel()
{
   char Choix;
   cout << "Consulter:" << endl;
   cout << "\t" << "P-patients\n";
   cout << "\t" << "I-interventions\n";
   cout << "\t" << "\nQ-Quitter\n";
   cout << "\t" << "\t\tVotre choix:";
   cin >> Choix;
   return toupper(Choix);
}

/*------------------------------------------------
/
/------------------------------------------------*/
void VueDuProfessionnelSante()
{
   string strCode;
   char Choix;
   bool erreur;
   do
   {
      erreur = false;
      EcranBienvenue();
      cout << "\nProfil professionnel de la sant�:\n";
      cout << "\n\tCode du professionnel de la sant�\n";
      cout << "\tCode PS:";
      cin >> strCode;
      try
      {
         citoyen = Trouver(strCode, typeVision::PROFESSIONNEL);
		 //Pour �viter de caster plus qu'une fois rendu dans les menus.
		 pro = static_cast<Professionnel*>(citoyen);
      }
      catch (runtime_error& e)
      {
         erreur = true;
         cout << "Erreur: " << e.what() << endl;
         Choix = MenuErreurCode();
         switch (toupper(Choix))
         {
         case 'Q': return;
         case 'S': break;
         default: ErreurOption(Choix); break;
         }
      }
      if (!erreur)
      {

		 citoyen->Afficher();

         Choix = MenuVueProfessionnel();
         switch (toupper(Choix))
         {
         case 'P': ConsulterPatients(); break;
         case 'I': ConsulterInterventions(); break;
         case 'Q': break;
         default: ErreurOption(Choix); break;
         }
      }
   } while (Choix != 'Q');
}

/*------------------------------------------------
/
/------------------------------------------------*/
void EnteteListePatient()
{
   EcranBienvenue();
   cout << "Patients de " << citoyen->getNom() << "\n-------------------------------------\n";
   cout << "NOM\t\t\t\tNAS\tNaissance\tNombre d'interventions\n";
   cout << "____________________________________________________________\n";
}


void Patient_sans()
{
	EnteteListePatient();
	pro->AfficherPatients();
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_nai()
{
	TriePatient(pro, typeTriePatient::NAISSANCE, true);
	Patient_sans();
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_Nai()
{
	TriePatient(pro, typeTriePatient::NAISSANCE, false);
	Patient_sans();
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_oNom()
{
	TriePatient(pro, typeTriePatient::NOM, true);
	Patient_sans();
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_ONom()
{
	TriePatient(pro, typeTriePatient::NOM, false);
	Patient_sans();
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_aNAS()
{
	TriePatient(pro, typeTriePatient::NAS, true);
	Patient_sans();
}
/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_ANAS()
{
	TriePatient(pro, typeTriePatient::NAS, false);
	Patient_sans();
}
/*------------------------------------------------
/
/------------------------------------------------*/
void ConsulterPatients()
{
   char Choix;
   EcranBienvenue();
   cout << "\tPatients de " << citoyen->getNom() <<  " tri�s par:\n\n";
   cout << "\tn-naissance .:\n";
   cout << "\tN-Naissance :.\n";
   cout << "\ta-NAS .:\n";
   cout << "\tA-NAS :.\n";
   cout << "\to-Nom .:\n";
   cout << "\tO-Nom :.\n";
   cout << "\ts-sans tri\n";
   cout << "\tQ-Quitter\n";
   cout << "\t\tVotre choix:";
   cin >> Choix;
   switch (Choix)
   {
   case 'n': Patient_nai(); break;
   case 'N': Patient_Nai(); break;
   case 'a': Patient_aNAS(); break;
   case 'A': Patient_ANAS(); break;
   case 'o': Patient_oNom(); break;
   case 'O': Patient_ONom(); break;
   case 's': Patient_sans(); break;
   case 'Q': Quitter(); break;
   default: ErreurOption(Choix); break;
   }
}

/*------------------------------------------------
/
/------------------------------------------------*/
void ConsulterInterventions()
{
   char Choix;
   EcranBienvenue();
   cout << "\tInterventions de " << citoyen->getNom() << " tri�es par:\n\n";
   cout << "\td-date .:\n";
   cout << "\tD-date :.\n";
   cout << "\te-�tablissement .:\n";
   cout << "\tE-�tablissement :.\n";
   cout << "\ts-sans tri\n";
   cout << "\tQ-Quitter\n";
   cout << "\t\tVotre choix:";
   cin >> Choix;
   switch (Choix)
   {
   case 'd': Interv_date(); break;
   case 'D': Interv_DATE(); break;
   case 'e': Interv_etabli(); break;
   case 'E': Interv_ETABLI(); break;
   case 's': Interv_sans(); break;
   case 'Q': Quitter(); break;
   default: ErreurOption(Choix); break;
   }
}


void Interv_sans()
{
	EcranBienvenue();
	cout << "Interventions de " << citoyen->getNom() << "\n-------------------------------------\n";
	cout << "Patient\t\t\t\tNAS\tDate\t\t�tablissement\n";
	cout << "________________________________________________________________________\n";
	pro->AfficherInterventions();
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Interv_date()
{
	TrieIntervention(pro, typeTrieIntervention::DATE, true);
	Interv_sans();
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Interv_DATE()
{
	TrieIntervention(pro, typeTrieIntervention::DATE, false);
	Interv_sans();
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Interv_etabli()
{
	TrieIntervention(pro, typeTrieIntervention::ETABLISSEMENT, true);
	Interv_sans();
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Interv_ETABLI()
{
	TrieIntervention(pro, typeTrieIntervention::ETABLISSEMENT, false);
	Interv_sans();
}

/*------------------------------------------------
/
/------------------------------------------------*/
void ConsulterProbleme()
{
   EcranBienvenue();
   cout << "Probl�mes m�dicaux de " << citoyen->getNom() << "\n-------------------------------------\n";
   cout << "Blessures:\n";
   cout << "Type\t\tD�but\t\tGu�rison\tDescription \n";
   cout << "___________________________________________________________________\n";
   citoyen->AfficherBlessure();
   cout << "\nMaladies:\n";
   cout << "Pathologie\tStade\tD�but\t\tGu�rison\tCommentaire \n";
   cout << "___________________________________________________________________\n";
   citoyen->AfficherMaladie();
   cout << endl;
   system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void ConsulterRessource()
{
   EcranBienvenue();
   cout << "Ressources utilis�es par " << citoyen->getNom() << "\n-------------------------------------\n";
   cout << "Rendez-vous simples:\n";
   cout << "�tablissement\t\tDate\t\tCode PS\n";
   cout << "______________________________________________\n";
   citoyen->AfficherRendezVous();
   cout << "\nHospitalisations:\n";
   cout << "Etablissement\t\tArriv�e\t\tCode PS\tChambre\tD�part\n";
   cout << "________________________________________________________________________\n";
   citoyen->AfficherHospitalisation();
   cout << endl;
   system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Quitter()
{
   EcranBienvenue();
   cout << "\n\n Au revoir ...\n";
   exit(0);
}

/*------------------------------------------------
/
/------------------------------------------------*/
void ErreurOption(char Choix)
{
   EcranBienvenue();
   cout << "\n\n ERREUR: Option " << Choix << " invalide \n";
   cout << "---------------------------------------------\n\n";

   MenuPrincipal();
}

/*------------------------------------------------
/
/------------------------------------------------*/
void EcranBienvenue()
{
   char coinHG = (char)201;
   char coinHD = (char)187;
   char coinBG = (char)200;
   char coinBD = (char)188;
   char ligneH = (char)205;
   char ligneV = (char)186;

   system("cls");
   setlocale(LC_ALL, "C");
   cout << "\t" << coinHG;
   for (int i = 0; i < 48; i++)
      cout << ligneH;
   cout << coinHD << endl;
   cout << "\t" << ligneV << "                                                " << ligneV << endl;
   cout << "\t" << ligneV << "  Votre Pr\x82nom Nom pr\x82sente :                   " << ligneV << endl;
   cout << "\t" << ligneV << "           Sant\x82 Express                        " << ligneV << endl;
   cout << "\t" << ligneV << "  Syst\x8Ame de consultation de dossiers sant\x82     " << ligneV << endl;
   cout << "\t" << ligneV << "                                                " << ligneV << endl;
   cout << "\t" << coinBG;
   for (int i = 0; i < 48; i++)
      cout << ligneH;
   cout << coinBD << endl;
   setlocale(LC_ALL, "");
}