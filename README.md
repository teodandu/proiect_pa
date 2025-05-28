# Proiect PA – Game of Life
Acest proiect implementează patru taskuri inspirate din jocul Game of Life. Fiecare task aplică reguli de evoluție pe o matrice de celule și analizează rezultatele în diverse moduri, utilizand diverse structuri de date.
Mai multe detalii găsiți pe site:https://site-pa.netlify.app/proiecte/game_of_life/.

## Structură

- **task1.c:** Aplică regulile clasice ale Game of Life pe o matrice.
   - Funcție importantă: `prelucrare()` -aplică regulile din jocul Game of Life.
- **task2.c:** Stocarea diferențelor dintre generatii în diverse structuri de date.
   - Funcție importantă: `compara_generatii()`-detectează și stochează într-o listă celulele care și-au schimbat starea.
- **task3.c:** Schimbarea regulilor și construirea un arbore de evoluție.
   - Funcții importante: `prelucrare_noua()`-aplică noile reguli Game of Life și `tree()`-construiește arborele binar ce conține coordonatele celulelor care si-au schimbat starea.
- **task4.c:** Reprezentarea unei generații sub forma unui graf și determinarea celui mai lung lanț Hamiltonian.
   - Funcție importantă: `dfs_hamiltonian()`-caută cel mai lung lanț Hamiltonian.
- **game_of_life.h / game_of_life.c**  
  -Conțin funcții care implementează regulile jocului Game of Life și operații utile asupra matricilor (alocare, copiere, eliberare memorie etc.).
- **tree.h / tree.c**  
  Conțin definiții pentru structuri de date (`TreeNode`, `ListNode`) și funcții pentru construirea și parcurgerea arborelui de evoluție.
- **main()** este localizat în fiecare fișier `taskX.c` și tratează citirea datelor, apelul funcțiilor și scrierea rezultatului.


## Utilizare
1. Structură de directoare:
├── in/       # Fișierele de intrare pentru fiecare task
├── ref/      # Fișierele de referință corecte
├── out/      # Aici vor fi generate fișierele de ieșire
├── src/      # Sursele proiectului (task1.c, task2.c, etc.)
├── Makefile
├── config.json

2.Pentru a testa automat ieșirile față de referință, utilizăm checkerul pe care îl putem descărca și vizualiza detalii despre el aici:https://site-pa.netlify.app/proiecte/checker/.
3.După compilarea taskurilor(utilizand make build), trebuie sa rulam checkerul. Acesta va executa automat toate taskurile și va salva fișierele de ieșire în out/, apoi le va compara cu cele din ref/.
