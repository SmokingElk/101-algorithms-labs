#include <bits/stdc++.h>


#pragma region QuickSort with Median of medians
void Medians(std::vector<int>& e, int st, int end);
void QuickSort(std::vector<int>& e, int st, int end, int pivot);
int kOrdStat(std::vector<int>& e, int st, int end, int k);
int QuickSort2(std::vector<int>& e, int st, int end);

void QuickSort(std::vector<int>& e, int st, int end, int pivot)
{
    if (st >= end)
    {
        return;
    }
    int i = st;
    int j = end;
    while (i <= j)
    {
        while (e[i] < pivot)
        {
            i++;
        }
        while (e[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            std::swap(e[i], e[j]);
            i++;
            j--;
        }
    }

    Medians(e, st, j);
    Medians(e, i, end);
}

int QuickSort2(std::vector<int>& e, int st, int end)
{
    int i = st;
    int j = end;
    int pivot = e[end];
    while (i <= j)
    {
        while (e[i] < pivot)
        {
            i++;
        }
        while (e[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            std::swap(e[i], e[j]);
            i++;
            j--;
        }
    }

    return j;
}

int kOrdStat(std::vector<int>& e, int st, int end, int k)
{
    if (k > end - st)
    {
        return e[st];
    }
    int pat;
    while (st < end)
    {
        pat = QuickSort2(e, st, end);
        if(pat == k)
        {
            return e[pat];
        }
        else if (pat > k)
        {
            end = pat - 1;

        }
        else if (pat < k)
        {
            st = pat + 1;
        }
    }
    if (st == end)
    {
        return e[st];
    }

    return -1;
}

void Medians(std::vector<int>& e, int st, int end)
{
    if (st >= end)
    {
        return;
    }
    std::vector<int> medians;
    int leftInd = st - 5;
    int rightInd = st - 1;
    while (rightInd < end)
    {
        if (leftInd + 5 < end)
        {
            leftInd += 5;
        }
        if (rightInd + 5 > end)
        {
            rightInd = end;
        }
        else
        {
            rightInd += 5;
        }
        medians.push_back(kOrdStat(e, leftInd, rightInd, 2 + leftInd));
    }

    int MedianOfmedians = kOrdStat(medians, 0, medians.size() - 1, medians.size() / 2);
    QuickSort(e, st, end, MedianOfmedians);
}
#pragma endregion


int main() {
    srand(time(0));

    std::vector<int> testArray;

    int arraySize = 20;
    for (int i = 0; i < arraySize; ++i) {
        testArray.push_back(rand() % 100);
    }

    std::cout << "Исходный массив:\n";
    for (int num : testArray) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    Medians(testArray, 0, testArray.size() - 1);

    std::cout << "Отсортированный массив:\n";
    for (int num : testArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}
