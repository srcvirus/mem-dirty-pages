#include<iostream>
#include<ctime>

using namespace std;

int main()
{
	time_t t1, t2;
	t1 = time(0);
	while(true)
	{
		t2 = time(0);  // t is an integer type
		int diff = t2 - t1;
		if (diff > 0)
		{
			cout << diff << endl;
		}
		t1 = t2;
	}
	return 0;
}
