// 3SATBase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __3SATBASECONSOLE_H__
#define __3SATBASECONSOLE_H__

#include <iostream>
#include <cmath>
#include<stdio.h>

#define FALSE_3SAT -1
#define TRUE_3SAT 1

typedef struct {

	int* decoding;		// decoding of variables
	int** pos_map;		// map of non-negated literals to clauses for tallying
	int** neg_map;		// map of negated literals to clauses for tallying
	int* pos_map_szs;	// list of sizes of each literal mapped in pos map
	int* neg_map_szs;	// list of sizes of each literal mapped in neg map
	int* powers;		// powers to jump forward by

} SATSolverMaster;

typedef struct {

	SATSolverMaster* master;	// master data that can be separated out for memory space conservation in multithreading

	int* cls_tly;				// running tallies of the number of literals matched in clauses

	bool* Z;					// current position in permutation space
	int k;						// original number of clauses
	int n;						// number of variables
	int pow_jump;				// current value of jump, to be updated each cycle
	bool* begin;				// first element begin of search space
	bool* end;					// last element end of search space
} SATSolver;


int MyQSort_partition(int arr_parm[], int low_parm, int high_parm);
void MyQSort(int arr[], int low_parm, int high_parm);
void SATSolver_updateTF(SATSolver* me, int lit, bool target);
void SATSolver_add(SATSolver* me, int pos_parm);
int SATSolver_initializePowJump(SATSolver* me);
bool SATSolver_GreaterThan(bool* a, bool* b, int n);
bool SATSolver_isSat(SATSolver* me, bool arr[]);
int SATSolver_pow(int base, int chop);
bool* SATSolver_int2bool(int n_parm, int position);
void SATSolverMaster_create(SATSolverMaster* master, int** lst, int k_parm, int n_parm);
void SATSolver_create(SATSolver* me, SATSolverMaster * master, int** lst, int k_parm, int n_parm, int chop, int pos);
void SATSolver_destroy(SATSolver* me);

#endif

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
