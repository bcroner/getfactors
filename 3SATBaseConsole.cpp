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

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void MyQSort(int arr [] , int low_parm, int high_parm)
{
	if (low_parm < high_parm)
	{
		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = MyQSort_partition(arr, low_parm, high_parm);

		// Separately sort elements before
		// partition and after partition
		MyQSort(arr , low_parm, pi - 1);
		MyQSort(arr , pi + 1, high_parm);
	}
}

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

	int** add_map = target ? me->master->pos_map : me->master->neg_map;
	int* add_map_szs = target ? me->master->pos_map_szs : me->master->neg_map_szs;
	int** sub_map = target ? me->master->neg_map : me->master->pos_map;
	int* sub_map_szs = target ? me->master->neg_map_szs : me->master->pos_map_szs;

	// first do the subtractions

	int pow = me->master->n - zpos;

	for (int i = 0; i < sub_map_szs [zpos]; i++) {
		int clause = sub_map[zpos][i];
		int old_val = me->cls_tly[clause];
		me->cls_tly[clause] = old_val - 1;
		if (old_val == 3) {
			bool deleted = false;
			// break up implies_ctx
			cls_lst** implies_ctx = me->master->powers[clause] > 0 ? me->pos_imp_ctx : me->neg_imp_ctx;
			cls_lst* ptr = implies_ctx[pow];
			while (ptr->next != NULL && ptr->next->cls_id != clause)
				ptr = ptr->next;
			if (ptr->next != NULL) {
				cls_lst* dump = ptr->next;
				ptr->next = ptr->next->next;
				delete dump;
				deleted = true;
			}
			// update implies_arr
			if (deleted && implies_ctx[pow]->next == NULL)
				me->implies_arr[pow] = me->master->powers[clause] > 0 ? pow : -pow;
		}
	}

	// now do the additions

	for (int i = 0; i < add_map_szs[zpos]; i++) {
		int clause = add_map[zpos] [i];
		int new_val = me->cls_tly [clause] + 1;
		me->cls_tly[clause] = new_val;
		if (new_val == 3) {
			// build up implies_ctx
			cls_lst** implies_ctx = me->master->powers[clause] > 0 ? me->pos_imp_ctx : me->neg_imp_ctx;
			cls_lst* ptr = implies_ctx[pow];
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new cls_lst();
			ptr->next->cls_id = clause;
			ptr->next->next = NULL;
		}
	}
}

/*
* 
* add- add a number 2^pos_parm to Z, zeroing out all lower bits
* 
*/

void SATSolver_add(SATSolver * me , int pos_parm) {

	// add 2^pos_parm to Z

	int pos = pos_parm < 0 ? -pos_parm : pos_parm;

	for (int i = me->master->n - pos; i >= 0; i--) {

		// if carry, continue loop, if no carry, break
		if (me->Z[i]) {
			me->Z[i] = false;
			SATSolver_updateTF(me , i, false);
		}
		else {
			me->Z[i] = true;
			SATSolver_updateTF(me , i, true);
			break;
		}
	}
	/*
	// zero out all lower bits of Z
	for (int j = me->master->n - pos + 1; j <= me->master->n ; j++)
		if (me->Z[j]) {
			me->Z[j] = false;
			SATSolver_updateTF(me , j, false);
		}
	*/
}

__int64 SATSolver_initializePowJump(SATSolver* me) {

	// initialize return value

	__int64 max_jump = -me->master->n - 1;

	// check if any clauses are satisfied and find jump powers corresponding to clauses

	for (int i = 0; i < me->master->k; i++)
		if (me->cls_tly[i] >= 3 && me->master->powers[i] > max_jump)
			max_jump = me->master->powers[i] < 0 ? -me->master->powers[i] - 1 : me->master->powers[i] - 1;

	return max_jump;

}

bool SATSolver_GreaterThanOrEqual(bool* a, bool* b , int n) {

	for (int i = 0; i <= n; i++)
		if (a[i] && !b[i])
			return true;
		else if (!a[i] && b[i])
			return false;

	return true;

}

bool SATSolver_isSat(SATSolver * me , bool *arr) {

	// main loop- until end condition

	do {

		me->pow_jump = SATSolver_initializePowJump(me);
		SATSolver_add(me, me->pow_jump);

	} while (!SATSolver_GreaterThanOrEqual(me->Z, me->end, me->master->n));

	if (SATSolver_GreaterThanOrEqual(me->Z, me->end, me->master->n))
		return false ;
	
	for (int i = 0; i < me->master->n; i++)
		arr[i] = me->Z[me->master->decoding[i]];

	return true;
}

bool * SATSolver_bool_pow(bool* base, __int64 pow, int n) {

	bool* prod = new bool[n];
	for (int i = 0; i < n - 1; i++)
		prod[i] = false;
	prod[n - 1] = true;

	for (int i = 0; i < pow; i++) {
		bool* dump = prod;
		prod = SATSolver_bool_mul(prod, base, n);
		delete[] dump;
	}

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

		bool sum_temp = (!a[n - 1 - i] && b[n - 1 - i]) || (a[n - 1 - i] && !b[n - 1 - i]);
		ret[n - 1 - i] = (!sum_temp && carry) || (sum_temp && !carry);
		carry = (a[n - 1 - i] && b[n - 1 - i]) || (a[n - 1 - i] && carry) || (b[n - 1 - i] && carry);

	}

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
			ret[n_parm - 1 - i] = true;
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
	me->Z = new bool [n_parm + 1];

	// set up first and last element to check: me->begin, me->end

	bool * two = SATSolver_int2bool(2, n_parm + 1);
	bool * unit = SATSolver_bool_pow(two, n_parm - chop, n_parm + 1);
	bool * offs = SATSolver_int2bool(pos, n_parm + 1);
	me->begin = SATSolver_bool_mul ( unit, offs, n_parm + 1) ;
	me->end = SATSolver_bool_add ( me->begin, unit, n_parm + 1);

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

	me->cls_tly = new __int8[k_parm];

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
		int decoded = me->master->decoding [ i ];
		if (me->begin[decoded])
			for (int j = 0; j < me->master->pos_map_szs[decoded]; j++) {
				int cls_ix = me->master->pos_map[decoded][j];
				int old_val = me->cls_tly[cls_ix];
				if (old_val > 3)
					old_val = old_val;
				me->cls_tly[cls_ix] = old_val + 1;
			}
		else
			for (int j = 0; j < me->master->neg_map_szs[decoded]; j++) {
				int cls_ix = me->master->neg_map[decoded][j];
				int old_val = me->cls_tly[cls_ix];
				if (old_val > 3)
					old_val = old_val;
				me->cls_tly[cls_ix] = old_val + 1;
			}
	}

	// initialize implies array with self-referential jump power implications

	//me->implies_arr = new int[n_parm];
	//for (int i = 0; i < n_parm; i++)
	//	me->implies_arr[i] = -(i+1);

	// initialize context with dummy heads

	me->pos_imp_ctx = new cls_lst * [n_parm];
	me->neg_imp_ctx = new cls_lst * [n_parm];
	for (int i = 0; i < n_parm; i++) {
		me->pos_imp_ctx[i] = new cls_lst();
		me->pos_imp_ctx[i]->cls_id = -1;
		me->pos_imp_ctx[i]->next = NULL;
		me->neg_imp_ctx[i] = new cls_lst();
		me->neg_imp_ctx[i]->cls_id = -1;
		me->neg_imp_ctx[i]->next = NULL;
	}

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

	// create the pow_cls list initialized with dummy heads

	master->pow_cls = new cls_lst * [n_parm];

	for (int i = 0; i < n_parm; i++) {
		master->pow_cls[i] = new cls_lst();
		master->pow_cls[i]->cls_id = -1;
		master->pow_cls[i]->next = NULL;
	}

	// order list of k clauses in cls_tly (clause tally) by lowest-order literal of each clause

	master->powers = new int[k_parm];

	for (int i = 0; i < k_parm; i++) {
		int lowest = -1;
		int lit_cur = 0;
		for (int j = 0; j < 3; j++) {
			// check for true TRUE_3SAT or false FALSE_3SAT
			if (lst[i][j] == FALSE_3SAT || lst[i][j] == TRUE_3SAT)
				continue;
			int ix = (lst[i][j] < 0 ? -lst[i][j] : lst[i][j]) - 2;
			if (master->decoding[ix] > lowest) {
				lowest = master->decoding[ix];
				lit_cur = lst[i][j] < 0 ? -lowest - 1 : lowest + 1;
			}
		}

		// record the jump power of the clause at i

		master->powers[i] = lit_cur < 0 ? - (n_parm - 1 - lowest) - 1 : (n_parm - 1 - lowest) + 1;

		// record the reverse jump power lookup

		cls_lst* ptr = master->pow_cls[n_parm - 1 - lowest];
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new cls_lst();
		ptr->next->cls_id = i;
		ptr->next->next = NULL;
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
			if ((lst[j][0] != FALSE_3SAT && lst[j][0] != TRUE_3SAT) && (lst[j][0] == -(i + 2)))
				master->pos_map_szs[master->decoding[i]]++;
			if ((lst[j][1] != FALSE_3SAT && lst[j][1] != TRUE_3SAT) && (lst[j][1] == -(i + 2)))
				master->pos_map_szs[master->decoding[i]]++;
			if ((lst[j][2] != FALSE_3SAT && lst[j][2] != TRUE_3SAT) && (lst[j][2] == -(i + 2)))
				master->pos_map_szs[master->decoding[i]]++;
		}
	}

	// determine the neg_map_szs

	for (int i = 0; i < n_parm; i++) {
		for (int j = 0; j < k_parm; j++) {
			// skip if true TRUE_3SAT or false FALSE_3SAT
			if ((lst[j][0] != FALSE_3SAT && lst[j][0] != TRUE_3SAT) && (lst[j][0] == (i + 2)))
				master->neg_map_szs[master->decoding[i]]++;
			if ((lst[j][1] != FALSE_3SAT && lst[j][1] != TRUE_3SAT) && (lst[j][1] == (i + 2)))
				master->neg_map_szs[master->decoding[i]]++;
			if ((lst[j][2] != FALSE_3SAT && lst[j][2] != TRUE_3SAT) && (lst[j][2] == (i + 2)))
				master->neg_map_szs[master->decoding[i]]++;
		}
	}

	// instantiate pos_map and neg_map for each variable

	for (int i = 0; i < n_parm; i++) {
		master->pos_map[master->decoding[i]] = new int[master->pos_map_szs[master->decoding[i]]];
		master->neg_map[master->decoding[i]] = new int[master->neg_map_szs[master->decoding[i]]];
	}

	// initialize pos_map and neg_map all to 3 minus non-T/F literals

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

				if (lst[j][k] == FALSE_3SAT || lst[j][k] == TRUE_3SAT)
					continue;

				int pos = (lst[j][k] < 0 ? -lst[j][k] : lst[j][k]) - 2;

				if (pos != i)
					continue;

				if (lst[j][k] < 0) {
					master->pos_map[master->decoding[pos]][pos_pos] = j;
					pos_pos++;
				}
				else {
					master->neg_map[master->decoding[pos]][pos_neg] = j;
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

	for (int i = 0; i < master->n; i++) {
		cls_lst* ptr = master->pow_cls[i]->next;
		while (ptr != NULL) {
			cls_lst* dump = ptr;
			ptr = ptr->next;
			delete dump;
		}
		delete master->pow_cls[i];
	}

	delete [] master->pow_cls;

	delete [] master->pos_map;
	delete [] master->neg_map;
	delete [] master->pos_map_szs;
	delete [] master->neg_map_szs;
	delete [] master->powers;
}

void SATSolver_destroy(SATSolver * me) {

	//delete [] me->implies_arr;
	
	for (int i = 0; i < me->master->n; i++) {

		cls_lst* ptr = me->pos_imp_ctx[i]->next;
		while (ptr != NULL) {

			cls_lst* dump = ptr;
			ptr = ptr->next;
			delete dump;

		}
		delete me->pos_imp_ctx[i];

		ptr = me->neg_imp_ctx[i]->next;
		while (ptr != NULL) {

			cls_lst* dump = ptr;
			ptr = ptr->next;
			delete dump;

		}
		delete me->neg_imp_ctx[i];
	}

	delete [] me->pos_imp_ctx;
	delete[] me->neg_imp_ctx;

	delete [] me->cls_tly;
	delete [] me->Z;
	delete [] me->begin;
	delete [] me->end;

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

	//int chop = n_parm < 50 ? 0 : 16;
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

	// free up master resources

	SATSolverMaster_destroy(master);
	delete master;

	for (int i = 0; i < num_threads; i++)
		if (solved && i != thread_id) {
			threadblock[thread_id]->join();
			delete threadblock[thread_id];
		}

	delete[] threadblock;

	if (solved)
		for (int i = 0; i < n_parm; i++)
			(*arr)[i] = arrs[thread_id][i];

	return solved;
}

#endif