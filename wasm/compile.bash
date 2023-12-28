em++ -O3 -o roaster.js \
  -DPOW_TESTER \
  -sALLOW_MEMORY_GROWTH \
  -sEXPORTED_FUNCTIONS=_main,_cpu_roaster_hash,_cpu_roaster_pow \
  ../src/0000_CpuRoaster.cpp \
  ../src/1100_HeapSort.cpp \
  ../src/1200_QuickSort.cpp \
  ../src/1300_MergeSort.cpp \
  ../src/1400_PrioQueue.cpp \
  ../src/1600_FibonacciHeap.cpp \
  ../src/1900_KruskalMST.cpp \
  ../src/2300_BinarySearch.cpp \
  ../src/2800_BloomFilter.cpp \
  ../src/2900_SuffixArray.cpp \
  ../src/3200_BinarySearchTree.cpp \
  ../src/3800_RedBlackTree.cpp \
  ../src/ExpandRand/expandRand.cpp
