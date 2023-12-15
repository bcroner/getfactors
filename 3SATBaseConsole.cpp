// 3SATBase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __3SATBASECONSOLE_C__
#define __3SATBASECONSOLE_C__

#include "3SATBaseConsole.hpp"

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

void SATSolver_updateTF(SATSolver* me, int lit, bool target) {

	int** add_map = target ? me->master->pos_map : me->master->neg_map;
	int* add_map_szs = target ? me->master->pos_map_szs : me->master->neg_map_szs;
	int** sub_map = target ? me->master->neg_map : me->master->pos_map;
	int* sub_map_szs = target ? me->master->neg_map_szs : me->master->pos_map_szs;

	// first do the subtractions

	for (int i = 0; i < sub_map_szs [lit]; i++) {
		int clause = sub_map[lit][i];
		int new_val = me->cls_tly [clause] - 1;
		me->cls_tly [clause] = new_val;
	}

	// now do the additions

	for (int i = 0; i < add_map_szs[lit]; i++) {
		int clause = add_map[lit] [i];
		int new_val = me->cls_tly [clause] + 1;
		me->cls_tly [clause] = new_val;
	}

}

/*
* 
* add- add a number 2^pos_parm to Z, zeroing out all lower bits
* 
*/

void SATSolver_add(SATSolver * me , int pos_parm) {

	// add 2^pos_parm to Z

	for (int i = pos_parm; i < me->master->n + 1; i++) {

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

	for (int i = 0; i < me->master->k; i++) {
		if (me->cls_tly[i] == 3) {
			int tmp_jump = me->master->powers [i];
			if (tmp_jump > max_jump)
				max_jump = tmp_jump;
		}
	}

	return max_jump;

}

bool SATSolver_GreaterThan(bool* a, bool* b , int n) {

	for (int i = n; i >= 0; i--)
		if (a && !b)
			return true;
		else if (!a && b)
			break;

	return false;

}

bool SATSolver_isSat(SATSolver * me , bool arr []) {

	me->pow_jump = SATSolver_initializePowJump ( me );
	bool found_match = me->pow_jump >= 0;
	if ( found_match )
		SATSolver_add(me, me->pow_jump);
	else {
		for (int i = 0; i < me->master->n; i++)
			arr[me->master->decoding [i]] =  me->Z[i];

		return true;
	}

	// main loop- until end condition

	// change this to check for if me->Z greater than me->end
	while (! SATSolver_GreaterThan (me->Z, me->end , me->master->n)) {

		found_match = false;
		me->pow_jump = -1;
		
		for (int i = 0; i < me->master->k; i++)
			me->cls_tly [i] = 0 ;

		// point_map points to either the neg_map or the pos_map of SATSolver * me

		int** point_map = NULL;
		int* point_map_szs = NULL;

		for (int i = 0; i < me->master->n; i++) {

			// point_map points to neg_map if 0 and pos_map if 1

			if (!me->Z[me->master->n - i]) {
				point_map = me->master->neg_map;
				point_map_szs = me->master->neg_map_szs;
			}
			else {
				point_map = me->master->pos_map;
				point_map_szs = me->master->pos_map_szs;
			}

			for (int j = 0; j < point_map_szs [me->master->n - i]; j++) {
				int cls_tly_pos = point_map[me->master->n - i] [j];
				int cur_tly_num = me->cls_tly [cls_tly_pos];
				me->cls_tly [cls_tly_pos] = cur_tly_num + 1;
				if (me->cls_tly [cls_tly_pos] == 3) {
					found_match = true;
					me->pow_jump = me->master->n - i;
					break;
				}
			}
			if (found_match)
				break;
		}

		if (!found_match)
			break;

		SATSolver_add(me , me->pow_jump);

	}

	if ( me->Z [me->master->n] )
		return false ;
	
	for (int i = 0; i < me->master->n; i++)
		arr[me->master->decoding [ i ]] = me->Z[i];

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

	int unit = SATSolver_pow(2, chop);
	int begin_pos = unit * pos;
	int end_pos = begin_pos + unit;

	me->begin = SATSolver_int2bool(n_parm, begin_pos);
	me->end = SATSolver_int2bool(n_parm, end_pos);

	// identify clauses having a true TRUE_3SAT value or a false FALSE_3SAT value

	int* lst_t = new int[k_parm];
	int* lst_f = new int[k_parm];

	for (int i = 0; i < k_parm; i++) {
		lst_t = 0;
		lst_f = 0;
	}

	int count_clauses_true = 0;
	int count_clauses_false = 0;
	for (int i = 0; i < k_parm; i++) {
		if (lst[i][0] == FALSE_3SAT || lst[i][1] == FALSE_3SAT || lst[i][2] == FALSE_3SAT)
			count_clauses_false++;
		if (lst[i][0] == TRUE_3SAT || lst[i][1] == TRUE_3SAT || lst[i][2] == TRUE_3SAT)
			count_clauses_true++;

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

	for (int i = 0; i < n_parm + 1; i++)
		me->Z[i] = me->begin [ me->master->decoding [ i ] ];

	// create the running clause tally cls_tly

	me->cls_tly = new int[k_parm];

	// initialize to all having 3 - non-t/f literals

	for (int i = 0; i < k_parm; i++)
		me->cls_tly[i] = lst_f[i] - lst_t[i];

	// populate clause tally with initial begin value

	for (int i = 0; i < n_parm; i++) {
		int decoded = me->master->decoding [ i ];
		int * point_map;
		int point_map_sz;
		if (me->begin[decoded]) {
			point_map = me->master->pos_map[decoded];
			point_map_sz = me->master->pos_map_szs[i];
		}
		else {
			point_map = me->master->neg_map[decoded];
			point_map_sz = me->master->neg_map_szs[i];
		}
		int map_sz = point_map_sz;
		for (int j = 0; j < map_sz; j++) {
			int cls_ix = point_map[j];
			int old_val = me->cls_tly [ j ];
			me->cls_tly [ cls_ix ] = old_val + 1;
		}
	}
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

	master->powers = (int*)malloc(sizeof(int) * k_parm);
	for (int i = 0; i < k_parm; i++) {
		int lowest = n_parm - 1;
		for (int j = 0; j < 3; j++) {
			// check for true TRUE_3SAT or false FALSE_3SAT
			if (lst[i][j] == FALSE_3SAT || lst[i][j] == TRUE_3SAT)
				continue;
			int lit_cur = (lst[i][j] < 0 ? -lst[i][j] : lst[i][j]) - 2;
			if (lit_cur < lowest)
				lowest = lit_cur;
		}
		master->powers[i] = lowest;
	}

	// create the map looking into running tally based on literals pos_map

	master->pos_map = new int* [n_parm];
	master->neg_map = new int* [n_parm];
	master->powers = new int[k_parm];

	// instantiate pos_map_szs and neg_map_szs

	master->pos_map_szs = new int[n_parm];
	master->neg_map_szs = new int[n_parm];

	// initialize pos_map_szs and neg_map_szs all to 0

	for (int i = 0; i < n_parm; i++) {
		master->pos_map_szs[i] = 0;
		master->neg_map_szs[i] = 0;
	}

	// determine the pos_map_szs

	for (int i = 0; i < n_parm; i++) {
		for (int j = 0; j < k_parm; j++) {
			// skip if true TRUE_3SAT or false FALSE_3SAT
			if ((lst[j][0] != FALSE_3SAT && lst[j][0] != TRUE_3SAT) && (lst[j][0] == -(i + 2)))
				master->pos_map_szs[i]++;
			if ((lst[j][1] != FALSE_3SAT && lst[j][1] != TRUE_3SAT) && (lst[j][1] == -(i + 2)))
				master->pos_map_szs[i]++;
			if ((lst[j][2] != FALSE_3SAT && lst[j][2] != TRUE_3SAT) && (lst[j][2] == -(i + 2)))
				master->pos_map_szs[i]++;
		}
	}

	// determine the neg_map_szs

	for (int i = 0; i < n_parm; i++) {
		for (int j = 0; j < k_parm; j++) {
			// skip if true TRUE_3SAT or false FALSE_3SAT
			if ((lst[j][0] != FALSE_3SAT && lst[j][0] != TRUE_3SAT) && (lst[j][0] == (i + 2)))
				master->neg_map_szs[i]++;
			if ((lst[j][1] != FALSE_3SAT && lst[j][1] != TRUE_3SAT) && (lst[j][1] == (i + 2)))
				master->neg_map_szs[i]++;
			if ((lst[j][2] != FALSE_3SAT && lst[j][2] != TRUE_3SAT) && (lst[j][2] == (i + 2)))
				master->neg_map_szs[i]++;
		}
	}

	// instantiate pos_map and neg_map for each variable

	for (int i = 0; i < n_parm; i++) {
		master->pos_map[i] = new int[master->pos_map_szs[i]];
		master->neg_map[i] = new int[master->neg_map_szs[i]];
	}

	// initialize pos_map and neg_map all to 3 minus non-T/F literals

	for (int i = 0; i < n_parm; i++) {
		for (int j = 0; j < master->pos_map_szs[i]; j++)
			master->pos_map[i][j] = 0;
		for (int j = 0; j < master->neg_map_szs[i]; j++)
			master->neg_map[i][j] = 0;
	}

	// for each variable in power, create an entry in cls_szs and populate pos_map, neg_map

	for (int i = n_parm - 1; i >= 0; i--) {
		int pos_pos = 0;
		int pos_neg = 0;
		for (int j = 0; j < k_parm; j++) {
			if (master->powers[j] == i) {
				for (int k = 0; k < 3; k++) {

					// check for t/f
					if (lst[j][k] == FALSE_3SAT || lst[j][k] == TRUE_3SAT)
						continue;

					int pos = (lst[j][k] < 0 ? -lst[j][k] : lst[j][k]) - 2;
					master->powers[j] = i;

					// now we must invert literals within clauses

					if (lst[j][k] < 0) {
						int pos = -lst[j][k] - 2;
						master->pos_map[pos][pos_pos]++;
						pos_pos++;
					}
					else {
						int pos = lst[j][k] - 2;
						master->neg_map[pos][pos_neg]++;
						pos_neg++;
					}
				}
			}
		}
	}
}

void SATSolverMaster_destroy(SATSolverMaster* master) {

	delete master->decoding;

	for (int i = 0; i < master->n; i++) {
		delete master->pos_map[i];
		delete master->neg_map[i];
	}
	delete master->pos_map;
	delete master->neg_map;
	delete master->pos_map_szs;
	delete master->neg_map_szs;
	delete master->powers;
}

void SATSolver_destroy(SATSolver * me) {

	delete me->cls_tly;
	delete me->Z;
	delete me->begin;
	delete me->end;

}

#endif

/*
int main()
{
	const char* satFilePath;
	const char* unsatFilePath;
	char buffer[250];

	errno_t err;

	int n;
	int k;

	int a_int;
	int b_int;
	int c_int;

	int** lst;

	int pos;

	satFilePath = "C:\\Users\\seeka\\source\\repos\\3SATByRedundantClausePath\\sat\\uf250.1065.100\\uf250-01.cnf";
	unsatFilePath = "C:\\Users\\seeka\\source\\repos\\3SATByRedundantClausePath\\unsat\\UUF250.1065.100\\uuf250-01.cnf";

	FILE* myFile;

	lst = NULL;
	myFile = NULL;
	pos = 0;

	err = fopen_s(&myFile, unsatFilePath, "r");

	if (myFile == NULL) {
		printf("problem opening file\n");
		return 1;
	}

	// check if header not included

	bool has_header = false;
	n = 0;
	k = 0;

	// if no header line, count the n and k values from the file

	while (fgets(buffer, 250, myFile)) {

		if (buffer[0] == 'c')
			continue;
		else if (buffer[0] == 'p') {
			has_header = true;
			break;
		}
		else if (buffer[0] == '0' || buffer[0] == '%')
			break;
		else {
			err = sscanf_s(buffer, "%d %d %d 0\s", &a_int, &b_int, &c_int);
			k++;
			int temp_a = (a_int < 0 ? -a_int : a_int);
			int temp_b = (b_int < 0 ? -b_int : b_int);
			int temp_c = (c_int < 0 ? -c_int : c_int);
			if (temp_a > n)
				n = temp_a;
			if (temp_b > n)
				n = temp_b;
			if (temp_c > n)
				n = temp_c;
		}
	}

	// if no header, instantiate a, b, c with size of extracted k value

	if (!has_header) {

		printf("n: %d\n", n);
		printf("k: %d\n", k);

		lst = new int* [k];
		for (int i = 0; i < k; i++)
			lst[i] = new int[3];
	}

	// reset to beginning of file

	fseek(myFile, 0, SEEK_SET);

	// read in file

	while (fgets(buffer, 250, myFile)) {

		//printf("%c\n", buffer[0]);

		if (buffer[0] == 'c')
			continue;
		else if (buffer[0] == 'p') {
			err = sscanf_s(buffer, "p cnf %d %d\n", &n, &k);
			printf("n: %d\n", n);
			printf("k: %d\n", k);

			lst = new int* [k];
			for (int i = 0; i < k; i++)
				lst[i] = new int[3];
		}
		else if (buffer[0] == '0' || buffer[0] == '%') {
			break;
		}
		else {

			if (lst == NULL)
				return 2;

			err = sscanf_s(buffer, "%d %d %d 0\s", &a_int, &b_int, &c_int);

			//printf("%d %d %d\n", a_int, b_int, c_int);

			if (pos < k) {

				lst[pos][0] = a_int;
				lst[pos][1] = b_int;
				lst[pos][2] = c_int;

			}
			pos++;

		}

	}

	fclose(myFile);

	int* arr = new int[n];

	SATSolver* me = new SATSolver();
	SATSolver_create(me , lst, k, n, n, 0);
	bool result = SATSolver_isSat(me, arr);
	
	printf("Satisfiable: ");
	printf(result ? "true" : "false");
	printf("\n");

	if (result)
		for (int i = 0; i < n; i++)
			printf(" %d", arr[i]);
	printf("\n");

	return 0;
}

*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
