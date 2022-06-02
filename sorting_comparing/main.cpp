#include <iostream>
using namespace std;

void input_A(int* A, int* B, int N);
void restore_A(int* A, int* B, int N);
void selection_sort(int* A, int N);

int find_ref_key(int* A, int i, int j);
int partition(int* A, int i, int j, int key);
void quick_sort(int* A, int i, int j);

int main()
{
	const unsigned int N = 50000;
	int A[50000];
	int B[50000];
	float average = 0;

	clock_t  begt, endt;

	input_A(A, B, N);
	cout << "selection sorting" << endl;

	for (int i = 0; i < 5; i++)
	{
		begt = clock();
		selection_sort(A, N);
		endt = clock();
		printf("time=%d\n", endt - begt);
		average += endt - begt;
		restore_A(A, B, N);
	}
	printf("average time=%f\n", average/5);

	cout << "\nquick sorting" << endl;

	for (int i = 0; i < 5; i++)
	{
		begt = clock();
		quick_sort(A, 0, N - 1);
		endt = clock();
		printf("time=%d\n", endt - begt);
		average += endt - begt;
		restore_A(A, B, N);
	}
	printf("average time=%f\n", average / 5);
}

void input_A(int* A, int* B, int N)
{
	for (int i = 0; i < N; i++)
		A[i] = B[i] = rand() % 10 - 5;
}

void restore_A(int* A, int* B, int N) 
{
	for (int i = 0; i < N; i++)
		A[i] = B[i];
}

void selection_sort(int* A, int N)
{
	int lowkey, lowindex;

	for (int i = 0; i < N - 1; i++)
	{
		lowindex = i;
		lowkey = A[i];
		for (int j = i + 1; j < N; j++)
		{
			if (A[j] < lowkey)
			{
				lowindex = j;
				lowkey = A[j];
			}
		}
		swap(A[i], A[lowindex]);
	}
}

int find_ref_key(int* A, int i, int j)
{
	int first_key = A[i];

	for (int k = i + 1; k <= j; k++)
	{
		if (A[k] > first_key)
			return k;
		else if (A[k] < first_key)
			return i;
	}
	return -1;
}

int partition(int* A, int i, int j, int key)
{
	int left = i, right = j;

	do
	{
		swap(A[left], A[right]);
		if (A[left]  < key)
		{
			left++;
		}
		else if (A[right]  >= key)
		{
			right--;
		}
	} while (left <= right);
	return left;
}

void quick_sort(int* A, int i, int j)
{
	int k, ref_key, ref_key_index;

	ref_key_index = find_ref_key(A, i, j);
	if (ref_key_index != -1)
	{
		ref_key = A[ref_key_index] ;
		k = partition(A, i, j, ref_key);
		quick_sort(A, i, k - 1);
		quick_sort(A, k, j);
	}
}