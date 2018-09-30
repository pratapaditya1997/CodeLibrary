// for every ith element stores the index of prev/nextGreater element in the array
// if no prevGreater, prevGreater[i]=-1
// if no nextGreater, nextGreater[i]=n
void calculate(const vector<int>& a) {
	int n=(int)a.size();
	vi prevGreater(n, -1), nextGreater(n, n), stck;
	for (int i = 0; i < n; i++) {
		while (stck.size() && a[i] >= a[stck.back()]) {
			nextGreater[stck.back()] = i;
			stck.pop_back();
		}
		if (stck.empty()) prevGreater[i] = -1;
		else prevGreater[i] = stck.back();
		stck.push_back(i);
	}
	// assign prev/nextGreater to some arrays or return one of them as needed
}
