## Nock -> nck algorithm

This is a public domain, English language exploration of an algorithm to compress Nock into a grammar. This compressed form of Nock is known as nck, pronounced nick. 

This document is thoroughly room temperature. If it proves fruitful, I will chill it.


Nock is formally a binary tree, which is 80% of why I like it. Every cell is a node with exactly two children, and every atom may be considered a leaf. 

n-ary trees are also a product of context-free grammars, given a linear input stream. This means Nock can be compressed into such a grammar, where every cell has exactly two resolutions (left or right), and each possible atom found within the structure is one option at the terminal rule. 

Each of these rules is given a number, and we may as well count from zero. It is probably helpful to have an epsilon rule, that may match any atom, and we will call this rule 0. Rule 1 is the noun we are compressing, rule 2 is the subject and rule 3 is the formula of that noun, and so on, that is, rule 2 for a cell subject, rule 3 for a cell formula, and other rules for atomic terminations. This assumes that both the subject and formula of the Nock noun are atoms, which is good for the UR-rule as it keeps the resulting graph extremely compact. 

So, for the degenerate case of a noun that is an atom, we have rule zero, epsilon, and rule 1, the atom, and a bitstream consisting of the bit 0, meaning 'choose the leftmost option of rule 1'. Left will conventionally represent the termination of a rule with one resolution. 

This is slightly larger, rather than compressed. Don't nck atoms. I mean, it's harmless, just, don't.

The noun is therefore represented as series of left-right, 0-1 bits that traverse the graph and end in the correct atoms. This is simple nck, it generates a unique rule for each atom and never uses the Epsilon rule. It will match the Nock noun for which it was created, because it's a straightforward compression of that noun.  

So, presuming we use the same Nock noun, the binary stream needs no terminating clauses. It simply reads out until it hits terminal atoms, then backtracks to unresolved branches and continues filling them in. 

So how far do we get on one bit? All the way to the left, if that bit is zero. If it's one, we go right one, and then all the way to the left. We then backtrack one node and see if there are choices, if not (that is, if the left-most node was a cell of two atoms), we add the atom and backtrack again. When there are choices, we consume another bit, and Bob's your uncle. 

So now, instead of a binary tree which only flows down, we have a DAG and a path through it. This is straightforward stuff. 

Let's observe a property: this algorithm makes the rules in the order it finds them, but that order is not used in decompression. The numbers are just names, the order an artifact of their discovery: the names can be permuted without loss of structure. 

This means in principle we can reuse the ruleset from one Nock noun to nck another Nock noun (which I am compulsively spelling nwn). This will work, in the sense that we'll have a superset of rules that will decompress both nouns. It will not work as well as we want, because our atoms are hard coded. This means we'll have large subgraphs that differ only by a few atoms, but poor reuse of that structure, since resolution to a different atom will rebound a considerable distance up the tree. 

It's not even totally clear that we'd end up with anything but a second stack of rules on top of the first. The product of two ncked nouns would be the size of the sum of the two nouns ncked separately. Not what we want. 

Nock has no concept of a variable, at all. nck, however, does: rule 0 resolves to any atom, because it's special. We aren't using it, yet, and it can't appear in the uncompressed Nock: Hoon resolves all variables, it must, because Nock has none. 

Let's zoom out, for a second: we're looking for a way to use Nock that doesn't rely on hinting to produce jet-assisted code. To do this, one step is to put all the jet-assisted formulas at the top of the rule stack, in a way that lets us reuse the rule stack on later nouns. Ideally, the very front are the hardware-level jets, followed by the most important Hoon code, and so on, embodying the entire Hoon kernel in a single compressed ruleset that all nouns are subsequently prepended with during the nckdown stage. 

This requires some changes to our algorithm, and probably to the Hoon toolpath. 

There's no special reason Hoon should have to emit Nock, however. It can emit a Nock intermediate that allows for generic atoms,
