# Knapsack problem - FPTAS (Fully polynomial-time approximation scheme)
## Usage
The name of the file with input data and the name of the file to save the results should be given as calling parameters, e.g.
```
$ gcc main.c -lm -o program.out
$ program.out inputData.txt outputData.txt
```
The above call will load the data from the `inputData.txt` file and save the result to the `outputData.txt` file.

The program loads data from a text file in the following format:
- epsilon value
- knapsack capacity
- number of items available
- item weight list (next values ​​in new lines)
- list of item values ​​(next values ​​in new lines)

The epsilon value should be in the range (0, 1], the rest should be non-negative integers.

The result is saved to a text file in the following format:
- maximum profit
- knapsack capacity used
- indexes of items that give the above profit (subsequent indexes in new lines; indexes counting from 0);
## Example:
- epsilon = `0.5`
- knapsack capacity = `10`
- number of items = `4`
- weights of subsequent items = `{1, 2, 3, 4}`
- values ​​of subsequent items = `{2, 4, 1, 10}`

Input file content:
```
0.5
10
4
1
2
3
4
2
4
1
10
```
Sample program input and output are included in the `inputData.txt` and `outputData.txt` files included with the source code.