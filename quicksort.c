#include <stdio.h>

static inline void swap_el(int array[], int a_ind, int b_ind)
{
        int tmp;

        tmp = array[a_ind];
        array[a_ind] = array[b_ind];
        array[b_ind] = tmp;
}

static int partition_Hoare(int array[], int l, int r)
{
        int pivot = array[l];
        int i = l - 1;
        int j = r + 1;

        while (1) {
                do {
                        i++;
                } while (array[i] < pivot);

                do {
                        j--;
                } while (array[j] > pivot);

                if (i >= j)
                        return j;

                swap_el(array, i, j);
        }
}

static void quicksort_Hoare(int array[], int l, int r)
{
        int div;

        if (l < r) {
                div = partition_Hoare(array, l, r);
                quicksort_Hoare(array, l, div);
                quicksort_Hoare(array, div + 1, r);
        }



}


int main(void)
{
        int arr[1000] = {3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 12398,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 12347,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 2947,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         322347 ,34234, 2, 324, 768, 98, 98, 8, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 134, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 453287, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 2, 1, 9, 5, 4, 1239847,
                         3, 7, 8, 5, 43287, 1, 9, 5, 4, 1239847};



        int i;

        quicksort_Hoare(arr, 0, 999);

        for (i = 0; i < 999; i++)
                printf("%d\n", arr[i]);

        return 0;
}
