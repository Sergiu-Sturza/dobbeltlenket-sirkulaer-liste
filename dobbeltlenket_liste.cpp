#include<iostream>
#include<string>
#include<cstdlib>
#include<memory>
#include <vector>
#include <algorithm>

struct Node {
	std::string Navn;
	int ID;
	Node* neste;
	Node* forrige;
	Node(std::string Navn, int ID)
	{
		this->Navn = Navn;
		this->ID = ID;
		neste = nullptr;
		forrige = nullptr;
	}
};

class DobbeltLenketSirkulaerListe {
private:
	Node* head = nullptr;
public:
	DobbeltLenketSirkulaerListe() {}

	void leggTil(int ID, std::string Navn) {
		Node* ny = new Node(Navn, ID);

		// Tillfelle A: sjekker om ID finnes fra før (ingen duplikater)
		if (head != nullptr) {
			Node* sjekk = head;
			do {
				if (sjekk->ID == ID) {
					std::cout << "ID" << ID << "finnes allerede. \n";
					return; //avbryt, vi legger ikke til
				}
				sjekk = sjekk->neste;
			} while (sjekk != head);
		}

		// Tilfelle B: tom liste
		if (head == nullptr) {
			head = ny;
			ny->neste = ny;  //peker på seg selv
			ny->forrige = ny;  // begge veier
			return;
		}

		//Tilfelle C: ny node har lavest ID -> settes foran head
		if (ID < head->ID) {
			Node* sist = head->forrige; // den siste i ringen
			ny->neste = head;
			ny->forrige = sist;
			sist->neste = ny;
			head->forrige = ny;
			head = ny; //ny er nå den minste -> ny head
			return;
		}

		// Tilfelle D: finn riktig plass inne i / på slutten av lista
		Node* current = head;
		while (current->neste != head && current->neste->ID < ID) {
			current = current->neste;
		}
		Node* etter = current->neste;  // noden som skal komme etter den nye
		ny->neste = etter;
		ny->forrige = current;
		current->neste = ny;
		etter->forrige = ny;
	}

	void skrivUt() {
		if (head == nullptr) {
			std::cout << "Listen er tom.\n";
			return;
		}
		Node* current = head;
		do {
			std::cout << "ID: " << current->ID << ", Navn: " << current->Navn << "\n";
			current = current->neste;
		} while (current != head); // går ut av loopen
	}

	// implementerer slett-funksjonen
	void slett(int ID) {
		// hvis lista er tom, det er ingenting å slette
		if (head == nullptr) {
			std::cout << "Listen er tom. \n";
			return;
		}

		// finn noden med riktig ID
		Node* current = head;
		do {
			// finner noden som skal slettes fra lista
			if (current->ID == ID) {
				// sjekker hvis current er den eneste noden i lista
				if (current->neste == current) {
					delete current;
					head = nullptr;
					return;
				}

				// vi kobler sammen nodene som var før og etter nodden som blir slettet
				current->forrige->neste = current->neste;
				current->neste->forrige = current->forrige;

				// hvis noden som skal slettes er headen, da må head flyttes til å være det neste noden i lista
				if (current == head) {
					head = current->neste;
				}

				// sletter noden
				delete current;
				return;
			}
			// erstater current node med neste node
			current = current->neste;
		}
		// går ut av loopen
		while (current != head);

		// skriver ut en prompt i tilfelle vi fant ingen node med den ID-en
		std::cout << "Fant ingen node med ID" << ID << ".\n";
	}

	void slett(std::string Navn) {
		// hvis navnet finnes ikke, sendes det en prompt om det
		if (head == nullptr) {
			std::cout << "Listen er tom. \n";
			return;
		}

		Node* current = head; // lager en midlertidig peker (current) som peker på første noden
		int antallSlettet = 0;
		int antallNoder = 0;

		// teller hvor mange noder det finnes i lista
		Node* teller = head;
		do {
			antallNoder++;
			teller = teller->neste;
		} while (teller != head);

		// går gjennom nøyaktig så mange noder som lista inneholder
		for (int i = 0; i < antallNoder; i++) {
			Node* neste = current->neste; // lagrer veien til neste node

			if (current->Navn == Navn) {
				// fant navnet som skal slettes

				if (current->neste == current) {
					// vi flytter pekeren til neste noden (som inneholder neste navn)
					delete current; //sletter noden med navnet vi fant i lista
					head = nullptr;
					return;
				}

				// kobler nabo-nodene sammen
				current->forrige->neste = current->neste;
				current->neste->forrige = current->forrige;

				if (current == head) {
					head = current->neste;
				}

				delete current;
				antallSlettet++;
			}
			current = neste;  
		}

		if (antallSlettet == 0) {
			std::cout << "Fant ingen node med navn " << Navn << ".\n";
		}
	}

	void skrivUtNavnAlfabetisk() {
		if (head == nullptr) {
			std::cout << "Listen er tom. \n";
			return;
		}

		// kopierer alle nodene i en vektor for å kunne rangere dem etter navn, ikke ID
		std::vector<Node*> noder;
		Node* current = head;
		do {
			noder.push_back(current);  // legger pekerne inn i vektoren
			current = current->neste;
		} while (current != head);

		// sorterer vectoren etter Navn ved å bruke std::sort
		std::sort(noder.begin(), noder.end(),
			[](Node* a, Node* b) {
			return a->Navn < b->Navn;
			});

		// skriver ut fra den sorterte vektoren
		for (Node* n : noder) {
			std::cout << "Navn: " << n->Navn
				<< ", ID: " << n->ID << "\n";
		}
	}

	~DobbeltLenketSirkulaerListe() {
		if (head == nullptr) return;  // tom liste så det er ingentig å rydde

		Node* current = head->neste;  // starter på node nr.2
		while (current != head) {
			Node* neste = current->neste; // lagre veien til neste node først
			delete current;   // sletter noden nr. 2
			current = neste;  // flytter pekeren til neste noden
		}
		delete head;  // til slutt sletter head noden
	}
};

int main() {
	DobbeltLenketSirkulaerListe liste;
	liste.leggTil(3, "Kari");
	liste.leggTil(1, "Ola");
	liste.leggTil(5, "Per");
	liste.leggTil(4, "Nina");
	liste.leggTil(1, "Duplikat");

	liste.skrivUt();

	return 0;
}
