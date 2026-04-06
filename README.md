# PushSwap
This is my second push swap project in which i want to improve the midpoint algo i've used in the first project.

> I put this project on hold for now but feel free to be inspired or even find the inefficiency and why this is ~500 operations worse than the previous version from 4 years ago.
## Parser
### Input
The parser is build to parse as much as possible.
- Mixed input e.g `./push_swap 5 9 "2 3 4" 10`
- From int min to int max
- a maximum of 2^32 -1 elements
- use of multi signed numbers e.g `--5, +-5, --++-++++----+---5`
Allowed chars: `\f\n\r\t\v0123456789+- and white space`
`\f\n\r\t\v` are converted to whitespace.
### Reducing
The parser reduces double+ white space sequenzes, and those multi signs before an element. `--5 -> +5` `++---+-+-5 -> -5` `++---+-+--5 -> +5` or simply if `-` count % 2 == 1 element is negative, otherwise positive.
### Output
The parser outputs an `unsigned int*` with the original list indexed beginning with 1, last element is alway 0 and not part of the elements to sort.
> This is important for the midpoint algo to work.

