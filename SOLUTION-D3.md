We found that the implementation of this deliverable was significantly less difficult than the previous one. We only had t o introduce two new types (TipArray and TipBool) that were structurally identical to existing ones (TipRef and TipInt). The implementation of constraint collection was slightly more tricky: some care had to be taken when dealing with interesting types (an empty array literal must indeed be an array, but an array has a type parameter).

Our implementation adds two subtypes of TipCons:
TipArray - single parameter type that implements arrays
TipBool - 0-parameter type that implements booleans

We extended the existing implementations of TipCons, Substituter, and CheckAssignable to support the new SIP features. 

We also implemented the relevant methods for our new AST nodes in TypeConstraintVisitor. This is where the bulk of the work was.

We overhauled existing TIP tests for assignability and constraint collection and implemented our own tests for the new type classes. All of these files are prefixed with Sip..., and are in the relevant locations.

The process of implementation was relatively smooth, but we ran into a wild error while our tests were still incomplete--attempting to run tip with --pt would result in a segmentation fault whenever arrays were used. Running tip normally, even when --verbose=3 was set with array use, worked fine. It turned out that this issue was a result of not implementing the relevant changes in Substituter--the Unifier would attempt and fail to traverse arrays correctly. This was rectified.

Test coverage is near perfect, there is currently some unreachable code that remains from previous CheckAssignable implementation that is marked as uncovered but kept in place in case we run into unforseen issues with the new way of doing things. 