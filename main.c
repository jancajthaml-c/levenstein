#include "levenstein.h"

#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

double diff(double start, double end) {
  double temp;
  if ((end - start) < 0) {
  	return 1000000000 + end - start;
  } else {
		return end - start;
  }
  return temp;
}

int _levensteinDistance(char* a, char* b) {
	return levensteinDistance(a, b, strlen(a), strlen(b));
}

int main() {
	printf("\nRunning unit tests\n");

	// expectations

	// matches
	if (_levensteinDistance("", "") != 0) {
		return 1;
	}
	if (_levensteinDistance("a", "a") != 0) {
		return 1;
	}
	if (_levensteinDistance("abc", "abc") != 0) {
		return 1;
	}

	// empty on one side
	if (_levensteinDistance("a", "") != 1) {
		return 1;
	}
	if (_levensteinDistance("", "a") != 1) {
		return 1;
	}
	if (_levensteinDistance("abc", "") != 3) {
		return 1;
	}
	if (_levensteinDistance("", "abc") != 3) {
		return 1;
	}

	// inserts only
	if (_levensteinDistance("a", "ab") != 1) {
		return 1;
	}
	if (_levensteinDistance("b", "ba") != 1) {
		return 1;
	}
	if (_levensteinDistance("ac", "abc") != 1) {
		return 1;
	}
	if (_levensteinDistance("abcdefg", "xabxcdxxefxgx") != 6) {
		return 1;
	}

	// deletes only
	if (_levensteinDistance("ab", "a") != 1) {
		return 1;
	}
	if (_levensteinDistance("ab", "b") != 1) {
		return 1;
	}
	if (_levensteinDistance("abc", "ac") != 1) {
		return 1;
	}
	if (_levensteinDistance("xabxcdxxefxgx", "abcdefg") != 6) {
		return 1;
	}

	// swaps only
	if (_levensteinDistance("a", "b") != 1) {
		return 1;
	}
	if (_levensteinDistance("ab", "ac") != 1) {
		return 1;
	}
	if (_levensteinDistance("ac", "bc") != 1) {
		return 1;
	}
	if (_levensteinDistance("abc", "axc") != 1) {
		return 1;
	}
	if (_levensteinDistance("xabxcdxxefxgx", "1ab2cd34ef5g6") != 6) {
		return 1;
	}

	// combination of insert + delete + swap
	if (_levensteinDistance("example", "samples") != 3) {
		return 1;
	}
	if (_levensteinDistance("sturgeon", "urgently") != 6) {
		return 1;
	}
	if (_levensteinDistance("levenshtein", "frankenstein") != 6) {
		return 1;
	}
	if (_levensteinDistance("distance", "difference") != 5) {
		return 1;
	}


	printf("passed");

	// micro benchmark

	int i;
	unsigned int times = 4000000;

	printf("\n\nRunning benchmark %lu times \n", (unsigned long) times);

	double total_time = 0;
	double clock_cost = 0;

	struct timespec t1;
	struct timespec t2;

	for (i = 0; i < times; ++i) {
		clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
		clock_cost += diff(t1.tv_nsec, t2.tv_nsec);

		clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
		_levensteinDistance("xabxcdxxefxgx", "1ab2cd34ef5g6");
		clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
		total_time += diff(t1.tv_nsec, t2.tv_nsec);
	}

	printf("median: %f ns/op\n\n", ((total_time-clock_cost)/times));

	return 0;
}