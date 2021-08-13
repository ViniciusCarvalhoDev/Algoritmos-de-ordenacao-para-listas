#include <iostream>
#include "../../../../Desktop/tp/include/Fila.hpp"

//função que compara strings

std::string compara(std::string n1, std::string n2) {
    int aux = -1;

    if (n1.length() > n2.length()) {
        for (int i = 0; i < n2.length(); i++)
        {
            if (n2[i] != n1[i])
            {
                if (n2[i] < n1[i]) {
                    aux = 2;
                }
                else {
                    aux = 1;
                }
                break;
            }
        }
    }
    else if (n2.length() > n1.length()) {
        for (int i = 0; i < n1.length(); i++)
        {
            if (n1[i] != n2[i])
            {
                if (n1[i] < n2[i])
                {
                    aux = 1;
                }
                else {
                    aux = 2;
                }
                break;
            }
        }
    }
    else {
        for (int i = 0; i < n1.length(); i++)
        {
            if (n1[i] != n2[i])
            {
                if (n1[i] < n2[i])
                {
                    aux = 1;
                }
                else {
                    aux = 2;
                }

            }
            else {
                aux = 0;
            }
        }
    }

    if (aux == 1)
    {
        return "A primeira vem antes";
    }
    else if (aux == 2) {
        return "A segunda vem antes";
    }
    else if (aux == 0)
    {
        return "Sao iguais";
    }
    else
    {
        if (n1.length() > n2.length())
        {
            return "A segunda vem antes";
        }
        else {
            return "A primeira vem antes";
        }
    }
}

//--- quickSort

void mergeSort(Fila<std::string> lista, int inicio, int fim) {

    if (inicio >= fim)
    {
        return;
    }
}

void swap(int i, int j, Fila<std::string> *lista)
{
    Celula<std::string>* item1 = lista->RecuperaPonteiro(i);
    Celula<std::string>* item2 = lista->RecuperaPonteiro(j);
    std::string aux = "";

    aux = item1->dado;
    item1->dado = item2->dado;
    item2->dado = aux;
}

int partition(Fila<std::string> *lista, int low, int high)
{
    std::string pivot = lista->Recupera(high); 
    int i = (low - 1);  

    for (int j = low; j <= high - 1; j++)
    {
        
        if (compara(lista->Recupera(j), pivot) == "A primeira vem antes")
        {
            i++;    
            swap(i,j, lista);
        }
    }
    swap(i + 1,high,lista);
    return (i + 1);
}


void quickSort(Fila<std::string> *lista, int low, int high)
{
    if (low < high)
    {
        
        int pi = partition(lista, low, high);

        quickSort(lista, low, pi - 1);
        quickSort(lista, pi + 1, high);
    }
}

//--- quickSort fim

//void Juntar(Fila<std::string>* lista, int ini, int meio, int fim, Fila<std::string>* aux) {
//    int esq = ini;
//    int dir = meio;
//
//    for (int i = ini; i < fim; ++i) {
//        if ((esq < meio) and ((dir >= fim) or (lista->Recupera(esq) < lista->Recupera(dir)))) {
//            aux->RecuperaPonteiro(i)->dado = lista->RecuperaPonteiro(esq)->dado;
//            ++esq;
//        }
//        else {
//            aux->RecuperaPonteiro(i)->dado = lista->RecuperaPonteiro(esq)->dado;
//            ++dir;
//        }
//    }
//    //copiando o vetor de volta
//    for (int i = ini; i < fim; ++i) {
//        lista->RecuperaPonteiro(i)->dado = aux->RecuperaPonteiro(i)->dado;
//    }
//}
//
//void MergeSort(Fila<std::string>* lista, int inicio, int fim, Fila<std::string>* aux) {
//    if ((fim - inicio) < 2) return;
//
//    int meio = ((inicio + fim) / 2);
//    MergeSort(lista, inicio, meio, aux);
//    MergeSort(lista, meio, fim, aux);
//    Juntar(lista, inicio, meio, fim, aux);
//}

void merge(Fila<std::string>* lista, int const left, int const mid, int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    Fila<std::string> lista1;
    Fila<std::string> lista2;

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        lista1.Enfileirar(lista->Recupera(left + i));
    for (auto j = 0; j < subArrayTwo; j++)
        lista2.Enfileirar(lista->Recupera(mid + 1 + j));

    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (compara(lista1.Recupera(indexOfSubArrayOne), lista2.Recupera(indexOfSubArrayTwo)) == "A primeira vem antes") {
            lista->RecuperaPonteiro(indexOfMergedArray)->dado = lista1.Recupera(indexOfSubArrayOne);
            indexOfSubArrayOne++;
        }
        else {
            lista->RecuperaPonteiro(indexOfMergedArray)->dado = lista2.Recupera(indexOfSubArrayTwo);
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        lista->RecuperaPonteiro(indexOfMergedArray)->dado = lista1.Recupera(indexOfSubArrayOne);
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        lista->RecuperaPonteiro(indexOfMergedArray)->dado = lista2.Recupera(indexOfSubArrayTwo);
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(Fila<std::string>* lista, int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursivly

    auto mid = begin + (end - begin) / 2;
    mergeSort(lista, begin, mid);
    mergeSort(lista, mid + 1, end);
    merge(lista, begin, mid, end);
}

int main()
{
    std::string n1 = "Lily 01100100";
    std::string n2 = "Leana 10011100";
    std::string n3 = "Rosetta 00000000";
    std::string n4 = "Floy 01011100";
    std::string n5 = "Eve 01000010";
    std::string n6 = "Norah 11001101";
    std::string n7 = "Walter 01001000";
    std::string n8 = "Jennie 11011111";
    std::string n9 = "Leone 00101110";
    std::string n10 = "Carlotta 11101001";

    Celula<std::string>* itemAtual = nullptr;
    

    Fila<std::string> lista;
    Fila<std::string> listaaux;

    lista.Enfileirar(n1);
    lista.Enfileirar(n2);
    lista.Enfileirar(n3);
    lista.Enfileirar(n4);
    lista.Enfileirar(n5);
    lista.Enfileirar(n6);
    lista.Enfileirar(n7);
    lista.Enfileirar(n8);
    lista.Enfileirar(n9);
    lista.Enfileirar(n10);

    //quickSort(&lista,0,9);
    mergeSort(&lista, 0, lista.Tamanho()-1);
    lista.Imprimir();


    return 0;
}

