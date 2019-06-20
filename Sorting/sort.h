#pragma once
template<class type>
void heapSort(type* arr, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = i; j > 0;) {
			int k = (j - 1) / 2;
			if (arr[k] < arr[j]) {
				type tmp = arr[k];
				arr[k] = arr[j];
				arr[j] = tmp;
			}
			j = k;
		}
	}
	for (int i = size - 1; i > 0; i -= 1) {
		type tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;
		int j = 0;
		while (2 * j + 1 < i) {
			int left = 2 * j + 1;
			int right = 2 * j + 2;
			int max;
			if (right < i)
				max = arr[left] > arr[right] ? left : right;
			else
				max = left;
			if (arr[j] < arr[max]) {
				type tmp = arr[max];
				arr[max] = arr[j];
				arr[j] = tmp;
			}
			j = max;
		}
	}
}

template<class type>
void quickSort(type* arr, int left, int right) {
	if (left >= right)
		return;
	int l = left, r = right;
	type tmp = arr[l];
	bool flag = true;
	while (l != r) {
		if (flag) {
			while (r > l&&arr[r] >= tmp)
				r -= 1;
			if (r > l && !(arr[r] >= tmp)) {
				arr[l] = arr[r];
				flag = false;
			}
		}
		else {
			while (r > l&&arr[l] <= tmp)
				l += 1;
			if (r > l && !(arr[l] <= tmp)) {
				arr[r] = arr[l];
				flag = true;
			}
		}
	}
	arr[l] = tmp;
	quickSort(arr, left, l - 1);
	quickSort(arr, l + 1, right);
}

template<class type>
void quickSort(type* arr, int size) {
	quickSort(arr, 0, size - 1);
}

template<class type>
void mergeSort(type *arr, int left, int right) {
	if (left == right)
		return;
	int mid = (right + left) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);
	int i = left, j = mid + 1;
	type* tmp = new type[right - left + 1];
	int k = 0;
	while (i <= mid&&j <= right) {
		int& min = arr[i] < arr[j] ? i : j;
		tmp[k] = arr[min];
		k += 1;
		min += 1;
	}
	if (i <= mid)
		for (; i <= mid; ++i, ++k)
			tmp[k] = arr[i];
	else
		for (; j <= right; ++j, ++k)
			tmp[k] = arr[j];
	int l = left;
	for (int k = 0; k < right - left + 1; ++k) {
		arr[l] = tmp[k];
		++l;
	}
	delete[] tmp;
}

template<class type>
void mergeSort(type* arr, int size) {
	mergeSort(arr, 0, size - 1);
}

template<class type>
void shellSort(type* arr, int size) {
	int n = size / 2;
	while (n>0) {
		for (int i = 0; i < n; ++i) {
			int j = i + n;
			while (j < size) {
				type tmp = arr[j];
				int k = j - n;
				while (k >= 0) {
					if (tmp < arr[k]) {
						arr[k + n] = arr[k];
						k -= n;
					}
					else
						break;
				}
				arr[k + n] = tmp;
				j += n;
			}
		}
		n /= 2;
	}
}