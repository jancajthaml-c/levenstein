int levenstein_distance(const char* a, const char* b, int length_a, int length_b);

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

double diff(double start, double end) {
  if ((end - start) < 0) {
  	return 1000000000 + end - start;
  } else {
	return end - start;
  }
  return 0;
}

void expectDistance(char* a, char* b, int distance) {
	int d = levenstein_distance(a, b, strlen(a), strlen(b));

	if (d != distance) {
		printf("`%s` and `%s` expected distance %d but got %d instead\n\n", a, b, distance, d);
		exit(EXIT_FAILURE);
	}
}

int main() {
	printf("\nRunning unit tests\n");

	// matches
	expectDistance("", "", 0);
	expectDistance("a", "a", 0);
	expectDistance("abc", "abc", 0);

	// empty on one side
	expectDistance("a", "", 1);
	expectDistance("", "a", 1);
	expectDistance("abc", "", 3);
	expectDistance("", "abc", 3);

	// inserts only
	expectDistance("a", "ab", 1);
	expectDistance("b", "ba", 1);
	expectDistance("ac", "abc", 1);
	expectDistance("abcdefg", "xabxcdxxefxgx", 6);

	// deletes only
	expectDistance("ab", "a", 1);
	expectDistance("ab", "b", 1);
	expectDistance("abc", "ac", 1);
	expectDistance("xabxcdxxefxgx", "abcdefg", 6);

	// swaps only
	expectDistance("a", "b", 1);
	expectDistance("ab", "ac", 1);
	expectDistance("ac", "bc", 1);
	expectDistance("abc", "axc", 1);
	expectDistance("xabxcdxxefxgx", "1ab2cd34ef5g6", 6);

	// combination of insert + delete + swap
	expectDistance("example", "samples", 3);
	expectDistance("sturgeon", "urgently", 6);
	expectDistance("levenshtein", "frankenstein", 6);
	expectDistance("distance", "difference", 5);

	printf("passed");

	// micro benchmark

	int i;
	unsigned int times = 4000000;

	printf("\n\nRunning benchmark %lu times \n", (unsigned long) times);

	double total_time = 0;
	double clock_cost = 0;

	struct timespec t1;
	struct timespec t2;

	char* string_a = "xabxcdxxefxgx";
	int len_a = strlen(string_a);
	char* string_b = "1ab2cd34ef5g6";
	int len_b = strlen(string_b);

	for (i = 0; i < times; ++i) {
		// clock cost runtime reference
		clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
		clock_cost += diff(t1.tv_nsec, t2.tv_nsec);
		// real test
		clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
		levenstein_distance(string_a, string_b, len_a, len_b);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
		total_time += diff(t1.tv_nsec, t2.tv_nsec);
	}

	printf("median: %f ns/op\n\n", ((total_time-clock_cost)/times));

	return 0;
}