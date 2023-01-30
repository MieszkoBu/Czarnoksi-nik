#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include "klasa.hpp"
#include "mapa.hpp"

void odczyt();
bool Ekwipunek::dodaj_przedmiot(Przedmiot przedmiot){
        if(obecny_ciezar + przedmiot.ciezar > pojemnosc){
            std::cout << "Jesteś zbyt ciężki " << przedmiot.nazwa << " brak miejsca w ekwipunku." << std::endl;
            return false;
        }

        stan_gry.przedmioty.push_back(przedmiot);
        obecny_ciezar += przedmiot.ciezar;
        std::cout << "Dodano " << przedmiot.nazwa << " do ekwipunku." << std::endl;
        return true;
}
bool Ekwipunek::usun_przedmiot(std::string nazwa){
        for(int i = 0; i < stan_gry.przedmioty.size(); i++){
            if(stan_gry.przedmioty[i].nazwa == nazwa) {
                obecny_ciezar -= stan_gry.przedmioty[i].ciezar;
                stan_gry.przedmioty.erase(stan_gry.przedmioty.begin() + i);
                std::cout << "Usunięto przedmiot " << nazwa << " z ekwipunku." << std::endl;
                return true;
            }
        }
        std::cout << "Nie znaleziono przedmiotu" << nazwa << " w ekwipunku." << std::endl;
        return false;
}
void Ekwipunek::pokaz_ekwipunek(){
        std::cout << "Ekwipunek (" << obecny_ciezar << " / " << pojemnosc << "):" <<std::endl;
        for(int i = 0; i < stan_gry.przedmioty.size(); i++){
            std::cout << " - " << stan_gry.przedmioty[i].nazwa << " ( wartość: " << stan_gry.przedmioty[i].wartosc << ", waga: " << stan_gry.przedmioty[i].ciezar << ", atak: " << stan_gry.przedmioty[i].wartosc_ataku << ", obrona: "<< stan_gry.przedmioty[i].wartosc_obrony<< ")" <<std::endl;
        }
}
bool Ekwipunek::zaloz_przedmiot(Przedmiot nazwa_przedmiotu){
    std::cout<<nazwa_przedmiotu.typ<<std::endl;
    if(nazwa_przedmiotu.typ == "Bron"){
        for(int i=0; i<stan_gry.przedmioty.size(); i++){
            if(stan_gry.przedmioty[i].nazwa == nazwa_przedmiotu.nazwa){
                if(nazwa_przedmiotu.nazwa == "Długa laska" || nazwa_przedmiotu.nazwa == "Złota laska" || nazwa_przedmiotu.nazwa == "Smocza laska"){
                    stan_gry.gracz->ma -= zalozona_bron.wartosc_ataku;
                }
                else{
                stan_gry.gracz->ak -= zalozona_bron.wartosc_ataku;
                }
                zalozona_bron = stan_gry.przedmioty[i];
                std::cout << "Zakładasz " << nazwa_przedmiotu.nazwa << " jako broń" << std::endl;
                if(nazwa_przedmiotu.nazwa == "Długa laska" || nazwa_przedmiotu.nazwa == "Złota laska" || nazwa_przedmiotu.nazwa == "Smocza laska"){
                    stan_gry.gracz->ma += zalozona_bron.wartosc_ataku;
                }
                else{
                stan_gry.gracz->ak += stan_gry.przedmioty[i].wartosc_ataku;
                }
                return true;
            }
        }
        std::cout << "Nie znaleziono broni o nazwie " << nazwa_przedmiotu.nazwa << " w ekwipunku." << std::endl;
        return false;
    }
    else if(nazwa_przedmiotu.typ == "zbroja"){
        for(int i=0; i<stan_gry.przedmioty.size(); i++){
            if(stan_gry.przedmioty[i].nazwa == nazwa_przedmiotu.nazwa){
                stan_gry.gracz->obr -= zalozona_bron.wartosc_obrony;
                zalozona_zbroja = stan_gry.przedmioty[i];
                std::cout << "Zakładasz " << nazwa_przedmiotu.nazwa << " jako zbroję" << std::endl;
                stan_gry.gracz->obr += stan_gry.przedmioty[i].wartosc_obrony;
                return true;
            }
        }
        std::cout << "Nie znaleziono zbroi o nazwie " << nazwa_przedmiotu.nazwa << " w ekwipunku." << std::endl;
        return false;
    }
    else{
        std::cout<<"To nie jest broń albo zbroja"<<std::endl;
    }
}
Przedmiot Ekwipunek::Pokaz_zalozona_bron(){
    return zalozona_bron;
}

void Dziennik::dodaj_zadanie(std::string opis){
        stan_gry.zadania.push_back(Zadanie(opis));
        std::cout<<"Przyjęto zadanie: " <<opis<<std::endl;
}
void Dziennik::aktualizacja_zadania(std::string opis){
        for(auto &zadanie : stan_gry.zadania){
            if(zadanie.opis == opis){
                zadanie.trwajace = false;
                zadanie.do_oddania = true;
                std::cout << "Wykonano czynność do zadania: " << zadanie.opis << std::endl;
                std::cout << "Wróć do zleceniobiorcy" << std::endl;
                return;
            }
        }
        std::cout << "Nie znaleziono takiego zadania" << std::endl;
}
void Dziennik::wykonaj_zadanie(std::string opis){
        for(auto &zadanie : stan_gry.zadania){
            if(zadanie.opis == opis){
                zadanie.wykonane = true;
                zadanie.do_oddania = false;
                std::cout << "Wykonano zadanie: " << zadanie.opis << std::endl;
                return;
            }
        }
        std::cout << "Nie znaleziono takiego zadania" << std::endl;
}
void Dziennik::wyswietl_zadania(){
        std::cout << "Lista zadań:" << std::endl;
        for(auto zadanie : stan_gry.zadania){
            std::cout << "- " << zadanie.opis;
            if(zadanie.wykonane == true){
                std::cout << " (wykonane)";
            }
            else if(zadanie.do_oddania == true){
                std::cout << " (odbierz nagrodę)";
            }
            std::cout<<std::endl;
        }
}
void Przeciwnik::atak_magia_gracza(Gracz &g, int ile_many){
        int czy_kryt = rand()%101;
        pm -= ile_many;
        if(this->magiczny_atak-g.obr>=0){
         if(czy_kryt <= szczescie*0.5){
                std::cout<<"Przeciwnik zaatakował cię krytykiem"<<std::endl;
                g.pz -= (4*magiczny_atak-g.obr);
            }
        else {
                g.pz -= (this->magiczny_atak-g.obr);
        }
        }
        if(g.pz <= 0){
            std::cout << "Gracz zginął!!" << std::endl;
            std::cout << "Koniec Gry!" << std::endl;
            exit(0);
        }
        else {
            if(this->magiczny_atak-g.obr>0){
                std::cout << "Przeciwnik zadał ci " << this->magiczny_atak-g.obr << " obrażeń magią. " << "Zostało ci "<< g.pz << " życia." << std::endl;
            }
            else{
                std::cout << "Przeciwnik nie zadał ci żadnych obrażeń. " << "Zostało ci "<< g.pz << " życia." << std::endl;
            }
        }
}
void Przeciwnik::atak_gracza(Gracz &g){
        int czy_kryt = rand()%101;
        pm -= 5;
        if(this->atak-g.obr>=0){
            if(czy_kryt <= szczescie*0.5){
                std::cout<<"Przeciwnik zaatakował cię krytykiem"<<std::endl;
                g.pz -= (4*atak-g.obr);
            }
            else{
                    g.pz -= (this->atak-g.obr);
            }
        }
        if(g.pz <= 0){
            std::cout << "Gracz zginął!!" << std::endl;
            std::cout << "Koniec Gry!" << std::endl;
            exit(0);
        }
        else {
            if(this->atak-g.obr>0){
                std::cout << "Przeciwnik zadał ci " << this->atak-g.obr << " obrażeń. " << "Zostało ci "<< g.pz << " życia." << std::endl;
            }
            else{
                std::cout << "Przeciwnik nie zadał ci żadnych obrażeń. " << "Zostało ci "<< g.pz << " życia." << std::endl;
            }
        }
}
void Gracz::nastepny_poziom(){
        std::cout<<"Gratulację wbito "<<stan_gry.poziom+1<<" poziom"<<std::endl;
        std::string atrybut;
        stan_gry.poziom++;
        stan_gry.pd = stan_gry.pd - stan_gry.pd_do_nastepnego_poziomu;
        stan_gry.pd_do_nastepnego_poziomu += 50;
        std::cout<<"Dodaj 5 bonusów do statystyk(PŻ, PM, Sila, Zwinność, Inteligencja, Szczęście)"<<std::endl;
        for(int i=1; i<=5; i++){
            std::cin>>atrybut;
            if(atrybut == "pz"){
                    stan_gry.bonus = new PZ();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

           }
            else if(atrybut == "pm"){
                    stan_gry.bonus = new PM();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else if(atrybut == "sila"){
                    stan_gry.bonus = new Sila();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else if(atrybut == "zwinnosc"){
                    stan_gry.bonus = new Zwinnosc();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else if(atrybut == "inteligencja"){
                    stan_gry.bonus = new Inteligencja();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else if(atrybut == "szczescie"){
                    stan_gry.bonus = new Szczescie();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else{
            std::cout<<"Nie ma takiego atrybutu."<<std::endl;
            i-=1;
           }
        }
        std::cout<<"To już wszystko."<<std::endl;
}
void Gracz::atak_magia_przeciwnika(Przeciwnik &przeciwnik,int ile_many){
        int czy_kryt = rand()%101;
        pm -= ile_many;
        if(ma-przeciwnik.obrona>=0){
            if(czy_kryt <= sz*0.5){
                std::cout<<"Atak krytykiem"<<std::endl;
                przeciwnik.pz -= (4*ma-przeciwnik.obrona);
        }
            else{
                    przeciwnik.pz -= (ma-przeciwnik.obrona);
            }
        }
        if (przeciwnik.pz <= 0){
            std::cout << "Zabito przeciwnika - " << przeciwnik.nazwa << std::endl;
            std::cout << "Zdobyto " << przeciwnik.pd << " doświadczenia i " << przeciwnik.zloto << " złota" <<std::endl;
            stan_gry.pd += przeciwnik.pd;
            stan_gry.zloto += przeciwnik.zloto;
        }
        else{
            if(this->ma-przeciwnik.obrona > 0){
                std::cout << "Zadałeś " << this->ma-przeciwnik.obrona << " obrażeń przeciwnikowi " << przeciwnik.nazwa <<". Zostało mu "<< przeciwnik.pz<< std::endl;
            }
            else{
                std::cout << "Nie zadałeś żadnych obrażeń przeciwnikowi " << przeciwnik.nazwa <<". Zostało mu "<< przeciwnik.pz<< std::endl;
            }
        }
        std::cout<<"Zużywasz "<<ile_many<<" many na ten atak i zostało ci " << stan_gry.gracz->pm << " many." <<std::endl;
}
void Gracz::atak_przeciwnika(Przeciwnik &przeciwnik){
        int czy_kryt = rand()%101;
        if(ak-przeciwnik.obrona>=0){
            if(czy_kryt <= sz*0.5){
            std::cout<<"Atak krytykiem"<<std::endl;
            przeciwnik.pz -= (4*ak-przeciwnik.obrona);
        }
        else{
            przeciwnik.pz -= (ak-przeciwnik.obrona);
        }
        }
        if (przeciwnik.pz <= 0){
            std::cout << "Zabito przeciwnika - " << przeciwnik.nazwa << std::endl;
            std::cout << "Zdobyto " << przeciwnik.pd << " doświadczenia i " << przeciwnik.zloto << " złota" <<std::endl;
            stan_gry.pd += przeciwnik.pd;
            stan_gry.zloto += przeciwnik.zloto;
        }
        else{
            if(this->ak-przeciwnik.obrona>0){
                std::cout<<ak<<std::endl;
                std::cout << "Zadałeś " << this->ak-przeciwnik.obrona << " obrażeń przeciwnikowi " << przeciwnik.nazwa <<". Zostało mu "<< przeciwnik.pz<< std::endl;
            }
            else{
                std::cout << "Zadałeś " << 0 << " obrażeń przeciwnikowi " << przeciwnik.nazwa <<". Zostało mu "<< przeciwnik.pz<< std::endl;
            }
        }
    }
Gracz::Gracz(std::string imie, std::string nazwisko, int start_pz, int start_pm, int atak, int magiczny_atak, int obrona, int sila,  int zwinnosc, int inteligencja, int szczescie) {
        this->imie = imie;
        this->nazwisko = nazwisko;

        pz = start_pz;
        pm = start_pm;
        ak = atak;
        ma = magiczny_atak;
        obr = obrona;
        sl = sila;
        zw = zwinnosc;
        in = inteligencja;
        sz = szczescie;
        max_pz = start_pz;
        max_pm = start_pm;
}

struct StanGry stan_gry;

void Gracz::wypisz_statystyki() {
        std::cout <<"Mam " << pz << " PŻ, " << pm << " PM, " << ak << " ataku, " << ma << " ataku magią, "  << obr  << " obrony, " << sl << " siły, " << zw << " zwinności, " << in << " inteligencji i " << sz << " szczęścia." << std::endl;
}
Wojownik::Wojownik(std::string imie, std::string nazwisko) : Gracz(imie, nazwisko, 40, 0, 24, 2, 8, 24, 8, 2, 1) {}

void Wojownik::opis_klasy() {
        std::fstream wojownik;
        std::string opis_wojownika;
        wojownik.open("wojownik.txt");
        if(!wojownik) std::cout<<"Wybacz, ale wojownik został zabity"<<std::endl;
        else while(!wojownik.eof()){
            getline(wojownik,opis_wojownika);
            std::cout<<opis_wojownika<<std::endl;
        }
        wojownik.close();
    }

Magik::Magik(std::string imie, std::string nazwisko) : Gracz(imie, nazwisko, 20, 50, 5, 30, 9, 5, 9, 30, 3) {}

void Magik::opis_klasy() {
        std::fstream magik;
        std::string opis_magika;
        magik.open("magik.txt");
        if(!magik) std::cout<<"Wybacz, ale magik został zabity"<<std::endl;
        else while(!magik.eof()){
            getline(magik,opis_magika);
            std::cout<<opis_magika<<std::endl;
        }
        magik.close();
    }

Silacz::Silacz(std::string imie, std::string nazwisko) : Gracz(imie, nazwisko, 15, 0, 40, 0, 15, 40, 15, 0, 0) {}

void Silacz::opis_klasy() {
        std::fstream silacz;
        std::string opis_silacza;
        silacz.open("silacz.txt");
        if(!silacz) std::cout<<"Wybacz, ale silacz został zabity"<<std::endl;
        else while(!silacz.eof()){
            getline(silacz,opis_silacza);
            std::cout<<opis_silacza<<std::endl;
        }
        silacz.close();
    }
Lotrzyk::Lotrzyk(std::string imie, std::string nazwisko) : Gracz(imie, nazwisko, 25, 10, 15, 7, 28, 15, 28, 7, 15) {}

void Lotrzyk::opis_klasy() {
        std::fstream lotrzyk;
        std::string opis_lotrzyka;
        lotrzyk.open("lotrzyk.txt");
        if(!lotrzyk) std::cout<<"Wybacz, ale lotrzyk został zabity"<<std::endl;
        else while(!lotrzyk.eof()){
            getline(lotrzyk,opis_lotrzyka);
            std::cout<<opis_lotrzyka<<std::endl;
        }
        lotrzyk.close();
    }

void Czlowiek::dodaj_bonusy(Gracz* gracz){
        gracz->pz+=4;
        gracz->max_pz+=4;
        gracz->pm+=4;
        gracz->max_pm+=4;
        gracz->sl+=4;
        gracz->ak+=4;
        gracz->in+=4;
        gracz->ma+=4;
        gracz->zw+=4;
        gracz->obr+=4;
        gracz->sz+=4;
    }
void Czlowiek::opis_rasy() {
        std::fstream czlowiek;
        std::string opis_czlowieka;
        czlowiek.open("czlowiek.txt");
        if(!czlowiek) std::cout<<"Wybacz, ale ludzie wygineli"<<std::endl;
        else while(!czlowiek.eof()){
            getline(czlowiek,opis_czlowieka);
            std::cout<<opis_czlowieka<<std::endl;
        }
        czlowiek.close();
    }

void Elf::dodaj_bonusy(Gracz* gracz){
        gracz->pz+=1;
        gracz->max_pz+=1;
        gracz->pm+=3;
        gracz->max_pm+=3;
        gracz->sl+=5;
        gracz->ak+=5;
        gracz->in+=3;
        gracz->ma+=3;
        gracz->zw+=11;
        gracz->obr+=11;
        gracz->sz+=5;
    }
void Elf::opis_rasy() {
        std::fstream elf;
        std::string opis_elfa;
        elf.open("elf.txt");
        if(!elf) std::cout<<"Wybacz, ale elfowie wygineli"<<std::endl;
        else while(!elf.eof()){
            getline(elf,opis_elfa);
            std::cout<<opis_elfa<<std::endl;
        }
        elf.close();
}

void Gnom::dodaj_bonusy(Gracz* gracz){
        gracz->pz-=5;
        gracz->max_pz-=5;
        gracz->pm+=7;
        gracz->max_pm+=7;
        gracz->in+=10;
        gracz->ma+=10;
        gracz->zw+=7;
        gracz->obr+=7;
        gracz->sz+=9;

    }

void Gnom::opis_rasy() {
        std::fstream gnom;
        std::string opis_gnoma;
        gnom.open("gnom.txt");
        if(!gnom) std::cout<<"Wybacz, ale gnomy wygineły"<<std::endl;
        else while(!gnom.eof()){
            getline(gnom,opis_gnoma);
            std::cout<<opis_gnoma<<std::endl;
        }
        gnom.close();
    }

void Krasnolud::dodaj_bonusy(Gracz* gracz){
        gracz->pz+=9;
        gracz->max_pz+=9;
        gracz->sl+=10;
        gracz->ak+=10;
        gracz->zw+=3;
        gracz->obr+=3;
        gracz->sz+=6;
    }
void Krasnolud::opis_rasy() {
        std::fstream krasnolud;
        std::string opis_krasnoluda;
        krasnolud.open("krasnolud.txt");
        if(!krasnolud) std::cout<<"Wybacz, ale krasnoludy wygineły"<<std::endl;
        else while(!krasnolud.eof()){
            getline(krasnolud,opis_krasnoluda);
            std::cout<<opis_krasnoluda<<std::endl;
        }
        krasnolud.close();
    }
    void PZ::dodatkowe_punkty(Gracz* gracz){
        gracz->pz+=1;
        gracz->max_pz+=1;
    }

     void PM::dodatkowe_punkty(Gracz* gracz){
        gracz->pm+=1;
        gracz->max_pm+=1;
    }


    void Sila::dodatkowe_punkty(Gracz* gracz){
        gracz->sl+=1;
        gracz->ak+=1;
    }

    void Zwinnosc::dodatkowe_punkty(Gracz* gracz){
        gracz->zw+=1;
        gracz->obr+=1;
    }
    void Inteligencja::dodatkowe_punkty(Gracz* gracz){
        gracz->in+=1;
        gracz->ma+=1;
    }
    void Szczescie::dodatkowe_punkty(Gracz* gracz){
        gracz->sz+=1;
    }


void wypisz_plec(enum plec p){
    if(p == mezczyzna) std::cout<<"Mężczyzna"<<std::endl;
    else std::cout<<"Kobieta"<<std::endl;

}
void wypisz_klase(enum klasa k){
    if(k == wojownik) std::cout<<"wojownik"<<std::endl;
    else if(k == silacz) std::cout<<"siłacz"<<std::endl;
    else if(k == magik) std::cout<<"magik"<<std::endl;
    else std::cout<<"łotrzyk"<<std::endl;
}

void wypisz_rase(enum rasa_g r){
    if(r == czlowiek) std::cout<<"człowiek"<<std::endl;
    else if(r == elf) std::cout<<"elf"<<std::endl;
    else if(r == gnom) std::cout<<"gnom"<<std::endl;
    else std::cout<<"krasnolud"<<std::endl;
}

int main() {
    std::string komenda;
    std::string profesja;
    std::string rasa_p;
    std::string atrybut;
    std::string plec;

    std::cout<<std::setfill('*')<<std::setw(24)<<"*"<<std::endl;
    std::cout<<"*    Czarnoksiężnik    *"<<std::endl;
    std::cout<<std::setfill('*')<<std::setw(24)<<"*"<<std::endl;
    std::cout<<"Rozpocznij Grę"<<std::endl;
    std::cout<<"Wczytaj Grę"<<std::endl;
    std::cout<<"Pomoc"<<std::endl;
    std::cout<<"Wyjście"<<std::endl;
    do{
    getline(std::cin,komenda);
    if(komenda=="rozpocznij gre"){
        std::fstream historia;
        std::string prolog;
        historia.open("historia.txt");
        while(!historia.eof()){
            getline(historia,prolog);
            std::cout<<prolog<<std::endl;
        }
        historia.close();
        std::cout<<"Witaj podróżniku"<<std::endl;
        delete stan_gry.gracz;
        do{
        std::cout<<"Jak masz na imię"<<std::endl;
        std::cin>>stan_gry.imie;
        std::cout<<"Jak masz na nazwisko"<<std::endl;
        std::cin>>stan_gry.nazwisko;
            std::cout<<"Jaką masz klasę? Masz do wyboru: wojownik, siłacz, magik, łotrzyk"<<std::endl;
            do{
            std::cin>>profesja;
            if(profesja == "wojownik"){
                    stan_gry.klasa = wojownik;
                    stan_gry.gracz = new Wojownik(stan_gry.imie,stan_gry.nazwisko);
            }


            else if(profesja == "magik"){
                    stan_gry.klasa = magik;
                    stan_gry.gracz = new Magik(stan_gry.imie,stan_gry.nazwisko);
            }

            else if(profesja == "silacz"){
                    stan_gry.klasa = silacz;
                    stan_gry.gracz = new Silacz(stan_gry.imie,stan_gry.nazwisko);
            }

            else if(profesja == "lotrzyk"){
                    stan_gry.klasa = lotrzyk;
                    stan_gry.gracz = new Lotrzyk(stan_gry.imie,stan_gry.nazwisko);
            }
            else std::cout<<"Nie ma takiej klasy, proszę wybrać odpowiednią"<<std::endl;
            }while(stan_gry.gracz == NULL);
            stan_gry.gracz->opis_klasy();
            stan_gry.gracz->wypisz_statystyki();
        std::cout<<"Podaj swoją rasę. Masz do wyboru: człowiek, elf, gnom, krasnolud"<<std::endl;
        do{
        std::cin>>rasa_p;
        if(rasa_p == "czlowiek"){
            stan_gry.rasa_g = czlowiek;
            stan_gry.rasa = new Czlowiek();
        }
        else if(rasa_p == "elf"){
            stan_gry.rasa_g = elf;
            stan_gry.rasa = new Elf();
        }
        else if(rasa_p == "gnom"){
            stan_gry.rasa_g = gnom;
            stan_gry.rasa = new Gnom();
        }
        else if(rasa_p == "krasnolud"){
            stan_gry.rasa_g = krasnolud;
            stan_gry.rasa = new Krasnolud();
        }
        else std::cout<<"Taka rasa nie istnieje, proszę wybrać inną"<<std::endl;
        }while(stan_gry.rasa == NULL);
        stan_gry.rasa->opis_rasy();
        stan_gry.rasa->dodaj_bonusy(stan_gry.gracz);
        stan_gry.gracz->wypisz_statystyki();
        std::cout<<"Masz jeszcze 10 punktów do wykorzystania"<<std::endl;
        for(int i=1; i<=10; i++){
            std::cin>>atrybut;
            if(atrybut == "pz"){
                    stan_gry.bonus = new PZ();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

           }
            else if(atrybut == "pm"){
                    stan_gry.bonus = new PM();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else if(atrybut == "sila"){
                    stan_gry.bonus = new Sila();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else if(atrybut == "zwinnosc"){
                    stan_gry.bonus = new Zwinnosc();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else if(atrybut == "inteligencja"){
                    stan_gry.bonus = new Inteligencja();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else if(atrybut == "szczescie"){
                    stan_gry.bonus = new Szczescie();
                    stan_gry.bonus->dodatkowe_punkty(stan_gry.gracz);

            }
            else{
            std::cout<<"Nie ma takiego atrybutu."<<std::endl;
            i-=1;
           }
        }
        stan_gry.gracz->wypisz_statystyki();
        std::cout<<"Podaj płeć"<<std::endl;
        do{
        std::cin>>plec;
        if(plec == "mezczyzna"){
            stan_gry.plec = mezczyzna;
        }
        else if(plec == "kobieta"){
            stan_gry.plec = kobieta;
        }
        else std::cout<<"Nie ma takiej płci"<<std::endl;
        }while(plec != "mezczyzna" && plec != "kobieta");
        std::cout<<stan_gry.imie<<std::endl;
        std::cout<<stan_gry.nazwisko<<std::endl;
        wypisz_klase(stan_gry.klasa);
        wypisz_rase(stan_gry.rasa_g);
        wypisz_plec(stan_gry.plec);
        stan_gry.gracz->wypisz_statystyki();
        std::cout<<"To ty?"<<std::endl;
        do{
        std::cin>>komenda;
        if(komenda != "nie" && komenda != "tak") std::cout<<"Nie rozumiem, możesz powtórzyć?"<<std::endl;
        }while(komenda != "nie" && komenda != "tak");
        }while(komenda != "tak");
        mapa();
        return 0;
    }
    else if(komenda == "wczytaj gre"){
        odczyt();
        std::cout<<"Gra wczytana"<<std::endl;
        mapa();
    }
    else if(komenda=="pomoc"){
        std::fstream pomoc;
        pomoc.open("pomoc.txt");
        std::string opis_pomoc;
        if(!pomoc) std::cout<<"Bohater nie potrzebuje pomocy"<<std::endl;
        else while(!pomoc.eof()){
            getline(pomoc,opis_pomoc);
            std::cout<<opis_pomoc<<std::endl;
        }
        pomoc.close();
    }
    else if(komenda=="wyjscie"){
        std::cout<<"Żegnaj"<<std::endl;
        return 0;
    }
    else std::cout<<"Nie ma takiego polecenia"<<std::endl;
    }while((komenda != "rozpocznij gre" && komenda != "wczytaj gre" && komenda != "wyjscie") || komenda == "pomoc");
}
