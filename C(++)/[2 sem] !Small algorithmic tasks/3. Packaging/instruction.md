# Packaging laboratory

## ENGLISH (Polish version below)

There are n packages with corresponding payments P and weights W.
You get Pi złotych if you deliver an i-th item.
The weight of the i-th item is Wi.
The mass of items cannot exceed C.
Choose some packages and pack a car optimally.

Additional informations:

- Maximum numeber of items: 15.
- The smallest element in P and W: 0
- The largest element in P and W: 1000
- The number of instances (cars to pack, the number of iterations of the main for loop): 500.

### Input

In next lines (four lines represent one car):

A number of items n.

Payments of items P.

Weights of items W.

The maximum mass of a car C.

### Output

In next lines:
The optimal profit.

### Example

**Input**

```
5
588 40 307 367 206
211 30 974 943 622
1766
1
596
997
550
```

**Output**

```
995
0
```

## POLSKI

Twoim zadaniem jest zapakowanie samochodu. Masz do wyboru n przedmiotów
Za przewóz i-tego przedmiotu możesz uzyskać Pi złotych (i=1,2,..,n).
Waga i-tego przedmiotu wynosi Wi (i=1,2,..,n).
Masa towaru w samochodzie nie może przekroczyć wartości C.
Upakuj samochód optymalnie, tj. tak by suma wag nie przekroczyła C oraz suma złotych była największa.

Dodatkowe informacje:

- Maksymalna ilość przedmiotów: 15.
- Minimalny element w P i W: 0
- Maksymalny element (największa wartość) w P i W: 1000
- Liczba testów: 1.
- Ilość zapytań (liczba iteracji głównej pętli): 500.
- Próba wstawienia wyniku - brak zaliczonego przedmiotu.

### Wejście

W kolejnych liniach (jeden samochód jest reprezentowany przez 4 kolejne linie).

Ilość przedmiotów.

Wypłaty za przedmiot.

Wagi przedmiotów.

Ładowność wozu.

### Wyjście

W kolejnych liniach.
Optymalny profit.

### Przykład

**Wejście**

```
5
588 40 307 367 206
211 30 974 943 622
1766
1
596
997
550
```

**Wyjście**

```
995
0
```