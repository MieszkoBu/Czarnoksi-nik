#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <tuple>
#include <conio.h>
#include "mapa.hpp"
#include "klasa.hpp"
enum pole {
    las = 'l', jezioro = 'j', dom = 'd', brama = 'n', brama_z = 'i', brama_r = 'g', brama_cz = 'd', ruiny = 'y',
    akademia_magii = 'a', bariera = 'b', skaly = 's', sklep_z_bronia = 'u', szpital = 'x',
    sklep = 'p', gildia_wojownikow = 'w', gildia_silaczy = 'c', gildia_lotrzykow = 'k', lodka = 'o', miasto = 'm', mur = 'r',
    zamek = 'z', zamek_cz = 'f', pole = 'e', leze = 'q', skarb = 'v', spacja = '/'
};
void zapisz(enum plec p,enum klasa k,enum rasa_g r, int poz, int pio, std::vector<Przedmiot> przedmioty, std::vector<Zadanie> zadania, Przedmiot zalozona_bron, Przedmiot zalozona_zbroja){
    std::ofstream zapis;
    zapis.open("zapis.txt");
    zapis<<stan_gry.gracz->imie << std::endl << stan_gry.gracz->nazwisko << std::endl;
    if(p == mezczyzna){
        zapis<<"mezczyzna"<<std::endl;
    }
    else if(p == kobieta){
        zapis<<"kobieta"<<std::endl;
    }
    if(r == czlowiek) zapis<<"czlowiek"<<std::endl;
    else if(r == elf) zapis<<"elf"<<std::endl;
    else if(r == gnom) zapis<<"gnom"<<std::endl;
    else if (r == krasnolud) zapis<<"krasnolud"<<std::endl;
    if(k == wojownik) zapis<<"wojownik"<<std::endl;
    else if(k == silacz) zapis<<"silacz"<<std::endl;
    else if(k == magik) zapis<<"magik"<<std::endl;
    else if (k == lotrzyk) zapis<<"lotrzyk"<<std::endl;
    zapis << stan_gry.gracz->max_pz << std::endl << stan_gry.gracz->max_pm << std::endl << stan_gry.gracz->pz << std::endl << stan_gry.gracz->pm << std::endl;
    if(k == magik){
        zapis << stan_gry.gracz->ak << std::endl;
        zapis << stan_gry.gracz->ma-zalozona_bron.wartosc_ataku << std::endl;
    }
    else{
        zapis << stan_gry.gracz->ak-zalozona_bron.wartosc_ataku << std::endl;
        zapis << stan_gry.gracz->ma << std::endl;
    }
    zapis << stan_gry.gracz->obr-zalozona_zbroja.wartosc_obrony << std::endl << stan_gry.gracz->sl <<  std::endl <<
    stan_gry.gracz->zw << std::endl << stan_gry.gracz->in << std::endl << stan_gry.gracz->sz << std::endl << stan_gry.poziom << std::endl << stan_gry.pd << std::endl << stan_gry.zloto << std::endl << stan_gry.pd_do_nastepnego_poziomu << std::endl << stan_gry.poz << std::endl <<
    stan_gry.pio <<std::endl << przedmioty.size() << std::endl;
    for(int i = 0; i < przedmioty.size(); i++){
            zapis << przedmioty[i].nazwa<<std::endl;
    }
    zapis << zadania.size() << std::endl;
    for(int i = 0; i < zadania.size(); i++){
            zapis << zadania[i].opis<<std::endl;
    }
    if(stan_gry.hydra_z == false){
        zapis << "false" << std::endl;
    }
    else{
        zapis << "true" << std::endl;
    }
    if(stan_gry.smok_z == false){
        zapis << "false" << std::endl;
    }
    else{
        zapis << "true" << std::endl;
    }
    if(stan_gry.hydra_zad == false){
        zapis << "false" << std::endl;
    }
    else{
        zapis << "true" << std::endl;
    }
    if(stan_gry.smok_zad == false){
        zapis << "false" << std::endl;
    }
    else{
        zapis << "true" << std::endl;
    }
    if(stan_gry.hydra_w == false){
        zapis << "false" << std::endl;
    }
    else{
        zapis << "true" << std::endl;
    }
    if(stan_gry.smok_w == false){
        zapis << "false" << std::endl;
    }
    else{
        zapis << "true" << std::endl;
    }
    if(stan_gry.zad_smok == false){
        zapis << "false" << std::endl;
    }
    else{
        zapis << "true" << std::endl;
    }
    if(stan_gry.zad_hydra == false){
        zapis << "false" << std::endl;
    }
    else{
        zapis << "true" << std::endl;
    }
    if(stan_gry.czar_zad == false){
        zapis << "false" << std::endl;
    }
    else{
        zapis << "true" << std::endl;
    }
    zapis.close();
    std::cout<<"Gra zapisana"<<std::endl;
}
void odczyt(){
    std::ifstream odczyt;
    std::string wiersz;
    int l=0;
    int pl = 0;
    int zl = 0;
    odczyt.open("zapis.txt");
    while(!odczyt.eof()){
        getline(odczyt,wiersz);
        if(l == 22){
            pl = stoi(wiersz);
        }
        if(l == 23 + pl){
            zl = stoi(wiersz);
        }
        if(l == 0){
        stan_gry.imie = wiersz;
        }
        else if(l == 1){
        stan_gry.nazwisko = wiersz;
        }
         else if(l == 2){
            if(wiersz == "mezczyzna"){
                stan_gry.plec = mezczyzna;
            }
            else if(wiersz == "kobieta"){
                stan_gry.plec = kobieta;
            }
        }
         else if(l == 3){
            if(wiersz == "czlowiek") {
                    stan_gry.rasa_g = czlowiek;
                    stan_gry.rasa = new Czlowiek();
            }
            else if(wiersz == "elf"){
                    stan_gry.rasa_g = elf;
                    stan_gry.rasa = new Elf();
            }
            else if(wiersz == "gnom") {
                    stan_gry.rasa_g = gnom;
                    stan_gry.rasa = new Gnom();
            }
            else if (wiersz == "krasnolud") {
                    stan_gry.rasa_g = krasnolud;
                    stan_gry.rasa = new Krasnolud();
            }
        }
        else if(l == 4){
            if(wiersz == "wojownik") {
                    stan_gry.klasa = wojownik;
                    stan_gry.gracz = new Wojownik(stan_gry.imie,stan_gry.nazwisko);
            }
            else if(wiersz == "silacz") {
                    stan_gry.klasa = silacz;
                    stan_gry.gracz = new Silacz(stan_gry.imie,stan_gry.nazwisko);
            }
            else if(wiersz == "magik") {
                    stan_gry.klasa = magik;
                    stan_gry.gracz = new Magik(stan_gry.imie,stan_gry.nazwisko);
            }
            else if (wiersz == "lotrzyk") {
                    stan_gry.klasa = lotrzyk;
                    stan_gry.gracz = new Lotrzyk(stan_gry.imie,stan_gry.nazwisko);
            }
        }
        else if(l == 5){
        stan_gry.gracz->max_pz = stoi(wiersz);
        }
        else if(l == 6){
        stan_gry.gracz->max_pm = stoi(wiersz);
        }
        else if(l == 7){
        stan_gry.gracz->pz = stoi(wiersz);
        }
        else if(l == 8){
        stan_gry.gracz->pm = stoi(wiersz);
        }
        else if(l == 9){
        stan_gry.gracz->ak = stoi(wiersz);
        }
        else if(l == 10){
        stan_gry.gracz->ma = stoi(wiersz);
        }
        else if(l == 11){
        stan_gry.gracz->obr = stoi(wiersz);
        }
        else if(l == 12){
        stan_gry.gracz->sl = stoi(wiersz);
        }
        else if(l == 13){
        stan_gry.gracz->zw = stoi(wiersz);
        }
        else if(l == 14){
        stan_gry.gracz->sz = stoi(wiersz);
        }
        else if(l == 15){
        stan_gry.gracz->in = stoi(wiersz);
        }
        else if(l == 16){
        stan_gry.poziom = stoi(wiersz);
        }
        else if(l == 17){
        stan_gry.pd = stoi(wiersz);
        }
        else if(l == 18){
        stan_gry.zloto = stoi(wiersz);
        }
        else if(l == 19){
        stan_gry.pd_do_nastepnego_poziomu = stoi(wiersz);
        }
        else if(l == 20){
        stan_gry.poz = stoi(wiersz);
        }
        else if(l == 21){
        stan_gry.pio = stoi(wiersz);
        }
         if(l == 22){
            if(pl != 0){
            for(int i = 0;i<pl;i++){
            l++;
            getline(odczyt,wiersz);
            Przedmiot miecz_szeroki("Miecz szeroki", 150, 0, 0, 0, 500, 10, "Bron");
            Przedmiot miecz_dwureczny("Miecz dwuręczny", 200, 0, 0, 0, 1500, 30, "Bron");
            Przedmiot smoczy_miecz("Smoczy miecz", 300, 0, 0, 0, 10000, 20, "Bron");
            Przedmiot pancerz("Pancerz", 0, 50, 0, 0, 1500, 15, "zbroja");
            Przedmiot smoczy_pancerz("Smoczy pancerz", 0, 150, 0, 0, 10000, 25, "zbroja");
            Przedmiot stalowe_rekawice("Stalowe rękawice", 150, 0, 0, 0, 500, 10, "Bron");
            Przedmiot tytanowe_rekawice("Tytanowe rękawice", 200, 0, 0, 0, 1500, 30, "Bron");
            Przedmiot smocze_rekawice("Smocze rękawice", 300, 0, 0, 0, 10000, 20, "Bron");
            Przedmiot kolczuga("Kolczuga", 0, 50, 0, 0, 1500, 15, "zbroja");
            Przedmiot smocza_kolczuga("Smocza kolczuga", 0, 150, 0, 0, 10000, 25, "zbroja");
            Przedmiot sztylet("Sztylet", 150, 0, 0, 0, 500, 10, "Bron");
            Przedmiot obsydianowy_sztylet("Obsydianowy sztylet", 200, 0, 0, 0, 1500, 30, "Bron");
            Przedmiot smoczy_sztylet("Smoczy sztylet", 300, 0, 0, 0, 10000, 20, "Bron");
            Przedmiot skora("Skóra", 0, 50, 0, 0, 1500, 15, "zbroja");
            Przedmiot smocza_skora("Smocza skóra", 0, 150, 0, 0, 10000, 25, "zbroja");
            Przedmiot dluga_laska("Długa laska", 150, 0, 0, 0, 500, 10, "Bron");
            Przedmiot zlota_laska("Złota laska", 200, 0, 0, 0, 1500, 30, "Bron");
            Przedmiot smocza_laska("Smocza laska", 300, 0, 0, 0, 10000, 20, "Bron");
            Przedmiot szaty("Szaty", 0, 50, 0, 0, 1500, 15, "zbroja");
            Przedmiot smocze_szaty("Smocze szaty", 0, 150, 0, 0, 10000, 25, "zbroja");
            Przedmiot mikstura_zdrowia("Mikstura zdrowia", 0, 0, 40, 0, 50, 5, "mikstura");
            Przedmiot mikstura_many("Mikstura many", 0, 0, 0, 40, 50, 5, "mikstura");
            if(wiersz == "Miecz szeroki"){
                stan_gry.przedmioty.push_back(miecz_szeroki);
                stan_gry.ciezar += miecz_szeroki.ciezar;
            }
            else if(wiersz == "Miecz dwuręczny"){
                stan_gry.przedmioty.push_back(miecz_dwureczny);
                stan_gry.ciezar += miecz_dwureczny.ciezar;
            }
            else if(wiersz == "Smoczy miecz"){
                stan_gry.przedmioty.push_back(smoczy_miecz);
                stan_gry.ciezar += smoczy_miecz.ciezar;
            }
            else if(wiersz == "Pancerz"){
                stan_gry.przedmioty.push_back(pancerz);
                stan_gry.ciezar += pancerz.ciezar;
            }
            else if(wiersz == "Smoczy pancerz"){
                stan_gry.przedmioty.push_back(smoczy_pancerz);
                stan_gry.ciezar += smoczy_pancerz.ciezar;
            }
            else if(wiersz == "Stalowe rękawice"){
                stan_gry.przedmioty.push_back(stalowe_rekawice);
                stan_gry.ciezar += stalowe_rekawice.ciezar;
            }
            else if(wiersz == "Tytanowe rękawice"){
                stan_gry.przedmioty.push_back(tytanowe_rekawice);
                stan_gry.ciezar += tytanowe_rekawice.ciezar;
            }
            else if(wiersz == "Smocze rękawice"){
                stan_gry.przedmioty.push_back(smocze_rekawice);
                stan_gry.ciezar += smocze_rekawice.ciezar;
            }
            else if(wiersz == "Kolczuga"){
                stan_gry.przedmioty.push_back(kolczuga);
                stan_gry.ciezar += kolczuga.ciezar;
            }
            else if(wiersz == "Smocza kolczuga"){
                stan_gry.przedmioty.push_back(smocza_kolczuga);
                stan_gry.ciezar += smocza_kolczuga.ciezar;
            }
            else if(wiersz == "Sztylet"){
                stan_gry.przedmioty.push_back(sztylet);
                stan_gry.ciezar += sztylet.ciezar;
            }
            else if(wiersz == "Obsydianowy sztylet"){
                stan_gry.przedmioty.push_back(obsydianowy_sztylet);
                stan_gry.ciezar += obsydianowy_sztylet.ciezar;
            }
            else if(wiersz == "Smoczy sztylet"){
                stan_gry.przedmioty.push_back(smoczy_sztylet);
                stan_gry.ciezar += smoczy_sztylet.ciezar;
            }
            else if(wiersz == "Skóra"){
                stan_gry.przedmioty.push_back(skora);
                stan_gry.ciezar += skora.ciezar;
            }
            else if(wiersz == "Smocza skóra"){
                stan_gry.przedmioty.push_back(smocza_skora);
                stan_gry.ciezar += smocza_skora.ciezar;
            }
            else if(wiersz == "Długa laska"){
                stan_gry.przedmioty.push_back(dluga_laska);
                stan_gry.ciezar += dluga_laska.ciezar;
            }
            else if(wiersz == "Złota laska"){
                stan_gry.przedmioty.push_back(zlota_laska);
                stan_gry.ciezar += zlota_laska.ciezar;
            }
            else if(wiersz == "Smocza laska"){
                stan_gry.przedmioty.push_back(smocza_laska);
                stan_gry.ciezar += smocza_laska.ciezar;
            }
            else if(wiersz == "Szaty"){
                stan_gry.przedmioty.push_back(szaty);
                stan_gry.ciezar += szaty.ciezar;
            }
            else if(wiersz == "Smocze szaty"){
                stan_gry.przedmioty.push_back(smocze_szaty);
                stan_gry.ciezar += smocze_szaty.ciezar;
            }
            else if(wiersz == "Mikstura zdrowia"){
                stan_gry.przedmioty.push_back(mikstura_zdrowia);
                stan_gry.ciezar += mikstura_zdrowia.ciezar;
            }
            else if(wiersz == "Mikstura many"){
                stan_gry.przedmioty.push_back(mikstura_many);
                stan_gry.ciezar += mikstura_many.ciezar;
            }
            else{
                std::cout<<"Nie znaleziono przedmiotu " << wiersz <<std::endl;
            }
            }
        }
        }
        else if(l == 23 + pl){
            if(zl != 0){
            for(int i=0;i<zl;i++){
            l++;
            getline(odczyt,wiersz);
            stan_gry.zadania.push_back(Zadanie(wiersz));
            }
        }
        }
        else if(l == 24 + pl + zl){
            if(wiersz == "true"){
                stan_gry.hydra_z = true;
            }
            else{
                stan_gry.hydra_z = false;
            }
        }
        else if(l == 25 + pl + zl){
            if(wiersz == "true"){
                stan_gry.smok_z = true;
            }
            else{
                stan_gry.smok_z = false;
            }
        }
        else if(l == 26 + pl + zl){
            if(wiersz == "true"){
                stan_gry.hydra_zad = true;
            }
            else{
                stan_gry.hydra_zad = false;
            }
        }
        else if(l == 27 + pl + zl){
            if(wiersz == "true"){
                stan_gry.smok_zad = true;
            }
            else{
                stan_gry.smok_zad = false;
            }
        }
        else if(l == 28 + pl + zl){
            if(wiersz == "true"){
                stan_gry.hydra_w = true;
            }
            else{
                stan_gry.hydra_w = false;
            }
        }
        else if(l == 29 + pl + zl){
            if(wiersz == "true"){
                stan_gry.smok_w = true;
            }
            else{
                stan_gry.smok_w = false;
            }
        }
        else if(l == 30 + pl + zl){
            if(wiersz == "true"){
                stan_gry.zad_smok = true;
            }
            else{
                stan_gry.zad_smok = false;
            }
        }
        else if(l == 31 + pl + zl){
            if(wiersz == "true"){
                stan_gry.zad_hydra = true;
            }
            else{
                stan_gry.zad_hydra = false;
            }
        }
        else if(l == 32 + pl + zl){
            if(wiersz == "true"){
                stan_gry.czar_zad = true;
            }
            else{
                stan_gry.czar_zad = false;
            }
        }
        l++;

    }
    odczyt.close();
}
int walka(Przeciwnik przeciwnik){
            while(przeciwnik.pz > 0 && stan_gry.gracz->pz > 0){
                std::string akcja;
                std::cout << "Co zamierzasz zrobić (atak,magia,ucieczka)" << std::endl;
                do{
                std::cin >> akcja;
                if(akcja == "atak"){
                   stan_gry.gracz->atak_przeciwnika(przeciwnik);
                }
                else if(akcja == "magia"){
                    int ile_many = rand()%11;
                    if(stan_gry.gracz->pm-ile_many >= 0){
                    stan_gry.gracz->atak_magia_przeciwnika(przeciwnik,ile_many);
                    }
                    else std::cout<<"Nie masz wystarczająco many, tracisz kolejkę."<<std::endl;
                }
                else if(akcja == "ucieczka"){
                    int czy_u;
                    czy_u = rand()%101;
                    if(czy_u < 50+stan_gry.gracz->zw-przeciwnik.obrona){
                        std::cout<<"Udało się uciec"<<std::endl;
                        return true;
                    }
                    else {
                        std::cout<<"Nie udało się uciec"<<std::endl;
                    }
                }
                else{
                    std::cout<<"Nie ma takiego ruchu, zrób coś innego."<<std::endl;
                }
                }while(akcja !="atak" && akcja != "magia" && akcja != "ucieczka");
                if(przeciwnik.pz > 0){
                    if(przeciwnik.atak > przeciwnik.magiczny_atak || przeciwnik.pm == 0){
                    przeciwnik.atak_gracza(*(stan_gry.gracz));
                    }
                    else {
                        int ile_many = rand()%11;
                        if(przeciwnik.pm - ile_many >= 0){
                        przeciwnik.atak_magia_gracza(*(stan_gry.gracz),ile_many);
                        }
                        else std::cout<<przeciwnik.nazwa<<" próbował cię zaatakować magią, ale nie miał wystarczająco dużo many."<<std::endl;
                    }
                }

            }
}



int miejsce(enum pole p, int poz, int pio, char mapa_g[41][35], std::string komenda, char pozpol, char pozpoln, char pozzach, char pozwschod, Ekwipunek plecak, enum plec pl, enum rasa_g r,enum klasa k, Dziennik dziennik, bool hydra_z, bool smok_z,bool czar_zad,int pozpio){
    std::fstream lokacja;
    lokacja.open("pozycja.txt");
    std::string l2;
    int linia = 0;
    if(poz == 4 && pio == 11){
        if(hydra_z == false){
            std::cout<<"Zbliżasz się do rzeki, wyczuwasz niebezpieczeństwo, chcesz podejść?"<<std::endl;
        do{
            std::cin>>komenda;
            if(komenda == "tak"){
                std::cout<<"Gdy zbliżasz się do rzeki, z niej wychodzi ogromny potwór z wieloma głowami, atakuje ciebie."<<std::endl;
                Przeciwnik hydra("Hydra", 1000, 900, 200, 300, 100, 10, 5000, 10000);
                //Przeciwnik hydra("Hydra", 5, 5, 5, 5, 5, 5, 5, 5);
                walka(hydra);
                if(pl == mezczyzna){
                    std::cout<<"Pokonałeś hydrę."<<std::endl;
                }
                else if(pl == kobieta){
                    std::cout<<"Pokonałaś hydrę."<<std::endl;
                }
            }
            else if(komenda == "nie"){
                std::cout<<"Zawracasz"<<std::endl;
                return false;
            }
            else{
                std::cout<<"Nie rozumiem, możesz powtórzyć?"<<std::endl;
            }
        }while(komenda !="tak" && komenda!="nie");
        }
        else if(hydra_z == true){
            std::cout<<"mijasz zwłoki hydry"<<std::endl;
        }
    }
    else if(poz == 12 && pio == 26 && smok_z == false){
            if(smok_z == false){
                std::cout<<"Gdy idziesz w głąb jaskini, atakuje ciebie smok."<<std::endl;
                Przeciwnik smok("Smok", 2000, 0, 350, 0, 150, 15, 6000, 15000);
                //Przeciwnik smok("Smok", 5, 0, 5, 0, 5, 5, 6000, 15000);
                walka(smok);
                if(pl == mezczyzna){
                    std::cout<<"Pokonałeś Smoka."<<std::endl;
                }
                else if(pl == kobieta){
                    std::cout<<"Pokonałaś Smoka."<<std::endl;
                }
            }
            else if(smok_z == true){
                std::cout<<"Mijasz zwłoki smoka."<<std::endl;
            }
    }
    else if(pozpio == 317){
        std::cout<<"Kim jesteś i co tu robisz?"<<std::endl;
        if(pl == mezczyzna){
        std::cout<<"Powiedziałeś królowi, że z rozkazu Pawła jesteś tu, żeby go zabić."<<std::endl;
        }
        else if(pl == kobieta){
        std::cout<<"Powiedziałaś królowi, że z rozkazu Pawła jesteś tu, żeby go zabić."<<std::endl;
        }
        std::cout<<"Atakujesz króla."<<std::endl;
        Przeciwnik Aleks("Aleks",500,0,100,0,50,0,0,0);
        walka(Aleks);
        if(pl == mezczyzna){
        std::cout<<"Zabiłeś króla"<<std::endl;
        }
        else if(pl == kobieta){
        std::cout<<"Zabiłaś króla"<<std::endl;
        }
        std::fstream zakonczenie;
        std::string wiersz;
        int linia = 0;
        zakonczenie.open("zakonczenia.txt");
        while(!zakonczenie.eof()){
            getline(zakonczenie,wiersz);
            if(linia >= 7 && linia <= 11){
            std::cout<<wiersz<<std::endl;
            }
            linia++;
        }
        zakonczenie.close();
        exit(0);
    }
    else if(p == miasto){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 58){
                std::cout<<l2<<std::endl;
            }
        }
        lokacja.close();
    }
    else if(p == zamek){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 64){
                std::cout<<l2<<std::endl;
            }
        }
        int czy_walka=rand()%101;
         if(czy_walka<80){
            if(pl == mezczyzna){
                std::cout<<"Zostałeś zaatakowany"<<std::endl;
            }
            else std::cout<<"Zostałaś zaatakowana"<<std::endl;
            Przeciwnik straznik("Strażnik", 400, 0, 100, 0, 50, 0, 50, 50);
            walka(straznik);
            return true;
         }
        lokacja.close();
    }
    else if(p == las){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 2){
                std::cout<<l2<<std::endl;
            }
        }
       int czy_walka=rand()%101;
         if(czy_walka<70){
            if(pl == mezczyzna){
                std::cout<<"Zostałeś zaatakowany"<<std::endl;
            }
            else std::cout<<"Zostałaś zaatakowana"<<std::endl;
            Przeciwnik goblin("Goblin", 50, 0, 4, 0, 5, 0, 5, 5);
            Przeciwnik trol("Trol", 150, 0, 40, 0, 0, 30, 70, 200);
            int z_kim = rand()%101;
            if(z_kim <= 90){
            walka(goblin);
            }
            else walka(trol);
            return true;
        }
        lokacja.close();
    }
    else if(p == dom){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 8){
                std::cout<<l2<<std::endl;
            }
        }
        std::cout<<"Kim jesteś, wypad z tąd"<<std::endl;
        std::cout<<"Wychodzisz."<<std::endl;
        lokacja.close();
        return false;
    }
    else if(p == ruiny){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 20){
                std::cout<<l2<<std::endl;
            }
        }
        int czy_walka=rand()%101;
         if(czy_walka<80){
            if(pl == mezczyzna){
                std::cout<<"Zostałeś zaatakowany"<<std::endl;
            }
            else std::cout<<"Zostałaś zaatakowana"<<std::endl;
            Przeciwnik szkielet("Szkielet", 300, 0, 100, 0, 30, 0, 100, 400);
            Przeciwnik szkielet_mag("Szkielet mag", 200, 300, 5, 150, 20, 30, 100, 400);
            int z_kim = rand()%101;
            if(z_kim <= 60){
            walka(szkielet);
            }
            else walka(szkielet_mag);
            return true;
        }
        lokacja.close();
    }
    else if(p == akademia_magii){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 24){
                std::cout<<l2<<std::endl;
            }
        }
        lokacja.close();
        if(k != magik){
            if(pl == mezczyzna){
                std::cout<<"Nie jesteś magikiem, nie jesteś godny żeby tu przebywać, wypierdzielaj stąd!!!"<<std::endl;
            }
            else if(pl == kobieta){
                std::cout<<"Nie jesteś magiczką, nie jesteś godna żeby tu przebywać, wypierdzielaj stąd!!!"<<std::endl;
            }
            return false;
        }
        else{
            if(stan_gry.pd >= stan_gry.pd_do_nastepnego_poziomu){
                if(pl == mezczyzna){
                std::cout<<"Witaj magiku widzę, że nabyłeś wystarczająco dużo doświadczenią żeby przejść szkolenie na wyższy poziom, ale będzie cię to kosztowało 100 złota, chcesz wbić wyższy poziom?"<<std::endl;
                }
                else if(pl == kobieta){
                std::cout<<"Witaj magiczko widzę, że nabyłaś wystarczająco dużo doświadczenią żeby przejść szkolenie na wyższy poziom, ale będzie cię to kosztowało 100 złota, chcesz wbić wyższy poziom?"<<std::endl;
                }
                do{
                    std::cin>>komenda;
                    if(komenda == "tak"){
                        if(stan_gry.zloto >= 100){
                            stan_gry.zloto -= 100;
                            stan_gry.gracz->nastepny_poziom();
                            std::cout<<"Wychodzisz."<<std::endl;
                            return false;
                        }
                        else{
                            if(pl == mezczyzna){
                            std::cout<<"Nie stać ciebie, wróć jak będziesz miał odpowiednio dużo złota"<<std::endl;
                            }
                            else if(pl == kobieta){
                            std::cout<<"Nie stać ciebie, wróć jak będziesz miała odpowiednio dużo złota"<<std::endl;
                            }
                            std::cout<<"Wychodzisz."<<std::endl;
                            return false;

                        }
                    }
                    else if(komenda == "nie"){
                         if(pl == mezczyzna){
                            std::cout<<"Wróć jak będziesz chciał podnieść poziom."<<std::endl;
                            }
                        else if(pl == kobieta){
                            std::cout<<"Wróć jak będziesz chciała podnieść poziom."<<std::endl;
                            }
                        std::cout<<"Wychodzisz."<<std::endl;
                        return false;
                    }
                    else{
                        std::cout<<"Nie rozumiem możesz powtórzyć?"<<std::endl;
                    }
                }while(komenda != "tak" && komenda != "nie");
            }
            else{
                std::cout<<"Widzę że nie masz wystarczjąco dużo doświadczenia żeby wbić wyższy poziom, wróć kiedy indziej."<<std::endl;
                std::cout<<"Wychodzisz"<<std::endl;
                return false;
            }
        }
    }
    else if(p == szpital){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 36){
                std::cout<<l2<<std::endl;
                if(pl = mezczyzna){
                    std::cout<<"Witaj podróżniku, chcesz się wyleczyć?"<<std::endl;
                    std::cout<<"Będzie cię to kosztowało 50 złota."<<std::endl;
                }
                else if(pl = kobieta){
                    std::cout<<"Witaj podróżniku, chcesz się wyleczyć?"<<std::endl;
                    std::cout<<"Będzie cię to kosztowało 50 złota."<<std::endl;
                }
                do{
                std::cin>>komenda;
                if(komenda == "tak"){
                    if(stan_gry.zloto-50<0){
                        std::cout<<"Nie stać ciebie, nie mamy czasu dla biedaków, wypad."<<std::endl;
                        return false;
                    }
                    else{
                        stan_gry.zloto -= 50;
                        stan_gry.gracz->pz = stan_gry.gracz->max_pz;
                        stan_gry.gracz->pm = stan_gry.gracz->max_pm;
                        if(pl = mezczyzna){
                            std::cout<<"Zostałeś wyleczony, zapraszamy ponownie."<<std::endl;
                        }
                        else std::cout<<"Zostałaś wyleczony, zapraszamy ponownie."<<std::endl;
                        return false;
                    }
                }
                else if(komenda == "nie"){
                        std::cout<<"Zapraszamy jak będziesz ranny, nigdy nie odmawiamy potrzebującym."<<std::endl;
                        return false;
                    }
                else{
                        std::cout<<"Nie zrozumiałem, możesz powtórzyć"<<std::endl;
                    }
                }while(komenda != "tak" && komenda != "nie");
            }
        }
        lokacja.close();
    }

    else if(p == gildia_wojownikow){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 46){
                std::cout<<l2<<std::endl;
            }
        }
        lokacja.close();
        if(k != wojownik){
            if(pl == mezczyzna){
                    std::cout<<"Nie jesteś wojownikiem, wypierdzielaj stąd!!"<<std::endl;
            }
            else if(pl == kobieta){
                    std::cout<<"Nie jesteś wojowniczką, wypierdzielaj stąd!!"<<std::endl;
            }
            return false;
        }
        else{
            if(stan_gry.pd >= stan_gry.pd_do_nastepnego_poziomu){
                if(pl == mezczyzna){
                std::cout<<"Witaj wojowniku widzę, że nabyłeś wystarczająco dużo doświadczenią żeby przejść szkolenie na wyższy poziom, ale będzie cię to kosztowało 100 złota, chcesz wbić wyższy poziom?"<<std::endl;
                }
                else if(pl == kobieta){
                std::cout<<"Witaj wojowniczko widzę, że nabyłaś wystarczająco dużo doświadczenią żeby przejść szkolenie na wyższy poziom, ale będzie cię to kosztowało 100 złota, chcesz wbić wyższy poziom?"<<std::endl;
                }
                do{
                    std::cin>>komenda;
                    if(komenda == "tak"){
                        if(stan_gry.zloto >= 100){
                            stan_gry.zloto -= 100;
                            stan_gry.gracz->nastepny_poziom();
                            std::cout<<"Wychodzisz."<<std::endl;
                            return false;
                        }
                        else{
                            if(pl == mezczyzna){
                            std::cout<<"Nie stać ciebie, wróć jak będziesz miał odpowiednio dużo złota"<<std::endl;
                            }
                            else if(pl == kobieta){
                            std::cout<<"Nie stać ciebie, wróć jak będziesz miała odpowiednio dużo złota"<<std::endl;
                            }
                            std::cout<<"Wychodzisz."<<std::endl;
                            return false;

                        }
                    }
                    else if(komenda == "nie"){
                         if(pl == mezczyzna){
                            std::cout<<"Wróć jak będziesz chciał podnieść poziom."<<std::endl;
                            }
                        else if(pl == kobieta){
                            std::cout<<"Wróć jak będziesz chciała podnieść poziom."<<std::endl;
                            }
                        std::cout<<"Wychodzisz."<<std::endl;
                        return false;
                    }
                    else{
                        std::cout<<"Nie rozumiem możesz powtórzyć?"<<std::endl;
                    }
                }while(komenda != "tak" && komenda != "nie");
            }
            else{
                std::cout<<"Widzę że nie masz wystarczjąco dużo doświadczenia żeby wbić wyższy poziom, wróć kiedy indziej."<<std::endl;
                std::cout<<"Wychodzisz"<<std::endl;
                return false;
            }
        }
    }
    else if(p == gildia_silaczy){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 48){
                std::cout<<l2<<std::endl;
            }
        }
        lokacja.close();
        if(k != silacz){
            if(pl == mezczyzna){
                std::cout<<"Nie jesteś siłaczem, won!!"<<std::endl;
            }
            else if(pl == kobieta){
                std::cout<<"Nie jesteś siłaczką, won!!"<<std::endl;
            }
            return false;
        }
        else{
            if(stan_gry.pd >= stan_gry.pd_do_nastepnego_poziomu){
                if(pl == mezczyzna){
                std::cout<<"Witaj siłaczu widzę, że nabyłeś wystarczająco dużo doświadczenią żeby przejść szkolenie na wyższy poziom, ale będzie cię to kosztowało 100 złota, chcesz wbić wyższy poziom?"<<std::endl;
                }
                else if(pl == kobieta){
                std::cout<<"Witaj siłaczko widzę, że nabyłaś wystarczająco dużo doświadczenią żeby przejść szkolenie na wyższy poziom, ale będzie cię to kosztowało 100 złota, chcesz wbić wyższy poziom?"<<std::endl;
                }
                do{
                    std::cin>>komenda;
                    if(komenda == "tak"){
                        if(stan_gry.zloto >= 100){
                            stan_gry.zloto -= 100;
                            stan_gry.gracz->nastepny_poziom();
                            std::cout<<"Wychodzisz."<<std::endl;
                            return false;
                        }
                        else{
                            if(pl == mezczyzna){
                            std::cout<<"Nie stać ciebie, wróć jak będziesz miał odpowiednio dużo złota"<<std::endl;
                            }
                            else if(pl == kobieta){
                            std::cout<<"Nie stać ciebie, wróć jak będziesz miała odpowiednio dużo złota"<<std::endl;
                            }
                            std::cout<<"Wychodzisz."<<std::endl;
                            return false;

                        }
                    }
                    else if(komenda == "nie"){
                         if(pl == mezczyzna){
                            std::cout<<"Wróć jak będziesz chciał podnieść poziom."<<std::endl;
                            }
                        else if(pl == kobieta){
                            std::cout<<"Wróć jak będziesz chciała podnieść poziom."<<std::endl;
                            }
                        std::cout<<"Wychodzisz."<<std::endl;
                        return false;
                    }
                    else{
                        std::cout<<"Nie rozumiem możesz powtórzyć?"<<std::endl;
                    }
                }while(komenda != "tak" && komenda != "nie");
            }
            else{
                std::cout<<"Widzę że nie masz wystarczjąco dużo doświadczenia żeby wbić wyższy poziom, wróć kiedy indziej."<<std::endl;
                std::cout<<"Wychodzisz"<<std::endl;
                return false;
            }
        }
    }
    else if(p == gildia_lotrzykow){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 52){
                std::cout<<l2<<std::endl;
            }
        }
        lokacja.close();
        if(k != wojownik){
            if(pl == mezczyzna){
                std::cout<<"Nie jesteś łotrzykiem, wyjdź!"<<std::endl;
            }
            if(pl == kobieta){
                std::cout<<"Nie jesteś łotrzycą, wyjdź!"<<std::endl;
            }
            return false;
        }
        else{
            if(stan_gry.pd >= stan_gry.pd_do_nastepnego_poziomu){
                if(pl == mezczyzna){
                std::cout<<"Witaj łotrzyku widzę, że nabyłeś wystarczająco dużo doświadczenią żeby przejść szkolenie na wyższy poziom, ale będzie cię to kosztowało 100 złota, chcesz wbić wyższy poziom?"<<std::endl;
                }
                else if(pl == kobieta){
                std::cout<<"Witaj łotrzyco widzę, że nabyłaś wystarczająco dużo doświadczenią żeby przejść szkolenie na wyższy poziom, ale będzie cię to kosztowało 100 złota, chcesz wbić wyższy poziom?"<<std::endl;
                }
                do{
                    std::cin>>komenda;
                    if(komenda == "tak"){
                        if(stan_gry.zloto >= 100){
                            stan_gry.zloto -= 100;
                            stan_gry.gracz->nastepny_poziom();
                            std::cout<<"Wychodzisz."<<std::endl;
                            return false;
                        }
                        else{
                            if(pl == mezczyzna){
                            std::cout<<"Nie stać ciebie, wróć jak będziesz miał odpowiednio dużo złota"<<std::endl;
                            }
                            else if(pl == kobieta){
                            std::cout<<"Nie stać ciebie, wróć jak będziesz miała odpowiednio dużo złota"<<std::endl;
                            }
                            std::cout<<"Wychodzisz."<<std::endl;
                            return false;

                        }
                    }
                    else if(komenda == "nie"){
                         if(pl == mezczyzna){
                            std::cout<<"Wróć jak będziesz chciał podnieść poziom."<<std::endl;
                            }
                        else if(pl == kobieta){
                            std::cout<<"Wróć jak będziesz chciała podnieść poziom."<<std::endl;
                            }
                        std::cout<<"Wychodzisz."<<std::endl;
                        return false;
                    }
                    else{
                        std::cout<<"Nie rozumiem możesz powtórzyć?"<<std::endl;
                    }
                }while(komenda != "tak" && komenda != "nie");
            }
            else{
                std::cout<<"Widzę że nie masz wystarczjąco dużo doświadczenia żeby wbić wyższy poziom, wróć kiedy indziej."<<std::endl;
                std::cout<<"Wychodzisz"<<std::endl;
                return false;
            }
        }
    }
    else if(p == zamek_cz){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 66){
                std::cout<<l2<<std::endl;
            }
        }
        lokacja.close();
        int czy_walka=rand()%101;
         if(czy_walka<70){
            if(pl == mezczyzna){
                std::cout<<"Zostałeś zaatakowany"<<std::endl;
            }
            else std::cout<<"Zostałaś zaatakowana"<<std::endl;
            Przeciwnik golem("Golem", 500, 0, 200, 0, 100, 0, 200, 600);
            Przeciwnik czarodziej("Czarodziej", 200, 500, 5, 200, 30, 40, 150, 700);
            int z_kim = rand()%101;
            if(z_kim <= 50){
            walka(golem);
            }
            else walka(czarodziej);
            return true;
        }
    }
    else if(p == pole){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 68){
                std::cout<<l2<<std::endl;
            }
        }
        lokacja.close();
        int czy_walka = rand()%101;
        if(czy_walka<55){
            if(pl == mezczyzna){
                std::cout<<"Zostałeś zaatakowany"<<std::endl;
            }
            else std::cout<<"Zostałaś zaatakowana"<<std::endl;
            Przeciwnik bandyta("Bandyta", 60, 0, 5, 0, 10, 0, 40, 70);
            walka(bandyta);
            return true;
        }
    }
    else if(p == leze){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 72){
                std::cout<<l2<<std::endl;
            }
        }
        lokacja.close();
    }
    else if(p == brama){
        std::cout<<"Przekraczasz bramę"<<std::endl;
    }
    else if(p == mur){
        std::cout<<"Nie możesz przekroczyć murów"<<std::endl;
        return false;
    }
    else if(p == skaly){
        std::cout<<"Nie możesz przekroczyć skał"<<std::endl;
        return false;
    }
    else if(p == bariera){
        std::cout<<"Czy na pewno chcesz wejść w barierę?"<<std::endl;
        std::cout<<"Czeka cię wtedy śmierć."<<std::endl;
        do{
            std::cin>>komenda;
            if(komenda == "nie"){
                return false;
            }
            else if(komenda == "tak"){
                std::fstream zakonczenie;
                zakonczenie.open("zakonczenia.txt");
                std::string lin;
                int l=0;
                while(!zakonczenie.eof()){
                    getline(zakonczenie,lin);
                    if(l>0 && l<=2){
                        std::cout<<lin<<std::endl;
                    }
                    l++;
                }
                zakonczenie.close();
                exit(0);
            }
            else std::cout<<"Nie rozumiem możesz powiedzieć jeszcze raz."<<std::endl;
        }while(komenda != "tak" && komenda != "nie");
    }
    else if(p == jezioro){
        std::cout<<"Nie możesz przekroczyć jeziora"<<std::endl;
        return false;
    }
    else if(p == brama_cz){
        std::cout<<"Przechodzisz przez bramę"<<std::endl;
    }
    else if(p == brama_z){
        if(czar_zad == false){
            std::cout<<"Próbujesz wejść do zamku, ale strażnicy każą ci zawrócić."<<std::endl;
            return false;
        }
        else if(czar_zad == true){
            std::cout<<"Gdy próbujesz przejść przez bramę, zatrzymuję cię strażnicy."<<std::endl;
            std::cout<<"Atakujesz ich."<<std::endl;
            Przeciwnik straznik("Strażnik", 400, 0, 100, 0, 50, 0, 50, 50);
            walka(straznik);
        }
    }
    if(pozpoln == 'l'){
        std::cout<<"Na północy widzisz las"<<std::endl;
    }
    else if(pozpoln == 'j'){
        std::cout<<"Na północy widzisz jezioro"<<std::endl;
    }
    else if(pozpoln == 'd'){
        std::cout<<"Na północy widzisz dom"<<std::endl;
    }
    else if(pozpoln == 'n'){
        std::cout<<"Na północy widzisz bramę"<<std::endl;
    }
    else if(pozpoln == 'i'){
        std::cout<<"Na północy widzisz bramę zamku"<<std::endl;
    }
    else if(pozpoln == 'g'){
        std::cout<<"Na północy widzisz bramę ruin"<<std::endl;
    }
    else if(pozpoln == 'd'){
        std::cout<<"Na północy widzisz bramę do zamku czarnoksiężnika"<<std::endl;
    }
    else if(pozpoln == 'y'){
        std::cout<<"Na północy widzisz ruiny"<<std::endl;
    }
    else if(pozpoln == 'a'){
        std::cout<<"Na północy widzisz akademię magii"<<std::endl;
    }
    else if(pozpoln == 'b'){
        std::cout<<"Na północy widzisz barierę"<<std::endl;
    }
    else if(pozpoln == 's'){
        std::cout<<"Na północy widzisz skały"<<std::endl;
    }
    else if(pozpoln == 'u'){
        std::cout<<"Na północy widzisz sklep z bronią"<<std::endl;
    }
    else if(pozpoln == 'x'){
        std::cout<<"Na północy widzisz szpital"<<std::endl;
    }
    else if(pozpoln == 'p'){
        std::cout<<"Na północy widzisz sklep"<<std::endl;
    }
    else if(pozpoln == 'w'){
        std::cout<<"Na północy widzisz gildię wojowników"<<std::endl;
    }
    else if(pozpoln == 'c'){
        std::cout<<"Na północy widzisz gildię siłaczy"<<std::endl;
    }
    else if(pozpoln == 'k'){
        std::cout<<"Na północy widzisz gildię łotrzyków"<<std::endl;
    }
    else if(pozpoln == 'o'){
        std::cout<<"Na północy widzisz łódkę"<<std::endl;
    }
    else if(pozpoln == 'r'){
        std::cout<<"Na północy widzisz mur"<<std::endl;
    }
    else if(pozpoln == 'z'){
        std::cout<<"Na północy widzisz komnaty zamku"<<std::endl;
    }
    else if(pozpoln == 'f'){
        std::cout<<"Na północy widzisz komnaty zamku czarnoksiężnika"<<std::endl;
    }
    else if(pozpoln == 'm'){
        std::cout<<"Na północy widzisz ulice miasta"<<std::endl;
    }
    else if(pozpoln == 'e'){
        std::cout<<"Na północy widzisz pole"<<std::endl;
    }
    else if(pozpoln == 'q'){
        std::cout<<"Na północy widzisz leże smoka"<<std::endl;
    }
    else if(pozpoln == 'v'){
        std::cout<<"Na północy widzisz skrzynię ze skarbem"<<std::endl;
    }
    if(pozpol == 'l'){
        std::cout<<"Na południu widzisz las"<<std::endl;
    }
    else if(pozpol == 'j'){
        std::cout<<"Na południu widzisz jezioro"<<std::endl;
    }
    else if(pozpol == 'd'){
        std::cout<<"Na południu widzisz dom"<<std::endl;
    }
    else if(pozpol == 'n'){
        std::cout<<"Na południu widzisz bramę"<<std::endl;
    }
    else if(pozpol == 'i'){
        std::cout<<"Na południu widzisz bramę zamku"<<std::endl;
    }
    else if(pozpol == 'g'){
        std::cout<<"Na południu widzisz bramę ruin"<<std::endl;
    }
    else if(pozpol == 'd'){
        std::cout<<"Na południu widzisz bramę do zamku czarnoksiężnika"<<std::endl;
    }
    else if(pozpol == 'y'){
        std::cout<<"Na południu widzisz ruiny"<<std::endl;
    }
    else if(pozpol == 'a'){
        std::cout<<"Na południu widzisz akademię magii"<<std::endl;
    }
    else if(pozpol == 'b'){
        std::cout<<"Na południu widzisz barierę"<<std::endl;
    }
    else if(pozpol == 's'){
        std::cout<<"Na południu widzisz skały"<<std::endl;
    }
    else if(pozpol == 'u'){
        std::cout<<"Na południu widzisz sklep z bronią"<<std::endl;
    }
    else if(pozpol == 'x'){
        std::cout<<"Na południu widzisz szpital"<<std::endl;
    }
    else if(pozpol == 'p'){
        std::cout<<"Na południu widzisz sklep"<<std::endl;
    }
    else if(pozpol == 'w'){
        std::cout<<"Na południu widzisz gildię wojowników"<<std::endl;
    }
    else if(pozpol == 'c'){
        std::cout<<"Na południu widzisz gildię siłaczy"<<std::endl;
    }
    else if(pozpol == 'k'){
        std::cout<<"Na południu widzisz gildię łotrzyków"<<std::endl;
    }
    else if(pozpol == 'o'){
        std::cout<<"Na południu widzisz łódkę"<<std::endl;
    }
    else if(pozpol == 'r'){
        std::cout<<"Na południu widzisz mur"<<std::endl;
    }
    else if(pozpol == 'z'){
        std::cout<<"Na południu widzisz komnaty zamku"<<std::endl;
    }
    else if(pozpol == 'f'){
        std::cout<<"Na południu widzisz komnaty zamku czarnoksiężnika"<<std::endl;
    }
     else if(pozpol == 'm'){
        std::cout<<"Na południu widzisz ulice miasta"<<std::endl;
    }
    else if(pozpol == 'e'){
        std::cout<<"Na południu widzisz pole"<<std::endl;
    }
    else if(pozpol == 'q'){
        std::cout<<"Na południu widzisz leże smoka"<<std::endl;
    }
    else if(pozpol == 'v'){
        std::cout<<"Na południu widzisz skrzynię ze skarbem"<<std::endl;
    }
    if(pozzach == 'l'){
        std::cout<<"Na zachodzie widzisz las"<<std::endl;
    }
    else if(pozzach == 'j'){
        std::cout<<"Na zachodzie widzisz jezioro"<<std::endl;
    }
    else if(pozzach == 'd'){
        std::cout<<"Na zachodzie widzisz dom"<<std::endl;
    }
    else if(pozzach == 'n'){
        std::cout<<"Na zachodzie widzisz bramę"<<std::endl;
    }
    else if(pozzach == 'i'){
        std::cout<<"Na zachodzie widzisz bramę zamku"<<std::endl;
    }
    else if(pozzach == 'g'){
        std::cout<<"Na zachodzie widzisz bramę ruin"<<std::endl;
    }
    else if(pozzach == 'd'){
        std::cout<<"Na zachodzie widzisz bramę do zamku czarnoksiężnika"<<std::endl;
    }
    else if(pozzach == 'y'){
        std::cout<<"Na zachodzie widzisz ruiny"<<std::endl;
    }
    else if(pozzach == 'a'){
        std::cout<<"Na zachodzie widzisz akademię magii"<<std::endl;
    }
    else if(pozzach == 'b'){
        std::cout<<"Na zachodzie widzisz barierę"<<std::endl;
    }
    else if(pozzach == 's'){
        std::cout<<"Na zachodzie widzisz skały"<<std::endl;
    }
    else if(pozzach == 'u'){
        std::cout<<"Na zachodzie widzisz sklep z bronią"<<std::endl;
    }
    else if(pozzach == 'x'){
        std::cout<<"Na zachodzie widzisz szpital"<<std::endl;
    }
    else if(pozzach == 'p'){
        std::cout<<"Na zachodzie widzisz sklep"<<std::endl;
    }
    else if(pozzach == 'w'){
        std::cout<<"Na zachodzie widzisz gildię wojowników"<<std::endl;
    }
    else if(pozzach == 'c'){
        std::cout<<"Na zachodzie widzisz gildię siłaczy"<<std::endl;
    }
    else if(pozzach == 'k'){
        std::cout<<"Na zachodzie widzisz gildię łotrzyków"<<std::endl;
    }
    else if(pozzach == 'o'){
        std::cout<<"Na zachodzie widzisz łódkę"<<std::endl;
    }
    else if(pozzach == 'r'){
        std::cout<<"Na zachodzie widzisz mur"<<std::endl;
    }
    else if(pozzach == 'z'){
        std::cout<<"Na zachodzie widzisz komnaty zamku"<<std::endl;
    }
    else if(pozzach == 'f'){
        std::cout<<"Na zachodzie widzisz komnaty zamku czarnoksiężnika"<<std::endl;
    }
    else if(pozzach == 'm'){
        std::cout<<"Na zachodzie widzisz ulice miasta"<<std::endl;
    }
    else if(pozzach == 'e'){
        std::cout<<"Na zachodzie widzisz pole"<<std::endl;
    }
    else if(pozzach == 'q'){
        std::cout<<"Na zachodzie widzisz leże smoka"<<std::endl;
    }
    else if(pozzach == 'v'){
        std::cout<<"Na zachodzie widzisz skrzynię ze skarbem"<<std::endl;
    }
    if(pozwschod == 'l'){
        std::cout<<"Na wschodzie widzisz las"<<std::endl;
    }
    else if(pozwschod == 'j'){
        std::cout<<"Na wschodzie widzisz jezioro"<<std::endl;
    }
    else if(pozwschod == 'd'){
        std::cout<<"Na wschodzie widzisz dom"<<std::endl;
    }
    else if(pozwschod == 'n'){
        std::cout<<"Na wschodzie widzisz bramę"<<std::endl;
    }
    else if(pozwschod == 'i'){
        std::cout<<"Na wschodzie widzisz bramę zamku"<<std::endl;
    }
    else if(pozwschod == 'g'){
        std::cout<<"Na wschodzie widzisz bramę ruin"<<std::endl;
    }
    else if(pozwschod == 'd'){
        std::cout<<"Na wschodzie widzisz bramę do zamku czarnoksiężnika"<<std::endl;
    }
    else if(pozwschod == 'y'){
        std::cout<<"Na wschodzie widzisz ruiny"<<std::endl;
    }
    else if(pozwschod == 'a'){
        std::cout<<"Na wschodzie widzisz akademię magii"<<std::endl;
    }
    else if(pozwschod == 'b'){
        std::cout<<"Na wschodzie widzisz barierę"<<std::endl;
    }
    else if(pozwschod == 's'){
        std::cout<<"Na wschodzie widzisz skały"<<std::endl;
    }
    else if(pozwschod == 'u'){
        std::cout<<"Na wschodzie widzisz sklep z bronią"<<std::endl;
    }
    else if(pozwschod == 'x'){
        std::cout<<"Na wschodzie widzisz szpital"<<std::endl;
    }
    else if(pozwschod == 'p'){
        std::cout<<"Na wschodzie widzisz sklep"<<std::endl;
    }
    else if(pozwschod == 'w'){
        std::cout<<"Na wschodzie widzisz gildię wojowników"<<std::endl;
    }
    else if(pozwschod == 'c'){
        std::cout<<"Na wschodzie widzisz gildię siłaczy"<<std::endl;
    }
    else if(pozwschod == 'k'){
        std::cout<<"Na wschodzie widzisz gildię łotrzyków"<<std::endl;
    }
    else if(pozwschod == 'o'){
        std::cout<<"Na wschodzie widzisz łódkę"<<std::endl;
    }
    else if(pozwschod == 'r'){
        std::cout<<"Na wschodzie widzisz mur"<<std::endl;
    }
    else if(pozwschod == 'z'){
        std::cout<<"Na wschodzie widzisz komnaty zamku"<<std::endl;
    }
    else if(pozwschod == 'f'){
        std::cout<<"Na wschodzie widzisz komnaty zamku czarnoksiężnika"<<std::endl;
    }
     else if(pozwschod == 'm'){
        std::cout<<"Na wschodzie widzisz ulice miasta"<<std::endl;
    }
    else if(pozwschod == 'e'){
        std::cout<<"Na wschodzie widzisz pole"<<std::endl;
    }
    else if(pozwschod == 'q'){
        std::cout<<"Na wschodzie widzisz leże smoka"<<std::endl;
    }
    else if(pozwschod == 'v'){
        std::cout<<"Na wschodzie widzisz skrzynię ze skarbem"<<std::endl;
    }
    return true;
}
struct {
    enum pole pole;
}lok;
void mapa(){
    char mapa_g[41][35];
    char pozycja;
    char pozpol;
    char pozpoln;
    char pozzach;
    char pozwsch;
    int pozpio;
    std::string komenda;
    std::fstream mapa_m;
    mapa_m.open("mapa.txt");
        for(int i=0;i<41;i++){
            for(int j=0;j<35;j++){
                mapa_m>>mapa_g[i][j];
            }
        }
    mapa_m.close();
    Przedmiot bron("Broń", 0, 0, 0, 0, 0, 0, "Bron");
    Przedmiot zbroja("Zbroja", 0, 0, 0, 0, 0, 0, "zbroja");
    Przedmiot miecz_szeroki("Miecz szeroki", 150, 0, 0, 0, 500, 10, "Bron");
    Przedmiot miecz_dwureczny("Miecz dwuręczny", 200, 0, 0, 0, 1500, 30, "Bron");
    Przedmiot smoczy_miecz("Smoczy miecz", 300, 0, 0, 0, 10000, 20, "Bron");
    Przedmiot pancerz("Pancerz", 0, 50, 0, 0, 1500, 15, "zbroja");
    Przedmiot smoczy_pancerz("Smoczy pancerz", 0, 150, 0, 0, 10000, 25, "zbroja");
    Przedmiot stalowe_rekawice("Stalowe rękawice", 150, 0, 0, 0, 500, 10, "Bron");
    Przedmiot tytanowe_rekawice("Tytanowe rękawice", 200, 0, 0, 0, 1500, 30, "Bron");
    Przedmiot smocze_rekawice("Smocze rękawice", 300, 0, 0, 0, 10000, 20, "Bron");
    Przedmiot kolczuga("Kolczuga", 0, 50, 0, 0, 1500, 15, "zbroja");
    Przedmiot smocza_kolczuga("Smocza kolczuga", 0, 150, 0, 0, 10000, 25, "zbroja");
    Przedmiot sztylet("Sztylet", 150, 0, 0, 0, 500, 10, "Bron");
    Przedmiot obsydianowy_sztylet("Obsydianowy sztylet", 200, 0, 0, 0, 1500, 30, "Bron");
    Przedmiot smoczy_sztylet("Smoczy sztylet", 300, 0, 0, 0, 10000, 20, "Bron");
    Przedmiot skora("Skóra", 0, 50, 0, 0, 1500, 15, "zbroja");
    Przedmiot smocza_skora("Smocza skóra", 0, 150, 0, 0, 10000, 25, "zbroja");
    Przedmiot dluga_laska("Długa laska", 150, 0, 0, 0, 500, 10, "Bron");
    Przedmiot zlota_laska("Złota laska", 200, 0, 0, 0, 1500, 30, "Bron");
    Przedmiot smocza_laska("Smocza laska", 300, 0, 0, 0, 10000, 20, "Bron");
    Przedmiot szaty("Szaty", 0, 50, 0, 0, 1500, 15, "zbroja");
    Przedmiot smocze_szaty("Smocze szaty", 0, 150, 0, 0, 10000, 25, "zbroja");
    Przedmiot mikstura_zdrowia("Mikstura zdrowia", 0, 0, 40, 0, 50, 5, "mikstura");
    Przedmiot mikstura_many("Mikstura zdrowia", 0, 0, 0, 40, 50, 5, "mikstura");
    Ekwipunek plecak(100,stan_gry.ciezar, bron, zbroja);
    Dziennik dziennik;
        do{
        if(stan_gry.poz == 4 && stan_gry.pio == 11){
            stan_gry.hydra_z = true;
        }
        if(stan_gry.poz == 12 && stan_gry.pio == 26){
            stan_gry.smok_z = true;
        }
        if(stan_gry.hydra_z == true && stan_gry.hydra_zad == true){
            if(stan_gry.zad_hydra == false){
                dziennik.aktualizacja_zadania("Upoluj Hydrę");
                stan_gry.zad_hydra = true;
            }
        }
        if(stan_gry.smok_z == true && stan_gry.smok_zad == true){
            if(stan_gry.zad_smok == false){
                dziennik.aktualizacja_zadania("Zgładź Smoka");
                stan_gry.zad_smok = true;
            }
        }
        int klawisz = getch();
        if(klawisz){
        switch(getch()) {
        case 72:
            komenda = "polnoc";
            break;
        case 80:
            komenda = "poludnie";
            break;
        case 75:
            komenda = "zachod";
            break;
        case 77:
            komenda = "wschod";
            break;
        default:
            getline(std::cin,komenda);
            break;
        }
        }
        if(komenda == "leczenie"){
            stan_gry.gracz->pz += mikstura_zdrowia.wartosc_leczenia;
            plecak.usun_przedmiot("Mikstura zdrowia");
            if(stan_gry.gracz->pz > stan_gry.gracz->max_pz) stan_gry.gracz->pz = stan_gry.gracz->max_pz;

        }
        if(komenda == "teleport"){
            int l,a;
            std::cin>>l;
            std::cin>>a;
            stan_gry.poz=l;
            stan_gry.pio=a;
        }
        if(komenda == "odzyskanie"){
            stan_gry.gracz->pz += mikstura_many.wartosc_leczenia;
            plecak.usun_przedmiot("Mikstura many");
            if(stan_gry.gracz->pm > stan_gry.gracz->max_pm) stan_gry.gracz->pm = stan_gry.gracz->max_pm;

        }
        if(komenda == "dziennik"){
            dziennik.wyswietl_zadania();
        }
        if(komenda == "usun miecz"){
            std::string miecz = "Miecz";
            plecak.usun_przedmiot(miecz);
        }
        if(komenda == "ekwipunek"){
            plecak.pokaz_ekwipunek();
        }
        if(komenda == "zaloz dluga laska"){
            plecak.zaloz_przedmiot(dluga_laska);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz zlota laska"){
            plecak.zaloz_przedmiot(zlota_laska);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz smocza laska"){
            plecak.zaloz_przedmiot(smocza_laska);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz szaty"){
            plecak.zaloz_przedmiot(szaty);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz smocze szaty"){
            plecak.zaloz_przedmiot(smocze_szaty);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz miecz szeroki"){
            plecak.zaloz_przedmiot(miecz_szeroki);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz miecz dwureczny"){
            plecak.zaloz_przedmiot(miecz_dwureczny);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz smoczy miecz"){
            plecak.zaloz_przedmiot(smoczy_miecz);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz pancerz"){
            plecak.zaloz_przedmiot(pancerz);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz smoczy pancerz"){
            plecak.zaloz_przedmiot(smoczy_pancerz);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz sztylet"){
            plecak.zaloz_przedmiot(sztylet);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz obsydianowy sztylet"){
            plecak.zaloz_przedmiot(obsydianowy_sztylet);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz smoczy sztylet"){
            plecak.zaloz_przedmiot(smoczy_sztylet);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz skora"){
            plecak.zaloz_przedmiot(skora);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz smocza skora"){
            plecak.zaloz_przedmiot(smocza_skora);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz stalowe rekawice"){
            plecak.zaloz_przedmiot(stalowe_rekawice);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz tytanowe rekawice"){
            plecak.zaloz_przedmiot(tytanowe_rekawice);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz smocze rekawice"){
            plecak.zaloz_przedmiot(smocze_rekawice);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz kolczuga"){
            plecak.zaloz_przedmiot(kolczuga);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "zaloz smocza kolczuga"){
            plecak.zaloz_przedmiot(smocza_kolczuga);
            Przedmiot bron = plecak.Pokaz_zalozona_bron();
        }
        if(komenda == "mapa"){
             for(int i=0;i<5;i++){
                for(int j=0;j<5;j++){
                if(i==2 && j==2){
                    std::cout<< 'x';
                }
                else{
                std::cout<<mapa_g[stan_gry.poz+i-2][stan_gry.pio+j-2];
                }
            }
            std::cout<<std::endl;
        }
        }
        if(komenda == "zapisz gre"){
            zapisz(stan_gry.plec,stan_gry.klasa,stan_gry.rasa_g,stan_gry.poz,stan_gry.pio,stan_gry.przedmioty, stan_gry.zadania,plecak.zalozona_bron,plecak.zalozona_zbroja);
        }
        if(komenda == "polnoc") stan_gry.poz-=1;
        else if(komenda == "poludnie") stan_gry.poz+=1;
        else if(komenda == "wschod") stan_gry.pio+=1;
        else if(komenda == "zachod") stan_gry.pio-=1;
        pozycja = mapa_g[stan_gry.poz][stan_gry.pio];
        pozpol = mapa_g[stan_gry.poz+1][stan_gry.pio];
        pozpoln = mapa_g[stan_gry.poz-1][stan_gry.pio];
        pozzach = mapa_g[stan_gry.poz][stan_gry.pio-1];
        pozwsch = mapa_g[stan_gry.poz][stan_gry.pio+1];
        if(pozycja == 'm') lok.pole = miasto;
        else if(pozycja == 'z') lok.pole = zamek;
        else if(pozycja == 'l') lok.pole = las;
        else if(pozycja == 'd') lok.pole = dom;
        else if(pozycja == 'y') lok.pole = ruiny;
        else if(pozycja == 'a') lok.pole = akademia_magii;
        else if(pozycja == 'u') lok.pole = sklep_z_bronia;
        else if(pozycja == 'x') lok.pole = szpital;
        else if(pozycja == 'p') lok.pole = sklep;
        else if(pozycja == 'w') lok.pole = gildia_wojownikow;
        else if(pozycja == 'c') lok.pole = gildia_silaczy;
        else if(pozycja == 'k') lok.pole = gildia_lotrzykow;
        else if(pozycja == 'f') lok.pole = zamek_cz;
        else if(pozycja == 'e') lok.pole = pole;
        else if(pozycja == 'q') lok.pole = leze;
        else if(pozycja == 'v') lok.pole = skarb;
        else if(pozycja == 'r') lok.pole = mur;
        else if(pozycja == 's') lok.pole = skaly;
        else if(pozycja == 'b') lok.pole = bariera;
        else if(pozycja == 'n') lok.pole = brama;
        else if(pozycja == 'i') lok.pole = brama_z;
        else if(pozycja == 'j') lok.pole = jezioro;
        else if(pozycja == 'd') lok.pole = brama_cz;
        if(komenda == "status"){
        std::cout<<"Imię: "<<stan_gry.imie<<std::endl;
        std::cout<<"Nazwisko: "<<stan_gry.nazwisko<<std::endl;
        std::cout<<"Klasa: ";
        wypisz_klase(stan_gry.klasa);
        std::cout<<"Rasa: ";
        wypisz_rase(stan_gry.rasa_g);
        std::cout<<"Płeć: ";
        wypisz_plec(stan_gry.plec);
        stan_gry.gracz->wypisz_statystyki();
        std::cout<<"Poziom: "<<stan_gry.poziom<<std::endl;
        std::cout<<"PD: "<<stan_gry.pd<<std::endl;
        std::cout<<"Wymagane PD do następnego poziomu: " << stan_gry.pd_do_nastepnego_poziomu << std::endl;
        std::cout<<"Złoto: "<<stan_gry.zloto<<std::endl;
        }
        pozpio = stan_gry.poz*100+stan_gry.pio;
        if(komenda == "polnoc" || komenda == "poludnie" || komenda == "wschod" || komenda == "zachod"){
        if(lok.pole !='p' && lok.pole !='u' && pozpio!=1210 && pozpio!=2225 && pozpio !=3832){
        if(miejsce(lok.pole,stan_gry.poz,stan_gry.pio,mapa_g,komenda,pozpol,pozpoln,pozzach,pozwsch,plecak,stan_gry.plec,stan_gry.rasa_g,stan_gry.klasa,dziennik,stan_gry.hydra_z,stan_gry.smok_z,stan_gry.czar_zad,pozpio) == false){
        if(komenda == "polnoc") stan_gry.poz+=1;
        else if(komenda == "polodnie") stan_gry.poz-=1;
        else if(komenda == "wschod") stan_gry.pio-=1;
        else if(komenda == "zachod") stan_gry.pio+=1;
        }
        }
        else {
            std::fstream lokacja;
            lokacja.open("pozycja.txt");
            std::string l2;
            int linia = 0;
            if(lok.pole == 'u'){
            while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 32){
                std::cout<<l2<<std::endl;
            }
        }

        std::cout<<"Chcesz podejść do sprzedawcy i obejrzeć broń?"<<std::endl;
        std::string k2,k3;
        do{
        std::cin>>k2;
        if(k2 == "tak"){
            if(stan_gry.klasa == wojownik){
            std::cout<<"Witaj co chcesz kupić?"<<std::endl;
            std::cout<<"- Miecz szeroki (atak: 150, cena: 500)"<<std::endl;
            std::cout<<"- Miecz dwuręczny (atak: 200, cena: 1500)"<<std::endl;
            std::cout<<"- Smoczy miecz (atak: 300, cena: 10000)"<<std::endl;
            std::cout<<"- Pancerz (obrona: 50, cena: 1500)"<<std::endl;
            std::cout<<"- Smoczy pancerz (obrona: 150, cena: 10000)"<<std::endl;
            Przedmiot miecz_szeroki("Miecz szeroki", 150, 0, 0, 0, 500, 10, "Bron");
            Przedmiot miecz_dwureczny("Miecz dwuręczny", 200, 0, 0, 0, 1500, 30, "Bron");
            Przedmiot smoczy_miecz("Smoczy miecz", 300, 0, 0, 0, 10000, 20, "Bron");
            Przedmiot pancerz("Pancerz", 0, 50, 0, 0, 1500, 15, "zbroja");
            Przedmiot smoczy_pancerz("Smoczy pancerz", 0, 150, 0, 0, 10000, 25, "zbroja");
            do{
            getline(std::cin,k3);
            if(k3 == "miecz szeroki"){
                if(stan_gry.zloto - miecz_szeroki.wartosc>=0){
                stan_gry.zloto -= miecz_szeroki.wartosc;
                plecak.dodaj_przedmiot(miecz_szeroki);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "miecz dwureczny"){
                if(stan_gry.zloto - miecz_dwureczny.wartosc>=0){
                stan_gry.zloto -= miecz_dwureczny.wartosc;
                plecak.dodaj_przedmiot(miecz_dwureczny);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            if(k3 == "smoczy miecz"){
                if(stan_gry.zloto - smoczy_miecz.wartosc>=0){
                stan_gry.zloto -= smoczy_miecz.wartosc;
                plecak.dodaj_przedmiot(smoczy_miecz);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            if(k3 == "pancerz"){
                if(stan_gry.zloto - pancerz.wartosc>=0){
                stan_gry.zloto -= pancerz.wartosc;
                plecak.dodaj_przedmiot(pancerz);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            if(k3 == "smoczy pancerz"){
                if(stan_gry.zloto - smoczy_pancerz.wartosc>=0){
                stan_gry.zloto -= smoczy_pancerz.wartosc;
                plecak.dodaj_przedmiot(smoczy_pancerz);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "wyjscie"){
                std::cout<<"Wychodzisz ze sklepu"<<std::endl;
            }
            else if(k3 != "miecz szeroki" && k3!= "miecz dwureczny" && k3 != "smoczy miecz" && k3 != "pancerz" && k3 != "smoczy pancerz"){
                std::cout<<"Nie mamy takiej broni lub zbroi."<<std::endl;
            }
            }while(k3 != "wyjscie");
            }
            else if(stan_gry.klasa == silacz){
            std::cout<<"Witaj co chcesz kupić?"<<std::endl;
            std::cout<<"- Stalowe rękawice (atak: 150, cena: 500)"<<std::endl;
            std::cout<<"- Tytanowe rękawice (atak: 200, cena: 1500)"<<std::endl;
            std::cout<<"- Smocze rękawice (atak: 300, cena: 10000)"<<std::endl;
            std::cout<<"- Kolczuga (obrona: 50, cena: 1500)"<<std::endl;
            std::cout<<"- Smocza kolczuga (obrona: 150, cena: 10000)"<<std::endl;
            Przedmiot stalowe_rekawice("Stalowe rękawice", 150, 0, 0, 0, 500, 10, "Bron");
            Przedmiot tytanowe_rekawice("Tytanowe rękawice", 200, 0, 0, 0, 1500, 30, "Bron");
            Przedmiot smocze_rekawice("Smocze rękawice", 300, 0, 0, 0, 10000, 20, "Bron");
            Przedmiot kolczuga("Kolczuga", 0, 50, 0, 0, 1500, 15, "zbroja");
            Przedmiot smocza_kolczuga("Smocza kolczuga", 0, 150, 0, 0, 10000, 25, "zbroja");
            do{
            getline(std::cin,k3);
            if(k3 == "stalowe rekawice"){
                if(stan_gry.zloto - stalowe_rekawice.wartosc>=0){
                stan_gry.zloto -= stalowe_rekawice.wartosc;
                plecak.dodaj_przedmiot(stalowe_rekawice);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "tytanowe rekawice"){
                if(stan_gry.zloto - tytanowe_rekawice.wartosc>=0){
                stan_gry.zloto -= tytanowe_rekawice.wartosc;
                plecak.dodaj_przedmiot(tytanowe_rekawice);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "smocze rekawice"){
                if(stan_gry.zloto - smocze_rekawice.wartosc>=0){
                stan_gry.zloto -= smocze_rekawice.wartosc;
                plecak.dodaj_przedmiot(smocze_rekawice);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "kolczuga"){
                if(stan_gry.zloto - kolczuga.wartosc>=0){
                stan_gry.zloto -= kolczuga.wartosc;
                plecak.dodaj_przedmiot(kolczuga);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "smocza kolczuga"){
                if(stan_gry.zloto - smocza_kolczuga.wartosc>=0){
                stan_gry.zloto -= smocza_kolczuga.wartosc;
                plecak.dodaj_przedmiot(smocza_kolczuga);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "wyjscie"){
                std::cout<<"Wychodzisz ze sklepu"<<std::endl;
            }
            else{
                std::cout<<"Nie mamy takiej broni lub zbroi."<<std::endl;
            }
            }while(k3 != "wyjscie");
            }
            else if(stan_gry.klasa == lotrzyk){
            std::cout<<"Witaj co chcesz kupić?"<<std::endl;
            std::cout<<"- Sztylet (atak: 150, cena: 500)"<<std::endl;
            std::cout<<"- Obsydianowy sztylet (atak: 200, cena: 1500)"<<std::endl;
            std::cout<<"- Smoczy sztylet (atak: 300, cena: 10000)"<<std::endl;
            std::cout<<"- Skóra (obrona: 50, cena: 1500)"<<std::endl;
            std::cout<<"- Smocza skóra (obrona: 150, cena: 10000)"<<std::endl;
            Przedmiot sztylet("Sztylet", 150, 0, 0, 0, 500, 10, "Bron");
            Przedmiot obsydianowy_sztylet("Obsydianowy sztylet", 200, 0, 0, 0, 1500, 30, "Bron");
            Przedmiot smoczy_sztylet("Smoczy sztylet", 300, 0, 0, 0, 10000, 20, "Bron");
            Przedmiot skora("Skóra", 0, 50, 0, 0, 1500, 15, "zbroja");
            Przedmiot smocza_skora("Smocza skóra", 0, 150, 0, 0, 10000, 25, "zbroja");
            do{
            getline(std::cin,k3);
            if(k3 == "sztylet"){
                if(stan_gry.zloto - sztylet.wartosc>=0){
                stan_gry.zloto -= sztylet.wartosc;
                plecak.dodaj_przedmiot(sztylet);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "obsydianowy sztylet"){
                if(stan_gry.zloto - obsydianowy_sztylet.wartosc>=0){
                stan_gry.zloto -= obsydianowy_sztylet.wartosc;
                plecak.dodaj_przedmiot(obsydianowy_sztylet);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "smoczy sztylet"){
                if(stan_gry.zloto - smoczy_sztylet.wartosc>=0){
                stan_gry.zloto -= smoczy_sztylet.wartosc;
                plecak.dodaj_przedmiot(smoczy_sztylet);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "skora"){
                if(stan_gry.zloto - skora.wartosc>=0){
                stan_gry.zloto -= skora.wartosc;
                plecak.dodaj_przedmiot(skora);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "smocza skora"){
                if(stan_gry.zloto - smocza_skora.wartosc>=0){
                stan_gry.zloto -= smocza_skora.wartosc;
                plecak.dodaj_przedmiot(smocza_skora);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "wyjscie"){
                std::cout<<"Wychodzisz ze sklepu"<<std::endl;
            }
            else{
                std::cout<<"Nie mamy takiej broni lub zbroi."<<std::endl;
            }
            }while(k3 != "wyjscie");
            }
            else if(stan_gry.klasa == magik){
            std::cout<<"Witaj co chcesz kupić?"<<std::endl;
            std::cout<<"- Długa laska (atak: 150, cena: 500)"<<std::endl;
            std::cout<<"- Złota laska (atak: 200, cena: 1500)"<<std::endl;
            std::cout<<"- Smocza laska (atak: 300, cena: 10000)"<<std::endl;
            std::cout<<"- Szaty (obrona: 50, cena: 1500)"<<std::endl;
            std::cout<<"- Smocze szaty (obrona: 150, cena: 10000)"<<std::endl;
            Przedmiot dluga_laska("Długa laska", 150, 0, 0, 0, 500, 10, "Bron");
            Przedmiot zlota_laska("Złota laska", 200, 0, 0, 0, 1500, 30, "Bron");
            Przedmiot smocza_laska("Smocza laska", 300, 0, 0, 0, 10000, 20, "Bron");
            Przedmiot szaty("Szaty", 0, 50, 0, 0, 1500, 15, "zbroja");
            Przedmiot smocze_szaty("Smocze szaty", 0, 150, 0, 0, 10000, 25, "zbroja");
            do{
            getline(std::cin,k3);
            if(k3 == "dluga laska"){
                if(stan_gry.zloto - dluga_laska.wartosc>=0){
                stan_gry.zloto -= dluga_laska.wartosc;
                plecak.dodaj_przedmiot(dluga_laska);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "zlota laska"){
                if(stan_gry.zloto - zlota_laska.wartosc>=0){
                stan_gry.zloto -= zlota_laska.wartosc;
                plecak.dodaj_przedmiot(zlota_laska);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "smocza laska"){
                if(stan_gry.zloto - smocza_laska.wartosc>=0){
                stan_gry.zloto -= smocza_laska.wartosc;
                plecak.dodaj_przedmiot(smocza_laska);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "szaty"){
                if(stan_gry.zloto - szaty.wartosc>=0){
                stan_gry.zloto -= szaty.wartosc;
                plecak.dodaj_przedmiot(szaty);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "smocze szaty"){
                if(stan_gry.zloto - smocze_szaty.wartosc>=0){
                stan_gry.zloto -= smocze_szaty.wartosc;
                plecak.dodaj_przedmiot(smocze_szaty);
                plecak.pokaz_ekwipunek();
            } else std::cout<<"Nie stać cię"<<std::endl;
            }
            else if(k3 == "wyjscie"){
                std::cout<<"Wychodzisz ze sklepu"<<std::endl;
            }
            else {
                std::cout<<"Nie mamy takiej broni lub zbroi."<<std::endl;
            }
            }while(k3 != "wyjscie");
            }
        }
        else if(k2 == "nie"){
            std::cout<<"Wychodzisz ze sklepu."<<std::endl;
            k3 = "wyjscie";
        }
        else {
            std::cout<<"Nie rozumiem, możesz powtórzyć?"<<std::endl;
        }
        }while(k3 != "wyjscie");
        lokacja.close();
        }
        else if(lok.pole == 'p'){
        while(std::getline(lokacja,l2)){
            linia++;
            if(linia == 40){
                std::cout<<l2<<std::endl;
            }
        }
        std::cout<<"Chcesz podejść do sprzedawcy?"<<std::endl;
        std::string k2;
        do{
        std::cin>>k2;
        if(k2 == "tak"){
            std::cout<<"Witaj co chcesz kupić?"<<std::endl;
            std::cout<<"Mikstura zdrowia"<<std::endl;
            std::cout<<"Mikstura many"<<std::endl;
            Przedmiot mikstura_zdrowia("Mikstura zdrowia", 0, 0, 40, 0, 50, 5, "mikstura");
            Przedmiot mikstura_many("Mikstura zdrowia", 0, 0, 0, 40, 50, 5, "mikstura");
            do{
            getline(std::cin,k2);
            if(k2 == "mikstura zdrowia"){
                if(stan_gry.zloto - mikstura_zdrowia.wartosc >= 0){
                    plecak.dodaj_przedmiot(mikstura_zdrowia);
                    stan_gry.zloto -= mikstura_zdrowia.wartosc;
                }
                else {
                    std::cout<<"Nie stać cię"<<std::endl;
                }
            }
            else if(k2 == "mikstura many"){
                if(stan_gry.zloto - mikstura_many.wartosc >= 0){
                    plecak.dodaj_przedmiot(mikstura_many);
                    stan_gry.zloto -= mikstura_many.wartosc;
                }
                else {
                    std::cout<<"Nie stać cię"<<std::endl;
                }
            }
            else if(k2 == "wyjscie"){
                std::cout<<"Wychodzisz ze sklepu."<<std::endl;
            }
            else if(k2 != "mikstura zdrowia" && k2 != "mikstura many"){
                std::cout<<"Nie mam czegoś takiego, możesz wybrać coś innego?"<<std::endl;
            }
            }while(k2 != "wyjscie");
        }
        else if(k2 == "nie"){
            std::cout<<"Wychodzisz ze sklepu."<<std::endl;
        }
        else {
                std::cout<<"Nie rozumiem, możesz powtórzyć?"<<std::endl;
        }
        }while(k2 != "wyjscie" && k2 != "nie");
        lokacja.close();
    }
    else if(pozpio == 1210){
        std::fstream zadanie;
        zadanie.open("postacie_niezalezne.txt");
        int h = 0;
        std::string linia;
        std::string kz;
        if(stan_gry.hydra_w == true){
            while(!zadanie.eof()){
            getline(zadanie,linia);
            if(h == 37){
                std::cout<<linia<<std::endl;
            }
            h++;
            }
        }
        else if(stan_gry.hydra_zad == false){
        while(!zadanie.eof()){
            getline(zadanie,linia);
            if(stan_gry.plec == mezczyzna){
                if(h >= 3 && h <= 9){
                    std::cout<<linia<<std::endl;
                }
            }
            else if(stan_gry.plec == kobieta){
                if(h >= 11 && h <= 17){
                    std::cout<<linia<<std::endl;
                }
            }
            h++;
        }
        do{
            std::cin>>kz;
            if(kz == "tak"){
                dziennik.dodaj_zadanie("Upoluj Hydrę");
                std::cout<<"Dziękuję."<<std::endl;
                stan_gry.hydra_zad = true;
            }
            else if(kz == "nie"){
                std::cout<<"Rozumiem, no to do zobaczenia później"<<std::endl;
                std::cout<<"Wychodzisz"<<std::endl;
            }
            else{
                std::cout<<"Nie rozumiem możesz powtórzyć?"<<std::endl;
            }
        }while(kz != "tak" && kz !="nie");
        }
        else if(stan_gry.zad_hydra == true){
            while(!zadanie.eof()){
            getline(zadanie,linia);
                if(h >= 29 && h <= 35){
                    std::cout<<linia<<std::endl;
                }
            h++;
        }
        stan_gry.pd += 400;
        stan_gry.zloto += 500;
        stan_gry.hydra_w = true;
        std::cout<<"Wychodzisz"<<std::endl;
        }
        else if(stan_gry.hydra_zad == true){
            while(!zadanie.eof()){
            getline(zadanie,linia);
            if(stan_gry.plec == mezczyzna){
                if(h >= 21 && h <= 22){
                    std::cout<<linia<<std::endl;
                }
            }
            else if(stan_gry.plec == kobieta){
                if(h >= 25 && h <= 26){
                    std::cout<<linia<<std::endl;
                }
            }
            h++;
        }
        std::cout<<"Wychodzisz"<<std::endl;
        }
    }
    else if(pozpio == 2225){
        std::fstream zadanie;
        zadanie.open("postacie_niezalezne.txt");
        int h = 0;
        std::string linia;
        std::string kz;
        if(stan_gry.smok_w == true){
            while(!zadanie.eof()){
            getline(zadanie,linia);
            if(h == 65){
                std::cout<<linia<<std::endl;
            }
            h++;
            }
        }
        if(stan_gry.smok_w == true){
            while(!zadanie.eof()){
            getline(zadanie,linia);
            if(h == 65){
                std::cout<<linia<<std::endl;
            }
            h++;
            }
        }
        else if(stan_gry.smok_zad == false){
        while(!zadanie.eof()){
            getline(zadanie,linia);
            if(stan_gry.plec == mezczyzna){
                if(h >= 40 && h <= 45){
                    std::cout<<linia<<std::endl;
                }
            }
            else if(stan_gry.plec == kobieta){
                if(h >= 47 && h <= 52){
                    std::cout<<linia<<std::endl;
                }
            }
            h++;
        }
        do{
            std::cin>>kz;
            if(kz == "tak"){
                dziennik.dodaj_zadanie("Zgładź Smoka");
                stan_gry.smok_zad = true;
                std::cout<<"Dziękuję"<<std::endl;
                std::cout<<"Wychodzisz"<<std::endl;
            }
            else if(kz == "nie"){
                std::cout<<"Rozumiem, no to do zobaczenia później"<<std::endl;
                std::cout<<"Wychodzisz"<<std::endl;
            }
            else{
                std::cout<<"Nie rozumiem możesz powtórzyć?"<<std::endl;
            }
        }while(kz != "tak" && kz !="nie");
        }
        else if(stan_gry.zad_smok == true){
            while(!zadanie.eof()){
            getline(zadanie,linia);
                if(h == 58){
                    std::cout<<linia<<std::endl;
                }
            h++;
        }
        stan_gry.smok_w = true;
        stan_gry.pd += 500;
        stan_gry.zloto += 1000;
        std::cout<<"Wychodzisz"<<std::endl;
        }
        else if(stan_gry.smok_zad == true){
            while(!zadanie.eof()){
            getline(zadanie,linia);
                if(h == 55){
                    std::cout<<linia<<std::endl;
                }
            h++;
        }
        std::cout<<"Wychodzisz"<<std::endl;
        }
    }
    else if(pozpio == 3832){
        std::fstream zadanie;
        zadanie.open("postacie_niezalezne.txt");
        int h = 0;
        std::string linia;
        std::string kz;
        if(stan_gry.czar_zad == false){
            while(!zadanie.eof()){
                getline(zadanie,linia);
                if(stan_gry.plec == mezczyzna){
                    if(h >= 69 && h<=71){
                        std::cout<<linia<<std::endl;
                    }
                }
                else if(stan_gry.plec == kobieta){
                    if(h >= 72 && h<=74){
                        std::cout<<linia<<std::endl;
                    }
                }
                h++;
            }
            do{
                std::cin>>kz;
                if(kz == "tak"){
                    std::cout<<"Mądrze postąpiłeś, wróć jak już go załątwisz"<<std::endl;
                    dziennik.dodaj_zadanie("Zgładź króla");
                    stan_gry.czar_zad = true;
                    std::cout<<"Zawracasz."<<std::endl;
                }
                else if(kz == "nie"){
                    std::cout<<"Rozumiem to w takim razie zabiję ciebie"<<std::endl;
                    Przeciwnik Pawel("Czarnoksiężnik Paweł", 3000, 3000, 10, 400,150,10,0,0);
                   // Przeciwnik Pawel("Czarnoksiężnik Paweł", 5, 5, 5, 5,5,10,0,0);
                    walka(Pawel);
                    if(stan_gry.plec == mezczyzna){
                    std::cout<<"Pokonałeś czarnoksiężnika"<<std::endl;
                    }
                    else if(stan_gry.plec == kobieta){
                    std::cout<<"Pokonałaś czarnoksiężnika"<<std::endl;
                    }
                    std::fstream zakonczenie;
                    std::string wiersz;
                    int linia = 0;
                    zakonczenie.open("zakonczenia.txt");
                    while(!zakonczenie.eof()){
                    getline(zakonczenie,wiersz);
                    if(linia >= 4 && linia <= 5){
                    std::cout<<wiersz<<std::endl;
                    }
                    linia++;
                    }
                    zakonczenie.close();
                    exit(0);
                }
                else if(kz != "tak" || kz!="nie"){
                    std::cout<<"Nie rozumiem, powtórz!"<<std::endl;
                }
            }while(kz!="tak" && kz!="nie");
        }
        else if(stan_gry.czar_zad == true){
            while(!zadanie.eof()){
                getline(zadanie,linia);
                if(h == 78){
                    std::cout<<linia<<std::endl;
                }
                h++;
            }
            std::cout<<"Zawracasz."<<std::endl;
        }
    }
        if(komenda == "polnoc") stan_gry.poz+=1;
        else if(komenda == "polodnie") stan_gry.poz-=1;
        else if(komenda == "wschod") stan_gry.pio-=1;
        else if(komenda == "zachod") stan_gry.pio+=1;
        }
        }
    }while(komenda != "wyjdz z gry");
    std::cout<<"Żegnaj"<<std::endl;
}

