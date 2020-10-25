from ch12.selection import selection_sort
from random import randint
import pytest


@pytest.fixture
def unordered():
    return [randint(1, 1000) for _ in range(10000)]


def test_selection(unordered):
    ordered = selection_sort(unordered)
    assert sorted(unordered) == ordered