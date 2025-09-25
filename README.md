# getfactors

Here's an attempted constructive proof that P = NP and the Integer Factorization Problem is NP-Complete.

I made use of Satlib: Holger H. Hoos and Thomas Stützle: SATLIB: An Online Resource for Research on SAT. In: I.P.Gent, H.v.Maaren, T.Walsh, editors, SAT 2000, pp.283-292, IOS Press, 2000. SATLIB is available online at www.satlib.org.

Not only do I introduce a new class of world-best 3SAT logic solvers that uses my exploit, I prove the Integer Factorization Problem is NP-Complete by a constructive reduction to 3SAT.

The function that sets up the integer factorization operation is nat_get_factors (...). It uses Tseytin Transformations to represent the factoring operation as a 3SAT instance, which it then solves and interprets the results.

The exploit used by the logic solver is to notice that a 3CNF tuple has up to 3 optionally-inverted boolean variables, and you can order them so that each variable has a position in an n-bit whole number we'll call Z.
This assigns an order to the bits so that each is a unique power of two. Select the lowest-order variable in a 3CNF tuple that evaluates to false according to the truth value assignments in the current value of Z.
This provides the power of 2 that you jump forward through the search space represented by the permutations of Z. Now, instead of checking every single permutation of n bits in the number Z in the worst case,
we skip over arbitrary swaths of the search space with each jump of some arbitrary power of 2. We call this 3SAT by Coverage of False Clauses, where we check if the entire search space is covered by clauses evaluating to false.

An additional exploit is utilized. Observe that when a jump of -x is immediately followed by a jump of x or when a jump of x is immediately followed by a jump of -x, they together cover for all possibilities up to the lower
of the two corresponding clauses' middle-magnitude numbers. In the source code, I refer to the lowest-magnitude number as the jump and the middle-magnitude number as the limit, and I store the limits corresponding to
selected jumps in the implies arrays, with the negative implies array representing jumps where the jump test produces a jump literal of a given magnitude going from false to true, and the positive implies array is the same
but for going from true to false. I obtained a provisional patent on this part of the process.

A third exploit involves the highest-order member of a 3CNF clause which I refer to as the base in the source code. If you are looking for a jump in the InitializePowJump () function and you find a clause that compares with the
previously chosen clause by (-x, x) or (x, -x) (meaning the literals are inverses of each other) in the jump values and (-y, y) or (y, -y) (meaning, again, the literals are inverses of each other) in the limit values,
you may replace the jump you take with the lower order of the bases of the two clauses.

This source code is not 100% debugged, as the nat_get_factors function returns erroneous results. But the core is debugged, consisting of the SAT solver and the addition and multiplication functions nat_add and nat_mul.

Update 09-10-2025: As you can tell, I've been tinkering with this. I feel like there are two main bugs to fix, and then I'm factoring large integers. Exciting times.

To get this to build, remove btc3sat.cpp and btc3sat.hpp from the project.

Your mother. (not you, Brent)
