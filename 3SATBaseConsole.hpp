// 3SATBase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef __3SATBASECONSOLE_H__
#define __3SATBASECONSOLE_H__

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <thread>
#include <condition_variable>
#include <mutex>

#define FALSE_3SAT -1
#define TRUE_3SAT 1

typedef struct {

	__int64* decoding;		// forward decoding of variables: from Z to original input ("lst" in create)
	__int64* encoding;		// reverse decoding of variables: from original input ("lst" in create) to Z
	__int64** pos_map;		// map of non-negated literals to clauses for tallying
	__int64** neg_map;		// map of negated literals to clauses for tallying
	__int64* pos_map_szs;	// list of sizes of each literal mapped in pos map
	__int64* neg_map_szs;	// list of sizes of each literal mapped in neg map
	__int64* powers;		// powers to jump forward by
	__int64* limits;		// second power limiting second operation (which is adding to Z)
	__int64 k;				// original number of clauses
	__int64 n;				// number of variables
	__int64 chops;			// number of equal-sized partitions chopping up search space: 2^chops 
	bool** begin;			// first element begin of search space
	bool** end;				// last element end of search space

} SATSolverMaster;

typedef struct {

	SATSolverMaster* master;	// master data that can be separated out for memory space conservation in multithreading

	__int64 * cls_tly;			// running tallies of the number of literals matched in clauses

	__int64* pos_implies_arr;	// positives implies array- what is implied by the encounter of jumps of recorded values
	__int64* neg_implies_arr;	// negatives implies array- what is implied by the encounter of jumps of recorded values

	bool* Z;					// current position in permutation space
} SATSolver;


//__int64 MyQSort_partition(__int64 arr_parm[], __int64 low_parm, __int64 high_parm);
void MyQSort(__int64 arr[], __int64 low_parm, __int64 high_parm);
void SATSolver_updateTF(SATSolver* me, __int64 lit, bool target);
void SATSolver_add(SATSolver* me, __int64 cls_ix);
__int64 SATSolver_initializePowJump(SATSolver* me);
bool SATSolver_GreaterThan(bool* a, bool* b, __int64 n);
bool SATSolver_isSat(SATSolver* me, __int64 chop, bool *arr);
bool * SATSolver_bool_pow(bool* base, __int64 pow, __int64 n);
bool * SATSolver_bool_add(bool *a, bool *b, __int64 n);
bool* SATSolver_bool_prepare_end(bool* a, bool* b, __int64 n);
bool * SATSolver_bool_mul(bool *a, bool *b, __int64 n);
bool* SATSolver_int2bool(__int64 a, __int64 n_parm);
bool* SATSolver_create_boundary(bool begin, __int64 chop, __int64 offs, __int64 n);
void SATSolverMaster_create(SATSolverMaster* master, __int64** lst, __int64 k_parm, __int64 n_parm, __int64 chops_parm);
void SATSolver_create(SATSolver* me, SATSolverMaster * master, __int64** lst, __int64 k_parm, __int64 n_parm, __int64 chop);
void SATSolverMaster_destroy(SATSolverMaster* master);
void SATSolver_destroy(SATSolver* me);
void thread_3SAT(__int64 tid, SATSolverMaster* master, bool* arr, __int64** lst, __int64 k_parm, __int64 n_parm, __int64 chop);
bool SATSolver_threads(__int64** lst, __int64 k_parm, __int64 n_parm, bool **arr);

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
