def selection_sort(unordered):
    ordered = unordered[:]
    e = len(ordered)

    for i in range(e - 1):
        # 슬라이싱한 리스트는 시작점이 바뀐다. 명심!
        min_idx = ordered[i:].index(min(ordered[i + 1 :])) + i
        if ordered[i] > ordered[min_idx]:
            ordered[i], ordered[min_idx] = ordered[min_idx], ordered[i]

    return ordered
