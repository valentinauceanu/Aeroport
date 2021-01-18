#include<iostream>
#include<cstring>
#include<string.h>
#include<vector>
#include<bits/stdc++.h>
#include<algorithm>
#include<regex>
using namespace std;

struct DATA{
    int zi;
    int luna;
    int an;
};

struct ZBOR{
    string tara_plecare, tara_destinatie;
    DATA data;
};

struct CONT{
    string mail;
    string parola;
};

struct OM{
    string nume;
    string prenume;
    int varsta;
};

struct REZERVARE{
    OM persoana;
    ZBOR zborulet;
    CONT contulet;
    int bilete;
};

class Operator{
   public:
      string user_existent;
      string parola_existenta;
      vector <ZBOR> zbori;

      Operator(){
          this->user_existent = "user";
          this->parola_existenta = "parola";
      }

      string conectare(string user, string parola){
          if (user != this->user_existent || parola != this->parola_existenta){
              throw "Conectarea nu a reusit! Parola sau user incorect/a!";
          }
          return "Conectare reusita!";
      }

       void adaugare(ZBOR z){
           zbori.push_back(z);
           cout << "Zbor adaugat cu succes!" << endl;
       }

       void stergere(string d, string p){
           vector<ZBOR>::iterator v = zbori.begin();
           while(v != zbori.end() ){
               if(v->tara_plecare == p && v->tara_destinatie == d){
                   v = zbori.erase(v);
                   break;
               }else v++;
           }
       }
       void cautare(string plec, string sosire){
           vector<ZBOR>::iterator v = zbori.begin();
           int aux = 0;

           while(v != zbori.end() ){
               if(v->tara_plecare == plec && v->tara_destinatie == sosire){
                   cout << "Zbor gasit!" << endl;
                   cout << v->data.zi << "." << v->data.luna << "." << v->data.an << "   p: " << v->tara_plecare << "   d: " << v->tara_destinatie << endl; 
                   aux = 1;
                   v++;
                   
               }else v++;
           }
           if(aux == 0) throw "Nu s-a gasit nici un zbor!";
       }

};

class Utilizator{
    public: 
        CONT cont;

        bool valid_mail(const string& email){
           const regex pattern
                ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
            return regex_match(email,pattern);
        }

        bool valid_pass(const string& pass){
            const regex pattern
                ("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[.#?!@$%^&*-]).{8,}$");
            return regex_match(pass,pattern);
        }

        string autentificare(string u, string p){
            if(u!=cont.mail || p!= cont.parola){
                throw "Autentificare nereusita! Va rugam reincercati!";
            }
            return "Autentificare reusita! Bine ati revenit!";
        }
       
};


void meniu_operator(){
    cout << ".................................................." << endl; 
    cout << "1. CONECTARE!" << endl;
    cout << "2. ADAUGARE ZBOR!" << endl;
    cout << "3. STERGERE ZBOR!" << endl;
    cout << ".................................................." << endl; 
}

void meniu_utilizator(){
    cout << ".................................................." << endl; 
    cout << "1. Creare cont!" << endl;
    cout << "2. Conectare! (Atentie, a se efectua crearea contului)" << endl;
    cout << "3. Cautare zbor!" << endl;
    cout << "4. Rezervare zbor!" << endl;
    cout << ".................................................." << endl; 
}

int main(){
    int choice1;
    Utilizator u1;
    Operator o1;
    string p,u;
    string a = "zero";

    cout << "---------------------------------------------------" << endl;
    cout << "----------------------ZBORURI----------------------" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << endl;
    cout << "1: Operator 2: Utilizator 3: Iesire aplicatie!" << endl;

    cin >> choice1;

    if(choice1 != 1 && choice1 != 2 && choice1 != 3){
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "--Nu este posibil, ne pare rau, dar vei fi scos!--" << endl;
        cout << "--------------------------------------------------" << endl;
        exit(1);
    }

    if(choice1 == 3){
        cout << endl;
        cout << ".................................................." << endl; 
        cout << "......................IESIRE......................" << endl;
        cout << ".................................................." << endl; 
        exit(1);
    }

    do{
        switch(choice1){
            case 1:
               int choice;
               meniu_operator();
               cout << endl;
               cout << "Urmatoarea actiune..." << endl;
               cin >> choice;
               if(choice == 1){
                   cout << endl;
                   cout << "Introduceti..." << endl;
                   do{
                       cout << endl;
                       cout << "User: " << endl;
                       cin >> u;
                       cout << "Parola: "<< endl;
                       cin >> p;
                       try{
                           a = o1.conectare(u,p);
                           cout << a << endl;
                        }catch ( const char* msg){
                            cerr << msg << endl;
                        }
                    }while (a != "Conectare reusita!");
                }
                if(choice == 2){
                    ZBOR zb;
                    cout << "Introduceti..." << endl;

                    do{
                        cout << "An: " ;
                        cin >> zb.data.an;
                        try{
                            if(zb.data.an < 2020){
                                throw "Zborul e in trecut, nu mai poate fi efectuat!";
                            }else a = "Reusit!";
                        }
                        catch (const char * msg){
                            cerr << msg << endl;
                        }
                    }while(a != "Reusit!");

                    do{
                        cout << "Luna: ";
                        cin >> zb.data.luna;
                        try{
                            if(zb.data.luna > 12 || (zb.data.luna < 12 && zb.data.an == 2020)){//e deja decembrie deci nu mai verific si pt data actuala
                                throw "Luna incorect introdusa!";
                            }else a = "Da";
                        }
                        catch (const char* msg){
                            cerr << msg << endl;
                        }
                    }while(a != "Da");

                    do{
                        cout << "Zi: ";
                        cin >> zb.data.zi;
                        try{
                            if( zb.data.zi < 7 && zb.data.luna == 12 && zb.data.an == 2020){//e deja decembrie deci nu mai verific si pt data actuala
                                throw "Zi incorect introdusa!";
                            }else if (zb.data.luna == 2 && zb.data.zi > 29 && zb.data.an % 4 == 0){
                                throw "Zi incorect introdusa!";
                            }else if (zb.data.luna == 2 && zb.data.zi > 28 && zb.data.an % 4 != 0){
                                throw "Zi incorect introdusa!";
                            }else if(zb.data.zi > 30){
                                if(zb.data.luna == 4){
                                    throw "Zi incorect introdusa!";
                                }else if(zb.data.luna == 6){
                                    throw "Zi incorect introdusa!";
                                }else if(zb.data.luna == 9){
                                    throw "Zi incorect introdusa!";
                                }else if(zb.data.luna == 11){
                                    throw "Zi incorect introdusa!";
                                }
                            }else a = "Sure";
                        }
                        catch (const char* msg){
                            cerr << msg << endl;
                        }
                    }while(a != "Sure");
                    //cout << zb.data.zi;
                    do{
                        cout << "Tara de plecare: ";
                        cin >> zb.tara_plecare;
                        try{
                            int n = (zb.tara_plecare).size();
                            for(int i = 0; i < n; i++){
                                char c = zb.tara_plecare[i];
                                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                                    a = "oui";
                                }else {
                                    a = "no";
                                    throw "Format tara incorect! Reintroduceti!";
                                }
                            }
                        }
                        catch(const char* msg){
                            cerr << msg << endl;
                        }
                    }while(a != "oui");

                    do{
                        cout << "Tara destinatie: ";
                        cin >> zb.tara_destinatie;
                        a = "No";
                        try{
                            int n = (zb.tara_destinatie).size();
                            for(int i = 0; i < n; i++){
                                char c = zb.tara_destinatie[i];
                                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                                    a = "oui";
                                }else {
                                    a = "nu";
                                    throw "Format tara incorect! Reintroduceti!";
                                }
                            }
                        }
                        catch(const char* msg){
                            cerr << msg << endl;
                        }
                    }while(a != "oui");

                    o1.adaugare(zb);
                    cout << endl;
                    int n = o1.zbori.size();
                    for(int i = 0; i < n; i++){
                        cout << o1.zbori[i].data.zi << ".";
                        cout << o1.zbori[i].data.luna << ".";
                        cout << o1.zbori[i].data.an << " ";
                        cout << o1.zbori[i].tara_plecare<< " ";
                        cout << o1.zbori[i].tara_destinatie << endl;
                    }
                }
                if(choice == 3){
                    ZBOR zb;
                    cout << ".................................................." << endl; 
                    cout << "................Zborurile existente............... " << endl;
                    cout << ".................................................." << endl; 
                    cout << endl;
                    int n = o1.zbori.size();
                    for(int i = 0; i < n; i++){
                        cout << o1.zbori[i].data.zi << ".";
                        cout << o1.zbori[i].data.luna << ".";
                        cout << o1.zbori[i].data.an << ". ";
                        cout << o1.zbori[i].tara_plecare << " ";
                        cout << o1.zbori[i].tara_destinatie <<endl;
                    }
                    cout << endl;
                    cout << "Introduceti datele zborului pe care doriti sa il stergeti!" << endl;
                    string dest;
                    string plec;
                    cout << "Destinatie..." << endl;
                    a = "No";
                    do{
                        cin >> dest;
                        try{
                            int n = dest.size();
                            for(int i = 0; i < n; i++){
                                char c = dest[i];
                                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                                    a = "oui";
                                }else {
                                    a = "nu";
                                    throw "Format tara incorect!";
                                }
                            }
                        }
                        catch(const char* msg){
                            cerr << msg << endl;
                        }
                    }while(a!="oui");
                    cout << "Plecare..." << endl;
                    a = "No";
                    do{
                        cin >> plec;
                        try{
                            int n = plec.size();
                            for(int i = 0; i < n; i++){
                                char c = plec[i];
                                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                                    a = "oui";
                                }else {
                                    a = "nu";
                                    throw "Format tara incorect!";
                                }
                            }
                        }
                        catch(const char* msg){
                            cerr << msg << endl;
                        }
                    }while(a!="oui");
                    o1.cautare(plec,dest);
                    o1.stergere(dest,plec);
                    cout << endl;
                    n = o1.zbori.size();
                    for(int i = 0; i < n; i++){
                        cout << o1.zbori[i].data.zi << ".";
                        cout << o1.zbori[i].data.luna << ".";
                        cout << o1.zbori[i].data.an << ". ";
                        cout << o1.zbori[i].tara_plecare << " ";
                        cout << o1.zbori[i].tara_destinatie <<endl;
                    }
                }
                break;
                case 2:
                    meniu_utilizator();
                    cin >> choice;
                    if(choice == 1){
                        string mail;
                        string v;
                        cout << "..................................................." << endl; 
                        cout << "...Bine ati venit! Crearea contului incepe acum!..." << endl;
                        cout << "..................................................." << endl; 
                        cout << endl;
                        do{
                            cout << "Introduceti adresa de mail!" << endl;
                            cin >> u1.cont.mail;
                            try{
                                if( (v = (u1.valid_mail(u1.cont.mail) ? "valid" : "invalid")) == "invalid"){
                                    throw "Adresa de mail invalida, introduceti alta!";
                                }else a = "reusit";
                            }
                            catch(const char  * msg){
                                cerr << msg << endl;
                            }
                        }while(a != "reusit");

                        do{
                            cout << "Introduceti o parola pentru cont, care sa aiba minim 8 caractere, minim o cifra, minim o litera mare si un caracter special!" << endl;
                            cin >> u1.cont.parola;
                            try{
                                if( (v = (u1.valid_pass(u1.cont.parola) ? "valid" : "invalid")) == "invalid"){
                                    throw "Parola prea slaba, introduceti alta!";
                                }else a = "da";
                            }
                            catch(const char* msg){
                                cerr << msg << endl;
                            }
                        }while(a != "da");
                        string pss;
                        do{
                            cout << "Reintroduceti parola!" << endl;
                            cin >> pss;
                            try{
                                if(pss != u1.cont.parola){
                                    throw "Parolele nu corespund, reincercati!";
                                }else cout << "Parola asigurata cu succes!" << endl;
                            }
                            catch(const char* msg){
                                cerr << msg << endl;
                            }
                        }while (pss != u1.cont.parola);
                    }
                    if(choice == 2){
                        cout << ".................................................." << endl; 
                        cout << ".................AUTENTIFICARE!..................."<< endl;
                        cout << ".................................................." << endl; 
                        cout << endl;
                        do{
                            cout << "Introduceti adresa de mail!" << endl;
                            cin >> u;
                            cout << "Introduceti parola!" << endl;
                            cin >> p;
                            try{
                                a = u1.autentificare(u,p);
                                cout << a << endl;
                            }
                            catch(const char* msg){
                                cerr << msg << endl;
                            }
                        }while(a != "Autentificare reusita! Bine ati revenit!");
                    }
                    if(choice == 3){
                        cout << endl;
                        cout << ".................................................." << endl;
                        cout << "..................CAUTARE ZBOR...................." << endl;
                        cout << ".................................................." << endl;
                        cout << endl;
                        string plecare;
                        string sosire;
                        string raspuns;
                        cout << "Doriti sa continuati cautarea? (Da/Nu)" << endl;
                        cin >> raspuns;
                        if(raspuns == "Nu") {
                            cout << "Reveniti la meniul principal!" << endl;
                            break;
                        }
                        do{
                            cout << "Introduceti datele!" << endl;
                            do{
                                a = "ne";
                                cout << "Locul de plecare..." << endl;
                                cin >> plecare;
                                try{
                                    int n = plecare.size();
                                    for(int i = 0; i < n; i++){
                                        char c = plecare[i];
                                        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                                            a = "oui";
                                        }else {
                                            a = "nu";
                                            throw "Format tara incorect! Reintroduceti!";
                                        }
                                    }
                                }
                                catch(const char* msg){
                                    cerr << msg << endl;
                                }
                            }while(a!="oui");
                            a = "nu";
                            do{
                                cout << "Destinatia..." << endl;
                                cin >> sosire;
                                try{
                                    int n = sosire.size();
                                    for(int i = 0; i < n; i++){
                                        char c = sosire[i];
                                        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                                            a = "oui";
                                        }else {
                                            a = "nu";
                                            throw "Format tara incorect! Reintroduceti!";
                                        }
                                    }
                                }
                                catch(const char* msg){
                                    cerr << msg << endl;
                                }
                            }while(a!="oui");
                            try{
                                o1.cautare(plecare,sosire);
                            }
                            catch(const char* msg){
                                cerr << msg << endl;
                            }
                            cout << "Doriti sa continuati cautarea? (Da/Nu)" << endl;
                            cin >> raspuns;
                            if(raspuns != "Da"){
                                cout << "Reveniti la meniul principal!" << endl;
                            }
                        }while(raspuns != "Nu");
                    }
                    if(choice == 4){
                        string decizie;
                        REZERVARE rez;
                        cout << ".................................................." << endl; 
                        cout << ".................Rezervare  zbor.................." << endl;
                        cout << ".................................................." << endl;
                        cout << "................Zboruri existente................." << endl;
                        cout << ".................................................." << endl;
                        cout << endl;
                        int n = (o1.zbori).size();
                        for(int i = 0; i < n; i++){
                            cout << o1.zbori[i].data.zi << ".";
                            cout << o1.zbori[i].data.luna << ".";
                            cout << o1.zbori[i].data.an << ". ";
                            cout << o1.zbori[i].tara_plecare << " ";
                            cout << o1.zbori[i].tara_destinatie <<endl;
                        }
                        cout << endl;
                        cout << "Rezervati din zborurile existente? (da/nu)" << endl;
                        cin >> decizie;
                        if(decizie == "da"){
                            cout << "Introduceti, va rog, datele acelui zbor si datele dumneavoastra!" << endl;
                            string dep;
                            string arr;
                            int zi, luna, an;
                            cout << endl;
                            cout << "Introduceti locul de plecare si de sosire pentru cautare!" << endl;
                            cout << endl;
                            cout << "Plecare: ";
                            cin >> dep;
                            cout << "Sosire: ";
                            cin >> arr;
                            cout << "...Data... " << endl;
                            cout << "Zi: ";
                            cin >> zi;
                            cout << "Luna: ";
                            cin >> luna;
                            cout << "An: ";
                            cin >> an;
                            try{
                                o1.cautare(dep,arr);
                            }
                            catch(const char* msg){
                                cout << "Nu se poate face rezervarea!" << endl;
                                cerr << msg << endl;
                                break;
                            }
                            int n = (o1.zbori).size();
                            for(int i = 0; i < n; i++){
                                if(o1.zbori[i].tara_plecare == dep && o1.zbori[i].tara_destinatie == arr && o1.zbori[i].data.zi == zi && o1.zbori[i].data.luna == luna && o1.zbori[i].data.an == an){
                                    rez.zborulet.tara_plecare = o1.zbori[i].tara_plecare;
                                    rez.zborulet.tara_destinatie = o1.zbori[i].tara_destinatie;
                                    rez.zborulet.data.zi = o1.zbori[i].data.zi;
                                    rez.zborulet.data.luna = o1.zbori[i].data.luna;
                                    rez.zborulet.data.an = o1.zbori[i].data.an;
                                }
                            }
                            cout << "Acum ca s-a ales zborul, va rugam sa va conectati! " << endl;
                            string new_u;
                            string new_p;
                            do{
                                cout << "Introduceti adresa de mail!" << endl;
                                cin >> new_u;
                                cout << "Introduceti parola!" << endl;
                                cin >> new_p;
                                try{
                                   a = u1.autentificare(new_u, new_p);
                                }
                                catch(const char* msg){
                                    cerr << msg << endl;
                                }
                            }while(a != "Autentificare reusita! Bine ati revenit!");
                            cout << endl;
                            cout << "Acum ca sunteti autentificat, va rugam introduceti datele personale" << endl;
                            cout << endl;
                            a = "not ok";
                            do{
                                cout << "Introduceti numele..." ;
                                cin >> rez.persoana.nume;
                                try{
                                    int n = (rez.persoana.nume).size();
                                    for(int i = 0; i < n; i++){
                                        char c = rez.persoana.nume[i];
                                        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                                            a = "ok";
                                        }else{
                                            a = "no";
                                            throw "Format nume incorect! Reintroduceti!";
                                        }
                                    }
                                }
                                catch(const char* msg){
                                    cerr << msg << endl;
                                }
                            }while(a != "ok");
                            a = "incerc aolo";
                            cout << endl;
                            do{
                                cout << "Introduceti prenumele..." ;
                                cin >> rez.persoana.prenume;
                                try{
                                    int n = (rez.persoana.prenume).size();
                                    for(int i = 0; i < n; i++){
                                        char c = rez.persoana.prenume[i];
                                        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                                            a = "ok";
                                        }else {
                                            a = "no";
                                            throw "Format prenume incorect! Reintroduceti!";
                                        }
                                    }
                                }
                                catch(const char* msg){
                                    cerr << msg << endl;
                                }
                            }while(a != "ok");
                            a = "nu";
                            cout << endl;
                            do{
                                cout << "Introduceti varsta...";
                                cin >> rez.persoana.varsta;
                                try{
                                    if(rez.persoana.varsta > 110 ){
                                        throw "Chiar ai varsta asta? Mai incearca";
                                    } 
                                    a = "ok";
                                }
                                catch (const char* msg){
                                    cerr << msg << endl;
                                }
                            }while(a!="ok");
                            cout << endl;
                            cout << "Acum ca avem datele dumneavoastra, introduceti numarul de bilete!" << endl;
                            a = "nu se mai termina";
                            do{
                                cin >> rez.bilete;
                                try{
                                    if(rez.bilete > 20){
                                        throw "Ne pare rau, ati introdus prea multe bilete, reintroduceti";
                                    }
                                    a = "ok";
                                }
                                catch(const char* msg){
                                    cerr << msg << endl;
                                }
                            }while(a!="ok");
                            cout << endl;
                            cout << "Va multumim ca ati ales aceasta linie aeriana!" << endl;
                            cout << "Datele rezervarii dumneavoastra: " << endl;
                            cout << endl;
                            cout << "Nume: " << rez.persoana.nume << endl << "Prenume: " << rez.persoana.prenume << endl <<"Varsta: " << rez.persoana.varsta << endl;
                            cout << "Total bilete: " << rez.bilete << endl;
                            cout << "Datele zborului: " << endl;
                            cout << "Plecare: " << rez.zborulet.tara_plecare << "   Sosire: " << rez.zborulet.tara_destinatie << " in data de: " << rez.zborulet.data.zi << "." << rez.zborulet.data.luna << "." << rez.zborulet.data.an<< endl;
                            cout << endl;
                            cout << "Va uram o zi placuta in continuare! ";
                            cout << endl;
                        }
                    }
        }
        cout << endl;
        cout << "1: Operator 2: Utilizator 3: Iesire aplicatie!" << endl;
        cin >> choice1;
    }while(choice1 != 3);
    if(choice1 == 3){
        cout << endl;
        cout << ".................................................." << endl; 
        cout << "......................IESIRE......................" << endl;
        cout << ".................................................." << endl; 
        exit(1);
    }
return 0;
}
