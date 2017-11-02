#include <iostream>
#include <unistd.h>
#include <thread>
#include <future>

using namespace std;

bool task (int n)
{
	sleep(n);
	cout << n << ": ";
	return true;
}

void task_f (future<int>& f)
{
	int n = f.get();
	sleep(n);
	cout << n << ": " << "DONE" << endl;
}
int main ()
{
	//Create thread and wait return value
	{
		future<bool> ft = async(task, 3);

		if (ft.get())
		{
			cout << "DONE 1" << endl;
		}
	}
	//Create thread and wait return value
	{
		packaged_task<bool(int)> tsk (task);
		future<bool> ret = tsk.get_future();

		thread th (move(tsk), 2);

		if (ret.get())
		{
			cout << "DONE 2" << endl;
		}
		th.join();
	}
	//Self set return future value
	{
		promise<int> prom;
		future<int> ft = prom.get_future();

		thread t1 (task_f, ref(ft));

		prom.set_value(1);

		t1.join();
	}
}