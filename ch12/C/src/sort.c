void selection_sort(int arr[], int len) {
    int min_idx, tmp;

    for (int i = 0; i < len - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[min_idx] > arr[j]) {
                min_idx = j;
            }
        }
        if (i != min_idx) {
        tmp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = tmp;
    }
}
}

void insertion_sort(int arr[], int len) {
    int key, j;
    for (int i = 1; i < len; i++) {
        key = arr[i];
        for (j = i - 1; arr[j] > key && j >= 0; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

