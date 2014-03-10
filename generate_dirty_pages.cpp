#include <cstdlib>
#include <iostream>
#include <cstdio>

#include <unistd.h>
#include <time.h>
#include <pthread.h>

using namespace std;

struct dirty_page_info
{
	void *mem_ptr;
	long range;
	struct timespec sleep_time;
};

bool is_numeric(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

void *generate_dirty_pages(void *dpi)
{
	struct dirty_page_info *dpinfo = (struct dirty_page_info *) dpi;
	char *wr_ptr = (char *)dpinfo->mem_ptr;
	for (int i = 0; i < dpinfo->range; i++)
	{
		//printf("iteration: %d wr_prt: %p\n", i, wr_ptr);
		*wr_ptr = 0;
		wr_ptr += 4*1024; // int is 4 bytes, so jumping 4*1024 = 4K bytes
		//cout << "usleep " << usleep(sleep_between_writes) << endl;
		//usleep(sleep_between_writes);
		nanosleep(&dpinfo->sleep_time, NULL);
	}
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Usage: ./generate_dirty_pages <dirty_rate>" << endl;
		exit(1);
	}

	if (!is_numeric(string(argv[1])))
	{
		cout << "Usage: ./generate_dirty_pages <dirty_rate>" << endl;
		cout << "<dirty_rate> must be numeric" << endl;
		exit(1);
	}

	long dirty_rate = atol(argv[1]); // page dirty rate per second

	// each second allocate dirty_rate amount of memory
	// write one byte after each 4K bytes 
	// uniformly distribute the writes over one second
	while(true)
	{
		double sleep_between_writes = (4.0 * 1000 * 1000) / dirty_rate; // sleep is in micro-seconds, 4.0 as we have 4 threads
		struct timespec sleep_time;
		sleep_time.tv_sec = sleep_between_writes / (1000 * 1000);
		sleep_time.tv_nsec = (((int)sleep_between_writes) % (1000 * 1000)) * 1000;
		//cout << "Info: sleep time (micro sec): " << sleep_between_writes << endl;
		//cout << "Info: sleep time (sec): " << sleep_time.tv_sec << endl;
		//cout << "Info: sleep time (nano sec): " << sleep_time.tv_nsec << endl;

		cout << "Info: Allocating " << dirty_rate * 4 *1024 << " Bytes" << endl;
		void *mem_ptr;
		mem_ptr = valloc(dirty_rate * 4 * 1024); // each memory page is of 4K bytes
		if (mem_ptr == 0)
		{
			cout << "Error: Out of memory" << endl;
			return 1;
		}

		// memory allocation successful, now generate dirty pages
		cout << "Info: Generating " << dirty_rate << " dirty pages per second" << endl;

		pthread_t drt_thrd1, drt_thrd2, drt_thrd3, drt_thrd4;

		struct dirty_page_info dpi1, dpi2, dpi3, dpi4;

		dpi1.mem_ptr = mem_ptr;
		dpi2.mem_ptr = (char *)mem_ptr + dirty_rate/4;
		dpi3.mem_ptr = (char *)mem_ptr + 2*dirty_rate/4;
		dpi4.mem_ptr = (char *)mem_ptr + 3*dirty_rate/4;

		dpi1.range = dpi2.range = dpi3.range = dpi4.range = dirty_rate/4;
		dpi1.sleep_time = dpi2.sleep_time = dpi3.sleep_time = dpi4.sleep_time = sleep_time;

		pthread_create(&drt_thrd1, NULL, generate_dirty_pages, (void *)&dpi1);
		pthread_create(&drt_thrd2, NULL, generate_dirty_pages, (void *)&dpi2);
		pthread_create(&drt_thrd3, NULL, generate_dirty_pages, (void *)&dpi3);
		pthread_create(&drt_thrd4, NULL, generate_dirty_pages, (void *)&dpi4);

		pthread_join(drt_thrd1, NULL);
		pthread_join(drt_thrd2, NULL);
		pthread_join(drt_thrd3, NULL);
		pthread_join(drt_thrd4, NULL);

		cout << "Info: Freeing memory" << endl;
		// free the allocated memory
		free(mem_ptr);

		// just for test purpose
		//break;
	}
	return 0;
}

