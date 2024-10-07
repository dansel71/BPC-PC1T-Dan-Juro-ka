int IsPrime(int num) {
	if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num % 7 == 0) {
		return 1;
	} else {
		return 0;
	}
}