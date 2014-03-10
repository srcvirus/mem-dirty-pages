all:
	g++ -pthread -g generate_dirty_pages.cpp -o generate_dirty_pages
clean:
	rm -f generate_dirty_pages
