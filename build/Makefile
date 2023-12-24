CXX=g++

all: cpu-roaster.o

expandRand.o: ../src/ExpandRand/expandRand.cpp ../src/ExpandRand/blake2b-ref.c  ../src/ExpandRand/byte_order.c   ../src/ExpandRand/sha3.c
	$(CXX) -O3 -o expandRand.o -c ../src/ExpandRand/expandRand.cpp

0000_AlgoSet.o: ../src/0000_AlgoSet.cpp
	$(CXX) -O3 -std=c++11 -o 0000_AlgoSet.o -c ../src/0000_AlgoSet.cpp

1100_HeapSort.o: ../src/1100_HeapSort.cpp
	$(CXX) -O3 -std=c++11 -o 1100_HeapSort.o -c ../src/1100_HeapSort.cpp

1200_QuickSort.o: ../src/1200_QuickSort.cpp
	$(CXX) -O3 -std=c++11 -o 1200_QuickSort.o -c ../src/1200_QuickSort.cpp

1300_MergeSort.o: ../src/1300_MergeSort.cpp
	$(CXX) -O3 -std=c++11 -o 1300_MergeSort.o -c ../src/1300_MergeSort.cpp

1400_PrioQueue.o: ../src/1400_PrioQueue.cpp
	$(CXX) -O3 -std=c++11 -o 1400_PrioQueue.o -c ../src/1400_PrioQueue.cpp

1600_FibonacciHeap.o: ../src/1600_FibonacciHeap.cpp
	$(CXX) -O3 -std=c++11 -o 1600_FibonacciHeap.o -c ../src/1600_FibonacciHeap.cpp

1900_KruskalMST.o: ../src/1900_KruskalMST.cpp
	$(CXX) -O3 -std=c++11 -o 1900_KruskalMST.o -c ../src/1900_KruskalMST.cpp

2300_BinarySearch.o: ../src/2300_BinarySearch.cpp
	$(CXX) -O3 -std=c++11 -o 2300_BinarySearch.o -c ../src/2300_BinarySearch.cpp

2400_KthSmallest.o: ../src/2400_KthSmallest.cpp
	$(CXX) -O3 -std=c++11 -o 2400_KthSmallest.o -c ../src/2400_KthSmallest.cpp

2700_CuckooHash.o: ../src/2700_CuckooHash.cpp
	$(CXX) -O3 -std=c++11 -o 2700_CuckooHash.o -c ../src/2700_CuckooHash.cpp

2800_BloomFilter.o: ../src/2800_BloomFilter.cpp
	$(CXX) -O3 -std=c++11 -o 2800_BloomFilter.o -c ../src/2800_BloomFilter.cpp

2900_SuffixArray.o: ../src/2900_SuffixArray.cpp
	$(CXX) -O3 -std=c++11 -o 2900_SuffixArray.o -c ../src/2900_SuffixArray.cpp

3200_BinarySearchTree.o: ../src/3200_BinarySearchTree.cpp
	$(CXX) -O3 -std=c++11 -o 3200_BinarySearchTree.o -c ../src/3200_BinarySearchTree.cpp

3400_BTree.o: ../src/3400_BTree.cpp
	$(CXX) -O3 -std=c++11 -o 3400_BTree.o -c ../src/3400_BTree.cpp

3800_RedBlackTree.o: ../src/3800_RedBlackTree.cpp
	$(CXX) -O3 -std=c++11 -o 3800_RedBlackTree.o -c ../src/3800_RedBlackTree.cpp

3900_ReversePolishNotation.o: ../src/3900_ReversePolishNotation.cpp
	$(CXX) -O3 -std=c++11 -o 3900_ReversePolishNotation.o -c ../src/3900_ReversePolishNotation.cpp

cpu-roaster.o: expandRand.o 0000_AlgoSet.o 1100_HeapSort.o 1200_QuickSort.o 1300_MergeSort.o 1400_PrioQueue.o 1600_FibonacciHeap.o 1900_KruskalMST.o 2300_BinarySearch.o 2400_KthSmallest.o 2700_CuckooHash.o 2800_BloomFilter.o 2900_SuffixArray.o 3200_BinarySearchTree.o 3400_BTree.o 3800_RedBlackTree.o 3900_ReversePolishNotation.o
	$(CXX) -o cpu-roaster.o -c expandRand.o 0000_AlgoSet.o 1100_HeapSort.o 1200_QuickSort.o 1300_MergeSort.o 1400_PrioQueue.o 1600_FibonacciHeap.o 1900_KruskalMST.o 2300_BinarySearch.o 2400_KthSmallest.o 2700_CuckooHash.o 2800_BloomFilter.o 2900_SuffixArray.o 3200_BinarySearchTree.o 3400_BTree.o 3800_RedBlackTree.o 3900_ReversePolishNotation.o

.PHONY: clean

clean:
	rm *.o

