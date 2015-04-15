


class DateEpoch
{
   int An;
   int Mois;
   int Jour;
   int Heure;
   int Minute;
   int Seconde;


public:
   DateEpoch();
   DateEpoch(int, int, int, int, int, int);
   DateEpoch(int, int, int);
   DateEpoch(int);
   time_t Epoch;
   void Affiche();
   bool operator< (const DateEpoch&);
   bool operator<= (const DateEpoch&);
   bool operator== (const DateEpoch&);
   bool operator!= (const DateEpoch&);
   bool operator>= (const DateEpoch&);
   bool operator> (const DateEpoch&);
   string ToString();

private:

   void ConvertEpochToFormat();
   void ConvertFormatToEpoch();
};