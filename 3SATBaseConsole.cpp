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
__int64 MyQSort_partition(__int64 arr_parm[], __int64 low_parm, __int64 high_parm)
{
	__int64 pivot = arr_parm[high_parm];    // pivot
	__int64 i = (low_parm - 1);  // Index of smaller element

	for (__int64 j = low_parm; j <= high_parm - 1; j++)
	{
		// swap if current element is greater than pivot
		if (arr_parm[j] > pivot)
		{
			i++;    // increment index of smaller element
			__int64 t = arr_parm[i];
			arr_parm[i] = arr_parm[j];
			arr_parm[j] = t;
		}
	}
	__int64 t = arr_parm[i + 1];
	arr_parm[i+1] = arr_parm[high_parm];
	arr_parm[high_parm] = t;
	return (i + 1);
}
//*/

// https://www.geeksforgeeks.org/c-program-for-iterative-quick-sort/

// A utility function to swap two elements
void swap(__int64* a, __int64* b)
{
	__int64 t = *a;
	*a = *b;
	*b = t;
}

/* This function is same in both iterative and recursive*/
__int64 partition(__int64 arr_parm[], __int64 low_parm, __int64 high_parm)
{
	__int64 pivot = arr_parm[high_parm];    // pivot
	__int64 i = (low_parm - 1);  // Index of smaller element

	for (__int64 j = low_parm; j <= high_parm - 1; j++)
	{
		// swap if current element is greater than pivot
		if (arr_parm[j] > pivot)
		{
			i++;    // increment index of smaller element
			__int64 t = arr_parm[i];
			arr_parm[i] = arr_parm[j];
			arr_parm[j] = t;
		}
	}
	__int64 t = arr_parm[i + 1];
	arr_parm[i + 1] = arr_parm[high_parm];
	arr_parm[high_parm] = t;
	return (i + 1);
}

/* A[] --> Array to be sorted,
   l  --> Starting index,
   h  --> Ending index */
void MyQSort(__int64 arr[], __int64 l, __int64 h)
{
	// Create an auxiliary stack
	__int64 * stack = new __int64 [h - l + 1];

	// initialize top of stack
	__int64 top = -1;

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
		__int64 p = partition(arr, l, h);

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
void MyQSort(__int64 arr [] , __int64 low_parm, __int64 high_parm)
{
	if (low_parm < high_parm)
	{
		__int64 pi = MyQSort_partition(arr, low_parm, high_parm);

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

void SATSolver_updateTF(SATSolver* me, __int64 zpos, bool target) {

	if (target) {

		for (__int64 i = 0; i < me->master->pos_map_szs[zpos]; i++) {
			__int64 clause = me->master->pos_map[zpos][i];
			__int64 old_val = me->cls_tly[clause];
			__int64 new_val = old_val - 1;
			me->cls_tly[clause] = new_val;
		}
		for (__int64 i = 0; i < me->master->neg_map_szs[zpos]; i++) {
			__int64 clause = me->master->neg_map[zpos][i];
			__int64 old_val = me->cls_tly[clause];
			__int64 new_val = old_val + 1;
			me->cls_tly[clause] = new_val;
		}

	} 
	else {

		for (__int64 i = 0; i < me->master->neg_map_szs[zpos]; i++) {
			__int64 clause = me->master->neg_map[zpos][i];
			__int64 old_val = me->cls_tly[clause];
			__int64 new_val = old_val - 1;
			me->cls_tly[clause] = new_val;
		}
		for (__int64 i = 0; i < me->master->pos_map_szs[zpos]; i++) {
			__int64 clause = me->master->pos_map[zpos][i];
			__int64 old_val = me->cls_tly[clause];
			__int64 new_val = old_val + 1;
			me->cls_tly[clause] = new_val;
		}

	}
}

/*
* 
* add- add a number 2^pos_parm to Z
* 
*/

void SATSolver_add(SATSolver * me , __int64 pos_parm) {

	// add 2^pos_parm to Z

	__int64 pos = pos_parm < 0 ? -pos_parm : pos_parm;

	bool sign = me->Z[pos];

	me->Z[pos] = !sign;
	SATSolver_updateTF(me, pos, !sign);

	if (sign)
		for (__int64 i = pos + 1; i < me->master->n; i++)
			if (me->Z[i]) {
				me->Z[i] = false;
				SATSolver_updateTF(me, i, false);
			}
			else {
				me->Z[i] = true;
				SATSolver_updateTF(me, i, true);
				break;
			}
	
	// zero out all lower bits of Z

	for (__int64 j = pos - 1; j >= 0; j--)
		if (me->Z[j]) {
			me->Z[j] = false;
			SATSolver_updateTF(me, j, false);
		}
}

__int64 SATSolver_initializePowJump(SATSolver* me) {

	//printf_s("initializePowJump prev_pos: %lld ", (__int64)prev_pos);

	// initialize return value

	__int64 max_jump = 0;

	// check if any clauses are satisfied and find jump powers corresponding to clauses

	for (__int64 i = 0; i < me->master->k; i++) {
		__int64 temp_jump = me->master->powers[i];
		__int64 abs_temp_jump = temp_jump < 0 ? -temp_jump : temp_jump;
		__int64 abs_max_jump = max_jump < 0 ? -max_jump : max_jump;
		//bool sign_match = (me->Z[abs_temp_jump - 1] && me->master->powers[i] > 0) || (!me->Z[abs_temp_jump - 1] && me->master->powers[i] < 0);
		if (/*sign_match &&*/ me->cls_tly[i] == 3 && abs_temp_jump > abs_max_jump)
		{
			max_jump = temp_jump;
			printf_s("%lld ", max_jump);
		}
	}

	//printf_s("\n");

	return max_jump;

}

bool SATSolver_GreaterThan(bool* a, bool* b, __int64 n) {

	__int64 i;

	for (i = n - 1; i >= 0; i--)
		if (a[i] && !b[i])
			return true;
		else if (!a[i] && b[i])
			return false;

	return false;

}

bool SATSolver_isSat(SATSolver* me, __int64 chop, bool* arr) {

	bool jump_occurred = false;
	bool prev_is_end = false;
	bool Z_got_bigger = false;

		
	printf_s("chop: %lld\n", chop);

	for (__int64 i = 0; i < me->master->n; i++)
		me->Z[i] = me->master->begin[chop][i];

	// main loop- until end condition

	__int64 count = 0;
	__int64 prev_pos = 0;	// de-exponentializer variable
	__int64 abs_prev_pos = 0;
	bool zero_jump = false;
	bool* prev_Z;

	prev_Z = new bool[me->master->n];

	for (__int64 i = 0; i < me->master->n; i++)
		prev_Z[i] = me->Z[i];

	__int64 temp_pow_jump = SATSolver_initializePowJump(me);
	__int64 abs_temp_pow_jump = temp_pow_jump < 0 ? -temp_pow_jump : temp_pow_jump;

	if (temp_pow_jump == 0) {
		delete[] prev_Z;
		return false;
	}
	else
		jump_occurred = true;

	// using prev_pos: de-exponentialize
	//if (temp_pow_jump > 0)
	//	prev_pos = temp_pow_jump;
	//else if (temp_pow_jump < 0 && abs_temp_pow_jump > prev_pos)
	//	prev_pos = 0;

	me->pow_jump = temp_pow_jump < 0 ? -temp_pow_jump - 1 : temp_pow_jump - 1;

	SATSolver_add(me, me->pow_jump);

	//Z_got_bigger = SATSolver_GreaterThan(me->Z, prev_Z, me->master->n);

	count++;

	//if (count % (1 * 1048576) == 0) {

	if (true) {
		for (__int64 i = 0; i < me->master->n; i++)
			printf_s("%lld", (__int64) me->Z[i]);
		//printf_s(" jump: %lld", me->pow_jump);
		printf_s(" jump: %I64d", temp_pow_jump);
		printf_s("\n");
	}

	while ( ( ! SATSolver_GreaterThan (me->Z, me->master->end[chop], me->master->n)) && ! (prev_is_end && jump_occurred) ) {

		jump_occurred = false;
		abs_prev_pos = prev_pos < 0 ? -prev_pos : prev_pos;

		__int64 count_matches = 0;

		for (__int64 i = 0; i < me->master->n; i++)
			if (prev_Z[i] == me->master->end[chop][i])
				count_matches++;

		if (count_matches == me->master->n)
			prev_is_end = true;

		for (__int64 i = 0; i < me->master->n; i++)
			prev_Z[i] = me->Z[i];

		temp_pow_jump = SATSolver_initializePowJump(me);
		abs_temp_pow_jump = temp_pow_jump < 0 ? -temp_pow_jump - 1 : temp_pow_jump - 1;

		if (temp_pow_jump == 0) {
			zero_jump = true;
			break;
		}
		else
			jump_occurred = true;

		// using prev_pos: de-exponentialize
		//if (temp_pow_jump > 0 && abs_temp_pow_jump > abs_prev_pos)
		//	prev_pos = temp_pow_jump;
		//else if (temp_pow_jump < 0 && abs_temp_pow_jump > prev_pos)
		//	prev_pos = 0;

		me->pow_jump = temp_pow_jump < 0 ? -temp_pow_jump - 1 : temp_pow_jump - 1;

		SATSolver_add(me, me->pow_jump);

		//Z_got_bigger = SATSolver_GreaterThan(me->Z, prev_Z, me->master->n);

		count++;

		//if (count % (1 * 1048576) == 0) {

		if (true) {

			for (__int64 i = 0; i < me->master->n; i++)
				printf_s("%lld", (__int64) me->Z[i]);
			//printf_s(" jump: %lld", me->pow_jump);
			printf_s(" jump: %I64d count_matches: %I64d", temp_pow_jump, count_matches);
			printf_s("\n");
		}

	}

	printf_s("count: %lld\n", (__int64)count);

	if (prev_is_end && jump_occurred) {
		delete[] prev_Z;
		return false;
	}

	for (__int64 i = 0; i < me->master->n; i++)
		arr[me->master->decoding[i]] = me->Z[i];

	delete[] prev_Z;

	return true;
}

bool * SATSolver_bool_pow(bool* base, __int64 pow, __int64 n) {

	bool* prod = new bool[n];
	for (__int64 i = 0; i < n ; i++)
		prod[i] = false;
	prod[pow] = true;

	return prod;

}

bool* SATSolver_bool_mul(bool* a, bool* b, __int64 n) {

	bool* sum = new bool[n];

	for (__int64 i = 0; i < n; i++)
		sum[i] = false;

	for (__int64 i = 0; i < n; i++) {
		bool* temp = new bool[n];

		for (__int64 j = 0; j < i; j++)
			temp[n - 1 - j] = false;

		for (__int64 j = 0; j < n - i; j++)
			temp[n - 1 - j - i] = b[n - 1 - i] && a[n - 1 - j];

		bool* new_sum = SATSolver_bool_add(temp, sum, n);
		bool* dump = sum;
		sum = new_sum;
		delete[] dump;
		delete[] temp;
	}

	return sum;

}

bool* SATSolver_bool_add(bool* a, bool* b, __int64 n) {

	bool carry = false;

	bool* ret = new bool[n];

	for (__int64 i = 0; i < n; i++) {

		bool sum_temp = (!a[i] && b[i]) || (a[i] && !b[i]);
		ret[i] = (!sum_temp && carry) || (sum_temp && !carry);
		carry = (a[i] && b[i]) || (a[i] && carry) || (b[i] && carry);

	}

	return ret;

}

bool* SATSolver_bool_prepare_end(bool* a, bool* b, __int64 n) {

	bool* ret = SATSolver_bool_add(a, b, n);

	__int64 position_first_true_bit;

	for (position_first_true_bit = n; !b[position_first_true_bit] && position_first_true_bit >= 0; position_first_true_bit--)
		;

	for (__int64 i = position_first_true_bit - 1; i >= 0; i--)
		ret[i] = true;

	return ret;

}


bool* SATSolver___int642bool(__int64 a, __int64 n_parm) {

	// create the return boolean array and initialize

	bool* ret = new bool[n_parm];

	for (__int64 i = 0; i < n_parm; i++)
		ret[i] = false;


	// for each bit position, determine true/false value, using a signed 64 bit signed integer

	for (__int64 i = 64 - 2; i >= 0; i--) {

		// form simple power
		__int64 simple_pow = 1;

		for (__int64 j = 0; j < i; j++)
			simple_pow *= 2;

		if (a >= simple_pow) {
			ret[i] = true;
			a = a - simple_pow;
		}
	}

	return ret;

}

bool* SATSolver_create_boundary(bool begin, __int64 chop, __int64 offs, __int64 n) {

	bool* ret = new bool[n];

	for (__int64 i = 0; i < chop; i++) {

		__int64 pow2 = 1;
		for (__int64 j = chop - 1 - i; j > 0; j--)
			pow2 *= 2;

		if (offs >= pow2) {
			ret[i] = true;
			offs -= pow2;
		}
		else
			ret[i] = false;
	}

	for (__int64 i = chop; i < n; i++)
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
void SATSolver_create(SATSolver * me, SATSolverMaster * master , __int64** lst, __int64 k_parm, __int64 n_parm, __int64 chop) {

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

	__int64* lst_t = new __int64[k_parm];
	__int64* lst_f = new __int64[k_parm];

	for (__int64 i = 0; i < k_parm; i++) {
		lst_t [i] = 0;
		lst_f [i] = 0;
	}

	for (__int64 i = 0; i < k_parm; i++) {

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

	me->cls_tly = new __int64[k_parm];

	for (__int64 i = 0; i < k_parm; i++)
		me->cls_tly[i] = 0;

	// initialize to all having 3 - non-t/f literals

	for (__int64 i = 0; i < k_parm; i++)
		if (lst_t[i] > 0)
			me->cls_tly[i] = 0;
		else
			me->cls_tly[i] = lst_f[i];

	// populate clause tally with initial begin value

	/*
	for (__int64 i = 0; i < me->master->k; i++)
		//if (lst[i][0] < 0 && lst[i][1] < 0 && lst[i][2] < 0)
			printf_s("%lld: %lld %lld %lld\n", i, lst[i][0], lst[i][1], lst[i][2]);
			*/

	/*
	for (__int64 i = 0; i < n_parm; i++) {
		for (__int64 j = 0; j < me->master->pos_map_szs[me->master->decoding[i]]; j++)
			if (!me->master->begin[chop][me->master->decoding[i]]) {
				__int64 cls_ix = me->master->pos_map[me->master->decoding[i]][j];
				__int64 old_val = me->cls_tly[cls_ix];
				me->cls_tly[cls_ix] = old_val + 1;
				if (cls_ix == 0)
					printf_s("pos i: %lld j: %lld\n", i, j);
			}
		for (__int64 j = 0; j < me->master->neg_map_szs[me->master->decoding[i]]; j++)
			if (me->master->begin[chop][me->master->decoding[i]]) {
				__int64 cls_ix = me->master->neg_map[me->master->decoding[i]][j];
				__int64 old_val = me->cls_tly[cls_ix];
				me->cls_tly[cls_ix] = old_val + 1;
				if (cls_ix == 0)
					printf_s("neg i: %lld j: %lld\n", i, j);
			}
	}
	*/

	for (__int64 i = 0; i < n_parm; i++) {
		for (__int64 j = 0; j < me->master->pos_map_szs[i]; j++)
			if (!me->master->begin[chop][i]) {
				__int64 cls_ix = me->master->pos_map[i][j];
				__int64 old_val = me->cls_tly[cls_ix];
				me->cls_tly[cls_ix] = old_val + 1;

				if (cls_ix == 21)
					printf_s("pos_map: i=%lld j=%lld\n", i, j);
			}
		for (__int64 j = 0; j < me->master->neg_map_szs[i]; j++)
			if (me->master->begin[chop][i]) {
				__int64 cls_ix = me->master->neg_map[i][j];
				__int64 old_val = me->cls_tly[cls_ix];
				me->cls_tly[cls_ix] = old_val + 1;

				if (cls_ix == 21)
					printf_s("neg_map: i=%lld j=%lld\n", i, j);
			}
	}

	// delete

	delete[] lst_t;
	delete[] lst_f;
}

void SATSolverMaster_create(SATSolverMaster * master, __int64** lst, __int64 k_parm, __int64 n_parm, __int64 chops_parm) {

	// chops

	master->chops = chops_parm;

	// calculate chops

	if (master->chops < 2)
		master->chops = 2;

	__int64 search_sz = 1;

	for (__int64 i = 0; i < master->chops; i++)
		search_sz *= 2;

	master->begin = new bool* [search_sz];
	master->end = new bool* [search_sz];

	for (__int64 chop = 0; chop < search_sz; chop++) {

		// set up first and last element to check: me->begin, me->end

		master->begin[chop] = SATSolver_create_boundary(true, master->chops, chop, n_parm);
		master->end[chop] = SATSolver_create_boundary(false, master->chops, chop, n_parm);

	}

	// populate histogram of the variables

	master->n = n_parm;
	master->k = k_parm;

	__int64* histogram = new __int64[n_parm];

	for (__int64 i = 0; i < n_parm; i++)
		histogram[i] = 0;

	for (__int64 i = 0; i < k_parm; i++)
		for (__int64 j = 0; j < 3; j++) {
			// check for existence of true TRUE_3SAT or false FALSE_3SAT
			if (lst[i][j] == FALSE_3SAT || lst[i][j] == TRUE_3SAT)
				continue;
			__int64 tmp = (lst[i][j] < 0 ? -lst[i][j] : lst[i][j]) - 2;
			__int64 cur = histogram[tmp];
			histogram[tmp] = cur + 1;
		}

	// create a sorted copy of the histogram

	__int64* histogram_srt = new __int64[n_parm];

	for (__int64 i = 0; i < n_parm; i++)
		histogram_srt[i] = histogram[i];

	MyQSort(histogram_srt, 0, n_parm - 1);

	// create a decoding based on the histogram

	master->decoding = new __int64[n_parm];
	master->encoding = new __int64[n_parm];

	for (__int64 i = 0; i < n_parm; i++) {
		__int64 count = histogram_srt[i];
		__int64 pos = 0;
		while (histogram[pos] != count)
			pos++;
		master->decoding[n_parm - 1 - i] = pos;
		master->encoding[pos] = n_parm - 1 - i;
		histogram[pos] = -count;
	}

	for (__int64 i = 0; i < k_parm; i++) {
		printf_s("%lld: ", i);
		for (int j = 0; j < 3; j++) {
			if ( lst [i][j] == FALSE_3SAT || lst [i][j] == TRUE_3SAT)
				printf_s("%lld ", lst [i][j]);
			else {
				__int64 codeword = lst[i][j] < 0 ? -lst[i][j] - 2 : lst[i][j] - 2;
				printf_s("%lld ", lst[i][j] < 0 ? -(master->encoding[codeword]) : (master->encoding[codeword]));
			}
		}
		printf_s("\n");
	}
	printf_s("\n");

	// order list of k clauses in cls_tly (clause tally) by lowest-order literal of each clause

	master->powers = new __int64[k_parm];
	for (__int64 i = 0; i < k_parm; i++)
		master->powers[i] = 0;

	for (__int64 i = 0; i < k_parm; i++) {

		/*

		__int64 l0 = lst[i][0] < 0 ? -lst[i][0] - 2 : lst[i][0] - 2;
		__int64 l1 = lst[i][1] < 0 ? -lst[i][1] - 2 : lst[i][1] - 2;
		__int64 l2 = lst[i][2] < 0 ? -lst[i][2] - 2 : lst[i][2] - 2;

		__int64 calcl0 = l0 < 0 ? 0 : master->decoding[l0];
		__int64 calcl1 = l1 < 0 ? 0 : master->decoding[l1];
		__int64 calcl2 = l2 < 0 ? 0 : master->decoding[l2];

		if (lst[i][0] != TRUE_3SAT && lst[i][0] != FALSE_3SAT && calcl0 >= calcl1 && calcl0 >= calcl2)
			master->powers[i] = lst[i][0] < 0 ? -(n_parm - 1 - calcl0) : (n_parm - 1 - calcl0);
		else if (lst[i][1] != TRUE_3SAT && lst[i][1] != FALSE_3SAT && calcl1 >= calcl0 && calcl1 >= calcl2)
			master->powers[i] = lst[i][1] < 0 ? -(n_parm - 1 - calcl1) : (n_parm - 1 - calcl1);
		else if (lst[i][2] != TRUE_3SAT && lst[i][2] != FALSE_3SAT && calcl2 >= calcl1 && calcl2 >= calcl0)
			master->powers[i] = lst[i][2] < 0 ? -(n_parm - 1 - calcl2) : (n_parm - 1 - calcl2);
		else
			master->powers[i] = 0;
			*/


		///*
		__int64 lowest = n_parm;
		__int64 lit_cur = 0;
		for (__int64 j = 0; j < 3; j++) {
			// check for true TRUE_3SAT or false FALSE_3SAT
			if (lst[i][j] == TRUE_3SAT)
				break;
			if (lst[i][j] == FALSE_3SAT)
				continue;
			__int64 ix = (lst[i][j] < 0 ? -lst[i][j] : lst[i][j]) - 2;
			if (master->encoding[ix] < lowest) {
				lowest = master->encoding[ix];
				lit_cur = lst[i][j] > 0 ? -lowest: lowest;
			}
		}

		// record the jump power of the clause at i

		master->powers[i] = lit_cur > 0 ? - (lowest) - 1 : (lowest) + 1;
		//*/

	}

	// create the map looking __int64o running tally based on literals pos_map

	master->pos_map = new __int64* [n_parm];
	master->neg_map = new __int64* [n_parm];

	// instantiate pos_map_szs and neg_map_szs

	master->pos_map_szs = new __int64[n_parm];
	master->neg_map_szs = new __int64[n_parm];

	// initialize pos_map_szs and neg_map_szs all to 0

	for (__int64 i = 0; i < n_parm; i++) {
		master->pos_map_szs[i] = 0;
		master->neg_map_szs[i] = 0;
	}

	// determine the pos_map_szs

	for (__int64 i = 0; i < n_parm; i++) {
		for (__int64 j = 0; j < k_parm; j++) {
			// skip if true TRUE_3SAT or false FALSE_3SAT
			if (lst[j][0] != FALSE_3SAT && lst[j][0] != TRUE_3SAT && lst[j][0] == -(i + 2))
				master->pos_map_szs[master->encoding[i]]++;
			if (lst[j][1] != FALSE_3SAT && lst[j][1] != TRUE_3SAT && lst[j][1] == -(i + 2))
				master->pos_map_szs[master->encoding[i]]++;
			if (lst[j][2] != FALSE_3SAT && lst[j][2] != TRUE_3SAT && lst[j][2] == -(i + 2))
				master->pos_map_szs[master->encoding[i]]++;
		}
	}

	// determine the neg_map_szs

	for (__int64 i = 0; i < n_parm; i++) {
		for (__int64 j = 0; j < k_parm; j++) {
			// skip if true TRUE_3SAT or false FALSE_3SAT
			if (lst[j][0] != FALSE_3SAT && lst[j][0] != TRUE_3SAT && lst[j][0] == (i + 2))
				master->neg_map_szs[master->encoding[i]]++;
			if (lst[j][1] != FALSE_3SAT && lst[j][1] != TRUE_3SAT && lst[j][1] == (i + 2))
				master->neg_map_szs[master->encoding[i]]++;
			if (lst[j][2] != FALSE_3SAT && lst[j][2] != TRUE_3SAT && lst[j][2] == (i + 2))
				master->neg_map_szs[master->encoding[i]]++;
		}
	}

	// instantiate pos_map and neg_map for each variable

	for (__int64 i = 0; i < n_parm; i++) {
		master->pos_map[master->encoding[i]] = new __int64[master->pos_map_szs[master->encoding[i]]];
		master->neg_map[master->encoding[i]] = new __int64[master->neg_map_szs[master->encoding[i]]];
	}

	// initialize pos_map and neg_map all to 0

	for (__int64 i = 0; i < n_parm; i++) {
		for (__int64 j = 0; j < master->pos_map_szs[master->encoding[i]]; j++)
			master->pos_map[master->encoding[i]][j] = 0;
		for (__int64 j = 0; j < master->neg_map_szs[master->encoding[i]]; j++)
			master->neg_map[master->encoding[i]][j] = 0;
	}

	// populate pos_map, neg_map
	for (__int64 i = 0; i < n_parm; i++) {

		__int64 pos_pos = 0;
		__int64 pos_neg = 0;

		for (__int64 j = 0; j < k_parm; j++) {

			for (__int64 k = 0; k < 3; k++) {

				if (lst[j][k] == TRUE_3SAT)
					break;

				if (lst[j][k] == FALSE_3SAT)
					continue;

				__int64 pos = (lst[j][k] < 0 ? -lst[j][k] : lst[j][k]) - 2;

				if (pos != i)
					continue;

				//if (j == 21)
				//	printf_s("clause 0. i = %lld", i);

				if (lst[j][k] < 0) {
					master->pos_map[master->encoding[i]][pos_pos] = j;
					pos_pos++;
				}
				else {
					master->neg_map[master->encoding[i]][pos_neg] = j;
					pos_neg++;
				}
			}

		}
	}
}

void SATSolverMaster_destroy(SATSolverMaster* master) {

	__int64 count_chops = 1;

	for (__int64 i = 0; i < master->chops; i++)
		count_chops *= 2;

	for (__int64 i = 0; i < count_chops; i++) {

		delete[] master->begin[i];
		delete[] master->end[i];

	}

	delete[] master->begin;
	delete[] master->end;

	delete[] master->decoding;
	delete[] master->encoding;

	for (__int64 i = 0; i < master->n; i++) {
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
__int64 thread_id = -1;

void thread_3SAT(__int64 tid, SATSolverMaster *master, bool * arr, __int64 ** lst, __int64 k_parm, __int64 n_parm, __int64 chop) {

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

bool SATSolver_threads(__int64** lst, __int64 k_parm, __int64 n_parm, bool ** arr) {

	//__int64 num_threads = n_parm < 50 ? 1 : std::thread::hardware_concurrency() ;
	__int64 num_threads = 1 ;

	std::thread ** threadblock = new std::thread * [num_threads];

	for (__int64 i = 0; i < num_threads; i++)
		threadblock[i] = NULL;

	bool** arrs = new bool*[num_threads];

	for (__int64 i = 0; i < num_threads; i++)
		arrs[i] = new bool[n_parm];

	// get the right number of chops- at least 2^chops

	__int64 chops = 2;
	
	if (num_threads > 4) {

		__int64 count_chops = 1;

		__int64 counter = 0;

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

	__int64 search_sz = 1;

	for (__int64 i = 0; i < master->chops; i++)
		search_sz *= 2;


	__int64 pos = 0;
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


	for (__int64 i = 0; i < num_threads; i++)
		if (solved && i != thread_id) {
			threadblock[thread_id]->join();
			delete threadblock[thread_id];
		}

	delete[] threadblock;

	if (solved)
		for (__int64 i = 0; i < n_parm; i++)
			(*arr)[i] = arrs[thread_id][i];

	// free up master resources

	SATSolverMaster_destroy(master);
	delete master;

	return solved;
}

#endif