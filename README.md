# game-of-life-cpp
Game of life implementation in C++

## How to run

On Linux run the `test.sh` script, it will compile and execute the project.

### Configuration

The map size and the number of iterations can be configures from the `#define` at the top of the `main.cpp` file.


### Sample output

```bash
Matrix initialized: 
0 0 1 0 0
0 0 1 0 0
0 0 1 0 0
0 0 1 0 0
0 0 0 0 0
Kernel: 
1 1 1
1 0 1
1 1 1
Iter [1]:
0 0 0 0 0
0 1 1 1 0
0 1 1 1 0
0 0 0 0 0
0 0 0 0 0
Iter [2]:
0 0 1 0 0
0 1 0 1 0
0 1 0 1 0
0 0 1 0 0
0 0 0 0 0
Iter [3]:
0 0 1 0 0
0 1 0 1 0
0 1 0 1 0
0 0 1 0 0
0 0 0 0 0
Iter [4]:
0 0 1 0 0
0 1 0 1 0
0 1 0 1 0
0 0 1 0 0
0 0 0 0 0
```

## Dependencies

- Eigen 3


<br><br><hr>


#### Miguel Granero 2023