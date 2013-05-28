## Nock -> nck algorithm

This is a public domain, English language + pseudocode exploration of an algorithm to compress Nock into a grammar. This compressed form of Nock is known as nck, pronounced nick. 

This document is thoroughly room temperature. If it proves fruitful, I will chill it.


Nock is formally a binary tree, which is 80% of why I like it. Every cell is a node with up to two children, and every atom may be considered a leaf. 

n-ary trees are also a product of context-free grammars, given a linear input stream. This means Nock can be compressed into such a grammar, where every cell has exactly two resolutions (left or right), and each possible atom found within the structure is one option at the terminal rule. 

Each of these rules is given a number, and we may as well count from zero. It is probably helpful to have an epsilon rule, that may match any atom, and we will call this rule 0. Rule 1 is the noun we are compressing, rule 2 is the subject and rule 3 is the formula of that noun, and so on, that is, rule 2 for a cell subject, rule 3 for a cell formula, and other rules for atomic terminations. This assumes that both the subject and formula of the Nock noun are atoms, which is good for the UR-rule as it keeps the resulting graph extremely compact. 

So, for the degenerate case of a noun that is an atom, we have rule zero, epsilon, and rule 1, the atom, and a bitstream consisting of the bit 0, meaning 'choose the leftmost option of rule 1'. Left will conventionally represent the termination of a rule with one resolution. 

This is slightly larger, rather than compressed. Don't nck atoms. I mean, it's harmless, just, don't.

The noun is therefore represented as series of left-right, 0-1 bits that traverse the graph and end in the correct atoms. This is simple nck, it generates a unique rule for each atom and never uses the Epsilon rule. It will match the Nock noun for which it was created, because it's a straightforward compression of that noun.  

So, presuming we use the same Nock noun, the binary stream needs no terminating clauses. It simply reads out until it hits terminal atoms, then backtracks to unresolved branches and continues filling them in. 

So how far do we get on one bit? All the way to the left, if that bit is zero. If it's one, we go right one, and then all the way to the left. We then backtrack one node and see if there are choices, if not (that is, if the left-most node was a cell of two atoms), we add the atom and backtrack again. When there are choices, we consume another bit, and Bob's your uncle. 
