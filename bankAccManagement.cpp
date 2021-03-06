#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
class Cont {
private:
	int id_cont;
	static int conturi;
	double valoare;
	bool inchis;
public:
	Cont()
	{
		conturi++;
		id_cont = conturi;
		valoare = 0;
		inchis = true;
	}

	void set_valoare(double bani)
	{
		this->valoare = bani;
	}
	void adauga_bani(double bani)
	{
		this->valoare = this->valoare + bani;
	}
	void scade_bani(double bani)
	{
		this->valoare = this->valoare - bani;
	}

	double get_valoare()
	{
		return this->valoare;
	}

	void set_id_cont(int id)
	{
		this->id_cont = id;
	}


	int get_id_cont()
	{
		return this->id_cont;
	}
	void set_inchis(bool cont)
	{
		this->inchis = cont;
	}
	bool get_inchis()
	{
		return this->inchis;
	}

	void afisare()
	{
		cout << "\nID cont -> " << id_cont << endl;
		cout << "\nBani in cont -> " << valoare << endl;
	}

	friend istream& operator>>(istream& is, Cont& c)
	{
		bool verif = false;
		c.set_inchis(verif);
		cout << "\nSuma depusa -> ";

		is >> c.valoare;


		return is;
	}

	friend ostream& operator<<(ostream& os, Cont& c)
	{
		os << "\nID cont ->" << c.id_cont << endl;
		os << "\nBani in cont ->" << c.valoare << endl;
	}



};
int Cont::conturi = 0;
class Client
{
private:
	int id_client;
	static int clienti;
	char* nume_client;
	char* prenume_client;
	Cont** vect_conturi;
	int nr_conturi;
	double bani_in_conturi;
	double valoare_conturi;
	bool cont_inchis;
public:
	Client()
	{
		clienti++;
		id_client = clienti;
		nume_client = new char[3];
		strcpy(nume_client, "NA");
		prenume_client = new char[3];
		strcpy(prenume_client, "NA");
		vect_conturi = new Cont * [0];
		nr_conturi = 0;
		bani_in_conturi = 0;
	}

	void set_id_client(int id)
	{
		this->id_client = id;
	}

	int get_id_client()
	{
		return this->id_client;
	}

	void set_nume_client(const char* nume)
	{
		delete[] this->nume_client;
		this->nume_client = new char[strlen(nume) + 1];
		strcpy(this->nume_client, nume);
	}

	char* get_nume_client()
	{
		return this->nume_client;
	}



	void set_prenume_client(const char* prenume)
	{
		delete[] this->prenume_client;
		this->prenume_client = new char[strlen(prenume) + 1];
		strcpy(this->prenume_client, prenume);
	}

	char* get_prenume_client()
	{
		return this->prenume_client;
	}




	void set_bani_in_conturi(int bani)
	{
		bani_in_conturi = bani;
	}

	double get_bani_in_conturi()
	{
		return this->bani_in_conturi;
	}

	void set_valoare_conturi() {
		valoare_conturi = 0;
		for (int i = 0; i < nr_conturi; i++)
		{
			valoare_conturi += vect_conturi[i]->get_valoare();
		}
	}
	double get_valoare_conturi()
	{
		return valoare_conturi;
	}

	void set_cont_inchis()
	{
		cont_inchis = false;
		for (int i = 0; i < nr_conturi; i++)
		{
			cont_inchis += vect_conturi[i]->get_inchis();
		}
	}

	bool get_cont_inchis() {
		return cont_inchis;
	}

	void deschidere_cont(Cont* c)
	{
		Cont** cont_copie = new Cont * [nr_conturi + 1];
		for (int i = 0; i < nr_conturi; i++)
		{
			*(cont_copie + i) = *(vect_conturi + i);
		}
		*(cont_copie + nr_conturi) = c;
		delete[] vect_conturi;
		vect_conturi = cont_copie;
		nr_conturi++;
	}

	void inchidere_cont(int id_cont) {
		for (int i = 0; i < nr_conturi; i++)
			if (vect_conturi[i]->get_id_cont() == id_cont)
			{
				delete[] vect_conturi[i];
				vect_conturi[i]->set_inchis(true);
			}

	}
	void get_nr_conturi(int nr)
	{
		nr_conturi = nr;
	}

	int set_nr_conturi()
	{
		return nr_conturi;
	}

	void afisare_conturi()
	{
		for (int i = 0; i < nr_conturi; i++)
			if (vect_conturi[i]->get_inchis() != true)
				vect_conturi[i]->afisare();
	}

	void depunere_bani(int id_cont)
	{
		for (int i = 0; i < nr_conturi; i++)
			if (vect_conturi[i]->get_id_cont() == id_cont)
			{
				double suma;
				cout << "Introduceti suma pe care vreti sa o depuneti -> ";
				cin >> suma;
				vect_conturi[i]->adauga_bani(suma);

			}
	}

	void retragere_bani(int id_cont)
	{
		for (int i = 0; i < nr_conturi; i++)
			if (vect_conturi[i]->get_id_cont() == id_cont)
			{
				double suma;
				cout << "Introduceti suma pe care vreti sa o retrageti -> ";
				cin >> suma;
				vect_conturi[i]->scade_bani(suma);

			}
	}

	void total_disponibil()
	{
		for (int i = 0; i < nr_conturi; i++)
		{
			bani_in_conturi = bani_in_conturi + vect_conturi[i]->get_valoare();
		}
	}



	void transfer_bani(int id1, int id2, double suma)
	{
		for (int i = 0; i < nr_conturi; i++)
			for (int j = 0; j < nr_conturi; j++)
				if (vect_conturi[i]->get_id_cont() == id1 && vect_conturi[j]->get_id_cont() == id2)
				{
					vect_conturi[i]->adauga_bani(suma);
					vect_conturi[j]->scade_bani(suma);
				}

	}

	Cont* get_cont(int i)
	{
		return *(vect_conturi + i);
	}
	Cont alege_cont(int id_cont)
	{
		for (int i = 0; i < nr_conturi; i++)
			if (vect_conturi[i]->get_id_cont() == id_cont)
				return *vect_conturi[i];
		Cont c;
		return c;
	}

	void afiseaza()
	{
		cout << "\nID client -> " << this->id_client << endl;
		cout << "Nume client -> " << this->nume_client << endl;
		cout << "Prenume client -> " << this->prenume_client << endl;
		cout << "Numar conturi client -> " << this->nr_conturi << endl;

	}
	friend istream& operator>>(istream& is, Client& c)
	{

		cout << "\nNume client -> ";
		is >> c.nume_client;
		cout << "Prenume client -> ";
		is >> c.prenume_client;
		return is;
	}

	friend ostream& operator<<(ostream& os, Client& c)
	{
		os << "ID client -> " << c.id_client;
		os << "Nume client -> " << c.nume_client;
		os << "Prenume client -> " << c.prenume_client;
		os << "Numar conturi ->" << c.nr_conturi;
	}



};
int Client::clienti = 0;

class Banca {
private:
	int id_banca;
	char* denumire_banca;
	Client** vector_clienti;
	int nr_clienti;
	double total_bani;
public:
	Banca()
	{
		id_banca = 0;
		denumire_banca = new char[3];
		strcpy(denumire_banca, "NA");
		vector_clienti = new Client * [0];
		nr_clienti = 0;
		total_bani = 0;
	}

	void set_denumire_banca(const char* denumire)
	{
		delete[] this->denumire_banca;
		this->denumire_banca = new char[strlen(denumire) + 1];
		strcpy(this->denumire_banca, denumire);

	}

	char* get_denumire_banca()
	{
		return this->denumire_banca;
	}

	void calcul_total_bani(int id)
	{
		for (int i = 0; i < nr_clienti; i++)
			if (vector_clienti[i]->get_id_client() == id)
				total_bani = vector_clienti[i]->get_bani_in_conturi();

	}

	double get_total_bani()
	{
		return this->total_bani;
	}

	Client* get_client(int i)
	{
		return *(vector_clienti + i);
	}

	void set_nr_clienti(int nr)
	{
		this->nr_clienti = nr;
	}

	int get_nr_clienti()
	{
		return this->nr_clienti;
	}

	void adauga_client(Client* cl)
	{
		Client** copie_client = new Client * [nr_clienti + 1];
		for (int i = 0; i < nr_clienti; i++)
			*(copie_client + i) = *(vector_clienti + i);
		*(copie_client + nr_clienti) = cl;
		delete[] vector_clienti;
		vector_clienti = copie_client;
		nr_clienti++;
	}

	void afiseaza_clienti()
	{
		for (int i = 0; i < nr_clienti; i++)
		{
			vector_clienti[i]->afiseaza();
		}
	}

	Client alege_client(int id_client)
	{
		for (int i = 0; i < nr_clienti; i++)
			if (vector_clienti[i]->get_id_client() == id_client)
				return *vector_clienti[i];
		Client c;
		return c;
	}

	void adauga_conturi(int id, Cont* cy)
	{
		get_client(id - 1)->deschidere_cont(cy);

	}

	friend istream& operator>>(istream& is, Banca& b)
	{
		cout << "ID banca -> ";
		is >> b.id_banca;
		cout << "Denumire banca -> ";
		is >> b.denumire_banca;
		return is;
	}
	friend ostream& operator<<(ostream& os, Banca& b)
	{
		os << "\nId banca -> " << b.id_banca << endl;
		os << "Denumire banca -> " << b.denumire_banca << endl;
		os << "Numar clienti-> " << b.nr_clienti << endl;
		return os;
	}


};

void main()
{
	Banca b;
	cin >> b;
	bool meniu = true;
	while (meniu)
	{

		cout << endl;
		cout << b;
		cout << "\n";
		cout << "\n1. Adauga client" << endl;
		cout << "2. Afiseaza clienti" << endl;
		cout << "3. Alege client" << endl;
		cout << "4. Exit\n";
		int a;
		cout << "\nAlegeti o optiune -> ";
		cin >> a;
		switch (a)
		{
		case 1:
		{
			cout << b;
			cout << "\n";
			Client* c = new Client();
			cin >> *c;
			b.adauga_client(c);


		}
		break;
		case 2:
		{
			cout << b;
			cout << "\n";
			b.afiseaza_clienti();
		}
		break;
		case 3:
		{


			cout << b << endl;
			int id;
			cout << "\nIntroduceti id client -> ";
			cin >> id;
			b.alege_client(id).afiseaza();
			int y = 1;
			do {


				cout << "\n1. Deschidere cont" << endl;
				cout << "2. Afiseaza conturi" << endl;
				cout << "3. Depunere bani" << endl;
				cout << "4. Retrageri bani" << endl;
				cout << "5. Transfer bani" << endl;
				cout << "6. Inchidere cont" << endl;
				
				cout << "7. Revenire la clienti\n";

				int x;
				cout << "\nAlegeti o optiune -> ";
				cin >> x;
				switch (x)
				{
				case 1:
				{
					Cont* co = new Cont();
					cin >> *co;


					b.adauga_conturi(id, co);



				}
				break;
				case 2:
				{
					b.alege_client(id).afiseaza();
					b.alege_client(id).afisare_conturi();

				}
				break;
				case 3:
				{
					int id_cont;

					cout << "\nIntroduceti id-ul contului in care vreti sa depuneti suma -> ";
					cin >> id_cont;
					b.alege_client(id).depunere_bani(id_cont);

				}
				break;
				case 4:
				{
					int id_cont;
					cout << "\nIntroduceti id-ul contului din care vreti sa retrageti suma -> ";
					cin >> id_cont;
					b.alege_client(id).retragere_bani(id_cont);
				}
				break;
				case 5:
				{
					int id_cont1;
					int id_cont2;
					double suma_dorita;
					cout << "\nTransfer in contul cu id-ul -> ";
					cin >> id_cont1;
					cout << "\nSuma pe care vreti sa o transferati -> ";
					cin >> suma_dorita;
					cout << "\nDin contul cu id-ul -> ";
					cin >> id_cont2;
					b.alege_client(id).transfer_bani(id_cont1, id_cont2, suma_dorita);

				}
				break;
				case 6:
				{
					int id_cont;
					cout << "\nIntroduceti id-ul contului pe care vreti sa-l inchideti: ";
					cin >> id_cont;
					cout << "\nSunteti sigur ca vreti sa inchideti contul cu id-ul " << id_cont << " ?";
					string confirmare;
					cout << "\nAlegeti: DA/NU";
					cin >> confirmare;
					if (confirmare == "DA")
						b.alege_client(id).inchidere_cont(id_cont);
					else break;

				}
				break;
				
				case 7:
				{
					y = 0;
				}

				}
			} while (y != 0);

		}
		}
	}


}