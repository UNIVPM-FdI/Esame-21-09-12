#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct libri 
{
	char nome[20];
	int inv;
	int disp;
	libri* succ;
};
typedef libri* lista; //definisco la lista

void inserimentordinato(lista& inz, libri a)
{lista p = 0, q, r;
for (q=inz; q!=0 && q->inv < a.inv; q = q->succ)
 p = q;
r = new libri;
strcpy(r->nome,a.nome); // essendo una stringa bisogna utilizzare il comnado strcpy per copiare da r->nome ad a.nome
r->inv=a.inv;
r->disp=a.disp;
r->succ = q;
// controlla se si deve inserire in testa
if (q == inz) inz = r;
 else p->succ = r;
}

/* nella soluzione del compito dragoni utilizza due funzioni per mettere i file nelle due liste diverse, quando basta passare alla funzione entrambi le iste
 e con un semplice if, nella funzione, che controlla se nella variabile disp(che legge dal file di testo) c'è l "1" o lo "0", e in base a questo va a mettere
 l'elemento o in una lista o nell'altra */
void inserisci (lista& p0,lista& q0) 
{
	libri x;
	fstream input;
	input.open("libri.dat",ios::in);
	 while (input.good())
	 {input >> x.nome >> x.inv >> x.disp ;
      if (x.disp==1) inserimentordinato(p0,x); // se ha numero di inventario =1 va messo nella lista presenti 
      else inserimentordinato(q0,x); // altrimenti lo mettiamo nella lista in prestito 
}
input.close(); 
}

void stampalista(lista p)
{
	while (p!=0)
	{
		cout << p->nome << " " << p->inv << " " << p->disp << endl;
		p=p->succ;
	}
}
void cerca(int numero)
{
	fstream input;
	bool cercato=false;
	int cod;
	char nome[20];
	input.open("utenti.dat",ios::in);
	while (input.good()) /*la funzione .good() è funzione booleana e legge una riga alla volta, fino a quando non trova la riga vuota restituendo false
	in modo da fermare il ciclo(while) perchè non è piu true la condizione del while */ 
	{
		input >> nome >> cod;
		if (cod==numero) 
		{
			cout <<  "il libro e' in prestito a " << nome << endl;
			cercato=true;
			return;
		}
	}
	if (cercato==false) cout << "il libro non e' in prestito a nessuna persona" << endl;
}

int main()
{
int numero;
lista presenti=0; //inizializzo i due puntatori delle due liste
lista in_prestito=0;
inserisci(presenti,in_prestito); // legge e inserisce nella lista corretta 
cout << "lista dei libri presenti" << endl; 
stampalista(presenti); // stampa la prima lista
cout << "lista dei libri in prestito" << endl;
stampalista(in_prestito); // stampa la prima lista
cout << "numero inventario libro che desidera" << endl;
cin >> numero;
cerca (numero);
return 0;
}




