Calina Cristian Florin 313 CA



Metoda abordata in implementarea codului a fost urmatoarea:




Mai intai am citit numarul de elevi si numarul de materii.

Prin intermediul functiei citire am citit ponderile materiilor pe o linie,
si matricea catalog ce continea notele elevilor.
Elevii se regasesc pe liniile matricei iar materiile pe coloane.

Dupa aceea am calculat in functia pozitie_proba, intr-o noua matrice, pozitiile elevilor 
la materiile respective (in locul notelor, matricea poz_proba continea locul pe care il 
ocupau elevii in clasamentul materiei respective prin nota lor).
Pentru aceasta am folosit un vector numit distincte in care retineam doar notele
distincte de la materia respectiva si apoi am verificat cate note din catalogul materiei 
curente al elevilor sunt mai mici decat notele din vectorul distincte , crescandu-le 
astfel pozitia. Daca nu ar fi existat vectorul distincte si as fi avut doua note egale
si una distincta, spre exemplu, nu s-ar fi efectuat implementarea corecta a pozitiilor.
(ca de exemplu 9.50 8.50 9.50 ar fi avut ca rezultat 1 3 1 in loc de 1 2 1)


Urmatorul pas a fost de a calcula in functia p1 media notelor obtinute la cele d probe
conform algoritmului din cerinta.

De asemenea, am calculat in functia p2 , pozitia medie in clasament tot conform algoritmilor 
din cerinta folosindu-ma de matricea cu pozitiile explicata mai sus (prin apelarea functiei
pozitie_proba)

In urmatoarea functie, punctaj_final , am apelat functiile p1 si p2 si am adunat in vectorul
punctaj_final_elev , media_notelor (p1) cu pozitia_medie (p2) pentru fiecare elev in parte.

In functia vector_ordine am apelat functia punctaj_final pentru a prelua valorile vectorului
punctaj_final_elev. Dupa aceea am comparat pe rand toti elevii (prin j) cu primul (prin i),
apoi cu al 2-lea si asa mai departe , iar daca punctaj_final_elev[j] era mai mare decat
punctaj_final_elev[i], cresteam pozitia elevui (i) in vectorul de ordine. Acesta retine ordinea
in functie de punctajul final al elevilor.

Urmatoarea functie ,numita afisare_clasament, apeleaza functia vector_ordine pentru a prelua
valorile vectorului ordine iar apoi acesta este parcurs si se cauta elevul de pe prima pozitie
afisandu-se sub forma 1.elevX unde X reprezinta cifra elevului de pe prima pozitie in clasament.



Ultima functie, afisare_perfectionare, foloseste un algoritm descris in felul urmator:

1. Parcurg toti elevii precum si materile si creez o matrice clona pentru matricea catalog.

2. Apelez functia vector_ordine pentru a prealua valorile vectorilor ordine si punctaj_final_elev.

3. Parcurg din nou toti elevii si il caut pe cel de pe primul loc, punandu-i pozitia intr-o variabila
numita loc1, iar dupa ce il gasesc folosesc break; .

4. Parcurg toti elevii din nou si initializez variabila s (care va retine numarul minim de materii
la care elevul trebuie sa ia 10 pentru a ajunge pe primul loc) cu 0.

5. Atat timp cat elevul curent nu a depasit elevul de pe primul loc , initializez 
variabilele max si materie cu 0 (max va retine materia cu influenta maxima iar materie va 
retine pozitia acesteia). 

6.Dupa aceea, parcurg toate disciplinele si verific daca nota elevului curent la disciplina curenta
este 10 si in caz afirmativ trec la urmatoarea materie. Daca nota este diferita de 10 , voi atribui 
unei variabile "nota" nota elevului curent la materia curenta si dupa ii voi creste nota acestuia 
la 10. Voi apela dupa aceea functia punctaj_final pentru a vedea modificarile vectorului punctaj_final_elev. 
Daca punctajul final al elevului va fi mai mare decat max , ii voi da lui max valoarea punctajului 
final al elevului si variabilei "materie" pozitia materiei.Dupa aceea voi reatribui in catalog 
nota initiala a elevului la acea materie.


7. Dupa ce se parcurg toate materiile si avem un max final si variabila "materie" are o anumita
valoare , ii voi atribui elevului la materia "materie" nota maxima . Dupa aceea reapelez functia
vector_ordine (pentru verificarea conditiei din while) si voi creste s-ul.


8. La iesirea din while voi reatribui valorile initiale ale matricei catalog in catalog2, si voi
trece la verificarea urmatorului elev.


Programul este modularizat avand foarte putine linii in main si 8 functii , acesta trece toate testele
in aproximativ 37 secunde si nu depaseste pe nici o linie mai mult de 80 de caractere respectand astfel
regulile impuse.
