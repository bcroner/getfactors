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

RZN AI Automated Axiomatic Theorem Prover Provisional Patent Specification

This is a description of how an automated theorem prover operates. It can be employed to solve theorems other than those in mathematics, such as the theorem that a gun exists that meets certain criteria, such as firing 200 rounds in 2 minutes.

I present the axiom set called the RZNAI Axioms. We rely on the standard logical NAND. XNOR is an alternative, as is some combination of AND, OR, and NOT. The problem with using multiple different logical relations is you have to keep track of which ones are being utilized. The NAND axiom can be used to discover mathematics, as well as physics, chemistry, dynamics+ballistics, statics, and electronics, and everything else that can be represented with logic. How do I discover mathematics with NAND gates and a 3SAT logic solver?

The axioms are as follows:

A NAND B = C


A	B	C
0	0	1
0	1	1
1	0	1
1	1	0


(~A | ~B | ~C) & (A | C) & (B | C) (Tseytin transformation as represented by my 3SAT solver)

We accept the above relationship to be true as defined above.

The entirety of mathematics then is discoverable and definable by a series of statements in the following form:

C = A NAND B

Where C, A, and B are binary variables.

For example:

C = A NAND B
F = D NAND E
G = F NAND C
H = G NAND G
.
.
.

We also represent AND, OR, and NOT with NAND:

C = A AND B:

D = A NAND B
C = D NAND D

C = A OR B:

D = A NAND A
E = B NAND B
C = D NAND E

B = NOT A:

B = A NAND A

These are simply ways to expand other logic gates into NAND gate expressions.

We have already discovered addition and multiplication in two’s complement.

Negation is just NOT for each of the gates and then adding 1 and discarding the final carry for two’s complement.

We can define i (root (-1)) like this:

i = Negate (1)
C = i * i

Division is discoverable, too.

C/B = A:

Define C = A mul B.
A is the result.

And subtraction is simple.

C = A sub B:

D = Negate (B)
C = A add D

So, let’s prove the theorem that if 1/1 + x/1 = 2/1, then x = 1. We have the left side of the equation, where we have two instances of the number 1. We express this as a ratio of two 2-bit integers. We assign truth values to the bits to express both instances of the number 1. We also express their addition in terms of NAND expressions as described above. On the right side we have the number 2, and we express the number as the truth values that are assigned to the two bits. Now what do we do to use this theorem proving system to show that the two are equivalent? We need to show that the left system of NANDs and variables is equivalent to the right side’s variables. And this is very simple. 1/1 + x/1 results in a sum that is unknown, but is expressed as a 2-bit number, or in other words as two bits, bits A and B. The right side is two bits, C and D, which are assigned. We produce the NAND equivalents of the following:

E = A XNOR C
F = B XNOR D
G = E AND F

And we assign G the truth value TRUE.

Then we check for satisfiability. If satisfiable (which it would be), then we have proven the theorem that if 1/1 + x/1 = 2, then x = 1.

Here is the final format consisting first of the independent boolean variables followed by the tabular NAND operator cells:


0	reserved  
1	Reserved for true/false  
2	Boolean variable 0  
3	Boolean variable 1  
…	…  
n	Boolean variable n - 2  
n+1	 Cell n + 1 = X0 NAND Y0  
n+2	 Cell n + 2 = X1 NAND Y1  
n+3	 Cell n + 3 = X2 NAND Y2  
n+4	 Cell n + 4 = X3 NAND Y3  
n+5	 Cell n + 5 = X4 NAND Y4  
n+6	 Cell n + 6 = X5 NAND Y5  
…	…  
n+z	 Cell n + z = XN NAND YN  

Here, each NAND operator inversely conjoins two boolean variables, yielding a third variable that represents the cell. We force both of these variables to reference cell variables and allotted variables of lower order than the cell itself with no self-referential variables to avoid contradictions, Russell’s Paradox, and other related issues. The consistency of using a standard NAND gate every time means that it’s very easy to produce the data set and very easy to interpret the results. When otherwise using multiple types of logic gates, things get complicated and messy.

To represent physics with this axiomatic system, for example, we would encode the mathematical relationships between the objects and systems. The way to discover the solution to a physics problem would then be to develop a grammar, such as a context-free grammar, that, when supplied with the discoverable symbols and numerical values, would construct the result of the physics problem. Following is an example of such a grammar.

We wish to discover a proof that 1/1 + x/1 = 2/1 where we may have up to N different variables.

[Number] => [Dividend] [Divisor]
[Dividend] => [VARCONST]
[Divisor] => [VARCONST]
[NULL] => one bit spacer
[VARCONST] => [two’s complement signed Integer]
[VARCONST] => X1
[VARCONST] => X2
.
.
.
[VARCONST] => XN
[two’s complement signed Integer] = bit sequence
[Sum] => [Number] [Number]
[Side] = Left
[Side] = Right
[Equates] = [Side] [Side]

This grammar is capable of producing an equation having a sum, a left side, and a right side. This is the design of the mathematics we are investigating for discoveries.

Following is another example of such a grammar.

We wish to discover a gun that is capable of firing 200 rounds in 2 minutes. We need to construct a grammar that describes the gun resulting from the discovery. Following are the parts of a gun that are related together in positions that expand an anatomy: Anatomy, Barrel, Magazine, Stock, Action, Muzzle, Grip, Sight, Cylinder, Hammer, Slide, Breech, Chamber, Firing pin, Safety, Bolt, Bore, Ejector, Trigger, Trigger Guard, Receiver, Butt, Ejection port, Frame.

[Anatomy] => [Barrel] [Magazine] [Stock] [Action] [Muzzle] [Grip] [Sight] [Cylinder] [Hammer] [Slide] [Breech] [Chamber] [Firing pin] [Safety] [Bolt] [Bore] [Ejector] [Trigger] [Trigger Guard] [Receiver] [Butt] [Ejection port] [Frame]

[Barrel] => [Material] [Shape] [Grooves] [Dimensions]
[Magazine] => [Tubular]
[Magazine] => [Box]
[Magazine] => [Internal box]
[Magazine] => [Detachable box]
[Magazine] => [Casket]
[Magazine] => [Tandem]
[Magazine] => [Rotary]
[Magazine] => [Capsule]
[Magazine] => [Drum]
[Magazine] => [Saddle-drum]
[Magazine] => [Pan]
[Magazine] => [Helical]
[Magazine] => [Hopper]
[Tubular] => [T1]
[Box] => [B1]
[Internal box] => [I1]
[Detachable box] => [D1]
[Detachable box] => [Stanag]
[Casket] => [C1]
[Tandem] => [T1]
[Rotary] => [R1]
[Capsule] => [P1]
[Drum] => [U1]
[Saddle-drum] => [L1]
[Pan] => [N1]
[Helical] => [H1]
[Hopper] => [E1]
[T1] => [Magazine options]
[B1] => [Magazine options]
[I1] => [Magazine options]
[D1] => [Magazine options]
[Stanag] => [Magazine options]
[C1] => [Magazine options]
[T1] => [Magazine options]
[R1] => [Magazine options]
[P1] => [Magazine options]
[U1] => [Magazine options]
[L1] => [Magazine options]
[N1] => [Magazine options]
[H1] => [Magazine options]
[E1] => [Magazine options]
[Magazine options] => [Ammunition] [Capacity]
[Ammunition] => Hollow point
[Ammunition] => 22LR
[Ammunition] => Soft point
[Ammunition] => Remington Arms
[Ammunition] => 56x45mm NATO
[Ammunition] => Boat tail bullets
[Ammunition] => Shotgun
[Ammunition] => 9mm ammo
[Ammunition] => Ballistic Tip
[Ammunition] => Birdshot
[Ammunition] => Magnum
[Ammunition] => OTM
[Ammunition] => Rimfire
[Ammunition] => Round nose bullets
[Ammunition] => 17HMR
[Ammunition] => Creedmoor
[Ammunition] => Jacketed hollow points
[Ammunition] => Pistol
[Capacity] => INTEGER

[Stock]
[Action]
.
.
.
[Ejection port]
[Frame]


Each expansion of a given grammar element is identified with an integer unique within this grammar element. These are stored in a table for the decoding of the final design. Everything eventually expands to numerical variables. The criteria for the gun are stated and the operations relating the numbers together are determined based on knowledge from ballistics science. For example, the groove pattern of the barrel is a variable that determines how quickly the bullet rotates as it approaches its target. The speed of rotation is a trade-off, where the higher the speed of rotation, the more stable the bullet is, but the more energy that is needed to produce this rate of rotation.

The claims are as follows:

    1. The use of the NAND gate or a logical equivalent as the base axiom.
    2. The structure of the data layout with first the independent boolean variables followed by the tabular NAND operator cells.
    3. The development of a grammar to express the variable design of the final theorem which is to be proven.
