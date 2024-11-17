# Table of Contents

1. [AVL_B](#avl_b)
   - [IteratorAll](#iteratorall)
   - [RemoveEmpty](#removeempty)
   - [Remove_Root](#remove_root)
   - [Remove_DNE](#remove_dne)
   - [Insert_Dupes](#insert_dupes)
   - [Simple_Remove_Case1](#simple_remove_case1)
   - [Simple_Remove_Case2](#simple_remove_case2)
   - [Simple_Remove_Case3](#simple_remove_case3)
2. [AVL_R](#avl_r)
   - [Simple_LeftOnly](#simple_leftonly)
   - [Simple_RightOnly](#simple_rightonly)
   - [Simple_RightLeft](#simple_rightleft)
   - [Simple_LeftRight](#simple_leftright)
   - [InsertDelete100](#insertdelete100)
3. [Stress Tests](#stress-tests)
   - [Stress_Insert](#stress_insert)
   - [Stress_Iterator](#stress_iterator)
   - [Stress_InsertDelete](#stress_insertdelete)
   - [Stress_InsertDeleteIterator_Dupes](#stress_insertdeleteiterator_dupes)

---

# AVL_B 
- `AVL_B` = AVL basic, no rotation
- **TO ENABLE THESE TESTCASES, SET "DO_NOROTATION" to 1** 
- "`#define DO_NOROTATION 1`"
- **TO DISABLE THESE TESTCASES, SET 1 -> 0**

### IteratorAll
- Inserts: pairs `{x,-x}` in the order defined by `vector<int> in`, where `x` is an `int` in `in`
- Removes: `nothing` (default `AVLTree` destructor called)
- Expects: `see below`
- Tests: iterators based on the sorted order defined by `vector<int> sorted`
- Test flow: [insert]->[inorder iterator test]->[check all random access iterators]

### RemoveEmpty
- Inserts: `nothing`
- Removes: `rand()`
- Expects: `tree empty`
- Test flow: [10*remove]

### Remove_Root
- Inserts: `{1,-1}` (if you aren't familiar with inserting pairs/vectors/etc. using `{x,y}`, search `brace-enclosed initializer list`)
- Removes: `KEY = 1`
- Expects: `{}`, empty tree
- Test flow: [insert `{1,-1}`]->[verify AVL]->[remove `KEY = 1`]->[verify empty tree]

### Remove_DNE
- Inserts: pairs `{x,-x}` in the order defined by `vector<int> in`, where `x` is an `int` in `in`
- Removes: `nothing`
- Expects: `see below`
- Tests: 
    - AVL validity after each insert
    - Presence of all original items inserted (all pairs `{x,-x}`)
    - If tree is empty
- Test flow: [insert all `{x,-x}`, verify]->[remove `KEY = not in tree`]->[verify presence of all original pairs]->[check tree not empty]

### Insert_Dupes
- Inserts: pairs `{x,-x}` in the order defined by `vector<int> in`, where `x` is an `int` in `in`
- Removes: `KEY = x` in the order defined by `vector<int> out`, where `x` is an `int` in `out`
- Expects: overwritten values
- Tests:
    - AVL validity after each insert
    - Original key-value pair values before overwrite
    - AVL validity after overwrite
    - Changed key-value pair values after overwrite
    - If tree is empty after removing all
- Test flow: [insert all `{x,-x}`, verify]->[insert all `{x,x}`, verify]->[remove all]->[check tree empty]

### Simple_Remove_Case1
- Inserts: pairs `{x,-x}` in the order defined by `vector<int> in`, where `x` is an `int` in `in`
- Removes: `KEY = x` in the order defined by `vector<int> out`, where `x` is an `int` in `out`
- Expects: empty tree in the end
- Tests:
    - Removing nodes with no children
    - AVL validity after every operation
- Test flow: [insert all, verify]->[delete all, verify]

### Simple_Remove_Case2
- Inserts: pairs `{x,-x}` in the order defined by `vector<int> in`, where `x` is an `int` in `in`
- Removes: `KEY = x` in the order defined by `vector<int> out`, where `x` is an `int` in `out`
- Expects: empty tree in the end
- Tests:
    - Removing nodes with 1 child
    - AVL validity after very operation
- Test flow: [insert all, verify]->[delete all, verify]

### Simple_Remove_Case3 
- This test is `predecessor`/`successor` independent
- Inserts: pairs `{x,-x}` in the order defined by `vector<int> in`, where `x` is an `int` in `in`
- Removes: `KEY = x` in the order defined by `vector<int> out`, where `x` is an `int` in `out`
- Expects: not empty tree in the end
- Tests:
    - Remove nodes with 2 children (1 root, 1 non root)
    - Both predecessor and successor configs using bfs (only need to get 1 correct)
- Test flow: [insert all, verify]->[delete key 1, verify]->[delete key 2, verify]

---

# AVL_R
- `AVL_R` = AVL with rotation
- **TO ENABLE THESE TESTCASES, SET "DO_ROTATION" to 1** 
- "`#define DO_ROTATION 1`"
- **TO DISABLE THESE TESTCASES, SET 1 -> 0**

### Simple_LeftOnly
- Inserts: pairs `{x,-x}` in the order defined by `vector<vector<int>> in`, where `x` is an `int` in `in[i]`
- Removes: everything in the same order as insertion
- Expects: an configuration validated using bfs
- Tests:
    - 3 subtests for single left rotations (zig zig)
    - All rotations **will** be single left rotations
- Test flow: [run all subtests]->[insert, verify]->[verify with bfs]

### Simple_RightOnly
- Same as `Simple_LeftOnly` except only right rotations (zag zag)

### Simple_RightLeft
- Same as `Simple_LeftOnly` except only right+left rotations (zag zig)

### Simple_LeftRight
- Same as `Simple_LeftOnly` except only left+right rotations (zig zag)

### InsertDelete100
- Seed = `0xf00df00d`
- Inserts: random pairs with key `x range = [1,100]`, `{x,-x}`, no dupes, random order
- Removes: everything in a random order
- Tests: expects `verifyAVL` to return `true` after each `insert` and `remove` call
- Test flow: [insert all, verify]->[shuffle order]->[delete all, verify]

---

# Stress tests 
- Also part of the `AVL_R` test suite
- **TO ENABLE THESE TESTCASES, SET "DO_AVLSTRESS" to 1** 
- "`#define DO_AVLSTRESS 1`"
- **TO DISABLE THESE TESTCASES, SET 1 -> 0**

### Stress_Insert 
- Seed = `0x5499fb55`
- Inserts: `100'000` randomly generated pairs
- Removes: `nothing`
- Tests: 
    - `OPTIONAL:` checks AVL integrity every `1'000` inserts
    - Checks AVL integrity after all `100'000` inserts
    - If tree is empty
- Test flow: [insert]->[test]

### Stress_Iterator
- Seed = `0xeb61803c`
- Inserts: in the same manner as `Stress_Insert`
- Removes: `nothing`
- Tests:
    - Complete inorder traversal using iterator
- Test flow: [insert]->[iterator]->[tree empty tests etc]

### Stress_InsertDelete
- Seed = `0x5700b135`
- Inserts: in the same manner as `InsertDelete100`
- Removes: in the same manner as `InsertDelete100`
- Tests: the same as `InsertDelete100` just much more
- Test flow: the same as `InsertDelete100`

### Stress_InsertDeleteIterator_Dupes
- Tests overwrites for accuracy, removes based on `unordered_map` indexing order, tests iterator again