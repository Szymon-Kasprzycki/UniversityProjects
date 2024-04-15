# Graph cycles laboratory

## ENGLISH (Polish version below)

Is a graph denoted by the [adjacency matrix](https://en.wikipedia.org/wiki/Adjacency_matrix) a [cycle graph](https://en.wikipedia.org/wiki/Cycle_graph)?

### Input

In the first line: a number of next lines.

In a line (expect the first): a number of vertices and after space an adjacency matrix written from the left to the right and from the top to the bottom.

### Output

1 if a graph is a cycle, else 0.

### Example

**Input**
5
3 011101110
7 0110000101000011000000000101000101000001010001010
7 0100001101000001010000010100000101000001011000010
5 0101010000000011000000100
5 0100110010000110110010100

**Output**
1
0
1
0
1

## POLSKI

Zbadaj, czy graf przedstawiony za pomocą macierzy sąsiedztwa jest cyklem.

### Wejście

W pierwszej linii ilość grafów do sprawdzenia.
W kolejnych liniach macierz sąsiedztwa wypisana od lewej do prawej z góry na dół.

### Wyjście

W kolejnych liniach 1, jeśli graf jest cyklem lub 0 w przeciwnym przypadku.

### Przykład

**Wejście**
5
3 011101110
7 0110000101000011000000000101000101000001010001010
7 0100001101000001010000010100000101000001011000010
5 0101010000000011000000100
5 0100110010000110110010100

**Wyjście**
1
0
1
0
1