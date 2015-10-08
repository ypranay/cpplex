# Introduction #
C++lex is a C++ implementation of the simplex algorithm which doesn't rely on dependencies other than the C++ standard library.

# Class library and solver #
The algorithm is implemented as class library, however the source code also includes a solver executable which is able to load formatted problems in the form:

```
[METADATA]

name Simple problem
vars 3

[VARIABLES]

0    x1  4
-2   x2  inf
-3   x3  232

[CONSTRAINTS]

1 3 4 > 0
0 0 1 < 1
1 2 0 < 2

[OBJECTIVE]

maximize 1 3 1
```

Where a constraint of the form:

```
1 3 4 > 0
```

Actually means that we want `x1 + 3*x2 + 4*x3` to be greater than zero, and an objective function of the form:

```
maximize 1 3 1
```

Tries to maximize the expression: `x1 + 3*x2 + x3`. **The `minimize` version is also available.**

While the class library outputs a solution std::vector which can be used within your code, the solver outputs all the details about the resolution, e.g. (for the problem above):

```
==============
Simple problem
==============

Number of regular constraints:   7
1	0	0	<=	 4
0	1	0	>=	-2
0	0	1	>=	-3
0	0	1	<=	 232
1	3	4	>=	 0
0	0	1	<=	 1
1	2	0	<=	 2

Number of non-negativity constraints: 1
1	0	0	non-negative 

Objective function:
max ( 1  3  1  ) * x 

Generating problem in standard form ... done.
Generating artificial problem ... done.
Solving artificial problem ...
Optimal found at step 4.
Done.
Base is clear about artificial variables, proceed ...
Solving problem ...
Optimal found at step 5.
Done.
Processing standard form solution ...
Done.

Optimal solution is:
x1:			        0
x2:			        1
x3:			        1

Solution value/cost:		4
Dual problem value:		4
```

A verbose/non verbose preprocessing constant allows to reduce the output. **Please note that the problem file facility has been implemented for debugging reasons and without any care to data sanitization or so (i.e. will throw exceptions if the file is non well-formed)**.

# Build #
The source code includes a Makefile which allows you to build the solver program under unix systems. A Visual Studio solution and related projects to build the libraries and the solver program are also available on the repository.

# License #
The software is provided under the GPLv3 license, read the LICENSE file in the source code for more details.

# Implementation notes #
At the moment the library only works with `long double` precision and does not support Integer Linear Programming (which is planned for the future).
The algorithm is based on the theory described in the book [Ricerca Operativa](http://books.google.com/books?id=coY-_6ox7U0C&printsec=frontcover) by Prof. Paolo Serafini.

# Keep in touch #
I decided to release this code after letting it aging into my development directories for more than a year and it was my first "big" project in C++, so if you have any suggestions on how to improve it, or you find it interesting and you decide to use it in your code, please just let me know. More details about how to contact me in the source code. :)

Tommaso Urli