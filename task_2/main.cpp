#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

/*
    This function resizes A so that it has a buffer
    big enough to fit the whole B vector
*/
void merge_sorted(vector<int>& A, vector<int>& B)
{
    int A_size_prev = A.size();

    /* Resize A so that it has a buffer that fits B */
    A.resize(A.size() + B.size());

    int i = A.size() - 1;
    int a = A_size_prev - 1;
    int b = B.size() - 1;

    /* Merge sorted vectors "in place" */
    while (a >= 0 && b >= 0)
    {
        if (A[a] > B[b])
        {
            A[i] = A[a];
            --a;
        }
        else
        {
            A[i] = B[b];
            --b;
        }
        --i;
    }

    /* Add the remanining items from B */
    while (b >= 0)
    {
        A[i] = B[b];
        --b;
        --i;
    }
}

void print_vec(const vector<int>& vec)
{
    for (int i : vec)
        std::cout << i << " ";
    std::cout << "\n"; 
}

void assert_vectors(const vector<int>& vec, const vector<int>& expected)
{
    assert(vec.size() == expected.size());
    for (size_t i = 0; i < vec.size(); ++i)
        assert(vec[i] == expected[i]);
    std::cout << "Test passed!\n";
}

int main()
{   
    /* Test 1 */
    vector<int> A = { 1, 3, 5, 7, 9, 11, 13, 15 };
    vector<int> B = { 2, 4, 6, 8 };
    vector<int> result = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13, 15 };
    merge_sorted(A, B);
    assert_vectors(A, result);

    /* Test 2 */
    A = { 3, 3, 3, 3, 3, 3, 3, 3 };
    B = { 1, 1, 1, 1 };
    result = { 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3 };
    merge_sorted(A, B);
    assert_vectors(A, result);

    /* Test 3 */
    A = { 1, 1, 1, 2, 3 };
    B = { 1, 4, 4, 4, 4, 100 };
    result = { 1, 1, 1, 1, 2, 3, 4, 4, 4, 4, 100};
    merge_sorted(A, B);
    assert_vectors(A, result);

    /* Test 4 */
    A = { 1, 1, 1, 2, 3 };
    B = { };
    result = { 1, 1, 1, 2, 3 };
    merge_sorted(A, B);
    assert_vectors(A, result);

    /* Test 5 */
    A = { };
    B = { 1, 2, 3 };
    result = { 1, 2, 3 };
    merge_sorted(A, B);
    assert_vectors(A, result);

    /* Test 6 */
    A = { };
    B = { };
    result = { };
    merge_sorted(A, B);
    assert_vectors(A, result);

    /* Test 7 */
    A = { 100, 100, 100, 100 };
    B = { 101, 101, 101, 101 };
    result = { 100, 100, 100, 100, 101, 101, 101, 101 };
    merge_sorted(A, B);
    assert_vectors(A, result);

    return 0;
}
