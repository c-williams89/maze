# aMAZEing
## ADDITIONAL FEATURES
- [ ] +1 `man(1)` page
- [ ] +2 LaTeX documentation
- [ ] +5 A\* algorithm
- [ ] +4 `-d` Doors
- [ ] +6 `-t` Terroidal maps
- [ ] +8 `-m sz` Map generator
- [ ] +5 `-D` Dig through walls
- [ ] +4 `-w` Water flag

<body>
​
	<h1>aMAZEing</h1>
​
	<p>Write a program that examines a map file, and prints out that map with a
	shortest path that goes between two indicated points.</p>
​
	<h2>DIcE Rubric</h2>
​
	<table>
		<tr>
			<th rowspan="6">Documentation</th>
			<td>Design Plan</td>
			<td>Easy to understand; Logical sequence; Clearly defined sections;
				Provides general overview of the project; Matches format provided; etc.</td>
			<td>3%</td>
		</tr>
		<tr>
			<td>Testing Plan</td>
			<td>Provides detailed steps to repeat test; Clear expected results;
				Appropriate coverage of requirements; etc.</td>
			<td>4%</td>
		</tr>
		<tr>
			<td>Project Writeup</td>
			<td>Demonstrates growth; Documents challenges and surprises; Summarizes
				lessons learned; etc.</td>
			<td>3%</td>
		</tr>
		<tr>
			<td>Writing</td>
			<td>Grammatical and spelling errors, formatting inconsistencies, etc.</td>
			<td>2%</td>
		</tr>
		<tr>
			<td>Code Formatting</td>
			<td>Follows style guide; Understandable variable and function names;
				Appropriate use of comments; Proper citation of outside code; etc.</td>
			<td>3%</td>
		</tr>
		<tr>
			<th>Total</th>
			<td></td>
			<th>15%</th>
		</tr>
		<tr>
			<th rowspan="4">Implementation</th>
			<td>Version Control</td>
			<td>Effective branching, merging, and tagging; Appropriate version
				control usage; one branch/merge per feature or requirement; no "active
				work" directly in main branch; No generated files in history; etc.</td>
			<td>5%</td>
		</tr>
		<tr>
			<td>Architecture</td>
			<td>Effective and efficient data structures used; Adheres to design
				outline; Modularity of design; etc.</td>
			<td>20%</td>
		</tr>
		<tr>
			<td>Testing</td>
			<td>Robust tests; Comprehensive tests; Appropriate automation; etc.</td>
			<td>5%</td>
		</tr>
		<tr>
			<th>Total</th>
			<td></td>
			<th>30%</th>
		</tr>
		<tr>
			<th rowspan="5">Execution</th>
			<td>Builds</td>
			<td>Parses/compiles without warnings; Supports build targets specified;
				etc.</td>
			<td>5%</td>
		</tr>
		<tr>
			<td>Safety</td>
			<td>Proper requesting and releasing of memory; Free of leaks; Free of
				using uninitialized memory; Fault tolerant; Invalid input does not
				result in crashes, loops, or unexpected results; etc.</td>
			<td>20%</td>
		</tr>
		<tr>
			<td>Requirements</td>
			<td>All requirements met; All inputs parsed correctly; All inputs and
				outputs produce expected/intended results; etc.</td>
			<td>20%</td>
		</tr>
		<tr>
			<td>Performance</td>
			<td>Scales appropriately with input; Executes in a timely manner;
				etc.</td>
			<td>10%</td>
		</tr>
		<tr>
			<th>Total</th>
			<td></td>
			<th>55%</th>
		</tr>
	</table>
​
​
	<h2 style="page-break-before: always;">Requirements</h2>
​
	<table>
		<tr>
			<th>Area</th>
			<th>Requirement</th>
		</tr>
		<tr>
			<td>Implementation</td>
			<td>Project must be submitted by 1659EDT on the due date specified.</td>
		</tr>
		<tr>
			<td>Implementation</td>
			<td>The project should be stored in the assigned VCS account, under the
				project name <code>maze</code>.</td>
		</tr>
		<tr>
			<td>Implementation</td>
			<td>No third-party header files/libraries may be used unless signed off by
			the Instructors.</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>The project must build and execute on the class machine.</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>The project must build the program <code>maze</code> in the
				top-level directory in response to <code>make</code>.</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>The project must build <code>maze</code> with
				debugging symbols in response to <code>make debug</code>.</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>The project must build and execute any automated tests in response to
				<code>make check</code> (it can presume the program was already built).</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>The project must build <code>maze</code> with
				profiling information in response to <code>make profile</code>.</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>The project must clean all project-generated files in response to
				<code>make clean</code>.</td>
		</tr>
​
		<tr>
			<td>Documentation</td>
			<td>All documentation must be in PDF format unless otherwise specified.</td>
		</tr>
		<tr>
			<td>Documentation</td>
			<td>All documentation should be located in a <code>doc/</code> folder at
				the top level of the project.</td>
		</tr>
		<tr>
			<td>Documentation</td>
			<td>The design document should be located in <code>doc/design.pdf</code></td>
		</tr>
		<tr>
			<td>Documentation</td>
			<td>The test plan should be located in <code>doc/testplan.pdf</code></td>
		</tr>
		<tr>
			<td>Documentation</td>
			<td>The writeup document should be located in
				<code>doc/writeup.pdf</code></td>
		</tr>
		<tr>
			<td>Documentation</td>
			<td>All C code should match the Linux kernel style guide, with the
				exception of blocks <em>always</em> having braces.</td>
		</tr>
		<tr>
			<td>Implementation</td>
			<td>All automated tests and test code should be located in a
				<code>test/</code> folder at the top level.</td>
		</tr>
​
		<tr>
			<td>Execution</td>
			<td>Program must be invoked as <code>maze <var>filename</var></code>,
				where <code><var>filename</var></code> is the map file to run
				against.</td>
		</tr>
​
		<tr>
			<td>Execution</td>
			<td>When run with a valid file, the program should print a shortest path
				from start to finish on the map, using the <code>'.'</code>
				character.</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>If no route exists, the map should be printed, nothing else, exiting
				with a success status.</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>Given an invalid file, the program should print an appropriate error
			message and then exit with a failure status.</td>
		</tr>
​
		<tr>
			<td>Execution</td>
			<td>A map file that contains characters other than <code>'#'</code>,
				<code>'@'</code>, <code>'&gt;'</code>, <code>'\n'</code> (newline), or
				<code>' '</code> (a space) is considered invalid (not considering extra credit).</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>If the map is not entirely surrounded by walls, then the map is
				invalid.  In other words, it should not be possible to walk off the
				bounds of the map from the starting position.</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>A map that does not have exactly one start and exactly one end is
				invalid.</td>
		</tr>
​
		<tr>
			<td>Execution</td>
			<td>Lines in the file may not necessarily be the same length.</td>
		</tr>
​
		<tr>
			<td>Implementation</td>
			<td>When creating a path, only orthogonal moves are allowed (no
				diagonals).</td>
		</tr>
​
		<tr>
			<td>Execution</td>
			<td>The only output to the screen should be the map, and the shortest path (if
				found), with the start and end points unchanged.</td>
		</tr>
​
​
		<tr>
			<td>Execution</td>
      <td>Code must build against C18. (<code>-std=c18</code>)</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>Code must build with no warnings from <code>-Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal</code>.</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>Program must not crash or get stuck in an infinite loop, even on
				invalid input.</td>
		</tr>
	</table>
​
	<h2>Input Formats</h2>
​
	<p>The file represents a map.  Walls are the <code>'#'</code> character, and
	empty space is a space character.  <code>'@'</code> represents the starting position,
	and <code>'&gt;'</code> is the destination.</p>
​
	<p>Here are the contents of a sample map file:</p>
​
<pre>
######################
#  &gt; ####   ##@     #
#    ##     ####### ###
## #### #   ###      ##
 # #### #######  ### ##
 # ####          ### ##
 #      ######       ##
#####################
</pre>
​
	<h2>Sample Output</h2>
​
​
	<pre><samp>&gt; <kbd>./maze map01.txt</kbd>
######################
#  &gt; ####   ##@.....#
# .. ##     #######.###
##.#### #   ###..... ##
 #.#### #######. ### ##
 #.####......... ### ##
 #......######       ##
#####################
</samp></pre>
​
​
	<h2>Suggested Additional Features</h2>
​
	<table>
		<tr>
			<th>Area</th>
			<th>Feature</th>
			<th>Value</th>
		</tr>
		<tr>
			<td>Documentation</td>
			<td>Write a <code>man(1)</code> page to document the program.</td>
			<td>+1</td>
		</tr>
		<tr>
			<td>Documentation</td>
			<td>Write the writeup, test plan, and design plan using TeX or LaTeX
				language (be sure to include the source files in the <code>doc</code>
				directory).</td>
			<td>+2</td>
		</tr>
​		<tr>
			<td>Implementation</td>
			<td>Use Dijkstras to find the path.</td>
			<td>+3</td>
		</tr>
		<tr>
			<td>Implementation</td>
			<td>Use A* to find the path.</td>
			<td>+5</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>Add support for "doors", triggered with <code>-d</code>. Closed doors
				are <code>'+'</code> characters in the map file, open doors are
				<code>'/'</code>.  If the printed path passes through a door, the door
				must be open.  Otherwise, the door's state should be unchanged from the
				input file.  It takes one extra "step" to open a door that is
				closed, which may affect the shortest path.</td>
			<td>+4</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>Add support for toroidal maps, which are triggered with a
				<code>-t</code> flag on the command line.  In this case, if the outer
				walls are missing on opposite sides of a map, instead of being an
				invalid map, this is now a passage that can be taken.  Without the
				<code>-t</code> flag, the program should still error out on such
				maps.  toroidal maps <em>must</em> be rectangular on the input file (no
				differing line lengths).</td>
			<td>+6</td>
		</tr>
		<tr>
			<td>Execution</td>
			<td>Add support for a map generator, triggered with the <code>-m <var>sz</var></code> flag.  It should build a solvable square map of dimensions <var>sz</var> &times; <var>sz</var> and print it with the solution.  The complexity of the map generated will be taken into account when scoring this feature.</td>
			<td>+8</td>
		</tr>
		<tr>
			<tr>
				<td>Execution</td>
				<td>Add support for digging through walls, triggered with the
					<code>-D</code> flag.  Any wall may be dug through, which takes ten
					times as long as a normal step through a regular part of the floor
					(space character).  So the path may go through a wall, but there may
					be a more efficient, longer path without digging.  Notice that the
					"dig" action (that takes ten steps) doesn't move the @ into the space
					dug out; it takes an extra step to actually move into the dug-out
					space.  Don't go off the edge of the map!</td>
				<td>+5</td>
			</tr>
		</tr>
		<tr>
			<tr>
				<td>Execution</td>
				<td>Add support for water on the map, triggered with the
					<code>-w</code> flag.  Water, which shows up as <code>'~'</code>,
					takes thrice as long to traverse as a regular part of the floor
					(space character).  So the path may go over it, but there might be a
					more efficient, longer path on land.</td>
				<td>+4</td>
			</tr>
		</tr>
	</table>
​
</body></html>
