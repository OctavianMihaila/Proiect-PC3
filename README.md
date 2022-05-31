# Proiect-PC3

/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */

# Implementare 

    Pentru implementarea hotelului smart am folosit structuri de
date invatate la SD cat si notiuni invatate la cursurile de 
PC si PC3.

    Hotelul dispune de doua optiuni de comanda, una pentru 
clienti(posibilitatea de a controla interactiv sistemul de lumini),
iar cealalta pentru administratie(gestionarea persoanelor cazate
si starea curent a camerelor).

    # Implementare becuri pe biti:

    Am ales un mod eficient de a implementa functionalitatile unui bec,
stocand intr-un singur int, informatiile legate de starea acestuia si
luminozitatea (R G B). Practic, privind big endian, primul byte este
rezervat pentru a specifica daca becul este on/off, iar urmatorii 3
in ordine reprezinta valorile R G B.


    # Implementare situatie actuala a camerelor din hotel.

    Am folosit un flag (room->used) pentru a marca starea fiecarei camere
din hotel(1, pentru inchiriat, 0 pentru libera, -1 in curs de curatare).
Astfel, in momentul in care o camera este eliberata, aceasta este introdusa
in coada de curatare, de unde va fi preluta pentru a fi curatata in functie
de disponibilitatea housekeeperilor. Ca un caz special, in situatia in care
se face request pentru a inchiria o camera aflata in coada de asteptare pentru
curatare, aceasta devine automat prioritara (trece prima in coada de curatare).

    # Implementare day_passed.

    Acest concept nu reprezinta altceva decat o cuanta de timp prin intermediul
careia putem tine evidenta zilelor ramase pentru fiecare chirias in parte. 
Totodata aceasta cuanta are rol si in procesul de cleanup. Mai exact, in
fiecare zi se pot curata un numar maxim de camere 
(nr_housekeepers * max_rooms_cleanup) din coada de curatare.

    Link github: https://github.com/OctavianMihaila/Proiect-PC3