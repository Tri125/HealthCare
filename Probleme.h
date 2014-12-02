class Probleme
{

protected:
   int nas;
   string dateDebut;
   string dateFin;
   string description;
   virtual void Afficher() = 0;

public:
   Probleme(int, string, string, string);
   Probleme();
};

