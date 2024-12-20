// 3SATBase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __3SATBASECONSOLE_C__
#define __3SATBASECONSOLE_C__

#include "3SATBaseConsole.hpp"

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <thread>

///* This function takes last element as pivot, places
//   the pivot element at its correct position in sorted
//	array, and places all smaller (smaller than pivot)
//   to left of pivot and all greater elements to right
//   of pivot */
/*
int MyQSort_partition(int arr_parm[], int low_parm, int high_parm)
{
	int pivot = arr_parm[high_parm];    // pivot
	int i = (low_parm - 1);  // Index of smaller element

	for (int j = low_parm; j <= high_parm - 1; j++)
	{
		// swap if current element is greater than pivot
		if (arr_parm[j] > pivot)
		{
			i++;    // increment index of smaller element
			int t = arr_parm[i];
			arr_parm[i] = arr_parm[j];
			arr_parm[j] = t;
		}
	}
	int t = arr_parm[i + 1];
	arr_parm[i+1] = arr_parm[high_parm];
	arr_parm[high_parm] = t;
	return (i + 1);
}
//*/

// https://www.geeksforgeeks.org/c-program-for-iterative-quick-sort/

// A utility function to swap two elements
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function is same in both iterative and recursive*/
int partition(int arr_parm[], int low_parm, int high_parm)
{
	int pivot = arr_parm[high_parm];    // pivot
	int i = (low_parm - 1);  // Index of smaller element

	for (int j = low_parm; j <= high_parm - 1; j++)
	{
		// swap if current element is greater than pivot
		if (arr_parm[j] > pivot)
		{
			i++;    // increment index of smaller element
			int t = arr_parm[i];
			arr_parm[i] = arr_parm[j];
			arr_parm[j] = t;
		}
	}
	int t = arr_parm[i + 1];
	arr_parm[i + 1] = arr_parm[high_parm];
	arr_parm[high_parm] = t;
	return (i + 1);
}

/* A[] --> Array to be sorted,
   l  --> Starting index,
   h  --> Ending index */
void MyQSort(int arr[], int l, int h)
{
	// Create an auxiliary stack
	int * stack = new int [h - l + 1];

	// initialize top of stack
	int top = -1;

	// push initial values of l and h to stack
	stack[++top] = l;
	stack[++top] = h;

	// Keep popping from stack while is not empty
	while (top >= 0) {
		// Pop h and l
		h = stack[top--];
		l = stack[top--];

		// Set pivot element at its correct position
		// in sorted array
		int p = partition(arr, l, h);

		// If there are elements on left side of pivot,
		// then push left side to stack
		if (p - 1 > l) {
			stack[++top] = l;
			stack[++top] = p - 1;
		}

		// If there are elements on right side of pivot,
		// then push right side to stack
		if (p + 1 < h) {
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}

	delete[] stack;
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
/*
void MyQSort(int arr [] , int low_parm, int high_parm)
{
	if (low_parm < high_parm)
	{
		int pi = MyQSort_partition(arr, low_parm, high_parm);

		// Separately sort elements before
		// partition and after partition
		MyQSort(arr , low_parm, pi - 1);
		MyQSort(arr , pi + 1, high_parm);
	}
}

//*/

/*
* 
* updateTF - update running tallies according to flipping of a bit specified by position.
*			Also update list of false-activated clauses.
* 
*	inputs:
*		me     : SATSolver data body
*		lit    : position of bit representing literal to flip
*		target : truth value of lit after flip
*
*	outputs:
*		updated SATSolver data body with new clause tally (cls_tly) values
*		updated SATSolver data body with new false activated (fls_act) list
* 
*/

void SATSolver_updateTF(SATSolver* me, int zpos, bool target) {

	if (target) {

		for (int i = 0; i < me->master->pos_map_szs[zpos]; i++) {
			int clause = me->master->pos_map[zpos][i];
			int old_val = me->cls_tly[clause];
			int new_val = old_val - 1;
			me->cls_tly[clause] = new_val;
		}
		for (int i = 0; i < me->master->neg_map_szs[zpos]; i++) {
			int clause = me->master->neg_map[zpos][i];
			int old_val = me->cls_tly[clause];
			int new_val = old_val + 1;
			me->cls_tly[clause] = new_val;
		}

	} 
	else {

		for (int i = 0; i < me->master->neg_map_szs[zpos]; i++) {
			int clause = me->master->neg_map[zpos][i];
			int old_val = me->cls_tly[clause];
			int new_val = old_val - 1;
			me->cls_tly[clause] = new_val;
		}
		for (int i = 0; i < me->master->pos_map_szs[zpos]; i++) {
			int clause = me->master->pos_map[zpos][i];
			int old_val = me->cls_tly[clause];
			int new_val = old_val + 1;
			me->cls_tly[clause] = new_val;
		}

	}
}

/*
* 
* add- add a number 2^pos_parm to Z
* 
*/

void SATSolver_add(SATSolver * me , int pos_parm) {

	// add 2^pos_parm to Z

	int pos = pos_parm < 0 ? -pos_parm : pos_parm;

	/*

	for (int i = 0; i < me->master->n + 1 - pos; i++) {

		// if carry, continue loop, if no carry, break
		if (me->Z[pos + i]) {
			me->Z[pos + i] = false;
			SATSolver_updateTF(me , pos + i, false);
		}
		else {
			me->Z[pos + i] = true;
			SATSolver_updateTF(me , pos + i, true);
			break;
		}
	}
	*/

	bool sign = me->Z[pos];

	me->Z[pos] = !sign;
	SATSolver_updateTF(me, pos, !sign);

	// zero out all lower bits of Z
	for (int j = 0; j < pos; j++)
		if (me->Z[j]) {
			me->Z[j] = false;
			SATSolver_updateTF(me, j, false);
		}
}

__int64 SATSolver_initializePowJump(SATSolver* me, int prev_pos) {

	// initialize return value

	__int64 max_jump = 0;

	// check if any clauses are satisfied and find jump powers corresponding to clauses

	for (int i = 0; i < me->master->k; i++) {
		__int64 temp_jump = me->master->powers[i];
		__int64 abs_temp_jump = temp_jump < 0 ? -temp_jump : temp_jump;
		__int64 abs_max_jump = max_jump < 0 ? -max_jump : max_jump;
		bool sign_match = (me->Z[abs_temp_jump - 1] && me->master->powers[i] > 0) || (!me->Z[abs_temp_jump - 1] && me->master->powers[i] < 0);
		if (sign_match && me->cls_tly[i] == 3 && abs_temp_jump > abs_max_jump && abs_temp_jump > prev_pos)	// prev_pos: this criterion is the de-exponentialization step
			max_jump = temp_jump;
	}

	return max_jump;

}

bool SATSolver_GreaterThan(bool* a, bool* b, int n) {

	int i;

	for (i = n - 1; i >= 0; i--)
		if (a[i] && !b[i])
			return true;
		else if (!a[i] && b[i])
			return false;

	return false;

}

bool SATSolver_isSat(SATSolver* me, bool* arr) {

	// main loop- until end condition

	__int64 count = 0;
	int prev_pos = 0;	// de-exponentializer variable
	bool zero_jump = false;
	bool* prev_Z;

	prev_Z = new bool[me->master->n];

	for (int i = 0; i < me->master->n; i++)
		prev_Z[i] = me->begin[i];

	int temp_pow_jump = SATSolver_initializePowJump(me, prev_pos);

	if (temp_pow_jump == 0) {
		delete[] prev_Z;
		return false;
	}

	// using prev_pos: de-exponentialize
	if (temp_pow_jump > 0)
		prev_pos = temp_pow_jump;
	else
		prev_pos = 0;

	me->pow_jump = temp_pow_jump < 0 ? -temp_pow_jump - 1 : temp_pow_jump - 1;

	SATSolver_add(me, me->pow_jump);

	count++;

	//if (count % (1 * 1048576) == 0) {

	if (true) {

		for (int i = 0; i <= me->master->n; i++)
			printf_s("%d", me->Z[i]);
		//printf_s(" jump: %d", me->pow_jump);
		printf_s(" jump: %d", temp_pow_jump);
		printf_s("\n");
	}

	while (!SATSolver_GreaterThan(me->Z, me->end, me->master->n) &&
		!SATSolver_GreaterThan(prev_Z, me->Z, me->master->n) ) {

		for (int i = 0; i < me->master->n; i++)
			prev_Z[i] = me->Z[i];

		temp_pow_jump = SATSolver_initializePowJump(me, prev_pos);

		if (temp_pow_jump == 0) {
			zero_jump = true;
			break;
		}

		// using prev_pos: de-exponentialize
		if (temp_pow_jump > 0)
			prev_pos = temp_pow_jump;
		else
			prev_pos = 0;

		me->pow_jump = temp_pow_jump < 0 ? -temp_pow_jump - 1: temp_pow_jump - 1;

		SATSolver_add(me, me->pow_jump);

		count++;

		//if (count % (1 * 1048576) == 0) {

		if (true) {

			for (int i = 0; i <= me->master->n; i++)
				printf_s("%d", me->Z[i]);
			//printf_s(" jump: %d", me->pow_jump);
			printf_s(" jump: %d", temp_pow_jump);
			printf_s("\n");
		}

	}

	printf_s("count: %d\n", count);

	if (zero_jump && (SATSolver_GreaterThan(me->Z, me->end, me->master->n) ||
		SATSolver_GreaterThan(prev_Z, me->Z, me->master->n))) {
		delete[] prev_Z;
		return false;
	}
	
	for (int i = 0; i < me->master->n; i++)
		arr[i] = me->Z[me->master->decoding[i]];

	delete[] prev_Z;

	return true;
}

bool * SATSolver_bool_pow(bool* base, __int64 pow, int n) {

	bool* prod = new bool[n];
	for (int i = 0; i < n ; i++)
		prod[i] = false;
	prod[pow] = true;

	return prod;

}

bool* SATSolver_bool_mul(bool* a, bool* b, int n) {

	bool* sum = new bool[n];

	for (int i = 0; i < n; i++)
		sum[i] = false;

	for (int i = 0; i < n; i++) {
		bool* temp = new bool[n];

		for (int j = 0; j < i; j++)
			temp[n - 1 - j] = false;

		for (int j = 0; j < n - i; j++)
			temp[n - 1 - j - i] = b[n - 1 - i] && a[n - 1 - j];

		bool* new_sum = SATSolver_bool_add(temp, sum, n);
		bool* dump = sum;
		sum = new_sum;
		delete[] dump;
		delete[] temp;
	}

	return sum;

}

bool* SATSolver_bool_add(bool* a, bool* b, int n) {

	bool carry = false;

	bool* ret = new bool[n];

	for (int i = 0; i < n; i++) {

		bool sum_temp = (!a[i] && b[i]) || (a[i] && !b[i]);
		ret[i] = (!sum_temp && carry) || (sum_temp && !carry);
		carry = (a[i] && b[i]) || (a[i] && carry) || (b[i] && carry);

	}

	return ret;

}

bool* SATSolver_bool_prepare_end(bool* a, bool* b, int n) {

	bool carry = false;

	bool* ret = new bool[n];

	int position_first_true_bit;

	for (position_first_true_bit = n; !b[position_first_true_bit] && position_first_true_bit >= 0; position_first_true_bit--)
		;

	for (int i = position_first_true_bit - 1; i >= 0; i--)
		ret[i] = true;

	return ret;

}


bool* SATSolver_int2bool(__int64 a, __int64 n_parm) {

	// create the return boolean array and initialize

	bool* ret = new bool[n_parm];

	for (int i = 0; i < n_parm; i++)
		ret[i] = false;


	// for each bit position, determine true/false value, using a signed 64 bit signed integer

	for (int i = 64 - 2; i >= 0; i--) {

		// form simple power
		__int64 simple_pow = 1;

		for (int j = 0; j < i; j++)
			simple_pow *= 2;

		if (a >= simple_pow) {
			ret[i] = true;
			a = a - simple_pow;
		}
	}

	return ret;

}


/* instantiate SATSolver class with list of clauses
* 
* lst: list of clauses
* k_parm: number of clauses (size of lst)
* n_parm: number of variables
* chop: power of 2, chopping up search space
* pos: position in chopping up search space
* 
* */
void SATSolver_create(SATSolver * me, SATSolverMaster * master , int** lst, int k_parm, int n_parm, int chop, int pos) {

	// valcheck

	if (lst == NULL)
		return;
	if (k_parm <= 0)
		return;
	if (n_parm <= 0)
		return;

	// instantiate class member variables

	me->master = master;
	me->Z = new bool [n_parm];

	// set up first and last element to check: me->begin, me->end

	bool * two = SATSolver_int2bool(2, n_parm);
	bool * unit = SATSolver_bool_pow(two, n_parm - chop, n_parm + 1);
	bool * offs = SATSolver_int2bool(pos, n_parm);
	me->begin = SATSolver_bool_mul ( unit, offs, n_parm) ;
	me->end = SATSolver_bool_prepare_end ( me->begin, unit, n_parm);

	delete[] two;
	delete[] unit;
	delete[] offs;

	// identify clauses having a true TRUE_3SAT value or a false FALSE_3SAT value

	int* lst_t = new int[k_parm];
	int* lst_f = new int[k_parm];

	for (int i = 0; i < k_parm; i++) {
		lst_t [i] = 0;
		lst_f [i] = 0;
	}

	for (int i = 0; i < k_parm; i++) {

		if (lst[i][0] == FALSE_3SAT)
			lst_f[i]++;
		if (lst[i][1] == FALSE_3SAT)
			lst_f[i]++;
		if (lst[i][2] == FALSE_3SAT)
			lst_f[i]++;

		if (lst[i][0] == TRUE_3SAT)
			lst_t[i]++;
		if (lst[i][1] == TRUE_3SAT)
			lst_t[i]++;
		if (lst[i][2] == TRUE_3SAT)
			lst_t[i]++;
	}

	// set value of Z to begin, decoded

	for (int i = 0; i <= n_parm; i++)
		me->Z[i] = me->begin [ i ];

	// create the running clause tally cls_tly

	me->cls_tly = new int[k_parm];

	for (int i = 0; i < k_parm; i++)
		me->cls_tly[i] = 0;

	// initialize to all having 3 - non-t/f literals

	for (int i = 0; i < k_parm; i++)
		if (lst_t[i] > 0)
			me->cls_tly[i] = 0;
		else
			me->cls_tly[i] = lst_f[i];

	// populate clause tally with initial begin value

	for (int i = 0; i < n_parm; i++) {
		for (int j = 0; j < me->master->pos_map_szs[me->master->decoding[i]]; j++)
			if (me->begin[i]) {
				int cls_ix = me->master->pos_map[me->master->decoding[i]][j];
				int old_val = me->cls_tly[cls_ix];
				me->cls_tly[cls_ix] = old_val + 1;
			}
		for (int j = 0; j < me->master->neg_map_szs[me->master->decoding[i]]; j++)
			if (!me->begin[i]) {
				int cls_ix = me->master->neg_map[me->master->decoding[i]][j];
				int old_val = me->cls_tly[cls_ix];
				me->cls_tly[cls_ix] = old_val + 1;
			}
	}

	// delete

	delete[] lst_t;
	delete[] lst_f;
}

void SATSolverMaster_create(SATSolverMaster * master, int** lst, int k_parm, int n_parm) {

	// populate histogram of the variables

	master->n = n_parm;
	master->k = k_parm;

	int* histogram = new int[n_parm];

	for (int i = 0; i < n_parm; i++)
		histogram[i] = 0;

	for (int i = 0; i < k_parm; i++)
		for (int j = 0; j < 3; j++) {
			// check for existence of true TRUE_3SAT or false FALSE_3SAT
			if (lst[i][j] == FALSE_3SAT || lst[i][j] == TRUE_3SAT)
				continue;
			int tmp = (lst[i][j] < 0 ? -lst[i][j] : lst[i][j]) - 2;
			int cur = histogram[tmp];
			histogram[tmp] = cur + 1;
		}

	// create a sorted copy of the histogram

	int* histogram_srt = new int[n_parm];

	for (int i = 0; i < n_parm; i++)
		histogram_srt[i] = histogram[i];

	MyQSort(histogram_srt, 0, n_parm - 1);

	// create a decoding based on the histogram

	master->decoding = new int[n_parm];

	for (int i = 0; i < n_parm; i++) {
		int count = histogram_srt[i];
		int pos = 0;
		while (histogram[pos] != count)
			pos++;
		master->decoding[i] = pos;
		histogram[pos] = -1;
	}

	// order list of k clauses in cls_tly (clause tally) by lowest-order literal of each clause

	master->powers = new int[k_parm];

	for (int i = 0; i < k_parm; i++) {
		int highest = -1;
		int lit_cur = 0;
		for (int j = 0; j < 3; j++) {
			// check for true TRUE_3SAT or false FALSE_3SAT
			if (lst[i][j] == TRUE_3SAT)
				break;
			if (lst[i][j] == FALSE_3SAT)
				continue;
			int ix = (lst[i][j] < 0 ? -lst[i][j] : lst[i][j]) - 2;
			if (master->decoding[ix] > highest) {
				highest = master->decoding[ix];
				lit_cur = lst[i][j] > 0 ? -highest: highest;
			}
		}

		// record the jump power of the clause at i

		master->powers[i] = lit_cur < 0 ? - (n_parm - 1 - highest) - 1 : (n_parm - 1 - highest) + 1;

	}

	// create the map looking into running tally based on literals pos_map

	master->pos_map = new int* [n_parm];
	master->neg_map = new int* [n_parm];

	// instantiate pos_map_szs and neg_map_szs

	master->pos_map_szs = new int[n_parm];
	master->neg_map_szs = new int[n_parm];

	// initialize pos_map_szs and neg_map_szs all to 0

	for (int i = 0; i < n_parm; i++) {
		master->pos_map_szs[master->decoding[i]] = 0;
		master->neg_map_szs[master->decoding[i]] = 0;
	}

	// determine the pos_map_szs

	for (int i = 0; i < n_parm; i++) {
		for (int j = 0; j < k_parm; j++) {
			// skip if true TRUE_3SAT or false FALSE_3SAT
			if (lst[j][0] != FALSE_3SAT && lst[j][0] != TRUE_3SAT && lst[j][0] == -(i + 2))
				master->pos_map_szs[master->decoding[i]]++;
			if (lst[j][1] != FALSE_3SAT && lst[j][1] != TRUE_3SAT && lst[j][1] == -(i + 2))
				master->pos_map_szs[master->decoding[i]]++;
			if (lst[j][2] != FALSE_3SAT && lst[j][2] != TRUE_3SAT && lst[j][2] == -(i + 2))
				master->pos_map_szs[master->decoding[i]]++;
		}
	}

	// determine the neg_map_szs

	for (int i = 0; i < n_parm; i++) {
		for (int j = 0; j < k_parm; j++) {
			// skip if true TRUE_3SAT or false FALSE_3SAT
			if (lst[j][0] != FALSE_3SAT && lst[j][0] != TRUE_3SAT && lst[j][0] == (i + 2))
				master->neg_map_szs[master->decoding[i]]++;
			if (lst[j][1] != FALSE_3SAT && lst[j][1] != TRUE_3SAT && lst[j][1] == (i + 2))
				master->neg_map_szs[master->decoding[i]]++;
			if (lst[j][2] != FALSE_3SAT && lst[j][2] != TRUE_3SAT && lst[j][2] == (i + 2))
				master->neg_map_szs[master->decoding[i]]++;
		}
	}

	// instantiate pos_map and neg_map for each variable

	for (int i = 0; i < n_parm; i++) {
		master->pos_map[master->decoding[i]] = new int[master->pos_map_szs[master->decoding[i]]];
		master->neg_map[master->decoding[i]] = new int[master->neg_map_szs[master->decoding[i]]];
	}

	// initialize pos_map and neg_map all to 0

	for (int i = 0; i < n_parm; i++) {
		for (int j = 0; j < master->pos_map_szs[master->decoding[i]]; j++)
			master->pos_map[master->decoding[i]][j] = 0;
		for (int j = 0; j < master->neg_map_szs[master->decoding[i]]; j++)
			master->neg_map[master->decoding[i]][j] = 0;
	}

	// populate pos_map, neg_map
	for (int i = 0; i < n_parm; i++) {

		int pos_pos = 0;
		int pos_neg = 0;

		for (int j = 0; j < k_parm; j++) {

			for (int k = 0; k < 3; k++) {

				if (lst[j][k] == TRUE_3SAT)
					break;

				if (lst[j][k] == FALSE_3SAT)
					continue;

				int pos = (lst[j][k] < 0 ? -lst[j][k] : lst[j][k]) - 2;

				if (pos != i)
					continue;

				if (lst[j][k] < 0) {
					master->pos_map[master->decoding[i]][pos_pos] = j;
					pos_pos++;
				}
				else {
					master->neg_map[master->decoding[i]][pos_neg] = j;
					pos_neg++;
				}
			}

		}
	}
}

void SATSolverMaster_destroy(SATSolverMaster* master) {

	delete [] master->decoding;

	for (int i = 0; i < master->n; i++) {
		delete [] master->pos_map[i];
		delete [] master->neg_map[i];
	}

	delete [] master->pos_map;
	delete [] master->neg_map;
	delete [] master->pos_map_szs;
	delete [] master->neg_map_szs;
	delete [] master->powers;
}

void SATSolver_destroy(SATSolver * me) {

	for (int i = 0; i < me->master->n; i++) {

		delete[] me->cls_tly;
		delete[] me->Z;
		delete[] me->begin;
		delete[] me->end;

	}
}

std::mutex m;
std::condition_variable cv;
bool done = false;
bool ready = true;
bool solved = false;
int thread_id = -1;

void thread_3SAT(int tid, SATSolverMaster *master, bool * arr, int ** lst, int k_parm, int n_parm, __int64 chop, __int64 pos) {

	SATSolver* s = new SATSolver();
	SATSolver_create(s, master, lst, k_parm, n_parm, chop, pos);

	bool sat = SATSolver_isSat(s, arr);

	{
		std::unique_lock<std::mutex> lock(m);
		cv.wait(lock, [] {return ready; });
		ready = false;
		done = sat;
		thread_id = tid;
		cv.notify_all();
	}
}

bool SATSolver_threads(int** lst, int k_parm, int n_parm, bool ** arr) {

	//int num_threads = n_parm < 50 ? 1 : std::thread::hardware_concurrency() ;
	int num_threads = 1 ;

	std::thread ** threadblock = new std::thread * [num_threads];

	for (int i = 0; i < num_threads; i++)
		threadblock[i] = NULL;

	bool** arrs = new bool*[num_threads];

	for (int i = 0; i < num_threads; i++)
		arrs[i] = new bool[n_parm];

	SATSolverMaster* master = new SATSolverMaster();
	SATSolverMaster_create(master, lst, k_parm, n_parm);

	__int64 top = 1;

	//int chop = 16;
	int chop = 0;

	for (int i = 0; i < chop; i++)
		top *= 2;

	for (int i = 0; i < num_threads; i++)
		threadblock[i] = new std::thread(thread_3SAT, i , master, arrs[i], lst, k_parm, n_parm, chop, i);

	__int64 pos = num_threads;

	do {
		{
			std::unique_lock<std::mutex> lock(m);
			cv.wait(lock, [] {return !ready; });
			threadblock[thread_id]->join();
			delete threadblock[thread_id];
			solved = done;
			if (solved)
				break;
			if (pos < top) {
				threadblock[thread_id] = new std::thread(thread_3SAT, thread_id, master, arrs[thread_id], lst, k_parm, n_parm, chop, pos);
				ready = true;
				thread_id = -1;
				cv.notify_all();
			}
		}
		pos++;
	} while (pos < top && !solved);


	for (int i = 0; i < num_threads; i++)
		if (solved && i != thread_id) {
			threadblock[thread_id]->join();
			delete threadblock[thread_id];
		}

	delete[] threadblock;

	if (solved)
		for (int i = 0; i < n_parm; i++)
			(*arr)[i] = arrs[thread_id][i];

	// free up master resources

	SATSolverMaster_destroy(master);
	delete master;

	return solved;
}

#endif