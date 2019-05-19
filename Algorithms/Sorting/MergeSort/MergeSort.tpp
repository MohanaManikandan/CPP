#include "MergeSort.h"

template <typename Object>
void merge_sort(std::vector<Object> &array)
{
    std::vector<Object> temp(array.size());
    merge_sort(array, temp, 0, array.size() - 1);
}

template <typename Object>
void merge(std::vector<Object> &array, std::vector<Object> &temp, int left_pos, int right_pos, int right_end)
{
    int left_end = right_pos - 1;
    int total_elements = right_end - left_pos + 1;
    int temp_index = left_pos;

    while (left_pos <= left_end && right_pos <= right_end)
    {
        if (array[left_pos] <= array[right_pos])
        {
            temp[temp_index++] = std::move(array[left_pos++]);
        }
        else
        {
            temp[temp_index++] = std::move(array[right_pos++]);
        }
    }

    while (left_pos <= left_end)
    {
        temp[temp_index++] = std::move(array[left_pos++]);
    }

    while (right_pos <= right_end)
    {
        temp[temp_index++] = std::move(array[right_pos++]);
    }

    for(int i = 0; i < total_elements; ++i, right_end--)
    {
        array[right_end] = std::move(temp[right_end]);
    }
}

template <typename Object>
void merge_sort(std::vector<Object> &array, std::vector<Object> &temp, int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        merge_sort(array, temp, left, center);
        merge_sort(array, temp, center + 1, right);
        merge(array, temp, left, center + 1, right);
    }
}

