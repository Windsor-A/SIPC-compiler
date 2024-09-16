So far this seemed the easiest deliverable. Implementation-wise it was easy to shift existing functionality to handle the new language elements--we started with the new binary expressions, finished off the boolean behavior, implemented arrays, and then implemented the rest of the elements in roughly alphabetical order. 

System tests were written ahead of time in a first for our project, and language features were tested on them while new ones were developed. 

Nothing was remarkably difficult, but llvm types were tricky (specifically, the conversions between them were a bit of a headache). It was fun to see the functionality still work when converted to *optimized* assembly, since a few of the hand tests were all constexpr, so for some of the array tests the array would be almost entirely optimized out. 

I would like to know how to implement a iterator-style for of references, so that e.g.

  for (y : x)  y = 1;

would set an array to all 1s. I think I have an OK idea of how to do this, but it was too much to try to implement this this time.

I look forward to the next step.
