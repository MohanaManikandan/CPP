#ifndef __MERGE_SORT__
#define __MERGE_SORT__

#include<vector>

template <typename Object>
void merge_sort(std::vector<Object>&);

template <typename Object>
void merge_sort(std::vector<Object>&, std::vector<Object>&, int left, int right);

template <typename Object>
void merge(std::vector<Object>&, int left_pos, int right_pos, int right_end);

#include "MergeSort.tpp"

#endif