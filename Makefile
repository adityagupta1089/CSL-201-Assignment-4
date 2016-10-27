all:
	g++ -g ./src/red_black_tree.cpp ./src/test.cpp -o ./bin/rbtree -fsanitize=undefined
clean:
	rm -rf ./bin/avl_test
