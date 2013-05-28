# Nock -> nck algorithm

This is a public domain, English language exploration of an algorithm to compress Nock into a grammar. This compressed form of Nock is known as nck, pronounced nick. 

This document is thoroughly room temperature. If it proves fruitful, I will chill it.


Nock is formally a binary tree, which is 80% of why I like it. Every cell is a node with exactly two children, and every atom may be considered a leaf. 

n-ary trees are also a product of context-free grammars, given a linear input stream. This means Nock can be compressed into such a grammar, where every cell has exactly two resolutions (left or right), and each possible atom found within the structure is the sole option at a single terminal rule. 

Each of these rules is given a number, and we may as well count from zero. It is probably helpful to have an epsilon rule, that may match any atom, and we will call this rule 0. Rule 1 is the noun we are compressing, rule 2 is the subject and rule 3 is the formula of that noun, and so on, that is, rule 2 for a cell subject, rule 3 for a cell formula, and other rules for atomic terminations. This assumes that both the subject and formula of the Nock noun are atoms, which is good for the UR-rule as it keeps the resulting graph extremely compact. 

So, for the degenerate case of a noun that is an atom, we have rule zero, epsilon, and rule 1, the atom, and a bitstream consisting of the bit 0, meaning 'choose the leftmost option of rule 1'. Left will conventionally represent the termination of a rule with one resolution. 

This is slightly larger, rather than compressed. Don't nck atoms. I mean, it's harmless, just, don't.

The noun is therefore represented as series of left-right, 0-1 bits that traverse the graph and end in the correct atoms. This is simple nck, it generates a unique rule for each atom and never uses the Epsilon rule. It will match the Nock noun for which it was created, because it's a straightforward compression of that noun.  

So, presuming we use the same Nock noun, the binary stream needs no terminating clauses. It simply reads out until it hits terminal atoms, then backtracks to unresolved branches and continues filling them in. 

So how far do we get on one bit? Each bit in simple nck will get us back a single noun. These are given back to us depth first, left-to-right, that is, this is the order that the Nock tree is reconstituted in. If we were generating ASCII we would make left brackets when we reach cells, atom strings when we reach atoms, and right brackets upon the final backtrack out of a cell rule. 

So now, instead of a binary tree which only flows down, we have a DAG and a path through it. This is straightforward stuff. 

Let's observe a property: this algorithm makes the rules in the order it finds them, but that order is not used in decompression. The numbers are just names, the order an artifact of their discovery: the names can be permuted without loss of structure. 

This means in principle we can reuse the ruleset from one Nock noun to nck another Nock noun (which I am compulsively spelling nwn). This will work, in the sense that we'll have a superset of rules that will decompress both nouns. It will not work as well as we want, because our atoms are hard coded. This means we'll have large subgraphs that differ only by a few atoms, but poor reuse of that structure, since resolution to a different atom will rebound a considerable distance up the tree. 

It's not even totally clear that we'd end up with anything but a second stack of rules on top of the first. The product of two ncked nouns would be the size of the sum of the two nouns ncked separately. Not what we want. 

Nock has no concept of a variable, at all. nck, however, does: rule 0 resolves to any atom, because it's special. We aren't using it, yet, and it can't appear in the uncompressed Nock: Hoon resolves all variables, it must, because Nock has none. 

Let's zoom out, for a second: we're looking for a way to use Nock that doesn't rely on hinting to produce jet-assisted code. To do this, one step is to put all the jet-assisted formulas at the top of the rule stack, in a way that lets us reuse the rule stack on later nouns. Ideally, the very front are the hardware-level jets, followed by the most important Hoon code, and so on, embodying the entire Hoon kernel in a single compressed ruleset that all nouns are subsequently prepended with during the nckdown stage. 

This requires some changes to our algorithm, and probably to the Hoon toolpath. 

##Nockdown

There's no special reason Hoon should have to emit Nock directly under all circumstances. For simplicity, I'll pretend Hoon emits an ASCII Nock file, that is then compressed into rules and a binary stream. We've intentionally avoided talking about rule encoding, but it ain't hard. 

What we then add is a placeholder character, call it @ for atom, that can match to any atom. Ordinary Hoon never emits this symbol, it is relegated to a special kind of definition that implies a call for jet assistance. It will still be possible to late-bind a rule in this fashion, but it's bad practice if you're not building a rule header. Hoon doesn't need variables; Nockdown is the wrong place to add them, in general. 

When the nck compressor hits an @, it 'throws' a rule. This means it gives the rule a high number, one high enough that it won't interfere with the header you're generating. This is why it's a bad idea to go strewing @s willy-nilly into your code base: throwing is potentially expensive if you're not doing it in early rules.

What you end up with is a deterministic header containing all the formula structures you wanted, with a single rule number that matches the start of each formula. You line them up in order on the left of the rule tree, with the formula structures off to the right, where you don't have to look at them if you don't want to. All the @s are gone, each one has been replaced with a rule that resolves to 0/epsilon, and all of those rules are above the header rules. There are ways to do this compactly, this is just a sketch. 

When you pass another Nock noun through the rules, you eliminate every variable in formulas that are reached. Here's how, minus confusing optimizations. 

We feed the noun in by attempting to go left, which is equivalent to checking if each structure that we've pre-loaded is the same as the first formula of the noun. If we find it, there will be rules that resolve to Epsilon, meaning any atom is ok.

If we reach an Epsilon, it's on a throw-rule, which means we're out of the part of the header that we don't want to change. So we add the atom in question as a resolution of the rule. There's some late-binding we have to do here, because until we're done compressing the Nock noun, we don't know how many options there will be. Conceivably it's a lot, but once the Nock noun is fully compressed, it will be a finite number of atoms. At that point, we know how many bits are needed to resolve the terminal rule, and we remove the Epsilon from the terminal rule. We then encode the final atom using only the number of bits needed, with the next bit after that a backtrack. 

Here's our last use of Rule zero: it gives us an unambigous end to the bit stream. The left option from Rule 1 is Rule 0, so if we backtrack all the way back to Rule 1 and go left, we exit, since we should never match rule 0 during execution or decompression. This is good because a bitstream can contain padding on the end to fill out the word of the target architecture; if that padding is all zeros, the noun will exit correctly. 

This modifies our earlier formula: Rule 1 is the egress, resolving to Rule 0 or Rule 2. Rule 2 is the noun in question, with all the precompiled header rules on the left and the rest of the Nock on the right. 

That means that every time you are directed left on rule 2, you are in jet land, and you can cheat as much as you want, matching substrings willy-nilly, passing variables around, calculating swiftly and returning to ground. When you go right on Rule 2, you're in Nockville, execute accordingly. 

Nockdown is a format where left moves on Rule 2 are compressed into a format useful for the Nock interpreter, whereas right moves on Rule 2 are completely unrolled into bog-standard binary Nock. This is beyond the scope of this document and well past the point where it's worth being specific, without either getting some feedback from @cgyarvin or forking off.

