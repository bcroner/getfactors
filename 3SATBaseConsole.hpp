// 3SATBase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include<stdio.h>

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
	arr_parm[i + 1] = arr_parm[high_parm];
	arr_parm[high_parm] = t;
	return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void MyQSort(int arr[], int low_parm, int high_parm)
{
	if (low_parm < high_parm)
	{
		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = MyQSort_partition(arr, low_parm, high_parm);

		// Separately sort elements before
		// partition and after partition
		MyQSort(arr, low_parm, pi - 1);
		MyQSort(arr, pi + 1, high_parm);
	}
}

typedef struct {

	int* decoding;		// decoding of variables
	int* cls_tly;		// running tallies of the number of literals matched in clauses
	int** pos_map;		// map of non-negated literals to clauses for tallying
	int** neg_map;		// map of negated literals to clauses for tallying
	int* pos_map_szs;	// list of sizes of each literal mapped in pos map
	int* neg_map_szs;	// list of sizes of each literal mapped in neg map
	int* powers;		// powers to jump forward by

	bool* Z;					// current position in permutation space
	int k;						// original number of clauses
	int n;						// number of variables
	int pow_jump;				// current value of jump, to be updated each cycle
	bool* begin;				// first element begin of search space
	bool* end;					// last element end of search space
} SATSolver;

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

void SATSolver_updateTF(SATSolver* me, int lit, bool target) {

	int** add_map = target ? me->pos_map : me->neg_map;
	int* add_map_szs = target ? me->pos_map_szs : me->neg_map_szs;
	int** sub_map = target ? me->neg_map : me->pos_map;
	int* sub_map_szs = target ? me->neg_map_szs : me->pos_map_szs;

	// first do the subtractions

	for (int i = 0; i < sub_map_szs[lit]; i++) {
		int clause = sub_map[lit][i];
		int new_val = me->cls_tly[clause] - 1;
		me->cls_tly[clause] = new_val;
	}

	// now do the additions

	for (int i = 0; i < add_map_szs[lit]; i++) {
		int clause = add_map[lit][i];
		int new_val = me->cls_tly[clause] + 1;
		me->cls_tly[clause] = new_val;
	}

}

/*
*
* add- add a number 2^pos_parm to Z, zeroing out all lower bits
*
*/

void SATSolver_add(SATSolver* me, int pos_parm) {

	// add 2^pos_parm to Z

	for (int i = pos_parm; i < me->n + 1; i++) {

		// if carry, continue loop, if no carry, break
		if (me->Z[i]) {
			me->Z[i] = false;
			//SATSolver_updateTF(me , i, false);
		}
		else {
			me->Z[i] = true;
			//SATSolver_updateTF(me , i, true);
			break;
		}
	}

	// zero out all lower bits of Z
	for (int j = 0; j < pos_parm; j++)
		if (me->Z[j]) {
			me->Z[j] = false;
			//SATSolver_updateTF(me , j, false);
		}

}

int SATSolver_initializePowJump(SATSolver* me) {

	// initialize return value

	int max_jump = -1;

	// check if any clauses are satisfied and find jump powers corresponding to clauses

	for (int i = 0; i < me->k; i++) {
		if (me->cls_tly[i] == 3) {
			int tmp_jump = me->powers[i];
			if (tmp_jump > max_jump)
				max_jump = tmp_jump;
		}
	}

	return max_jump;

}

bool SATSolver_GreaterThan(bool* a, bool* b, int n) {

	for (int i = n; i >= 0; i--)
		if (a && !b)
			return true;
		else if (!a && b)
			break;

	return false;

}

bool SATSolver_isSat(SATSolver* me, int arr[]) {

	me->pow_jump = SATSolver_initializePowJump(me);
	bool found_match = me->pow_jump >= 0;
	if (found_match)
		SATSolver_add(me, me->pow_jump);
	else {
		for (int i = 0; i < me->n; i++)
			arr[me->decoding[i]] = me->Z[i];

		return true;
	}

	// main loop- until end condition

	// change this to check for if me->Z greater than me->end
	while (!SATSolver_GreaterThan(me->Z, me->end, me->n)) {

		found_match = false;
		me->pow_jump = -1;

		for (int i = 0; i < me->k; i++)
			me->cls_tly[i] = 0;

		// point_map points to either the neg_map or the pos_map of SATSolver * me

		int** point_map = NULL;
		int* point_map_szs = NULL;

		for (int i = 0; i < me->n; i++) {

			// point_map points to neg_map if 0 and pos_map if 1

			if (!me->Z[me->n - i]) {
				point_map = me->neg_map;
				point_map_szs = me->neg_map_szs;
			}
			else {
				point_map = me->pos_map;
				point_map_szs = me->pos_map_szs;
			}

			for (int j = 0; j < point_map_szs[me->n - i]; j++) {
				int cls_tly_pos = point_map[me->n - i][j];
				int cur_tly_num = me->cls_tly[cls_tly_pos];
				me->cls_tly[cls_tly_pos] = cur_tly_num + 1;
				if (me->cls_tly[cls_tly_pos] == 3) {
					found_match = true;
					me->pow_jump = me->n - i;
					break;
				}
			}
			if (found_match)
				break;
		}

		if (!found_match)
			break;

		SATSolver_add(me, me->pow_jump);

	}

	if (me->Z[me->n])
		return false;

	for (int i = 0; i < me->n; i++)
		arr[me->decoding[i]] = me->Z[i];

	return true;
}

int SATSolver_pow(int base, int chop) {

	if (chop != 0)
		return (base * SATSolver_pow(base, chop - 1));
	else
		return 1;

}

bool* SATSolver_int2bool(int n_parm, int position) {

	// create the return boolean array and initialize

	bool* ret = new bool[n_parm + 1];

	for (int i = 0; i <= n_parm; i++)
		ret[i] = false;

	// for each bit position, determine true/false value

	for (int i = n_parm; i >= 0; i--) {

		int temp_size = SATSolver_pow(2, i);
		if (temp_size <= position) {
			ret[i] = true;
			position = position - temp_size;
		}

	}

	return ret;

}


/* instantiate SATSolver class with list of clauses
*
* lst: list of clauses
* l_sz: list of lengths of each clause in lst
* k_parm: number of clauses (size of lst)
* n_parm: number of variables
* chop: power of 2, chopping up search space
* pos: position in chopping up search space
*
* */
void SATSolver_create(SATSolver* me, int** lst, int k_parm, int n_parm, int chop, int pos) {

	// valcheck

	if (lst == NULL)
		return;
	if (k_parm <= 0)
		return;
	if (n_parm <= 0)
		return;

	// instantiate class member variables

	me->k = k_parm;
	me->n = n_parm;

	me->Z = new bool[n_parm + 1];

	// set up first and last element to check: me->begin, me->end

	int unit = SATSolver_pow(2, chop);
	int begin_pos = unit * pos;
	int end_pos = begin_pos + unit;

	me->begin = SATSolver_int2bool(n_parm, begin_pos);
	me->end = SATSolver_int2bool(n_parm, end_pos);

	// populate histogram of the variables

	int* histogram = new int[n_parm];

	for (int i = 0; i < n_parm; i++)
		histogram[i] = 0;

	for (int i = 0; i < k_parm; i++)
		for (int j = 0; j < 3; j++) {
			int tmp = (lst[i][j] < 0 ? -lst[i][j] : lst[i][j]) - 1;
			int cur = histogram[tmp];
			histogram[tmp] = cur + 1;
		}

	// create a sorted copy of the histogram

	int* histogram_srt = new int[n_parm];

	for (int i = 0; i < n_parm; i++)
		histogram_srt[i] = histogram[i];

	MyQSort(histogram_srt, 0, me->n - 1);

	// create a decoding based on the histogram

	me->decoding = new int[n_parm];

	for (int i = 0; i < me->n; i++) {
		int count = histogram_srt[i];
		int pos = 0;
		while (histogram[pos] != count)
			pos++;
		me->decoding[i] = pos;
		histogram[pos] = -1;
	}

	// order list of k clauses in cls_tly (clause tally) by lowest-order literal of each clause

	int* powers = (int*)malloc(sizeof(int) * me->k);
	for (int i = 0; i < me->k; i++) {
		int lowest = me->n - 1;
		for (int j = 0; j < 3; j++) {
			int lit_cur = (lst[i][j] < 0 ? -lst[i][j] : lst[i][j]) - 1;
			if (lit_cur < lowest)
				lowest = lit_cur;
		}
		powers[i] = lowest;
	}

	// create the map looking into running tally based on literals pos_map

	me->pos_map = new int* [n_parm];
	me->neg_map = new int* [n_parm];
	me->powers = new int[k_parm];

	// instantiate pos_map_szs and neg_map_szs

	me->pos_map_szs = new int[n_parm];
	me->neg_map_szs = new int[n_parm];

	// initialize pos_map_szs and neg_map_szs all to 0

	for (int i = 0; i < n_parm; i++) {
		me->pos_map_szs[i] = 0;
		me->neg_map_szs[i] = 0;
	}

	// determine the pos_map_szs

	for (int i = 0; i < me->n; i++) {
		for (int j = 0; j < k_parm; j++) {
			if (lst[j][0] == -(i + 1))
				me->pos_map_szs[i]++;
			if (lst[j][1] == -(i + 1))
				me->pos_map_szs[i]++;
			if (lst[j][2] == -(i + 1))
				me->pos_map_szs[i]++;
		}
	}

	// determine the neg_map_szs

	for (int i = 0; i < me->n; i++) {
		for (int j = 0; j < k_parm; j++) {
			if (lst[j][0] == (i + 1))
				me->neg_map_szs[i]++;
			if (lst[j][1] == (i + 1))
				me->neg_map_szs[i]++;
			if (lst[j][2] == (i + 1))
				me->neg_map_szs[i]++;
		}
	}

	// instantiate pos_map and neg_map for each variable

	for (int i = 0; i < me->n; i++) {
		me->pos_map[i] = new int[me->pos_map_szs[i]];
		me->neg_map[i] = new int[me->neg_map_szs[i]];
	}

	// initialize pos_map and neg_map all to 0

	for (int i = 0; i < me->n; i++) {
		for (int j = 0; j < me->pos_map_szs[i]; j++)
			me->pos_map[i][j] = 0;
		for (int j = 0; j < me->neg_map_szs[i]; j++)
			me->neg_map[i][j] = 0;
	}

	// for each variable in power, create an entry in cls_szs and populate pos_map, neg_map

	for (int i = me->n - 1; i >= 0; i--) {
		int pos_pos = 0;
		int pos_neg = 0;
		for (int j = 0; j < me->k; j++) {
			if (powers[j] == i) {
				for (int k = 0; k < 3; k++) {
					int pos = (lst[j][k] < 0 ? -lst[j][k] : lst[j][k]) - 1;
					me->powers[j] = i;

					// now we must invert literals within clauses

					if (lst[j][k] < 0) {
						int pos = -lst[j][k] - 1;
						me->pos_map[pos][pos_pos]++;
						pos_pos++;
					}
					else {
						int pos = lst[j][k] - 1;
						me->neg_map[pos][pos_neg]++;
						pos_neg++;
					}
				}
			}
		}
	}

	// set value of Z to begin, decoded

	for (int i = 0; i < me->n + 1; i++)
		me->Z[i] = me->begin[me->decoding[i]];

	// create the running clause tally cls_tly

	me->cls_tly = new int[k_parm];

	// initialize to all zeros

	for (int i = 0; i < k_parm; i++)
		me->cls_tly[i] = 0;

	// populate clause tally with initial begin value

	for (int i = 0; i < n_parm; i++) {
		int decoded = me->decoding[i];
		int* point_map;
		int point_map_sz;
		if (me->begin[decoded]) {
			point_map = me->pos_map[decoded];
			point_map_sz = me->pos_map_szs[i];
		}
		else {
			point_map = me->neg_map[decoded];
			point_map_sz = me->neg_map_szs[i];
		}
		int map_sz = point_map_sz;
		for (int j = 0; j < map_sz; j++) {
			int cls_ix = point_map[j];
			int old_val = me->cls_tly[j];
			me->cls_tly[cls_ix] = old_val + 1;
		}
	}
}

void SATSolver_destroy(SATSolver* me) {

	delete me->Z;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
