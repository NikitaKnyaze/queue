#include <iostream>
#include <thread>
#include <chrono>

bool stop{false};

void client( int& count)
{
	int count_max = 20;
	while (count < count_max)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		count++;
		std::cout << "Client count= " << count << "\n";
	}
	stop = true;
}

void operation(int& count)
{
	while(count!=0 || !stop)
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		count--;
		std::cout << "operation count= " << count << "\n";
	} 
}

int main()
{
	int count{};
	std::thread t1{ client, std::ref(count) };
	std::thread t2{ operation,  std::ref(count) };
	t1.join();
	t2.join();

	return EXIT_SUCCESS;
}