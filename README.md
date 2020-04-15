# Buddy-System-Memory-Allocation
COA Mini project for SE sem 4

<table style="width: 100%;" cellpadding="1">
<tbody>
<tr>
<td style="width: 49.9136%;">&nbsp;60004180110</td>
<td style="width: 67.0864%;">&nbsp;Tejas Ghone</td>
</tr>
<tr>
<td style="width: 49.9136%;">&nbsp;60004180119</td>
<td style="width: 67.0864%;">&nbsp;Vatsal Soni&nbsp;</td>
</tr>
<tr>
<td style="width: 49.9136%;">&nbsp;60004180125</td>
<td style="width: 67.0864%;">&nbsp;Yashodhan Joshi&nbsp;</td>
</tr>
<tr>
<td style="width: 49.9136%;">&nbsp;60004180127</td>
<td style="width: 67.0864%;">&nbsp;Yatharth Vyas&nbsp;</td>
</tr>
</tbody>
</table>
### About
The buddy system is a memory allocation and management algorithm that manages memory in power of two increments. Assume the memory size is 2U, suppose a size of S is required.
If 2U-1<S<=2U: Allocate the whole block
Else: Recursively divide the block equally and test the condition at each time, when it satisfies, allocate the block and get out the loop.

### Description
Buddy allocation system is an algorithm in which a larger memory block is divided into small parts to satisfy the request. This algorithm is used to give best fit. The two smaller parts of block are of equal size and called as buddies. In the same manner one of the two buddies will further divide into smaller parts until the request is fulfilled. Benefit of this technique is that the two buddies can combine to form the block of larger size according to the memory request.

### Implementation and efficiency
In comparison to other simpler techniques such as dynamic allocation, the buddy memory system has little external fragmentation, and allows for compaction of memory with little overhead. The buddy method of freeing memory is fast, with the maximal number of compactions required equal to log2(highest order). Typically the buddy memory allocation system is implemented with the use of a binary tree to represent used or unused split memory blocks. The "buddy" of each block can be found with an exclusive OR of the block's address and the block's size.
