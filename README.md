# 3D Connect4
Contained are the files necessary to run the 3D Connect4 C++ engine. The engine uses a Monte Carlo Tree Search with Upper Confidence Bounds a.k.a Upper Confidence Tree (UCT).

## Using the Engine:
  After having been compiled the engine can be run with the resultant executable with the following command line arguments:
  * true/false - to specify whether you would like to play first or second.
  * time - amount of time for the engine to think per move.
  
  When the engine prompts you to enter a move, your move can be entered as follows:
  
 
 Bottom Layer:
 
|    |    |    |    |  
|----|----|----|----|
| 0  | 1  | 2  | 3  |
| 4  | 5  | 6  | 7  |
| 8  | 9  | 10 | 11 |
| 12 | 13 | 14 | 15 |

Second Layer:

|    |    |    |    |  
|----|----|----|----|
| 16 | 17 | 18 | 19 |
| 20 | 21 | 22 | 23 |
| 24 | 25 | 26 | 27 |
| 28 | 29 | 30 | 31 |

Third Layer:

|    |    |    |    |  
|----|----|----|----|
| 32 | 33 | 34 | 35 |
| 36 | 37 | 38 | 39 |
| 40 | 41 | 42 | 43 |
| 44 | 45 | 46 | 47 |

Top Layer:

|    |    |    |    |  
|----|----|----|----|
| 48 | 49 | 50 | 51 |
| 52 | 53 | 54 | 55 |
| 56 | 57 | 58 | 59 |
| 60 | 61 | 62 | 63 |

Once the engine's thinking time is up, it will make it's move and display the board, which is repesented similarly to how the moves are displayed above. The engine will also display the information about the moves it analysed during its search.
