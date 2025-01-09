#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

enum class Limba {
    Romana,
    Engleza
};

class Configuratie {
private:
    static Limba limbaCurenta;

public:
    static void seteazaLimba(Limba limba) {
        limbaCurenta = limba;
    }

    static Limba obtineLimba() {
        return limbaCurenta;
    }
};

Limba Configuratie::limbaCurenta = Limba::Romana;

map<string, map<Limba, string>> dictionar = {
    {"Cafea Espresso", {{Limba::Romana, "Cafea Espresso"}, {Limba::Engleza, "Espresso Coffee"}}},
    {"Ciocolata calda", {{Limba::Romana, "Ciocolata calda"}, {Limba::Engleza, "Hot chocolate"}}},
    {"Briosa ciocolata", {{Limba::Romana, "Briosa ciocolata"}, {Limba::Engleza, "Chocolate muffin"}}},
    {"Ceai Verde", {{Limba::Romana, "Ceai Verde"}, {Limba::Engleza, "Green Tea"}}},
    {"Nume", {{Limba::Romana, "Nume"}, {Limba::Engleza, "Name"}}},
    {"Functie", {{Limba::Romana, "Functie"}, {Limba::Engleza, "Role"}}},
    {"Ospatar", {{Limba::Romana, "Ospatar"}, {Limba::Engleza, "Waiter"}}},
    {"Ora inceput", {{Limba::Romana, "Ora inceput"}, {Limba::Engleza, "Start Time"}}},
    {"Ora sfarsit", {{Limba::Romana, "Ora sfarsit"}, {Limba::Engleza, "End Time"}}},
    {"Data", {{Limba::Romana, "Data"}, {Limba::Engleza, "Data"}}},
    {"Cost", {{Limba::Romana, "Cost"}, {Limba::Engleza, "Price"}}},
    {"Pret", {{Limba::Romana, "Pret"}, {Limba::Engleza, "Price"}}},
    {"Stoc", {{Limba::Romana, "Stoc"}, {Limba::Engleza, "Stock"}}},
    {"Client", {{Limba::Romana, "Client"}, {Limba::Engleza, "Client"}}},
    {"Produse", {{Limba::Romana, "Produse"}, {Limba::Engleza, "Products"}}},
    {"Pret total", {{Limba::Romana, "Pret total"}, {Limba::Engleza, "Total price"}}},
    {"Degustare Cafea", {{Limba::Romana, "Degustare Cafea"}, {Limba::Engleza, "Coffee Tasting"}}},
    {"Concert Live", {{Limba::Romana, "Concert Live"}, {Limba::Engleza, "Live Concert"}}},
    {"Raport financiar", {{Limba::Romana, "Raport financiar"}, {Limba::Engleza, "Financial Report"}}},
    {"Venituri totale din comenzi", {{Limba::Romana, "Venituri totale din comenzi"}, {Limba::Engleza, "Total Order Income"}}},
    {"Costuri totale ale produselor", {{Limba::Romana, "Costuri totale ale produselor"}, {Limba::Engleza, "Total Product Price"}}},
    {"Salarii totale ale angajatilor", {{Limba::Romana, "Salarii totale ale angajatilor"}, {Limba::Engleza, "Total Employee Salary"}}},
    {"Costuri totale ale evenimentelor", {{Limba::Romana, "Costuri totale ale evenimentelor"}, {Limba::Engleza, "Total Event Cost"}}},
    {"Profitul zilnic", {{Limba::Romana, "Profitul zilnic"}, {Limba::Engleza, "Daily Profit"}}}
};

string traduce(string text) {
    auto limba_curenta = Configuratie::obtineLimba();
    if (dictionar.find(text) != dictionar.end()) {
        if (dictionar[text].find(limba_curenta) != dictionar[text].end()) {
            return dictionar[text][limba_curenta];
        }
    }
    return text;
}

class Entitate { //Concept OOP: Clasa
public:
    virtual string toCSV(bool antet = false) = 0;
    virtual void fromCSV(string linie) = 0; //Concept OOP: Abstractizare
    virtual ~Entitate() = default;
};

class Angajati : public Entitate { //Concept OOP: Mostenire
protected:  //Concept OOP: Incapsulare
    string nume;
    string functie;
    string ora_inceput;
    string ora_sfarsit;

public:
    Angajati() = default;
    //Concept OOP: Constructor
    Angajati(string numE, string functiE, string ora_incepuT, string ora_sfarsiT) {
        nume = numE;
        functie = functiE;
        ora_inceput = ora_incepuT;
        ora_sfarsit = ora_sfarsiT;
    }

    string toCSV(bool antet = false) override {
        if (antet) {
            return traduce("Nume") + "," + traduce("Functie") + "," + traduce("Ora inceput") + "," + traduce("Ora sfarsit");
        } else {
            return nume + "," + traduce(functie) + "," + ora_inceput + "," + ora_sfarsit;;
        }
    }

    void fromCSV(string linie) override {
        stringstream ss(linie);
        getline(ss, nume, ',');
        getline(ss, functie, ',');
        getline(ss, ora_inceput, ',');
        getline(ss, ora_sfarsit, ',');
    }

    string getFunctie() {
        return functie;
    }

    virtual ~Angajati() = default; //Concept OOP: Destructor
};
class Manager : public Angajati {
public:
    Manager(string numE, string ora_incepuT, string ora_sfarsiT) : Angajati(numE, "Manager", ora_incepuT, ora_sfarsiT) {}

};

class Barista : public Angajati {
public:
    Barista(string numE, string ora_incepuT, string ora_sfarsiT) : Angajati(numE, "Barista", ora_incepuT, ora_sfarsiT) {}

};

class Ospatar : public Angajati {
public:
    Ospatar(string numE, string ora_incepuT, string ora_sfarsiT) : Angajati(numE, "Ospatar", ora_incepuT, ora_sfarsiT) {}

};
class Produse : public Entitate {
private:
    string nume;
    double pret;
    int stoc;

    map<string, string> traduceri = {
        {"Cafea Espresso", "Espresso Coffee"},
        {"Ceai Verde", "Green Tea"}
    };

public:
    Produse() = default;
    Produse(string numE, double preT, int stoC) {
        nume = numE;
        pret = preT;
        stoc = stoC;
    }

    string toCSV(bool antet = false) override {
        if (antet) {
            return traduce("Nume") + "," + traduce("Pret") + "," + traduce("Stoc");
        } else {
            string produs_tradus = traduce(nume);
            ostringstream stream;
            stream << fixed << setprecision(2) << pret;
            return produs_tradus + "," + stream.str() + "," + to_string(stoc);
        }
    }

    void fromCSV(string linie) override {
        stringstream ss(linie);
        getline(ss, nume, ',');
        if (nume == "Nume") {
            return;
        }
        ss >> pret;
        ss.ignore(1, ',');
        ss >> stoc;
    }

    void scadeStoc(int cantitate) {
        if (cantitate > stoc) {
            throw runtime_error("Stoc insuficient pentru " + nume);
        }
        stoc -= cantitate;
    }

    double getPret() {
        return pret;
    }
    int getStoc() {
        return stoc;
    }
    string getNume() {
        return nume;
    }
    static Produse cautaProdusCSV(string nume_produs, string fisier) {
        string produs_tradus = traduce(nume_produs);
        ifstream in(fisier);
        if (!in.is_open()) {
            throw runtime_error("Fisierul nu a putut fi deschis pentru citire: " + fisier);
        }
        string linie;
        while (getline(in, linie)) {
            Produse produs;
            produs.fromCSV(linie);
            if (produs.getNume() == produs_tradus) {
                return produs;
            }
        }
        throw invalid_argument("Produsul " + nume_produs + " nu exista in fisierul CSV.");
    }
};

class Comenzi : public Entitate {
private:
    string client;
    vector<Produse> produse;
    double pret_total;

public:
    Comenzi() = default;
    Comenzi(string clienT, vector<string> produsE, string fisier) {
        client = clienT;
        pret_total = 0.0;
        for (auto numeProdus : produsE) {
            Produse produs = Produse::cautaProdusCSV(numeProdus, fisier);
            produse.push_back(produs);
            pret_total += produs.getPret();
        }
    }
    void aplicaReducere(int nr_comenzi_client) {
        if (nr_comenzi_client > 5) {
                pret_total *= 0.9;
            }
        }

    string getClient() {
        return client;
    }
    double getPretTotal() {
        return pret_total;
    }

    string toCSV(bool antet = false) override {
        if (antet) {
            return traduce("Client") + "," + traduce("Produse") + "," + traduce("Pret total");
        } else {
            string produse_traduse;
            for (auto &produs : produse) {
                produse_traduse += traduce(produs.getNume()) + ";";
            }

            ostringstream stream;
            stream << fixed << setprecision(2) << pret_total;
            return client + "," + produse_traduse + stream.str();
        }
    }

    void fromCSV(string linie) override {
        stringstream ss(linie);
        getline(ss, client, ',');
        ss >> pret_total;
        ss.ignore(1, ',');
        string produs;
        while (getline(ss, produs, ';')) {
            produse.push_back(Produse(produs, 0.0, 0));
        }
    }
};

class Evenimente : public Entitate{
private:
    string nume;
    string data;
    double cost;

public:
    Evenimente() = default;
    Evenimente(string numE, string datA, double cosT) {
        nume = numE;
        data = datA;
        cost = cosT;
    }
    string getNume() {
        return nume;
    }
    string getData() {
        return data;
    }
    double getCosturi() {
        return cost;
    }
    string toCSV(bool antet = false) override {
        if (antet) {
            return traduce("Nume") + "," + traduce("Data") + "," + traduce("Cost");
        } else {
            ostringstream stream;
            stream << fixed << setprecision(2) << cost;
            return traduce(nume) + "," + data + "," + stream.str();
        }
    }
    void fromCSV(string linie) {
        stringstream ss(linie);
        getline(ss, nume, ',');
        getline(ss, data, ',');
        ss >> cost;
    }
};

//Concept OOP: Template
template <typename T>
class GestionareEntitati {
private:
    vector<T> entitati;

public:
    void adauga(const T& entitate) {
        entitati.push_back(entitate);
    }

    void sterge(size_t index) {
        if (index >= entitati.size()) {
            throw out_of_range("Index invalid");
        }
        entitati.erase(entitati.begin() + index);
    }

    vector<T>& getEntitati() {
        return entitati;
    }

    void salvareCSV(string fisier) {
        try {
            ofstream out(fisier);
            if (!out.is_open()) {
                throw runtime_error("Nu se poate deschide fisierul: " + fisier);
            }

            if (!entitati.empty()) {
                string antet = entitati[0].toCSV(true);
                out << antet << endl;
            }

            for (auto &entitate : entitati) {
                string linie = entitate.toCSV(false);
                out << linie << endl;
            }

            cout << "Datele au fost salvate in fisierul: " << fisier << endl;
            out.close();
        } catch (runtime_error error) {
            cerr << "Eroare la salvarea in fisier" << endl;
        }
    }


    void incarcareCSV(string fisier) {
        ifstream in(fisier);
        if (!in.is_open()) {
            throw runtime_error("Nu se poate deschide fisierul: " + fisier);
        }
        string linie;
        getline(in, linie);
        while (getline(in, linie)) {
            T entitate;
            entitate.fromCSV(linie);
            entitati.push_back(entitate);
        }
        in.close();
    }
};

//Concept OOP: Design Pattern(Singleton)
class GestionareOrase {
private:
    static GestionareOrase* instance;
    GestionareOrase() {}

    map<string, GestionareEntitati<Angajati>> angajati_orase;
    map<string, GestionareEntitati<Produse>> produse_orase;
    map<string, GestionareEntitati<Comenzi>> comenzi_orase;
    map<string, GestionareEntitati<Evenimente>> evenimente_orase;

    map<string, int> comenzi_client;
public:
    static GestionareOrase* getInstance() {
        if (!instance) {
            instance = new GestionareOrase();
        }
        return instance;
    }

    void adaugaAngajat(string oras, Angajati angajat) {
        angajati_orase[oras].adauga(angajat);
    }

    void stergeAngajat(string oras, string numeAngajat) {
        auto angajati = angajati_orase[oras].getEntitati();
        auto it = find_if(angajati.begin(), angajati.end(), [numeAngajat](Angajati& angajat) {
            return angajat.toCSV(false).find(numeAngajat) == 0;
        });

        if (it != angajati.end()) {
            angajati.erase(it);
            angajati_orase[oras].salvareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Angajati.csv");
        }
    }

    void adaugaProdus(string oras, Produse produs) {
        produse_orase[oras].adauga(produs);
    }

    void stergeProdus(string oras, string numeProdus) {
        auto &produse = produse_orase[oras].getEntitati();
        auto it = find_if(produse.begin(), produse.end(), [numeProdus](Produse& produs) {
            return produs.getNume() == numeProdus;
        });

        if (it != produse.end()) {
            produse.erase(it);
            produse_orase[oras].salvareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Produse.csv");
        }
    }

    void adaugaComanda(string oras, Comenzi comanda) {
        string client = comanda.getClient();
        if (comenzi_client.find(client) != comenzi_client.end()) {
            comenzi_client[client]++;
        } else {
            comenzi_client[client] = 1;
        }
        int nr_comenzi_client = comenzi_client[client];

        comanda.aplicaReducere(nr_comenzi_client);
        comenzi_orase[oras].adauga(comanda);
    }

    int numarComenzi(string client) {
        if(comenzi_client.find(client) != comenzi_client.end()) {
            return comenzi_client.at(client);
        }
        return 0;
    }

    void adaugaEveniment(string oras, Evenimente eveniment) {
        evenimente_orase[oras].adauga(eveniment);
    }

    void stergeEveniment(string oras, string numeEveniment) {
        auto& evenimente = evenimente_orase[oras].getEntitati();
        auto it = find_if(evenimente.begin(), evenimente.end(), [numeEveniment](Evenimente& eveniment) {
            return eveniment.getNume() == numeEveniment;
        });

        if (it != evenimente.end()) {
            evenimente.erase(it);
            evenimente_orase[oras].salvareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Evenimente speciale.csv");
        }
    }

    void salvareCSV(string oras) {
        angajati_orase[oras].salvareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Angajati.csv");
        produse_orase[oras].salvareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Produse.csv");
        comenzi_orase[oras].salvareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Comenzi.csv");
        evenimente_orase[oras].salvareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Evenimente speciale.csv");

        genereazaRaport(oras);
    }

    void incarcareCSV(string oras) {
        angajati_orase[oras].incarcareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Angajati.csv");
        produse_orase[oras].incarcareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Produse.csv");
        comenzi_orase[oras].incarcareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Comenzi.csv");
        evenimente_orase[oras].incarcareCSV("D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Evenimente speciale.csv");

    }
    void genereazaRaport(string oras) {
        double venituriTotale = 0.0;
        for (auto comanda : comenzi_orase[oras].getEntitati()) {
            venituriTotale += comanda.getPretTotal();
        }

        double costuriTotaleProduse = 0.0;
        for (auto produs : produse_orase[oras].getEntitati()) {
            costuriTotaleProduse += produs.getPret() * produs.getStoc();
        }

        double salariiTotale = 0.0;
        for (auto angajat : angajati_orase[oras].getEntitati()) {
            if (angajat.getFunctie() == "Manager") {
                salariiTotale += 5000;
            } else if (angajat.getFunctie() == "Barista") {
                salariiTotale += 3000;
            } else if (angajat.getFunctie() == "Ospatar") {
                salariiTotale += 2500;
            }
        }

        double costuriTotaleEvenimente = 0.0;
        for (auto eveniment : evenimente_orase[oras].getEntitati()) {
            costuriTotaleEvenimente += eveniment.getCosturi();
        }

        double profit = venituriTotale - (costuriTotaleProduse + salariiTotale + costuriTotaleEvenimente);

        salvareRaportFinanciar(oras, venituriTotale, costuriTotaleProduse, salariiTotale, costuriTotaleEvenimente, profit);
    }
    void salvareRaportFinanciar(string oras, double venituri_totale, double costuri_totale_produse, double salarii_totale, double costuri_totale_evenimente, double profit) {
        string caleFisier = "D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Rapoarte financiare.csv";
        ofstream raport(caleFisier);

        if (!raport.is_open()) {
            cerr << "Nu se poate deschide fisierul pentru salvarea raportului financiar: " << caleFisier << endl;
            return;
        }

        raport << traduce("Raport financiar") << "\n";
        raport << traduce("Venituri totale din comenzi") << ":" << venituri_totale << "\n";
        raport << traduce("Costuri totale ale produselor") << ":" << costuri_totale_produse << "\n";
        raport << traduce("Salarii totale ale angajatilor") << ":" << salarii_totale << "\n";
        raport << traduce("Costuri totale ale evenimentelor") << ":" << costuri_totale_evenimente << "\n";
        raport << traduce("Profitul zilnic") << ":" << profit << "\n";

        raport.close();
    }


    ~GestionareOrase() {
        delete instance;
    }
};

GestionareOrase* GestionareOrase::instance = nullptr;


int main() {
    GestionareOrase* gestionareOrase = GestionareOrase::getInstance();

    Configuratie::seteazaLimba(Limba::Romana);
    string oras = "Bucuresti";
    string fisier_produse = "D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Produse.csv";

    //Concept OOP: Obiect
    Angajati manager("Andrei Valentin", "Manager", "09:00", "16:00");
    gestionareOrase->adaugaAngajat("Bucuresti", manager);

    //Concept OOP: Polimorfism
    gestionareOrase->adaugaAngajat("Bucuresti", Angajati("Ion Popescu", "Ospatar", "09:00", "17:00"));
    gestionareOrase->adaugaAngajat("Bucuresti", Angajati("Maria Ionescu", "Barista", "08:00", "16:00"));

    gestionareOrase->adaugaProdus("Bucuresti", Produse("Cafea Espresso", 10.5, 50));
    gestionareOrase->adaugaProdus("Bucuresti", Produse("Ceai Verde", 8.5, 30));

    gestionareOrase->adaugaComanda("Bucuresti", Comenzi("Alex Vasile", {"Cafea Espresso"}, fisier_produse));
    gestionareOrase->adaugaEveniment("Bucuresti", Evenimente("Degustare Cafea", "2025-01-10", 200.0));
    gestionareOrase->adaugaEveniment("Bucuresti", Evenimente("Concert Live", "2025-01-15", 300.0));

    gestionareOrase->salvareCSV("Bucuresti");
    gestionareOrase->genereazaRaport("Bucuresti");
    cout<<endl;

    Configuratie::seteazaLimba(Limba::Engleza);
    oras = "Brasov";
    fisier_produse = "D:\\CLion\\Calatoria_cafelei\\" + oras + "\\Produse.csv";

    gestionareOrase->adaugaAngajat("Brasov", Angajati("Gabriel Alexandru", "Ospatar", "09:00", "17:00"));
    cout << "Angajat adaugat in Brasov: Gabriel Alexandru, ospatar" << endl;
    gestionareOrase->adaugaAngajat("Brasov", Angajati("David Marinescu", "Barista", "08:00", "16:00"));
    cout << "Angajat adaugat in Brasov: David Marinescu, barista" << endl;

    gestionareOrase->adaugaProdus("Brasov", Produse("Cafea Espresso", 10.5, 50));
    gestionareOrase->adaugaProdus("Brasov", Produse("Ceai Verde", 8.5, 30));
    gestionareOrase->adaugaProdus("Brasov", Produse("Ciocolata calda", 13, 20));
    gestionareOrase->stergeProdus("Brasov", "Ceai Verde");

    gestionareOrase->adaugaComanda("Brasov", Comenzi("Tiberiu Pop", {"Cafea Espresso", "Cafea Espresso", "Ciocolata calda"}, fisier_produse));
    gestionareOrase->adaugaComanda("Brasov", Comenzi("Tiberiu Pop", {"Cafea Espresso", "Cafea Espresso", "Ciocolata calda"}, fisier_produse));
    gestionareOrase->adaugaComanda("Brasov", Comenzi("Tiberiu Pop", {"Cafea Espresso", "Cafea Espresso", "Ciocolata calda"}, fisier_produse));
    gestionareOrase->adaugaComanda("Brasov", Comenzi("Tiberiu Pop", {"Cafea Espresso", "Cafea Espresso", "Ciocolata calda"}, fisier_produse));
    gestionareOrase->adaugaComanda("Brasov", Comenzi("Tiberiu Pop", {"Cafea Espresso", "Cafea Espresso", "Ciocolata calda"}, fisier_produse));
    gestionareOrase->adaugaComanda("Brasov", Comenzi("Tiberiu Pop", {"Cafea Espresso", "Cafea Espresso", "Ciocolata calda"}, fisier_produse));


    gestionareOrase->adaugaEveniment("Brasov", Evenimente("Degustare Cafea", "2025-01-10", 100.0));
    gestionareOrase->adaugaEveniment("Brasov", Evenimente("Concert Live", "2025-01-15", 250.0));
    gestionareOrase->stergeEveniment("Brasov", "Concert Live");

    gestionareOrase->salvareCSV("Brasov");
    gestionareOrase->genereazaRaport("Brasov");
    return 0;
}
