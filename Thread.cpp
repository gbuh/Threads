#include <iostream>
#include <windows.h>
#include <thread>		//C++11

using namespace std;

void foo(int n)
{ 
	for (int i = 0; i < 5; i++)
	{
		cout << "Is Foo   " << n << " = " << this_thread::get_id() << endl;
		Sleep(700);
	}
}
void bar(int n)
{
	for (int i = 0; i < 10; i++)
	{
		cout << "Is Bar   " << n << " = " << this_thread::get_id() << endl;
		Sleep(700);
	}
}
int main()
{
	cout << "Hardware concurrency: " << thread::hardware_concurrency() << endl;
	//Establishment of an independent thread
	thread t1 (foo, 1);
	thread t2 (bar, 2);
	//If the thread is active at the moment
	if (t1.joinable())
		//The main thread will wait for the completion of the flow
		t1.join();
	//The main thread will not wait for the completion of this flow. It allows him to work independently
	t2.detach();
	cout << "Main: " << this_thread::get_id() << endl;
	system("pause");
}