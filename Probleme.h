class Probleme
{

protected:
   int nas;
   string dateDebut;
   string dateFin;
   string description;

public:
   Probleme(int, string, string, string);
   Probleme();
   virtual void Afficher() = 0;
};

