#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int min_fun(int a, int b) {
	return (a <= b) ? a : b;
}

//pseudo-polynomial time knapsack algorithm
void ppKnapsack(int n, int *w, int *v, int V, int **m, char **items) {
	//initialization
	m[0][0] = 0;
	for (int i = 1; i <= V; i++) {
		m[0][i] = -1;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= V; j++) {
			if (v[i - 1] > j) {
				m[i][j] = m[i - 1][j];
				items[i][j] = 0;
			}
			else {
				if (m[i - 1][j - v[i - 1]] == -1) {
					m[i][j] = m[i - 1][j];
				}
				else if (m[i - 1][j] == -1) {
					m[i][j] = m[i - 1][j - v[i - 1]] + w[i - 1];
				}
				else {
					m[i][j] = min_fun(m[i - 1][j], m[i - 1][j - v[i - 1]] + w[i - 1]);
				}
				items[i][j] = (m[i][j] == m[i - 1][j]) ? 0 : 1;
			}
		}
	}
}


//get list of items to take
void getSet(char **items, int *v, int n, int value, int *set, int *count) {
	count[0] = 0;
	int j = value;

	for (int i = n; i > 0; i--) {
		if (items[i][j] == 1) {
			j -= v[i - 1];
			set[count[0]] = i - 1;
			count[0] += 1;
		}
	}
}

int main(int argc, char **argv) {
	FILE *f_in = fopen(argv[1], "r");

	if (f_in == NULL) {
		printf("Unable to open data file.");
		return 1;
	}

	//epsilon
	float e;
	//knapsack capacity
	int W;
	//amount of items
	int n;
	int maxValue;
	//sum of all values
	int V = 0;

	fscanf(f_in, "%f", &e);

	fscanf(f_in, "%d", &W);

	fscanf(f_in, "%d", &n);

	if (e <= 0.0 || e > 1.0 || W < 0 || n < 0) {
		printf("Invalid input data.");
		fclose(f_in);
		return 1;
	}

	//weights of items
	int *w = malloc(sizeof(int) * n);
	//values of items
	int *v = malloc(sizeof(int) * n);
	//original values of items
	int *old_v = malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		fscanf(f_in, "%d", &w[i]);
		if (w[i] < 0) {
			printf("Invalid input data.");
			fclose(f_in);
			free(w);
			free(v);
			free(old_v);
			return 1;
		}
	}

	fscanf(f_in, "%d", &v[0]);
	if (v[0] < 0) {
		printf("Invalid input data.");
		fclose(f_in);
		free(w);
		free(v);
		free(old_v);
		return 1;
	}
	maxValue = v[0];
	for (int i = 1; i < n; i++) {
		fscanf(f_in, "%d", &v[i]);
		if (v[i] < 0) {
			printf("Invalid input data.");
			fclose(f_in);
			free(w);
			free(v);
			free(old_v);
			return 1;
		}
		maxValue = (maxValue > v[i]) ? maxValue : v[i];
	}

	fclose(f_in);

	double K = (maxValue * e) / n;

	for (int i = 0; i < n; i++) {
		old_v[i] = v[i];
		v[i] = (int)floor(v[i] / K);
		V += v[i];
	}

	//table of optimal solutions
	int **m = malloc(sizeof(int*) * (n + 1));
	for (int i = 0; i <= n; i++) {
		m[i] = malloc(sizeof(int) * (V + 1));
	}

	char **items = malloc(sizeof(char*) * (n + 1));
	for (int i = 0; i <= n; i++) {
		items[i] = malloc(sizeof(char) * (V + 1));
	}

	ppKnapsack(n, w, v, V, m, items);
	int value;
	int weight;
	for (value = V; value >= 0; value--) {
		if (m[n][value] <= W && m[n][value] != -1) {
			weight = m[n][value];
			break;
		}
	}

	free(w);
	for (int i = 0; i <= n; i++) {
		free(m[i]);
	}
	free(m);

	int *S = malloc(sizeof(int) * n);
	int count = 0;

	getSet(items, v, n, value, S, &count);

	//calculate profit using original values
	value = 0;
	for (int i = count - 1; i >= 0; i--) {
		value += old_v[S[i]];
	}

	FILE *f_out = fopen(argv[2], "w");

	if (f_out == NULL) {
		printf("Unable to write result to file.");
		return 1;
	}

	fprintf(f_out, "%d\n%d", value, weight);
	for (int i = count - 1; i >= 0; i--) {
		fprintf(f_out, "\n%d", S[i]);
	}

	fclose(f_out);
	free(v);
	free(old_v);
	free(S);
	return 0;
}