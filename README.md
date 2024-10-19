# getfactors

Here's an attempted constructive proof that P = NP and the Integer Factorization Problem is NP-Complete.

https://www.amazon.com/NP-3SAT-Coverage-False-Clauses-ebook/dp/B08P93KY4B?ref_=ast_author_dp

All that somebody needs to do is fix the manageIncrement function so that it takes advantage of the regular repeating patterns. Basically, anytime you recognize that a pattern of jumps repeats itself, just repeat the jump that eventually follows, taking care to ensure that no jump in the overall pattern is broken by a truth value switch. I feel that the best way to achieve this is with a stack that has the lower-order bits of Z on the bottom, and that pops the higher-order bits off the top down through the point where a Z-bit's truth value switches. And be aware that this truth value switch would normally be a part of the extension of the shorter base pattern (except for when a solution is found or the portion of the search space assigned to that thread of execution is completed). The person who implements this fix may be me one day, but for now, I'm whipped.
