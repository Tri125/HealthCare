class Professionnel : public Citoyen
{
private:
   string codeps;
   string titre;
   map<int, Citoyen*> mapPatients;

public:
   Professionnel();
   Professionnel(int, string, string, string, string);
   string getCodePS();
};

