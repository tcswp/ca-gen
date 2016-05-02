#CAgen

CAgen draws elementary and life-like cellular automata on a display. This program is intended to be a screensaver on GNU/Linux.

##Usage
`cagen [CA TYPE] [RULE] [OPTION]`

OPTIONS
`-l <Bx/Sy rule>` 	generate 2D life-like CA
`-d <density>`		generation 0 population density (floating-point value w/ range (0,1))

`-e <Wolfram code>`	generate 1D elementary CA		
`-r`			generation 0 random configuration

`-s <N times>`		scale N times
`-f <r,g,b>`		foreground color in decimal RGB values
`-b <r,g,b>`		background color in decimal RGB values

NOTE
CAgen defaults to a monochrome Conway's Life game (B3/s23) with population density 0.25 scaled 4x.