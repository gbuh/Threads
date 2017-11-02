#include <iostream>
#include <unistd.h>
#include <vector>
#include <mutex>
#include <thread>

using namespace std;

void foo (int& num, mutex& mtx)
{
	while (1)
	{
		mtx.lock();
		num += 2;
		cout << "Foo: " << num << endl;
		mtx.unlock();
		//If you comment out the one thread will run several times in a row
		usleep(50000);
	}
}
void bar (int& num, mutex& mtx)
{
	while (1)
	{
		//If you remove the lock synchronization will be lost
		mtx.lock();
		num -= 2;
		cout << "Bar: " << num << endl;
		mtx.unlock();
		usleep(50000);
	}
}
int main ()
{
	int num = 10;
	mutex mtx;
	
	thread t1 (foo, ref(num), ref(mtx));
	thread t2 (bar, ref(num), ref(mtx));

	t1.join();
	t2.join();
}