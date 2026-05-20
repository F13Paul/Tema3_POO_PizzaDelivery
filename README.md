# Proiect POO - Pizza Delivery

## Enunț

Am incercat sa implemntez un sistem de gestiune a comenzilor unui restaurant de tip Pizza Delivery. O comanda poate fi alcatuita din mai multe produse cum ar fi pizza, bauturi si desertui. Clientul are libertatea de a isi alege produsele dorite sau chiar de a propune un nou produs ce poate fi adaugat utlerior in comanda. Inainte de a finaliza achizitia, persoana poate opta pentru o reducere care se aplica la totalul final al comenzii. Reducerile sunt de 2 tipuri: fixe, exprimata in lei, sau procentuala, exprimata printr-un numat intre 0-100(%).

La final, clientul primeste un bon oe care se afla toate produse comandate, numele acestora, pretul lor final, caracteristica lor ( pizza - ingrediente, bautura - volum, desret - kcal), dar si pretul final al comenzii dupa si inainte de reducere.

## Rezolvare

Pentru a implementa un astfel de sistem, am folosit notiuni de programarea orientata pe obiecte, notiuni acumulate pe parcursul semestrului prin participarea la cursuri, seminare si laboratoare, cat si prin consultarea diferitelor materiale de pe internet.
Logica implementarii este urmatoarea: 

Am o clasa de baza (PRODUS) din care deriva 3 clase:

    -> pizza

    -> bautura

    -> desert

Fiecare produs face parte din una dintre aceste categrii, avand ca atribute comune, pretul de baza si denumirea, restul atributelor fiind specifice fiecarei clase. De exemplu, un desert are un numar de calorii.

Pentru a gestiona produsele alese de client, am implementat o noua clasa Comanda.Aceasta contile o colectie de produse si permite adaugarea mai multor obiecte de tipuri diferite. Deoarece prdusele sunt stocate prin pointeri la clasa de baza, am folosit polimorfismul pentru a trata uniform obiectele de tip Pizza, Bautura si Desert.

Pentru copierea corecta a obiectelor derivate, am folosit metoda virtuala clone(). Astfel, atunci cand este adaugat un produs in comanda, se creeaza o copie polimorfica a acestuia, fara a pierde informatii specifice clasei derivate.

Deoarece fiecare obiect primeste un id unic/diferit prin atributul static din clasa Produs, iar in comanda se adauga o copie a produsului, pe bon vom vedea cum id-ul produselor are o valoare para(2, 4, 6, ...).

Pentru a respecta cerintele temei, am adaugat si doua design pattern-uri: Factory Pattern si Strategy Pattern.

Factory Pattern este implementat prin clasa ProdusFactory, unde avem metode statice care creeaza produse predefinite ( pizza diavola, pizza pollo, cola, apa minerala, clatite cu finetti). Rolul clasei este de a centralizza crearea de produse standard din meniu. Astfel, in main nu mai este nevoie sa scriu de fiecare data constructorii completi, ci doar sa apelelez metodele corespunzatoare.

Strategy Pattern este folosti pentru sistemul de reduceri. Am creat o clasa abstracta StrategieReducre, care defineste metoda aplica(). Clasele derivate implementeaza aceasta metoda in mod diferit: fara reducere strategy nu modifica pretul, reducere fixa strategy scade o suma fixa din total, iar reducere procentuala strategy aplica o reducere procentuala. Astfel, design-ul permite schimbarea modulul de calcul al reducerii fara a modifica restul programului.

Pentru partea de programare generica, am implementat clasa template Template<'T'> , care reitne descrierea reducerii si valoarea care este un de tip generic T. Pentru reducerea fixa, clasa 'Reducere Fixa Strategy' mosteneste Reducere<'int'>, iar pentru reducere procentuala, clasa 'Reducere Procentuala Strategy' mosteneste Reducere<'double'>. Aceeasi clasa template poate fi folosita pentru reduceri cu valori de tipuri diferite. Am integrat si o functie template libera, afisareReducere, care poate afisa orice reducere bazata pe Reducere<'T'>.

La rularea programului clientului ii sunt prezentate pe ecran mai multe optiuni ( 10 la momentul redactarii, numarul poate creste in functie de cate produse predefinite adaugam in clasa ProdusFactory) acestea sunt urmatoarele:
```text
  === Sistem PizzaDelivery ===

    1. Adauga pizza custom
    2. Adauga Pizza Diavola
    3. Adauga Pizza Pollo
    4. Adauga Cola
    5. Adauga Apa minerala
    6. Adauga Clatite cu Finetti
    7. Adauga bautura custom
    8. Adauga desert custom
    9. Afiseaza comanda
    10. Alege reducere pentru intreaga comanda
    0. Finalizeaza comanda
```

Utilizatorul alege un numar intre 0 si 10, numarul corespunde optiunii dorite, daca am alege de exemplu optinuea 1 ( am introduce 1 de la tastatura) vom fi rugati sa ne personalizam pizza. Personalizarea consta in a introduce numele pizzei pe care o vom crea, numarul de ingredinete urmat de denumirea acestora si pretul de baza ( pretul final calculandu-se in functie de numarul de ingredinete).

Daca utlizatorul alege optiunea 2, fiind un produs predefinit, se adauga in comanda o pizza diavola, produs creat in PorudsFactory. In acest caz, clientul nu mai trebuie sa introduca manual datele produsului, deoarece acesta este deja definit in meniu. Optiunile 3-8 functioneaza intr-un mod similar, unele adauga produse predefinite, iar altele permit crearea unor produse personalizate.

Optinuea 9 afiseaza comanda curenta, chiar daca nu am finalizat, deoarece prdusele sunt stocate intr-un vector din clasa Comanda. Se afiseaza toate produsele, caracteristicile acestora, nuamr de pizza din comanda si totalul curent.

Alegerea opriunii 10 permite alegerea unei reduceri pentru intreaga comanda. 

```text
In acest moment clientului ii este afisat urmatorul meniu:
  === Reduceri disponibile ===
    1. Fara reducere
    2. Reducere fixa
    3. Reducere procentuala
```

alegerea optiunii 1 nu modifica totalul comenzii, fiind deja optiunea implicita, dar daca se alege optinuea 2, utlizatorul trebuie sa introduca o valoarea numerica pentru reducerea fixa, acesta suma fiind scazuta din totalul comenzii. Pentru optiunea 3, valoarea introdusa trebuie sa fie valida, adica sa se afle in intervalul 0 si 100. Programul transforma aceasta valoare in procente si aplica reducerea potrivita. Reducerile nu se cumuleaza, daca utilizatorul alege o reducere noua, acesta o inlocuiteste pe cea anterioara.

Alegerea optiunii 0 finalizeaza comanda. Programul afiseaza bonul. Pe acesta vom gasi produsele comandata, cu descrierea specifica fiecareia, numarul de pizze, cat si totalul intainte de reducere si totalul dupa aplicarea reducerii.

Aplicatia simuleaza un sistem simplu, dar functional, de comanda pentru un restaurant de tip Pizza Delivery. 
Consider ca prin realizarea acestui proiect am reusit sa consolidez cunostinte de baza legate de programarea orientata pe obiecte si sa imi formez o baza solida de la care sa plec pentru proiectele viitoare.

Bibliografie:

Cursuri POO 

Seminarii POO

Laboratoare POO

Github Mariu Micluta


Student care a realizat lucrarea : Frincu Paul-Octavian

Prof. coordonator: Camelia Obreja

