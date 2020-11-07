int seq_search(int arr[], int len, int key) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

int seq_search2(int arr[], int len, int key) {
    int i;
    arr[len] = key;
    for (i = 0; arr[i] != key; i++)
        ;
    if (i == len)
        return -1;
    else
        return i;
}

int binary_search(int arr[], int len, int key) {
    int s = 0, e = len, m;

    while (s <= e) {
        m = (s + e) / 2;
        if (arr[m] > key) {
            e = m - 1;
        } else if (arr[m] < key) {
            s = m + 1;
        } else {
            return m;
        }
    }

    return -1;
}