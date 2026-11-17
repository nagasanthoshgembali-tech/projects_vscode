# Binary Search - Student Notebook

## 📚 Table of Contents
1. [Introduction](#introduction)
2. [How Binary Search Works](#how-binary-search-works)
3. [Algorithm Explanation](#algorithm-explanation)
4. [Code Walkthrough](#code-walkthrough)
5. [Time & Space Complexity](#time--space-complexity)
6. [Examples](#examples)
7. [Practice Problems](#practice-problems)
8. [Key Takeaways](#key-takeaways)

---

## Introduction

**Binary Search** is a highly efficient algorithm for finding a target value in a **sorted array**. It works by repeatedly dividing the search interval in half, eliminating half of the remaining elements with each comparison.

### Prerequisites
- The array **MUST be sorted** (in ascending or descending order)
- Works best with arrays that have random access (like arrays or lists)

---

## How Binary Search Works

### Step-by-Step Approach

1. Start with the entire sorted array
2. Find the middle element
3. Compare the middle element with the target:
   - **Equal**: Target found! Return the index
   - **Target < Middle**: Search the left half
   - **Target > Middle**: Search the right half
4. Repeat until target is found or search space becomes empty

### Visual Example

```
Array: [2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78]
Target: 23

Step 1: left=0, right=10, mid=5
        Array[5] = 23  ✓ Found at index 5!

Example with target 56:

Step 1: left=0, right=10, mid=5
        Array[5] = 23  (56 > 23, search right)
        
Step 2: left=6, right=10, mid=8
        Array[8] = 56  ✓ Found at index 8!
```

---

## Algorithm Explanation

### The Algorithm (Iterative Approach)

```
1. Initialize left = 0, right = array_size - 1
2. While left <= right:
   a. Calculate mid = left + (right - left) / 2
   b. If arr[mid] == target:
      - Return mid (target found)
   c. Else if arr[mid] < target:
      - left = mid + 1 (search right half)
   d. Else:
      - right = mid - 1 (search left half)
3. Return -1 (target not found)
```

### Why `left + (right - left) / 2`?

This formula avoids **integer overflow** that could occur with `(left + right) / 2` when dealing with very large indices.

---

## Code Walkthrough

### Function Signature

```c
int binarySearch(int arr[], int size, int target)
```

- **Parameters:**
  - `arr[]`: The sorted array to search in
  - `size`: Number of elements in the array
  - `target`: The element we're looking for
- **Return Value:**
  - Index of target if found (0 to size-1)
  - -1 if target is not in the array

### Detailed Code Analysis

```c
int binarySearch(int arr[], int size, int target) {
    int left = 0;              // Start pointer at beginning
    int right = size - 1;      // End pointer at last element

    while (left <= right) {    // Continue while search space exists
        int mid = left + (right - left) / 2;  // Find middle (safe formula)

        if (arr[mid] == target) {        // Target found!
            return mid;                   // Return its index
        } else if (arr[mid] < target) {  // Target is in right half
            left = mid + 1;               // Move left pointer right
        } else {                          // Target is in left half
            right = mid - 1;              // Move right pointer left
        }
    }

    return -1;  // Target not found in array
}
```

### Main Function Flow

1. **Input**: Takes array size from user
2. **Array Input**: Reads sorted array elements
3. **Target Input**: Reads the element to search for
4. **Search**: Calls binarySearch()
5. **Output**: Reports whether element was found and its index

---

## Time & Space Complexity

### Time Complexity: **O(log n)**

| Operation | Iterations |
|-----------|-----------|
| Array size: 8 | max 3 comparisons (2³ = 8) |
| Array size: 1,000 | max 10 comparisons (2¹⁰ ≈ 1000) |
| Array size: 1,000,000 | max 20 comparisons (2²⁰ ≈ 1M) |

**Why logarithmic?** Because we eliminate half the remaining elements with each comparison.

### Space Complexity: **O(1)**

- Uses only a constant amount of extra space (left, right, mid variables)
- No recursive calls, so no call stack overhead

### Comparison with Linear Search

| Aspect | Linear Search | Binary Search |
|--------|---------------|---------------|
| **Time** | O(n) | O(log n) |
| **Best case** | O(1) | O(1) |
| **Prerequisite** | None | Array must be sorted |
| **Example (n=1M)** | ~1M operations | ~20 operations |

---

## Examples

### Example 1: Target Found

```
Array: [1, 3, 5, 7, 9, 11, 13]
Target: 7

Iteration 1: left=0, right=6, mid=3, arr[3]=7 ✓ Found!
Return: 3
```

### Example 2: Target in Right Half

```
Array: [1, 3, 5, 7, 9, 11, 13]
Target: 11

Iteration 1: left=0, right=6, mid=3, arr[3]=7
            7 < 11, so left = 4
            
Iteration 2: left=4, right=6, mid=5, arr[5]=11 ✓ Found!
Return: 5
```

### Example 3: Target in Left Half

```
Array: [1, 3, 5, 7, 9, 11, 13]
Target: 3

Iteration 1: left=0, right=6, mid=3, arr[3]=7
            3 < 7, so right = 2
            
Iteration 2: left=0, right=2, mid=1, arr[1]=3 ✓ Found!
Return: 1
```

### Example 4: Target Not Found

```
Array: [1, 3, 5, 7, 9, 11, 13]
Target: 6

Iteration 1: left=0, right=6, mid=3, arr[3]=7
            6 < 7, so right = 2
            
Iteration 2: left=0, right=2, mid=1, arr[1]=3
            6 > 3, so left = 2
            
Iteration 3: left=2, right=2, mid=2, arr[2]=5
            6 > 5, so left = 3
            
Iteration 4: left=3, right=2
            left > right, exit loop
Return: -1 (not found)
```

---

## Practice Problems

### Problem 1: Find First Occurrence
Modify binary search to find the **first occurrence** of a target in an array with duplicates.

**Hint:** When target is found, don't return immediately. Instead, keep searching the left half.

### Problem 2: Find Last Occurrence
Modify binary search to find the **last occurrence** of a target in an array with duplicates.

**Hint:** When target is found, search the right half.

### Problem 3: Find Insertion Position
Given a sorted array and a target, find the position where the target should be inserted to keep the array sorted.

**Example:** Array [1, 3, 5, 7], Target 6 → Insert at index 3

### Problem 4: Search in Rotated Sorted Array
An array was originally sorted, then rotated. Search for a target in it.

**Example:** Array [4, 5, 6, 7, 0, 1, 2], Target 0

### Problem 5: Peak Element
Find the index of a peak element (an element greater than its neighbors).

---

## Key Takeaways

### ✅ When to Use Binary Search
- Data is **sorted**
- Need to search frequently
- Array is large (O(log n) advantage is significant)
- Random access is available

### ❌ When NOT to Use Binary Search
- Array is unsorted (unless you sort it first)
- Need to find all occurrences (not just first)
- Data structure doesn't support random access (use linear search on linked lists)

### 💡 Important Points
1. **Array MUST be sorted** - This is the fundamental requirement
2. **Safe mid calculation** - Use `left + (right - left) / 2` to avoid overflow
3. **Loop condition** - Use `while (left <= right)` for inclusive search
4. **Index bounds** - Always check that indices stay within valid range

### 🚀 Variations & Extensions
- **Recursive Binary Search**: Same logic but uses recursion
- **Binary Search on Rotated Array**: Needs modification to handle rotation
- **Binary Search for Range**: Find first and last occurrence of target
- **Binary Search on Infinite Arrays**: Need to find bounds first

---

## Summary Table

| Aspect | Details |
|--------|---------|
| **Time Complexity** | O(log n) |
| **Space Complexity** | O(1) |
| **Best for** | Sorted arrays, frequent searches |
| **Prerequisite** | Array must be sorted |
| **Difficulty** | Easy to implement, easy to make mistakes |
| **Real-world use** | Search engines, databases, version control |

---

## Notes for Self

- [ ] Understand why sorting is required
- [ ] Practice finding bugs in binary search implementations
- [ ] Try implementing recursive version
- [ ] Solve at least 3 practice problems above
- [ ] Compare performance with linear search on large arrays

---

**Happy Learning! 🎓**
