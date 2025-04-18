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
	//for (int j = 0; j < pos; j++)
	//	if (me->Z[j]) {
	//		me->Z[j] = false;
	//		SATSolver_updateTF(me, j, false);
	//	}
}

__int64 SATSolver_initializePowJump(SATSolver* me, __int64 prev_pos) {

	//printf_s("initializePowJump ");

	// initialize return value

	__int64 max_jump = 0;

	// check if any clauses are satisfied and find jump powers corresponding to clauses

	for (int i = 0; i < me->master->k; i++) {
		int temp_jump = me->master->powers[i];
		int abs_temp_jump = temp_jump < 0 ? -temp_jump : temp_jump;
		int abs_max_jump = max_jump < 0 ? -max_jump : max_jump;
		bool sign_match = (me->Z[abs_temp_jump - 1] && me->master->powers[i] > 0) || (!me->Z[abs_temp_jump - 1] && me->master->powers[i] < 0);
		if (sign_match && me->cls_tly[i] == 3 && abs_temp_jump > abs_max_jump && (abs_temp_jump > prev_pos || temp_jump < 0))
		{
			max_jump = temp_jump;
			printf_s("%d ", (int)max_jump);
		}
	}

	printf_s("\n");

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

bool SATSolver_isSat(SATSolver* me, int chop, bool* arr) {

	bool jump_occurred = false;
	bool prev_is_end = false;
	bool Z_got_bigger = false;

		
	printf_s("chop: %d\n", chop);

	for (int i = 0; i < me->master->n; i++)
		me->Z[i] = me->master->begin[chop][i];

	// main loop- until end condition

	__int64 count = 0;
	__int64 prev_pos = 0;	// de-exponentializer variable
	bool zero_jump = false;
	bool* prev_Z;

	prev_Z = new bool[me->master->n];

	for (int i = 0; i < me->master->n; i++)
		prev_Z[i] = me->Z[i];

	__int64 temp_pow_jump = SATSolver_initializePowJump(me, prev_pos);
	__int64 abs_temp_pow_jump = temp_pow_jump < 0 ? -temp_pow_jump : temp_pow_jump;

	if (temp_pow_jump == 0) {
		delete[] prev_Z;
		return false;
	}
	else
		jump_occurred = true;

	// using prev_pos: de-exponentialize
	if (temp_pow_jump > 0)
		prev_pos = temp_pow_jump;
	else if (abs_temp_pow_jump > prev_pos)
		prev_pos = 0;

	me->pow_jump = temp_pow_jump < 0 ? -temp_pow_jump - 1 : temp_pow_jump - 1;

	SATSolver_add(me, (int)me->pow_jump);

	Z_got_bigger = SATSolver_GreaterThan(me->Z, prev_Z, me->master->n);

	count++;

	//if (count % (1 * 1048576) == 0) {

	if (true) {

		for (int i = 0; i < me->master->n; i++)
			printf_s("%d", me->Z[i]);
		//printf_s(" jump: %d", me->pow_jump);
		printf_s(" jump: %d", temp_pow_jump);
		printf_s("\n");
	}

	while ( Z_got_bigger ) {

		jump_occurred = false;

		int count_matches = 0;

		for (int i = 0; i < me->master->n; i++)
			if (prev_Z[i] == me->master->end[chop][i])
				count_matches++;

		if (count_matches == me->master->n)
			prev_is_end = true;

		for (int i = 0; i < me->master->n; i++)
			prev_Z[i] = me->Z[i];

		temp_pow_jump = SATSolver_initializePowJump(me, prev_pos);
		abs_temp_pow_jump = temp_pow_jump < 0 ? -temp_pow_jump : temp_pow_jump;

		if (temp_pow_jump == 0) {
			zero_jump = true;
			break;
		}
		else
			jump_occurred = true;

		// using prev_pos: de-exponentialize
		if (temp_pow_jump > 0)
			prev_pos = temp_pow_jump;
		else if (abs_temp_pow_jump > prev_pos)
			prev_pos = 0;

		me->pow_jump = temp_pow_jump < 0 ? -temp_pow_jump - 1 : temp_pow_jump - 1;

		SATSolver_add(me, (int)me->pow_jump);

		Z_got_bigger = SATSolver_GreaterThan(me->Z, prev_Z, me->master->n);

		count++;

		//if (count % (1 * 1048576) == 0) {

		if (true) {

			for (int i = 0; i < me->master->n; i++)
				printf_s("%d", me->Z[i]);
			//printf_s(" jump: %d", me->pow_jump);
			printf_s(" jump: %d count_matches: %d", temp_pow_jump, count_matches);
			printf_s("\n");
		}

	}

	printf_s("count: %d\n", (int)count);

	if (prev_is_end && jump_occurred) {
		delete[] prev_Z;
		return false;
	}

	for (int i = 0; i < me->master->n; i++)
		arr[me->master->decoding[i]] = me->Z[i];

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

	bool* ret = SATSolver_bool_add(a, b, n);

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

bool* SATSolver_create_boundary(bool begin, int chop, int offs, int n) {

	bool* ret = new bool[n];

	for (int i = 0; i < chop; i++) {

		int pow2 = 1;
		for (int j = chop - 1 - i; j > 0; j--)
			pow2 *= 2;

		if (offs >= pow2) {
			ret[i] = true;
			offs -= pow2;
		}
		else
			ret[i] = false;
	}

	for (int i = chop; i < n; i++)
		ret[i] = begin ? false : true;

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
void SATSolver_create(SATSolver * me, SATSolverMaster * master , int** lst, int k_parm, int n_parm, int chop) {

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

	//for (int i = 0; i < me->master->k; i++)
	//	//if (lst[i][0] < 0 && lst[i][1] < 0 && lst[i][2] < 0)
	//		printf_s("%d: %d %d %d\n", i, lst[i][0], lst[i][1], lst[i][2]);

	for (int i = 0; i < n_parm; i++) {
		for (int j = 0; j < me->master->pos_map_szs[me->master->decoding[i]]; j++)
			if (!me->master->begin[chop][me->master->decoding[i]]) {
				int cls_ix = me->master->pos_map[me->master->decoding[i]][j];
				int old_val = me->cls_tly[cls_ix];
				me->cls_tly[cls_ix] = old_val + 1;
			}
		for (int j = 0; j < me->master->neg_map_szs[me->master->decoding[i]]; j++)
			if (me->master->begin[chop][me->master->decoding[i]]) {
				int cls_ix = me->master->neg_map[me->master->decoding[i]][j];
				int old_val = me->cls_tly[cls_ix];
				me->cls_tly[cls_ix] = old_val + 1;
			}
	}


	// delete

	delete[] lst_t;
	delete[] lst_f;
}

void SATSolverMaster_create(SATSolverMaster * master, int** lst, int k_parm, int n_parm, int chops_parm) {

	// chops

	master->chops = chops_parm;

	// calculate chops

	if (master->chops < 2)
		master->chops = 2;

	__int64 search_sz = 1;

	for (int i = 0; i < master->chops; i++)
		search_sz *= 2;

	master->begin = new bool* [search_sz];
	master->end = new bool* [search_sz];

	for (int chop = 0; chop < search_sz; chop++) {

		// set up first and last element to check: me->begin, me->end

		master->begin[chop] = SATSolver_create_boundary(true, master->chops, chop, n_parm);
		master->end[chop] = SATSolver_create_boundary(false, master->chops, chop, n_parm);

	}

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
	for (int i = 0; i < k_parm; i++)
		master->powers[i] = 0;

	for (int i = 0; i < k_parm; i++) {

		///*
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

				if (j == 6 && pos == 6)
					printf_s("mofo\n");

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

	int count_chops = 1;

	for (int i = 0; i < master->chops; i++)
		count_chops *= 2;

	for (int i = 0; i < count_chops; i++) {

		delete[] master->begin[i];
		delete[] master->end[i];

	}

	delete[] master->begin;
	delete[] master->end;

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

	delete[] me->cls_tly;
	delete[] me->Z;
}

std::mutex m;
std::condition_variable cv;
bool done = false;
bool ready = true;
bool solved = false;
int thread_id = -1;

void thread_3SAT(int tid, SATSolverMaster *master, bool * arr, int ** lst, int k_parm, int n_parm, int chop) {

	SATSolver* s = new SATSolver();
	SATSolver_create(s, master, lst, k_parm, n_parm, chop);

	bool sat = SATSolver_isSat(s, chop, arr);

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

	// get the right number of chops- at least 2^chops

	int chops = 2;
	
	if (num_threads > 4) {

		int count_chops = 1;

		int counter = 0;

		for (counter = 0; count_chops < num_threads; counter++)
			count_chops *= 2;

		if (count_chops == num_threads)
			chops = counter;

		else
			chops = counter + 1;

	}

	SATSolverMaster* master = new SATSolverMaster();
	SATSolverMaster_create(master, lst, k_parm, n_parm, chops);

	///*

	int search_sz = 1;

	for (int i = 0; i < master->chops; i++)
		search_sz *= 2;


	int pos = 0;
	for (pos = 0; pos < num_threads; pos++)
		threadblock[pos] = new std::thread(thread_3SAT, pos , master, arrs[pos], lst, k_parm, n_parm, pos);

	do {
		{
			std::unique_lock<std::mutex> lock(m);
			cv.wait(lock, [] {return !ready; });
			threadblock[thread_id]->join();
			delete threadblock[thread_id];
			solved = done;
			if (solved)
				break;
			if (pos < search_sz) {
				threadblock[thread_id] = new std::thread(thread_3SAT, thread_id, master, arrs[thread_id], lst, k_parm, n_parm, pos);
				ready = true;
				thread_id = -1;
				cv.notify_all();
			}
		}
		pos++;
	} while (pos < search_sz && !solved);

	//*/


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