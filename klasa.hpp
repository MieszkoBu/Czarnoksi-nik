#ifndef KLASA_HPP
#define KLASA_HPP


class Gracz;
class Przeciwnik {
public:
    std::string nazwa;
    int pz;
    int pm;
    int atak;
    int magiczny_atak;
    int obrona;
    int szczescie;
    int pd;
    int zloto;
    Przeciwnik(std::string nazwa, int pz, int pm, int atak, int magiczny_atak, int obrona, int szczescie, int pd, int zloto) :
        nazwa(nazwa), pz(pz), pm(pm), atak(atak), magiczny_atak(magiczny_atak), obrona(obrona), szczescie(szczescie), pd(pd), zloto(zloto) {}

    void atak_gracza(Gracz &g);
    void atak_magia_gracza(Gracz &g, int ile_many);
};

class Gracz {
public:
    std::string imie;
    std::string nazwisko;
    int max_pz;
    int max_pm;
    int pz;
    int pm;
    int ak;
    int ma;
    int obr;
    int sl;
    int zw;
    int in;
    int sz;
    Gracz(std::string imie, std::string nazwisko, int start_pz, int start_pm, int atak, int magiczny_atak, int obrona, int sila, int zwinnosc, int inteligencja, int szczescie);
    void wypisz_statystyki();
    virtual void opis_klasy() = 0;
    virtual ~Gracz() = default;
    void atak_przeciwnika(Przeciwnik &przeciwnik);
    void atak_magia_przeciwnika(Przeciwnik &przeciwnik, int ile_many);
    void nastepny_poziom();
};


class Przedmiot{
public:
    std::string nazwa;
    int wartosc_ataku;
    int wartosc_obrony;
    int wartosc_leczenia;
    int wartosc_odzyskaknia_many;
    int wartosc;
    int ciezar;
    std::string typ;
    Przedmiot(std::string nazwa, int wartosc_ataku, int wartosc_obrony, int wartosc_leczenia, int wartosc_odzyskaknia_many, int wartosc, int ciezar, std::string typ):
        nazwa(nazwa), wartosc_ataku(wartosc_ataku), wartosc_obrony(wartosc_obrony), wartosc_leczenia(wartosc_leczenia), wartosc_odzyskaknia_many(wartosc_odzyskaknia_many), wartosc(wartosc), ciezar(ciezar), typ(typ) {}
};
class Ekwipunek{
public:
    int pojemnosc;
    int obecny_ciezar;
    Przedmiot zalozona_bron;
    Przedmiot zalozona_zbroja;
    Ekwipunek(int pojemnosc, int obecny_ciezar, Przedmiot zalozona_bron, Przedmiot zalozona_zbroja):
        pojemnosc(pojemnosc), obecny_ciezar(obecny_ciezar), zalozona_bron(zalozona_bron), zalozona_zbroja(zalozona_zbroja) {}
    bool dodaj_przedmiot(Przedmiot przedmiot);
    bool usun_przedmiot(std::string nazwa);
    void pokaz_ekwipunek();
    bool zaloz_przedmiot(Przedmiot przedmiot);
    Przedmiot Pokaz_zalozona_bron();
};

class Zadanie {
public:
    std::string opis;
    bool trwajace;
    bool do_oddania;
    bool wykonane;
    Zadanie(std::string opis):
        opis(opis), trwajace(true), do_oddania(false), wykonane(false) {}
};

class Dziennik {
public:
    void dodaj_zadanie(std::string opis);
    void aktualizacja_zadania(std::string opis);
    void wykonaj_zadanie(std::string opis);
    void wyswietl_zadania();
};
class Wojownik : public Gracz {
public:
    Wojownik(std::string imie, std::string nazwisko);
    void opis_klasy();
};

class Magik : public Gracz {
public:
    Magik(std::string imie, std::string nazwisko);
        void opis_klasy();

};

class Silacz : public Gracz {
public:
    Silacz(std::string imie, std::string nazwisko);
        void opis_klasy();

};

class Lotrzyk : public Gracz {
public:
    Lotrzyk(std::string imie, std::string nazwisko);
    void opis_klasy();

};
class Rasa{
public:
    virtual void dodaj_bonusy(Gracz*) = 0;
    virtual void opis_rasy() = 0;
};

class Czlowiek : public Rasa{
public:
    void dodaj_bonusy(Gracz* gracz);
    void opis_rasy();
};

class Elf : public Rasa{
public:
    void dodaj_bonusy(Gracz* gracz);
    void opis_rasy();
};

class Gnom : public Rasa{
public:
    void dodaj_bonusy(Gracz*);
    void opis_rasy();
};

class Krasnolud : public Rasa{
public:
    void dodaj_bonusy(Gracz* gracz);
    void opis_rasy();
};
class Bonusy{
public:
    virtual void dodatkowe_punkty(Gracz*) = 0;
};
class PZ : public Bonusy{
public:
    void dodatkowe_punkty(Gracz* gracz);
};

class PM : public Bonusy{
public:
    void dodatkowe_punkty(Gracz* gracz);
};
class Sila : public Bonusy{
public:
    void dodatkowe_punkty(Gracz* gracz);
};
class Zwinnosc : public Bonusy{
public:
    void dodatkowe_punkty(Gracz* gracz);
};
class Inteligencja : public Bonusy{
public:
    void dodatkowe_punkty(Gracz* gracz);
};
class Szczescie : public Bonusy{
public:
    void dodatkowe_punkty(Gracz* gracz);
};

enum plec{
    mezczyzna, kobieta
};
enum klasa {
    wojownik, silacz, magik, lotrzyk
};
enum rasa_g {
    czlowiek, elf, gnom, krasnolud
};
enum bron_w{
    szeroki_miecz, krotki_miecz, miecz_dwureczny
};
enum bron_m{
    laska
};
enum bron_s{
    rekawice
};
enum bron_l{
    sztylety
};
struct StanGry {
    // Cechy gracza
    std::string imie;
    std::string nazwisko;
    enum klasa klasa;
    enum rasa_g rasa_g;
    Rasa* rasa = NULL;
    enum plec plec;
    // stan gracza;
    Bonusy* bonus = NULL;
    Gracz* gracz = NULL;
    int poziom = 1;
    int pd = 0;
    int pd_do_nastepnego_poziomu = 100;
    int zloto = 0;
    int poz = 15;
    int pio = 11;
    std::vector<Przedmiot> przedmioty;
    std::vector<Zadanie> zadania;
    int ciezar = 0;
    bool hydra_z = false;
    bool smok_z = false;
    bool hydra_zad = false;
    bool smok_zad = false;
    bool hydra_w = false;
    bool smok_w = false;
    bool zad_smok = false;
    bool zad_hydra = false;
    bool czar_zad = false;
};
extern struct StanGry stan_gry;

void wypisz_plec(enum plec p);
void wypisz_klase(enum klasa k);
void wypisz_rase(enum rasa_g r);

#endif // KLASA_HPP
