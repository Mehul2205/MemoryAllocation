# MemoryAllocation
The real challenge of efficiently managing memory is seen in the case of a system which has multiple processes running at the same time. Since primary memory can be space-multiplexed, the memory manager can allocate a portion of primary memory to each process for its own use. However, the memory manager must keep track of which processes are running in which memory locations, and it must also determine how to allocate and deallocate available memory when new processes are created and when old processes complete execution. While various different strategies are used to allocate space to processes competing for memory, three of the most popular are Best fit, Worst fit, and First fit.

![MemoryAllocation](https://user-images.githubusercontent.com/48055152/58043012-ca6da580-7b59-11e9-97ce-8439c2038284.png)


## 1. Best fit

The allocator places a process in the smallest block of unallocated memory in which it will fit. For example, suppose a process requests 12KB of memory and the memory manager currently has a list of unallocated blocks of 6KB, 14KB, 19KB, 11KB, and 13KB blocks. The best-fit strategy will allocate 12KB of the 13KB block to the process.
Although, best fit minimizes the wastage space, it consumes a lot of processor time for searching the block which is close to required size.
### Code Screenshot

![image1](https://user-images.githubusercontent.com/48055152/58042993-c0e43d80-7b59-11e9-92ed-c817a129c48c.png)

## 2. Worst fit

The memory manager places a process in the largest block of unallocated memory available. The idea is that this placement will create the largest hold after the allocations, thus increasing the possibility that, compared to best fit, another process can use the remaining space. Using the same example as above, worst fit will allocate 12KB of the 19KB block to the process, leaving a 7KB block for future use.
If a large process comes at a later stage, then memory will not have space to accommodate it.

### Code Screenshot

![image2](https://user-images.githubusercontent.com/48055152/58042994-c17cd400-7b59-11e9-8618-5d5a8b5dec90.png)


## 3. First fit

There may be many holes in the memory, so the operating system, to reduce the amount of time it spends analyzing the available spaces, begins at the start of primary memory and allocates memory from the first hole it encounters large enough to satisfy the request. Using the same example as above, first fit will allocate 12KB of the 14KB block to the process.
Its advantage is that it is the fastest search as it searches only the first block i.e. enough to assign a process.

### Code Screenshot

![image4](https://user-images.githubusercontent.com/48055152/58042992-c0e43d80-7b59-11e9-9605-343b5403a6a1.png)


#### All above strategies are implemented using linked list.
#### This code is created by Mehul Patni in C++
