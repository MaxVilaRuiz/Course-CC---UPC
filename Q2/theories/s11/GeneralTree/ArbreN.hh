#ifndef ARBREN_HH
#define ARBREN_HH

#include "utils_pro2.hh"
#include <vector>

template <class T> class ArbreNari { 
  private:
  // especificaci� operacions privades

  struct node_arbreNari {
    T info;
    vector<node_arbreNari*> seg;
  };

  int N;
  node_arbreNari* primer_node;
	
  static node_arbreNari* copia_node_arbreNari(node_arbreNari* m) { 
  /* Pre: cert */
  /* Post: el resultat �s NULL si m �s NULL; en cas contrari, el resultat apunta
          al node arrel d'una jerarquia de nodes que �s una c�pia de la 
          jerarquia de nodes que t� el node apuntat per m com a arrel */
    node_arbreNari* n;
    if (m == NULL) n = NULL;
    else {
      n = new node_arbreNari;
      n->info = m->info;
      int ari = m->seg.size();
      n->seg = vector<node_arbreNari*>(ari);
      for (int i = 0; i < ari; ++i) 
        n->seg[i] = copia_node_arbreNari(m->seg[i]);
    }
    return n;
  }

  static void esborra_node_arbreNari(node_arbreNari* m) {  
    /* Pre: cert */
    /* Post no fa res si m �s NULL; en cas contrari, allibera espai de tots els nodes
            de la jerarquia que t� el node apuntat per m com a arrel */
    if (m != NULL) {
      int ari = m->seg.size();
      for (int i = 0; i < ari; ++i) 
        esborra_node_arbreNari(m->seg[i]);
      delete m;
    }
  }

  public:
  // especificaci� operacions p�bliques

  /* Pre: cert */
  /* Post: el p.i. �s un arbre buit d'aritat n */
  ArbreNari(int n) {
    N = n;
    primer_node= NULL;
  }

  /* Pre: cert */
  /* Post: el p.i. �s un arbre amb arrel x i n fills buits */
  ArbreNari(const T &x, int n) {
    N = n;
    primer_node= new node_arbreNari;
    primer_node->info = x;
    primer_node->seg = vector<node_arbreNari*>(N);
    for (int i=0; i<N; ++i) 
      primer_node->seg[i] = NULL;
  }

  /* Pre: cert */
  /* Post: el p.i. �s una c�pia d'original */
  ArbreNari(const ArbreNari& original) {
    N = original.N;
    primer_node = copia_node_arbreNari(original.primer_node);
  }

  // Destructora: Esborra autom�ticament els objectes locals en
  // sortir d'un �mbit de visibilitat
  ~ArbreNari() {
    esborra_node_arbreNari(primer_node);
  }

  /* Pre: cert */
  /* Post: El p.i. passa a ser una c�pia d'original i qualsevol
      contingut anterior del p.i. ha estat esborrat 
      (excepte si el p.i. i original ja eren el mateix objecte) */
  ArbreNari& operator=(const ArbreNari& original) {
    if (this != &original) {
      esborra_node_arbreNari(primer_node);
      N = original.N;
      primer_node = copia_node_arbreNari(original.primer_node);
    }
    return *this;
  }

  /* Pre: cert */
  /* Post: el p.i. �s un arbre buit */
  void a_buit() {
    esborra_node_arbreNari(primer_node);
    primer_node= NULL;
  }        

  /* Pre: cert */
  /* Post: el resultat indica si el p.i. �s un arbre buit */
  bool es_buit() const {
    return (primer_node == NULL);
  }

  /* Pre: cert */
  /* Post: el resultat �s l'aritat del p.i. */
  int aritat() const {
    return N;
  }

  /* Pre: el p.i. no �s buit */
  /* Post: el resultat �s l'arrel del p.i. */
  T arrel() const {
    if (primer_node != NULL)   return primer_node->info;
    else throw PRO2Excepcio("El p.i. d'arrel no pot ser buit a la crida");
  }

  /* Pre:  el p.i. �s buit i la longitud de v �s igual a l'aritat del p.i.*/
  /* Post: el p.i. t� x com a arrel i els N elements originals  
          de v com a fills, v passa a contenir arbres buits */
  void plantar(const T &x, vector<ArbreNari> &v) {
    if (primer_node==NULL){
      if (v.size()==N){ 
        node_arbreNari* aux= new node_arbreNari;
        aux->info= x;
        aux->seg = vector<node_arbreNari*>(N);
        for (int i=0; i<N; ++i) {
          aux->seg[i] = v[i].primer_node;
          v[i].primer_node = NULL;
        }
        primer_node = aux;
      }
      else throw PRO2Excepcio("Al plantar, el size del vector ha de ser igual a l'aritat de l'arbre");
    }
    else throw PRO2Excepcio("El p.i. de plantar ha de ser buit a la crida");
  }

  /* Pre:  el p.i. no �s buit i li diem A, v �s un arbre buit */
  /* Post: el p.i. �s buit, v passa a contenir els N fills de l'arbre A  */
  void fills(vector<ArbreNari> &v) {
    if (primer_node!=NULL){
      if (v.size()==0){ 
        node_arbreNari* aux= primer_node;
        v= vector<ArbreNari> (N,ArbreNari(N));
        for (int i=0; i<N; ++i) {
          v[i].primer_node = aux->seg[i];  
        }
        primer_node= NULL;
        delete aux;
      }
      else throw PRO2Excepcio("No es pot passar a fills un vector no buit");
    }
    else throw PRO2Excepcio("El p.i. de fills no pot ser buit a la crida");
  }

};

#endif
