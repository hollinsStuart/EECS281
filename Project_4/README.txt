We've included the test from the project specification,
spec-test.txt, along without output for all three modes.

There are several other input files: sample-ab.txt, sample-c.txt,
sample-d.txt, sample-e.txt, and sample-f.txt.
  sample-ab.txt has 10000 vertices, sample-c.txt and sample-d.txt
  each have 30, sample-e.txt has 11 vertices.

There are output files for sample-ab.txt run with MST and FASTTSP,
while samples c-e were run with all 3 modes.

The file sample-d.txt is the same as sample-c.txt, EXCEPT
that it has been shifted up and to the right by 50, putting all
vertices in Quadrant 1 of the graph.  If you get the same answers
when running samples c and d in MST mode, and sample c output is
wrong, it's because you forgot to account for transitioning from
one region to another.  When running OPTTSP, if you get sample d
right but sample c wrong, it's because you forgot that in FAST
and OPT, you DO NOT consider the border between regions.

The file sample-e.txt has 11 vertices selected from sample d;
the vertices were selected so that many fast and optimal solutions
give different output.  This test case should help with debugging
OPTTSP mode.

The file sample-e-debug-output.txt is there to help you debug
Part C (mode OPTTSP) with sample-e.txt as input.  Inside of that
file, we show you how to produce the output discussed in the video,
what the initial path was, the best path length (from part B), and
the debugging output in a large table.

Every line of the table shows the current path, permLength
(column PL), the current running cost (the black region from the
lecture slides), arm 1 and arm 2 (the blue connecting arms from
the slides), the MST cost (gray in the slides), and the total
(black + blue + gray).

If you start with the same path and the same best cost so far,
and get different results than this table, it should be easy
to identify the first line that's wrong, which value is wrong,
and then narrow down your debugging focus.

The file sample-f.txt is just like sample-e.txt, except that it
DOES have locations in all four quadrants!  If you get different
output for sample-e and sample-f for FASTTSP or OPTTSP, you know
that the problem lies in using the distance calculation from
Part A when you shouldn't.
