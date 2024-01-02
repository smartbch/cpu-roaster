for f in 1900_KruskalMST 1100_HeapSort 1200_QuickSort 1300_MergeSort 1400_PrioQueue 1600_FibonacciHeap 2300_BinarySearch 2800_BloomFilter 2900_SuffixArray 3200_BinarySearchTree 3800_RedBlackTree; do
	echo "========= $f ========="
	em++ -o a.js -DSELF_TEST -std=c++11 -O3 -sALLOW_MEMORY_GROWTH ../src/$f.cpp expandRand.wasm.o
	wasm-opt -O4 --enable-bulk-memory a.wasm -o b.wasm; mv b.wasm a.wasm
	/usr/bin/time -l node ./a.js
	echo "--- Native ------"
	g++ -DSELF_TEST -std=c++11 -O3 ../src/$f.cpp expandRand.o
	/usr/bin/time -l ./a.out
done
