# maze

## Description
`maze` is a command-line utility tool for examining a text file representing a maze,
identifying the shortest path between two points using Dijkstra's algorithm, and 
printing that path if it exists.

## Installation
The entire project can be cloned from Git.

Developed with C18 and compiled with gcc-9.

---

### Build
`maze` can easily be built using the make tool.
To build and compile the program:
```sh
<project_root> $ make
```
to create the executable `maze`.

---

### Run
`maze` must be invoked with a valid text file containg walls '#', one start point '@', one end point '>',
water options '~', doors '+' and spaces. `maze` also accepts additional optional arguments:
- -d - Allows traversal through closed doors for an additional cost of 2.
- -D - Allows traversal through walls for an additional cost of 11.
- -w - Allows traversal through water for an additional cost of 3.
```sh
<project_root> $ ./maze <FILE> [OPTION...]
```

### Examples:
With the test maze `all_flags.txt`
```
$ ./maze test/test_data/all_flags.txt 
##################
#> #          # @#
#  ############# #
#     ~~~~~      #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#        +       #
##################

$ ./maze test/test_data/all_flags.txt -D
##################
#>..............@#
#  ############# #
#     ~~~~~      #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#        +       #
##################

$ ./maze test/test_data/all_flags.txt -d
##################
#>.#          # @#
# .#############.#
# .   ~~~~~     .#
# .#############.#
# .#############.#
# .#############.#
# .#############.#
# .#############.#
# .#############.#
# ......./.......#
##################

$ ./maze test/test_data/all_flags.txt -w
##################
#>.#          # @#
# .#############.#
# ...............#
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#        +       #
##################

$ ./maze test/test_data/all_flags.txt -w -d -D
##################
#> #          # @#
#. #############.#
#................#
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#  ############# #
#        +       #
##################

```

---

### Debug/Error Checking
to build `maze` with debug flags:
```sh
<project_root> $ make debug
```
to be able to debug with gdb.
```sh
<project_root> $ gdb --args ./maze <FILE> [OPTIONS...]
```

To check `maze` against valgrind for memory leaks and errors, build with debug flags and run with `valgrind` prepended.
```sh
<project_root> $ make debug
<project_root> $ valgrind ./maze <FILE> [OPTIONS...]
```
or in one line:
```sh
<project_root> $ make valgrind ARGS=<FILE>
<project_root> $ make valgrind ARGS="<FILE> [OPTIONS...]"
```
EX:
```sh
<project_root> $ make valgrind ARGS=test/test_data/valid_map.txt
<project_root> $ make valgrind ARGS="test/test_data/valid_map.txt -d -D -w
```

---

### Performance/Optimization
To be able to view performance information, build and execute with profiling flags:
```sh
<project_root> $ make profile
<project_root> $ ./maze <FILE> [OPTIONS...]
```
After the program has been run, use `gprof` to view graph profile
```sh
<project_root> $ gprof ./maze gmon.out > data/analysis.txt
```
**NOTE: gprof will create `gmon.out` in the top level directory by default, however this command redirects the report to text format in `data/`**

---

### Testing
Automated unit tests have been written for `maze` and can be run using make.
```sh
<project_root> $ make check
```
will build and run automated unit testing.
```sh
100%: Checks: 11, Failures: 0, Errors: 0
test/test_io_helper.c:9:P:core:*curr++:0: Passed
test/test_io_helper.c:30:P:core:*curr++:0: Passed
test/test_matrix.c:36:P:core:*curr++:0: Passed
test/test_matrix.c:43:P:core:*curr++:0: Passed
test/test_matrix.c:51:P:core:*curr++:0: Passed
test/test_matrix.c:68:P:core:*curr++:0: Passed
test/test_matrix.c:83:P:core:*curr++:0: Passed
test/test_matrix.c:97:P:core:*curr++:0: Passed
test/test_matrix.c:112:P:core:*curr++:0: Passed
test/test_matrix.c:121:P:core:*curr++:0: Passed
test/test_matrix.c:132:P:core:*curr++:0: Passed
```

---

### Cleanup
After running the program, execute:
```sh
<project_root> $ make clean
```
to delete object files as well as data created from `make profile`

---

## Support 
Additional support can be found in the man page:
```sh
<project_root> $ man ./doc/maze.1
```