all:
	g++ ./src/red_black_tree.cpp ./src/rb_test.cpp -o ./bin/rb_test
	g++ ./src/avl_tree.cpp ./src/avl_test.cpp -o ./bin/avl_test
clean:
	rm -rf ./bin/avl_test
