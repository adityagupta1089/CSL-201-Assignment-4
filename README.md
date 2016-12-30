# Instructions:
1. To Build:   
```
$make
```
2. To Run:
    * AVL Tree:  
	```
	$./bin/avl_test
	```
    * R/B Tree:   
	```
	$./bin/rb_test
	```
3. Use different options available in UI that is based on `tree<K=int,V=int>`.

# NOTE:
In printing of Red-Black tree, a node like `[-10(R)0,-1]` means a red [(R)] node with key `-10` and total and black heights as `0` and `-1` respectively.
      
# Questions:
1. **[20 marks]** Implement an ordered map with height balanced binary search tree (AVL tree). The ordered map should contain the following functions in its interface:-
	1. **firstEntry(k)**: Return an iterator to the entry with smallest key value; if the map is empty, it returns end.
	2. **lastEntry(k)**: Return an iterator to the entry with largest key value; if the map is empty, it returns end.
	3. **ceilingEntry(k)**: Return an iterator to the entry with the least key value greater than or equal to k; if there is no such entry, it returns end.
	4. **floorEntry(k)**: Return an iterator to the entry with the greatest key value less than or equal to k; if there is no such entry, it returns end.
	5. **lowerEntry(k)**: Return an iterator to the entry with the greatest key value less than k; if there is no such entry, it returns end.
	6. **higherEntry(k)**: Return an iterator to the entry with the least key value greater than k; if there is no such entry, it returns end.
	7. **size()**: Return the number of entries in M.
	8. **empty()**: Return true if M is empty and false otherwise.
	9. **find(k)**: If M contains an entry e=(k,v),with key equal to k,then return an iterator preferring to this entry, and otherwise return the special iterator end.
	10. **put(k,v)** : If M does not have an entry with key equal to k, then add entry (k,v) to M, and otherwise, replace the value field of this entry with v; return an iterator to the inserted/modified entry.
	11. **erase(k)**: Remove from M the entry with key equal to k; an error condition occurs if M has no such entry.
	12. **erase(p)**: Remove from M the entry referenced by iterator p; an error condition occurs if p points to the end sentinel.
Insert a given sequence of numbers in an initially empty AVL tree. Display the resulting binary
tree after each step. If you have to rotate the tree after inserting an element, display the tree
after each rotation.
2. **[10 marks]** Read a sequence of n space separated integers from a file and insert into the ordered map implementation of the previous question. Now, for a given target sum, write a function that returns true if there is a pair with sum equals to target sum, otherwise returns false. The time complexity of the algorithm should be O(n) and only O(log n) extra memory space can be used. Do not modify the structure of the binary search tree. Note that you cannot read the numbers out in an array as this will require O(n) memory space. Your algorithm should work on the AVL tree.
3. **[20]** Implement a Red Black tree. Along with insert(k,v) , remove(k) , and search(k) ,include the following functions:
	a. Delete a node from the red black tree.
	b. Count the number of leaves in a tree.
	c. Return the height of a tree.
	d. Return a list of all keys in a tree between a and b.
The program should display the tree after each step.
