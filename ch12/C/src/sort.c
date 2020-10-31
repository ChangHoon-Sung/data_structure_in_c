int temp[100000];

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

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
            swap(&arr[min_idx], &arr[i]);
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

void bubble_sort(int arr[], int len) {
    int temp;

    for (int i = len - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void inc_insertion_sort(int arr[], int first, int last, int gap) {
    int key, j;
    for (int i = first + gap; i <= last; i += gap) {
        key = arr[i];
        for (j = i - gap; j >= first && key < arr[j]; j -= gap) {
            arr[j + gap] = arr[j];
        }
        arr[j + gap] = key;
    }
}

void shell_sort(int arr[], int len) {
    for (int gap = len / 2; gap > 0; gap /= 2) {
        if (gap % 2 == 0) gap++;
        for (int i = 0; i < gap; i++) {
            inc_insertion_sort(arr, i, len - 1, gap);
        }
    }
}

void merge(int arr[], int left, int mid, int right) {
    int idx = 0, left_idx = left, right_idx = mid + 1;

    while (left_idx <= mid && right_idx <= right) {
        if (arr[left_idx] <= arr[right_idx]) {
            temp[idx++] = arr[left_idx++];
        } else {
            temp[idx++] = arr[right_idx++];
        }
    }

    if (left_idx <= mid) {
        while (left_idx <= mid) {
            temp[idx++] = arr[left_idx++];
        }
    } else {
        while (right_idx <= right) {
            temp[idx++] = arr[right_idx++];
        }
    }

    for (int i = left; i <= right; i++) {
        arr[i] = temp[i - left];
    }
}

void merge_sort(int arr[], int left, int right) {
    int mid;

    if (left == right) return;
    if (left < right) {
        mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}