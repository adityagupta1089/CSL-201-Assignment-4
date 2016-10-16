all:
	g++ -g ./src/avl_tree.cpp ./src/red_black_tree.cpp ./src/test.cpp -o ./bin/avl_test
clean:
	rm -rf ./bin/avl_test
