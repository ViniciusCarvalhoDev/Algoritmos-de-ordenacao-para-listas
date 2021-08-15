#include <iostream>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "../../../../Desktop/tp/include/Fila.hpp"
#include "../../../../Desktop/tp/src/Linha.cpp"

//função que compara strings

bool compara(std::string n1, std::string n2) {

    int tamanho;

    if (n1.size() < n2.size() == true)
        tamanho = n1.size();
    else
        tamanho = n2.size();

    for (int i = 0; i < tamanho; i++)
    {
        if (n1[i] != n2[i] == true)
            return n1[i] < n2[i];
    }

    if (n2.size() > n1.size() == true)
        return true;

    return false;
}

//--- quickSort

void trocar(int i, int j, Fila<Linha> *lista)
{
    Celula<Linha>* item1 = lista->RecuperaPonteiro(i);
    Celula<Linha>* item2 = lista->RecuperaPonteiro(j);

    std::string aux = "";
    int aux2;

    aux = item1->dado.nome;
    aux2 = item1->dado.dados;

    item1->dado.nome = item2->dado.nome;
    item1->dado.dados = item2->dado.dados;

    item2->dado.nome = aux;
    item2->dado.dados = aux2;
}

void trocarInt(int i, int j, Fila<Linha>* lista)
{
    Celula<Linha>* item1 = lista->RecuperaPonteiro(i);
    Celula<Linha>* item2 = lista->RecuperaPonteiro(j);

    int aux;
    std::string aux2;

    aux = item1->dado.dados;
    aux2 = item1->dado.nome;

    item1->dado.dados = item2->dado.dados;
    item1->dado.nome = item2->dado.nome;

    item2->dado.dados = aux;
    item2->dado.nome = aux2;
}

int partition(Fila<Linha> *lista, int low, int high)
{
    std::string pivot = lista->RecuperaPonteiro(high)->dado.nome; 
    int i = (low - 1);  

    for (int j = low; j <= high - 1; j++)
    {
        Linha aux = lista->RecuperaPonteiro(j)->dado;
        if (compara(aux.nome, pivot) == true)
        {
            i++;    
            trocar(i,j, lista);
        }
    }
    trocar(i + 1,high,lista);
    return (i + 1);
}


void quickSort(Fila<Linha> *lista, int low, int high)
{
    if (low < high)
    {
        
        int pi = partition(lista, low, high);

        quickSort(lista, low, pi - 1);
        quickSort(lista, pi + 1, high);
    }
}

void merge(Fila<Linha>* lista, int const left, int const mid, int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    Fila<std::string> lista1;
    Fila<int> lista1Int;

    Fila<std::string> lista2;
    Fila<int> lista2Int;

    for (auto i = 0; i < subArrayOne; i++) {
        lista1.Enfileirar(lista->RecuperaPonteiro(left + i)->dado.nome);
        lista1Int.Enfileirar(lista->RecuperaPonteiro(left + i)->dado.dados);
    }
    for (auto j = 0; j < subArrayTwo; j++){
        lista2.Enfileirar(lista->RecuperaPonteiro(mid + 1 + j)->dado.nome);
        lista2Int.Enfileirar(lista->RecuperaPonteiro(mid + 1 +j)->dado.dados);
    }

    auto indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0; 
    int indexOfMergedArray = left; 


    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (compara(lista1.Recupera(indexOfSubArrayOne), lista2.Recupera(indexOfSubArrayTwo)) == true) {
            lista->RecuperaPonteiro(indexOfMergedArray)->dado.nome = lista1.Recupera(indexOfSubArrayOne);
            lista->RecuperaPonteiro(indexOfMergedArray)->dado.dados = lista1Int.Recupera(indexOfSubArrayOne);
            indexOfSubArrayOne++;
        }
        else {
            lista->RecuperaPonteiro(indexOfMergedArray)->dado.nome = lista2.Recupera(indexOfSubArrayTwo);
            lista->RecuperaPonteiro(indexOfMergedArray)->dado.dados = lista2Int.Recupera(indexOfSubArrayTwo);
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        lista->RecuperaPonteiro(indexOfMergedArray)->dado.nome = lista1.Recupera(indexOfSubArrayOne);
        lista->RecuperaPonteiro(indexOfMergedArray)->dado.dados = lista1Int.Recupera(indexOfSubArrayOne);
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        lista->RecuperaPonteiro(indexOfMergedArray)->dado.nome = lista2.Recupera(indexOfSubArrayTwo);
        lista->RecuperaPonteiro(indexOfMergedArray)->dado.dados = lista2Int.Recupera(indexOfSubArrayTwo);
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(Fila<Linha>* lista, int const begin, int const end)
{
    if (begin >= end) {
        return;
    }
    auto mid = begin + (end - begin) / 2;
    mergeSort(lista, begin, mid);
    mergeSort(lista, mid + 1, end);
    merge(lista, begin, mid, end);
}

//merge sort fim

//heapSort

void heapify(Fila<Linha>* lista, int n, int i)
{
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 

    if (l < n && lista->RecuperaPonteiro(l)->dado.dados > lista->RecuperaPonteiro(largest)->dado.dados)
        largest = l;

    if (r < n && lista->RecuperaPonteiro(r)->dado.dados > lista->RecuperaPonteiro(largest)->dado.dados)
        largest = r;

    if (largest != i) {
        trocarInt(i, largest,lista);
        heapify(lista, n, largest);
    }
}


void heapSort(Fila<Linha> *lista, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(lista, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        trocarInt(0,i, lista);

        heapify(lista, i, 0);
    }
}

//heapSort fim

//hadix 

int getMax(Fila<Linha>* lista, int n)
{
    int mx = lista->RecuperaPonteiro(0)->dado.dados;
    for (int i = 1; i < n; i++)
        if (lista->RecuperaPonteiro(i)->dado.dados > mx)
            mx = lista->RecuperaPonteiro(i)->dado.dados;
    return mx;
}


void countSort(Fila<Linha>* lista, int n, int exp)
{
    int *output = new int[n];
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++)
        count[(lista->RecuperaPonteiro(i)->dado.dados / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(lista->RecuperaPonteiro(i)->dado.dados / exp) % 10] - 1] = lista->RecuperaPonteiro(i)->dado.dados;
        count[(lista->RecuperaPonteiro(i)->dado.dados / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        lista->RecuperaPonteiro(i)->dado.dados = output[i];
}

// Radix Sort
void radixsort(Fila<Linha>* lista, int n)
{
    int m = getMax(lista, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(lista, n, exp);
}


int main()
{
    std::string n1 = "Lily";
    std::string n2 = "Leana";
    std::string n3 = "Rosetta";
    std::string n4 = "Floy";
    std::string n5 = "Eve";
    std::string n6 = "Norah";
    std::string n7 = "Walter";
    std::string n8 = "Jennie";
    std::string n9 = "Leone";
    std::string n10 = "Carlotta";

    int n11 = std::stoi("01100100");
    int n21 = std::stoi("10011100");
    int n31 = std::stoi("00000000");
    int n41 = std::stoi("01011100");
    int n51 = std::stoi("01000010");
    int n61 = std::stoi("11001101");
    int n71 = std::stoi("01001000");
    int n81 = std::stoi("11011111");
    int n91 = std::stoi("00101110");
    int n101 = std::stoi("11101001");

    Fila<std::string> listaNomes;
    Fila<int> listaInteiros;

    Fila<Linha> linhas;

    listaNomes.Enfileirar(n1);
    listaNomes.Enfileirar(n2);
    listaNomes.Enfileirar(n3);
    listaNomes.Enfileirar(n4);
    listaNomes.Enfileirar(n5);
    listaNomes.Enfileirar(n6);
    listaNomes.Enfileirar(n7);
    listaNomes.Enfileirar(n8);
    listaNomes.Enfileirar(n9);
    listaNomes.Enfileirar(n10);

    listaInteiros.Enfileirar(n11);
    listaInteiros.Enfileirar(n21);
    listaInteiros.Enfileirar(n31);
    listaInteiros.Enfileirar(n41);
    listaInteiros.Enfileirar(n51);
    listaInteiros.Enfileirar(n61);
    listaInteiros.Enfileirar(n71);
    listaInteiros.Enfileirar(n81);
    listaInteiros.Enfileirar(n91);
    listaInteiros.Enfileirar(n101);


    for (int i = 0; i < listaInteiros.Tamanho(); i++)
    {
        Linha aux = Linha(listaNomes.Recupera(i), listaInteiros.Recupera(i));
        linhas.Enfileirar(aux);
    }

    //radixsort(&linhas, listaNomes.Tamanho());
    heapSort(&linhas, 10);
    mergeSort(&linhas, 0, listaNomes.Tamanho()-1);
    
    //radixsort(&linhas, listaNomes.Tamanho());
    //quickSort(&linhas,0,listaNomes.Tamanho()-1);

    //linhas.Imprimir();

    for (int i = 0; i < linhas.Tamanho(); i++)
    {
        Linha dados = linhas.RecuperaPonteiro(i)->dado;
        std::cout << dados.nome << " " << dados.dados << std::endl;
    }

    return 0;
}

