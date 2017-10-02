#ifndef MERGESORT_H
#define MERGESORT_H

//mergesort sorting algorithm implementation
//properties:
//time complexity: O(NlogN) there are logN merge and each merge requires N comparison
//space complexity: O(N) an extra array with the input size is needed
//stability: the algorithm is stable if the merge is implemented as stable
//time and space performance are independent from the input


//basic merge implementation
template <typename Item>
void merge(Item arr[], Item aux[], int l, int m, int r) {
  
  //fill the auxiliary array
  for (int i = l; i <= r; ++i) aux[i] = arr[i];

  int j = l;
  int k = m + 1;
  
  //merge into the original array
  for (int i = l; i <= r; ++i) {
    if (j > m) arr[i] = aux[k++];
    else if (k > r) arr[i] = aux[j++];
    else arr[i] = (aux[j] <= aux[k]) ? aux[j++] : aux[k++];
  }
}

//basic mergesort implementation
template <typename Item>
void mergesort(Item arr[], Item aux[], int l, int r) {
  if (r <= l) return;
  int m = (r + l) / 2;
  mergesort(arr, aux, l, m);
  mergesort(arr, aux, m + 1, r);
  merge(arr, aux, l, m, r);
}

//bitonic merge implementation: the second half of the auxiliary
//array is filled in bitonic order
template <typename Item>
void bitonicMerge(Item arr[], Item aux[], int l, int m, int r) {
  int i, j;
  //fill first half in order
  for (i = 0; i <= m; i++) aux[i] = arr[i];
  //fill second half in bitonic order
  for (j = m+1; j <= r; ++j) aux[j] = arr[r+m+1-j];
  //set index back;
  i = 0;
  j = r;
  for (int k = l; k <= r; ++k) arr[k] = (aux[i] <= aux[j]) ? aux[i++] : aux[j--];

}

//wrapper function for auxiliary array
template <typename Item>
void mergesort(Item arr[], int l, int r) {
  Item* aux = new Item [r - l + 1];
  mergesort(arr, aux, l, r);
  delete[] aux;
}

//iterative mergesort implementation
template <typename Item>
void mergesortIt(Item arr[], Item aux[], int l, int r) {
  
  //step through subarrays size 
  for (int size = 1; size <= (r-l); size *=2) {
    //step through subarrays idx
    for (int left_idx = l; left_idx <= (r-size); left_idx += size*2) {
      int m = left_idx + size - 1;  //NOT (left_idx + right_idx) / 2;
      int right_idx = left_idx + (size*2) - 1;
      merge(arr, aux, left_idx, m, (right_idx < r) ? right_idx : r);
    }
  }
}


#endif
