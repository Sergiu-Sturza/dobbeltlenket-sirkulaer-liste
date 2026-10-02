Doubly Linked Circular List (C++)

A doubly linked circular list implemented in C++ as a class. Each node points to both its next and previous neighbour, and the last node links back to the first, so the nodes form a closed ring. The list is kept sorted by ID at all times.

University coursework (Programmering 3 — Algoritmer), USN Kongsberg.

Operations
Method	What it does
leggTil(int ID, string Navn)	Inserts a node, keeping the list sorted by ID; rejects duplicate IDs
slett(int ID)	Removes the node with the given ID
slett(string Navn)	Removes all nodes with the given name
skrivUt()	Prints all elements in ID order
skrivUtNavnAlfabetisk()	Prints all elements sorted alphabetically by name

A destructor frees every node when the list goes out of scope, so there are no memory leaks.

Design note

The list uses a single head pointer (the node with the lowest ID). There is no separate tail pointer — the last node is reached through head->forrige, taking advantage of the circular structure.

Build & run
bash
g++ -std=c++17 dobbeltlenket_liste.cpp -o liste
./liste          # on Windows: liste.exe
Full write-up

The complete lab report (concept, design choices, test cases and results) is in Raport_Sergiu_Sturza.docx — written in Norwegian.