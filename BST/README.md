# Table of Contents

1. [BST (Normal, Non-Stress Tests)](#bst)
   - [Remove_Empty](#remove_empty)
   - [Insert_Dupes](#insert_dupes)
   - [ExactNodeCount_Remove_Case1](#exactnodecount_remove_case1)
   - [ExactNodeCount_Remove_Case2](#exactnodecount_remove_case2)
   - [ExactNodeCount_Remove_Case3](#exactnodecount_remove_case3)
   - [Iterator_Empty](#iterator_empty)
   - [Iterator_RandomAccess](#iterator_randomaccess)
   - [Iterator_Case1](#iterator_case1)
   - [Iterator_Case2](#iterator_case2)
   - [Iterator_Case3](#iterator_case3)
2. [Stress Tests (Also BST)](#stress-tests)
   - [Stress_Insert](#stress_insert-seed)
   - [Stress_Insert_Dupe](#stress_insert_dupe)
   - [Stress_Remove](#stress_remove)
   - [Stress_Remove_Dupe](#stress_remove_dupe)

---

# BST
- Normal, non-stress tests in the `BST` test suite
- **TO ENABLE THESE TESTCASES, SET "DO_BSTNORMAL" to 1** 
- "`#define DO_BSTNORMAL 1`"
- **TO DISABLE THESE TESTCASES, SET 1 -> 0**

### Remove_Empty
- Removes from an empty tree

### Insert_Dupes
- Checks for value overwrite

### ExactNodeCount_Remove_Case1
- Remove case `1` = remove child with `0` parents
- This test will check the BST to make sure that it consists of only valid nodes

### ExactNodeCount_Remove_Case2
- Remove case `2` = remove child with `1` parent
- This test will check the BST to make sure that it consists of only valid nodes

### ExactNodeCount_Remove_Case3
- Remove case `3` = remove child with `2` parents
- This test will check the BST to make sure that it consists of only valid nodes
- This doesn't explicity test pointers so it works with both `successor` and `predecessor` (I tested)

### Iterator_Empty
- Tests `tree.begin()` on an empty tree

### Iterator_RandomAccess
- Tests iterator from `find` function for every key-value pair in the tree

### Iterator_Case1
- Normal tree

### Iterator_Case2
- Tree is a line starting from `tree.begin()` going to `tree.root_`

### Iterator_Case3
- Tree is a line starting from `tree.root_` going to `tree.end()` (to the right)

---

# Stress tests
- Also part of the `BST` test suite
- **TO ENABLE THESE TESTCASES, SET "DO_BSTSTRESS" to 1** 
- "`#define DO_BSTSTRESS 1`"
- **TO DISABLE THESE TESTCASES, SET 1 -> 0**

### Stress_Insert
- Seed = `0xb00b1e5`
- Inserts `100'000` items (no dupes)
- Checks with iterator and `std::set`

### Stress_Insert_Dupe
- Seed = `0xdeadbeef`
- Inserts `100'000` items
- Checks with iterator and set

### Stress_Remove
- Seed = `0x6c278ab9`
- Inserts `100'000` (no dupes), removes `100'000` using `std::unordered_set` indexing order

### Stress_Remove_Dupe
- Seed = `0x1ee71ee7`
- Inserts `100'000`, removes `100'000` using `std::unordered_set` indexing order