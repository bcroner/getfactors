# getfactors

Here's a constructive proof that P = NP and the Integer Factorization Problem is NP-Complete.

RZN AI 3SAT De-Exponentializer Provisional Patent

In this document I discuss how a logic solver operates.

The goal of a logic satisfiability solver is to take a logic expression and determine the truth values to assign to the boolean variables that results in the entire logic expression to evaluate to TRUE. In terms of logic satisfiability, any instance can be represented in the 3CNF format (3-conjunctive normal form). Problems in this form are known as 3SAT problems (3-satisfiability). In a 3CNF clause, we have three literals that are disjoined together (logical ORed together). A literal is any boolean variable that optionally can be inverted (logical NOT). All the clauses in the 3SAT instance are conjoined (ANDed together).

We note that a clause evaluates to FALSE in exactly one of the 8 possible truth value assignments, and that is when each of the literals evaluates to FALSE. These are easy to find. We also note that in the problem with K clauses and N boolean variables, we can form N-bit numbers where the order of a bit can be assigned to a specific one of the N instance variables. There we would have 2^N different possibilities. If you can travel across the search space of all the 2^N numbers in order from lowest to highest, and every single one of these N-bit numbers has at least one 3SAT instance clause’s set of three bit values in it resulting in that clause evaluating to FALSE, then that instance is not satisfiable. If, however, one or more of these N-bit numbers does not contain bit values that result in a clause evaluating to FALSE, then the instance is satisfiable and one of the satisfying truth value assignments is the N-bit number that was located having no clauses evaluating to FALSE. The order of the clause is determined by the lowest order among the three bits within it.

We have an N-bit number Z that starts at the lowest possible within a section of the search space that is assigned to this particular thread of execution. We (optionally) initialize a running tally of how many literals within each clause evaluates to FALSE based on the initial value of this lowest starting N-bit number. This step simply improves efficiency so we don’t have to keep counting out every single clause that may evaluate to FALSE. We wish to locate the highest-order bit that matches a clause that evaluates to FALSE. We locate any clauses which do, and we find the highest-order bit like this possible. We take Z and flip that bit. This creates a new Z value, and we update the running tally with the changed values of Z. When a bit value in the number Z flips from TRUE to FALSE, we ensure that the next time we get a new bit corresponding to a clause that evaluates to FALSE, its order is higher than the order of this bit which flipped from TRUE to FALSE. This ensures that Z numbers keep getting larger.

The claims:

1.	We store the bit order value corresponding to the clause that evaluates to FALSE having the bit switch from TRUE to FALSE.
2.	We impose a criterion that the next bit value from a clause evaluating to FALSE be of higher order than the stored value.
