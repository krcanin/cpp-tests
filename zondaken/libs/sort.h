#ifndef SORT_H
#define SORT_H

#pragma once

template<class T>
int default_compare(T x, T y) {
	return x - y;
}

template<class T>
void swap(T* i, T* j) {
	T t = *i;
	*i = *j;
	*j = t;
}

template<class T>
T* sub_array(T* A, unsigned int l, unsigned int r) {
	unsigned int n = r - l + 1;
	T* result = new T[n];

	unsigned int i = 0;

	while (l <= r) {
		result[i++] = A[l++];
	}
			
	return result;
}

/*
 * bubble_sort
 */
template<class T>
void bubble_sort(T* A, unsigned int l, unsigned int r, int(*compare)(T, T) = default_compare) {
	bool flag = true;
	unsigned i, j;

	i = r;

	while (i >= r && flag) {
		flag = false;

		for (j = l; j < i; ++j) {
			if (compare(A[j], A[j + 1]) > 0) {
				swap(&A[j], &A[j + 1]);
				flag = true;
			}
		}
	}
}

/*
 * selection_sort
 */
template<class T>
void selection_sort(T* A, unsigned int l, unsigned int r, int(*compare)(T, T) = default_compare) {
	unsigned int i, j;
	unsigned int min;

	for (i = l; i < r; ++i) {
		min = i;

		for (j = i + 1; j <= r; ++j) {
			if (compare(A[j], A[min]) < 0) {
				min = j;
			}
		}

		if (min > i) swap(&A[i], &A[min]);
	}
}

/*
 * insertion_sort
 */
template<class T>
void insertion_sort(T* A, unsigned int l, unsigned int r, int(*compare)(T, T) = default_compare) {
	unsigned int i, j;

	for (i = l; i < r; ++i) {
		j = i + 1;

		while (compare(A[j], A[j - 1]) < 0) {
			swap(&A[j], &A[j - 1]);
			--j;
		}
	}
}

/*
 * quick_sort
 * two-way partitioning
 */
template<class T>
unsigned int partition(T* A, unsigned int l, unsigned int r, int(*compare)(T, T) = default_compare) {
	/* two-way partitioning (USED HERE): https://www.youtube.com/watch?v=MZaf_9IZCrc */
	/* three-way partitioning: https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/ */
	unsigned int i, j;

	i = j = l;
	T& pivot = A[r];

	while (j < r) {
		if (compare(A[j], pivot) < 0) {
			swap(&A[i], &A[j]);
			++i;
		}

		++j;
	}

	swap(&A[i], &pivot);

	return i;
}

template<class T>
void quick_sort(T* A, unsigned int l, unsigned int r, int(*compare)(T, T) = default_compare) {
	if (l < r) {
		unsigned int pivot = partition(A, l, r, compare);
		if (pivot > 0) quick_sort(A, l, pivot - 1, compare);
		quick_sort(A, pivot + 1, r, compare);
	}
}

/*
 * heap_sort
 */
template<class T>
void max_heapify(T* A, unsigned int i, unsigned int n, int(*compare)(T, T) = default_compare) {
	unsigned int l = 2 * i + 1;
	unsigned int r = l + 1;

	if (i < n) {
		unsigned int max = 0;
		bool flag = false;

		if (l < n && r < n) {
			max = compare(A[l], A[r]) > 0 ? l : r;
			flag = true;
		} else if (l < n) {
			max = l;
			flag = true;
		} else if (r < n) {
			max = r;
			flag = true;
		}

		if (flag && compare(A[max], A[i]) > 0) {
			swap(&A[i], &A[max]);
			max_heapify(A, max, n, compare);
		}
	}
}

template<class T>
void build_max_heap(T* A, unsigned int l, unsigned int r, int(*compare)(T, T) = default_compare) {
	if (l == r) return;

	unsigned int n = r - l + 1;
	unsigned int i = l + (n / 2) - 1;

	bool flag = true;

	while (i >= l && flag) {
		max_heapify(A, i, n, compare);

		if (i == 0) {
			flag = false;
		} else {
			--i;
		}
	}
}

template<class T>
void heap_sort(T* A, unsigned int l, unsigned int r, int(*compare)(T, T) = default_compare) {
	/* calculate length */
	unsigned int n = r - l + 1;

	/* build max heap out of unordered array */
	build_max_heap(A, l, r, compare);

	/* switch max to the relative end and build the max heap out of the partial array */
	for (unsigned int i = r; i > l; --i) {
		swap(&A[0], &A[i]);
		max_heapify(A, 0, i, compare);
	}
}

/*
 * merge_sort
 */
template<class T>
T* merge(T* A, T* B, unsigned int l, unsigned int r, int(*compare)(T, T) = default_compare) {
	T* result = new T[l + r];

	unsigned int i, j, k;
	i = j = 0;
	k = 0;

	while (i < l && j < r) {
		if (compare(A[i], B[j]) < 0) {
			result[k++] = A[i++];
		} else {
			result[k++] = B[j++];
		}
	}

	while (i < l) {
		result[k++] = A[i++];
	}

	while (j < r) {
		result[k++] = B[j++];
	}

	delete[] A;
	delete[] B;

	return result;
}

template<class T>
T* merge_sort(T* A, unsigned int l, unsigned int r, int(*compare)(T, T) = default_compare) {
	unsigned int n = r - l + 1;

	if (n < 2) {
		return A;
	} else {
		// merge of merge-sorted l half and merge-sorted r half and return it
		unsigned int middle = n / 2;

		T* l_part = merge_sort(sub_array(A, l, middle - 1), 0, middle - l - 1);
		T* r_part = merge_sort(sub_array(A, middle, r), 0, r - middle);

		delete[] A;

		return merge(l_part, r_part, middle - l, 0, r - middle + 1, compare);
	}
}

#endif
