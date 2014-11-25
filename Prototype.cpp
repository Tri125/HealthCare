/*------------------------------------------------
/   Hiver 2014 420-202
/   Prototype de départ pour le TP 3
/   Squelette de la fonctionnalité
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

/*------------------------------------------------
/
/------------------------------------------------*/

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
	cout << "\tP-Professionnel de la santé\n\n";
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
	do
	{
		EcranBienvenue();
		cout << "\nProfil citoyen\n";
		cout << "\n\tNuméro d'assurance sociale du citoyen\n";
		cout << "\tNAS:";
		cin >> strNAS;
      Chargement(strNAS, typeVision::CITOYEN);
		cout << "--------------------\n";
		cout << "Nom:\t\tRoger Lamothe" << endl;
		cout << "Né(e) le:\t1949-11-15\n";
		cout << "--------------------\n";
		cout << "Historique:\n\t8 problèmes\n\t9 ressources utilisées\n\n";
		cout << "--------------------\n";

		Choix = MenuVueCitoyen();
		switch (toupper(Choix))
		{
		case 'P': ConsulterProbleme(); break;
		case 'R': ConsulterRessource(); break;
		case 'Q': break;
		default: ErreurOption(Choix); break;
		}
	} while (Choix != 'Q');
}

/*------------------------------------------------
/
/------------------------------------------------*/
char MenuVueCitoyen()
{
	char Choix;
	cout << "Consulter:" << endl;
	cout << "\t" << "P-problèmes\n";
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
	do
	{
		EcranBienvenue();
		cout << "\nProfil professionnel de la santé:\n";
		cout << "\n\tCode du professionnel de la santé\n";
		cout << "\tCode PS:";
		cin >> strCode;
      Chargement(strCode, typeVision::PROFESSIONNEL);
		cout << "--------------------\n";
		cout << "Nom:\t\tLouise Décarie, chirurgienne cardiaque" << endl;
		cout << "Né(e) le:\t1969-11-15\n";
		cout << "--------------------\n";
		cout << "Historique:\n\t8 patients \n\t14 interventions\n\n";
		cout << "--------------------\n";

		Choix = MenuVueProfessionnel();
		switch (toupper(Choix))
		{
		case 'P': ConsulterPatients(); break;
		case 'I': ConsulterInterventions(); break;
		case 'Q': break;
		default: ErreurOption(Choix); break;
		}
	} while (Choix != 'Q');
}

/*------------------------------------------------
/
/------------------------------------------------*/
void EnteteListePatient()
{
	EcranBienvenue();
	cout << "Patients de Louise Décarie\n-------------------------------------\n";
	cout << "NOM                           NAS     Naissance    Nombre d'interventions\n";
	cout << "____________________________________________________________\n";
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_nai()
{
	EnteteListePatient();
	cout << "André Jobin                    1     1912-01-30     3\n";
	cout << "Coralie Sanschagrin          437     1945-01-30     4\n";
	cout << "Béatrice Marco                23     1972-01-30     2\n";
	cout << "Françoise Dolto                3     1995-11-03     1\n";
	cout << "Geneviève Letram               4     1996-10-31     1\n";
	cout << "Hélène Lefebvre              345     1997-12-30     1\n";
	cout << "Émile Ajar                     2     2002-01-30     1\n";
	cout << "Diane Avecchagrin           7899     2012-01-30     1\n";
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_Nai()
{
	EnteteListePatient();
	cout << "Diane Avecchagrin           7899     2012-01-30     1\n";
	cout << "Émile Ajar                     2     2002-01-30     1\n";
	cout << "Hélène Lefebvre              345     1997-12-30     1\n";
	cout << "Geneviève Letram               4     1996-10-31     1\n";
	cout << "Françoise Dolto                3     1995-11-03     1\n";
	cout << "Béatrice Marco                23     1972-01-30     2\n";
	cout << "Coralie Sanschagrin          437     1945-01-30     4\n";
	cout << "André Jobin                    1     1912-01-30     3\n";
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_oNom()
{
	EnteteListePatient();
	cout << "André Jobin                    1     1912-01-30     3\n";
	cout << "Béatrice Marco                23     1972-01-30     2\n";
	cout << "Coralie Sanschagrin          437     1945-01-30     4\n";
	cout << "Diane Avecchagrin           7899     2012-01-30     1\n";
	cout << "Émile Ajar                     2     2002-01-30     1\n";
	cout << "Françoise Dolto                3     1995-11-03     1\n";
	cout << "Geneviève Letram               4     1996-10-31     1\n";
	cout << "Hélène Lefebvre              345     1997-12-30     1\n";
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_ONom()
{
	EnteteListePatient();
	cout << "Hélène Lefebvre              345     1997-12-30     1\n";
	cout << "Geneviève Letram               4     1996-10-31     1\n";
	cout << "Françoise Dolto                3     1995-11-03     1\n";
	cout << "Émile Ajar                     2     2002-01-30     1\n";
	cout << "Diane Avecchagrin           7899     2012-01-30     1\n";
	cout << "Coralie Sanschagrin          437     1945-01-30     4\n";
	cout << "Béatrice Marco                23     1972-01-30     2\n";
	cout << "André Jobin                    1     1912-01-30     3\n";
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_aNAS()
{
	EnteteListePatient();
	cout << "André Jobin                    1     1912-01-30     3\n";
	cout << "Émile Ajar                     2     2002-01-30     1\n";
	cout << "Françoise Dolto                3     1995-11-03     1\n";
	cout << "Geneviève Letram               4     1996-10-31     1\n";
	cout << "Béatrice Marco                23     1972-01-30     2\n";
	cout << "Hélène Lefebvre              345     1997-12-30     1\n";
	cout << "Coralie Sanschagrin          437     1945-01-30     4\n";
	cout << "Diane Avecchagrin           7899     2012-01-30     1\n";
	cout << endl;
	system("pause");
}
/*------------------------------------------------
/
/------------------------------------------------*/
void Patient_ANAS()
{
	EnteteListePatient();
	cout << "Diane Avecchagrin           7899     2012-01-30     1\n";
	cout << "Coralie Sanschagrin          437     1945-01-30     4\n";
	cout << "Hélène Lefebvre              345     1997-12-30     1\n";
	cout << "Béatrice Marco                23     1972-01-30     2\n";
	cout << "Geneviève Letram               4     1996-10-31     1\n";
	cout << "Françoise Dolto                3     1995-11-03     1\n";
	cout << "Émile Ajar                     2     2002-01-30     1\n";
	cout << "André Jobin                    1     1912-01-30     3\n";
	cout << endl;
	system("pause");
}
/*------------------------------------------------
/
/------------------------------------------------*/
void ConsulterPatients()
{
	char Choix;
	EcranBienvenue();
	cout << "\tPatients de Louise Décarie triés par:\n\n";
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
	cout << "\tInterventions de Louise Décarie triées par:\n\n";
	cout << "\td-date .:\n";
	cout << "\tD-date :.\n";
	cout << "\te-établissement .:\n";
	cout << "\tE-établissement :.\n";
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
	case 's': Interv_ETABLI(); break;
	case 'Q': Quitter(); break;
	default: ErreurOption(Choix); break;
	}
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Interv_date()
{
	EcranBienvenue();
	cout << "Interventions de Louise Décarie\n-------------------------------------\n";
	cout << "Patient                      NAS      Date      Établissement\n";
	cout << "________________________________________________________________________\n";
	cout << "André Jobin                    1   1989-01-24   CLSC du Sud\n";
	cout << "André Jobin                    1   2001-11-24   CLSC du Sud\n";
	cout << "André Jobin                    1   2002-02-24   CH de St-Jérôme\n";
	cout << "Béatrice Marco                23   2004-10-30   CLSC du Sud\n";
	cout << "Béatrice Marco                23   2008-06-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2009-07-30   CH de St-Jérôme\n";
	cout << "Coralie Sanschagrin            2   2010-06-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2010-11-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2011-10-30   CLSC du Sud\n";
	cout << "Diane Avecchagrin           7899   2012-04-22   CLSC du Nord\n";
	cout << "Émile Ajar                     2   2013-04-02   CH de St-Jérôme\n";
	cout << "Françoise Dolto                3   2013-04-13   CH Hotel-Dieu\n";
	cout << "Geneviève Letram               4   2013-04-19   CH de St-Jérôme\n";
	cout << "Hélène Lefebvre              345   2014-01-12   CLSC du Sud\n";
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Interv_DATE()
{
	EcranBienvenue();
	cout << "Interventions de Louise Décarie\n-------------------------------------\n";
	cout << "Patient                      NAS      Date      Établissement\n";
	cout << "________________________________________________________________________\n";
	cout << "Hélène Lefebvre              345   2014-01-12   CLSC du Sud\n";
	cout << "Geneviève Letram               4   2013-04-19   CH de St-Jérôme\n";
	cout << "Françoise Dolto                3   2013-04-13   CH Hotel-Dieu\n";
	cout << "Émile Ajar                     2   2013-04-02   CH de St-Jérôme\n";
	cout << "Diane Avecchagrin           7899   2012-04-22   CLSC du Nord\n";
	cout << "Coralie Sanschagrin            2   2011-10-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2010-11-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2010-06-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2009-07-30   CH de St-Jérôme\n";
	cout << "Béatrice Marco                23   2008-06-30   CLSC du Sud\n";
	cout << "Béatrice Marco                23   2004-10-30   CLSC du Sud\n";
	cout << "André Jobin                    1   2001-11-24   CLSC du Sud\n";
	cout << "André Jobin                    1   1989-01-24   CLSC du Sud\n";
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Interv_etabli()
{
	EcranBienvenue();
	cout << "Interventions de Louise Décarie\n-------------------------------------\n";
	cout << "Patient                      NAS      Date      Établissement\n";
	cout << "________________________________________________________________________\n";
	cout << "Coralie Sanschagrin            2   2009-07-30   CH de St-Jérôme\n";
	cout << "Geneviève Letram               4   2013-04-19   CH de St-Jérôme\n";
	cout << "Émile Ajar                     2   2013-04-02   CH de St-Jérôme\n";
	cout << "Françoise Dolto                3   2013-04-13   CH Hotel-Dieu\n";
	cout << "Diane Avecchagrin           7899   2012-04-22   CLSC du Nord\n";
	cout << "Coralie Sanschagrin            2   2011-10-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2010-11-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2010-06-30   CLSC du Sud\n";
	cout << "Hélène Lefebvre              345   2014-01-12   CLSC du Sud\n";
	cout << "Béatrice Marco                23   2008-06-30   CLSC du Sud\n";
	cout << "Béatrice Marco                23   2004-10-30   CLSC du Sud\n";
	cout << "André Jobin                    1   2001-11-24   CLSC du Sud\n";
	cout << "André Jobin                    1   1989-01-24   CLSC du Sud\n";
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void Interv_ETABLI()
{
	EcranBienvenue();
	cout << "Interventions de Louise Décarie\n-------------------------------------\n";
	cout << "Patient                      NAS      Date      Établissement\n";
	cout << "________________________________________________________________________\n";
	cout << "Diane Avecchagrin           7899   2012-04-22   CLSC du Nord\n";
	cout << "Coralie Sanschagrin            2   2011-10-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2010-11-30   CLSC du Sud\n";
	cout << "Coralie Sanschagrin            2   2010-06-30   CLSC du Sud\n";
	cout << "Hélène Lefebvre              345   2014-01-12   CLSC du Sud\n";
	cout << "Béatrice Marco                23   2008-06-30   CLSC du Sud\n";
	cout << "Béatrice Marco                23   2004-10-30   CLSC du Sud\n";
	cout << "André Jobin                    1   2001-11-24   CLSC du Sud\n";
	cout << "André Jobin                    1   1989-01-24   CLSC du Sud\n";
	cout << "Françoise Dolto                3   2013-04-13   CH Hotel-Dieu\n";
	cout << "Coralie Sanschagrin            2   2009-07-30   CH de St-Jérôme\n";
	cout << "Geneviève Letram               4   2013-04-19   CH de St-Jérôme\n";
	cout << "Émile Ajar                     2   2013-04-02   CH de St-Jérôme\n";
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void ConsulterProbleme()
{
	EcranBienvenue();
	cout << "Problèmes médicaux de Roger Lamothe\n-------------------------------------\n";
	cout << "Blessures:\n";
	cout << "Type         Début        Guérison    Description \n";
	cout << "______________________________________________________________\n";
	cout << "Fracture     2014-03-24               Fracture ouverte du tibia\n";
	cout << "Brûlure      2011-02-02   2011-03-14  Brûlure 2ième degré au visage\n";
	cout << "Contusion    2010-01-30   2010-02-01  Hématome majeur suite à un accident d'auto\n";
	cout << "Intoxication 2009-09-12   2010-04-12  Perte de vision suite à une surdose d'alcool\n";
	cout << "\nMaladies:\n";
	cout << "Pathologie            Stade Début       Guérison     Commentaire \n";
	cout << "______________________________________________________________\n";
	cout << "Schlérose en plaque   3     1990-01-24               État chronique mais stable\n";
	cout << "Cancer de la prostate 1     1995-02-02  2000-12-20   Aucune récidive après plus de 5 ans\n";
	cout << "Polyomiélite          2     1954-02-01  1956-11-30   Stabilisation de la maladie\n";
	cout << "Gonorrhée             4     2009-09-12  2009-12-12   Guérison après anti-biotique\n";
	cout << endl;
	system("pause");
}

/*------------------------------------------------
/
/------------------------------------------------*/
void ConsulterRessource()
{
	EcranBienvenue();
	cout << "Ressources utilisées par Roger Lamothe\n-------------------------------------\n";
	cout << "Rendez-vous simples:\n";
	cout << "Établissement       Date         Code PS\n";
	cout << "______________________________________________\n";
	cout << "CLSC du Sud         2012-01-24   D-128        \n";
	cout << "CLSC du Sud         2011-02-02   D-145        \n";
	cout << "Clinique des jeunes 2010-01-30   D-128        \n";
	cout << "CH St-Jérôme        2009-09-12   P-334        \n";
	cout << "CLSC St-Jérôme      2007-12-12   P-2828       \n";
	cout << "\nHospitalisations:\n";
	cout << "Etablissement            Arrivée      Code PS       Chambre Départ\n";
	cout << "________________________________________________________________________\n";
	cout << "CH Notre-Dame            2013-11-24   NC-103         233                 \n";
	cout << "CH Hotel-Dieu            1995-02-02   D-1145        1544    1995-12-20    \n";
	cout << "CH Notre-Dame            1954-02-01   G-8912         201    1954-11-30    \n";
	cout << "CHU de Sherbrooke        2009-09-12   P-334          864    2009-10-02    \n";
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
	for (int i = 0; i<48; i++)
		cout << ligneH;
	cout << coinHD << endl;
	cout << "\t" << ligneV << "                                                " << ligneV << endl;
	cout << "\t" << ligneV << "  Votre Pr\x82nom Nom pr\x82sente :                   " << ligneV << endl;
	cout << "\t" << ligneV << "           Sant\x82 Express                        " << ligneV << endl;
	cout << "\t" << ligneV << "  Syst\x8Ame de consultation de dossiers sant\x82     " << ligneV << endl;
	cout << "\t" << ligneV << "                                                " << ligneV << endl;
	cout << "\t" << coinBG;
	for (int i = 0; i<48; i++)
		cout << ligneH;
	cout << coinBD << endl;
	setlocale(LC_ALL, "");
}