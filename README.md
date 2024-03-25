# antlr4-vba-benchmark
This repository is intended to reproduce some 
performance issues within ANTLR4. It parses
ca. 600 lines of example VBA code found in the 'data'
subfolder using the VBA grammar from the 'Rubberduck' project.

Runtimes measured on Github Actions are approximately

| | Windows | Linux |
|-|--|--|
|Release| 4.8s | 3.5s |
|Debug|46.5s| 29.7s|

Even the fastest time: 3.5 seconds for 600 lines of code,
is pretty slow.

The Rubberduck VBA grammar is not optimal, as it handles whitespace
in the parser.