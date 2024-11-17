#include <check_bst.h>

#include <gtest/gtest.h>

TEST(BST_S, SampleCase)
{
	//Initialize tree
	BinarySearchTree<std::string, std::string> testTree;

	//Perform operations on the tree
	testTree.insert(std::make_pair("test", "value"));

	//Checks the structure of the tree
	EXPECT_TRUE(verifyBST(testTree));

	//Perform additional checks
	EXPECT_EQ("value", testTree.find("test")->second);
}


TEST(BST_S, Random50InsertRemove)
{
	srand(0);

	BinarySearchTree<int, int> testTree;
	std::set<int> items;

	//Add 50 items
	for(size_t counter = 0; counter < 50; counter++)
	{
		int random = rand();
		testTree.insert(std::make_pair(random, random));
		items.insert(random);
	}

	//Verify tree
	EXPECT_TRUE(verifyBST(testTree));
    for(auto it = items.begin(); it != items.end(); it++)
	{
		EXPECT_EQ(*it, testTree.find(*it)->second);
	}

	//Remove Items
	for(auto it = items.begin(); it != items.end(); it++)
	{
		testTree.remove(*it);
	}

	//Verify tree
	EXPECT_TRUE(verifyBST(testTree));
	EXPECT_TRUE(testTree.empty());

}

/************************ ==== ************************
 |                        SELF                        |
 ************************ ==== ************************/

#include <set>
#include <vector>
#include <unordered_set>

#define DO_BSTSTRESS 0
#define DO_BSTNORMAL 1

#ifndef VMAC
#define VMAC
#define vcA template<class A
vcA> using V = std::vector<A>;
using vi = V<int>;
#endif

#if DO_BSTNORMAL

TEST(BST,Remove_Empty) {
    BinarySearchTree<int,int> ttree;
    for(int i = 10; i <= 100; i+=10)
        ttree.remove(i);
    EXPECT_TRUE(ttree.empty()) << "\n\033[31mHOW\n\033[0m";
}

TEST(BST,Insert_Dupes) {
    //  dupe write over -> -in[i] to in[i]
    //  in
    vi in = {30,20,40,10,25,35,50};

    //  insert & check valid
    BinarySearchTree<int,int> ttree;
    for(auto&i:in) {
        ttree.insert({i,-i});
        EXPECT_TRUE(verifyBST(ttree));
    }
    for(auto&i:in)
        EXPECT_EQ(-i,ttree.find(i)->second);

    //  write over
    for(auto&i:in) {
        ttree.insert({i,i});
        EXPECT_TRUE(verifyBST(ttree));
    }
    for(auto&i:in)
        EXPECT_EQ(i,ttree.find(i)->second);
    EXPECT_FALSE(ttree.empty());
}

TEST(BST,ExactNodeCount_Remove_Case1) {
    //  in, out, leftover
    vi in = {10,5,15,1,7,12,19,6,9,13};
    vi out = {1,6,9,13,19};
    vi leftover = {10,5,15,7,12};

    //  insert & check for presence of in & validity
    BinarySearchTree<int,int> ttree;
    for(auto&i:in) {
        ttree.insert({i,-i});
        EXPECT_TRUE(verifyBST(ttree));
    }
    for(auto&i:in)
        EXPECT_EQ(-i,ttree.find(i)->second);
    
    //  remove & check for bst validity
    for(auto&i:out) {
        ttree.remove(i);
        EXPECT_TRUE(verifyBST(ttree));
    }
    
    //  check for presence of out 5
    auto it = BinarySearchTree<int,int>::iterator(NULL);
    for(auto&i:out)
        EXPECT_EQ(it,ttree.find(i));

    //  check for prescence of leftover 5
    //  check for correct key in leftover 5
    for(auto&i:leftover) {
        EXPECT_NE(it,ttree.find(i));
        EXPECT_EQ(-i,ttree.find(i)->second);
    }
    EXPECT_FALSE(ttree.empty());
}

TEST(BST,ExactNodeCount_Remove_Case2) {
    //  no leftover
    vi in = {10,20,30,40,50,5,15,25,35,45};
    vi out = {50,45,40,35,30,25,20,15,10,5};

    //  insert & check valid
    BinarySearchTree<int,int> ttree;
    for(auto&i:in) {
        ttree.insert({i,-i});
        EXPECT_TRUE(verifyBST(ttree));
    }
    for(auto&i:in)
        EXPECT_EQ(-i,ttree.find(i)->second);
    
    //  remove & check valid
    for(auto&i:out) {
        ttree.remove(i);
        EXPECT_TRUE(verifyBST(ttree));
    }

    //  check for presence of in
    auto it = BinarySearchTree<int,int>::iterator(NULL);
    for(auto&i:in)
        EXPECT_EQ(it,ttree.find(i));
    EXPECT_TRUE(ttree.empty());
}

TEST(BST,ExactNodeCount_Remove_Case3) {
    //  all deletes are case 3
    vi in = {50,40,30,20,10,55,45,35,25,15};
    vi out = {20,15,30,25,40,35,50,45};
    vi leftover = {10,55};

    //  insert & check valid
    BinarySearchTree<int,int> ttree;
    for(auto&i:in) {
        ttree.insert({i,-i});
        EXPECT_TRUE(verifyBST(ttree));
    }
    for(auto&i:in)
        EXPECT_EQ(-i,ttree.find(i)->second);
    
    //  remove & check valid
    for(auto&i:out) {
        ttree.remove(i);
        EXPECT_TRUE(verifyBST(ttree));
    }

    //  check presence of in
    auto it = BinarySearchTree<int,int>::iterator(NULL);
    for(auto&i:out)
        EXPECT_EQ(it,ttree.find(i));
    EXPECT_FALSE(ttree.empty());
    
    //  check presence of leftovers
    for(auto&i:leftover)
        EXPECT_EQ(-i,ttree.find(i)->second);
}

TEST(BST,Iterator_Empty) {
    BinarySearchTree<int,int> ttree;
    auto it = ttree.begin();
    int ct = 0;
    while(it != ttree.end()) {
        ++it;
        ++ct;
    }
    EXPECT_EQ(ct,0);
}

TEST(BST,Iterator_RandomAccess) {
    //  in
    vi in = {1,2,3,4,5,6,7,8,9,10};
    BinarySearchTree<int,int> ttree;
    
    //  insert
    for(auto&i:in) {
        ttree.insert({i,-i});
        EXPECT_TRUE(verifyBST(ttree));
    }
    
    //  test all val
    for(auto&i:in)
        EXPECT_EQ(-i,ttree.find(i)->second);
    
    //  test random access to all elements
    for(auto&i:in) {
        auto it = ttree.find(i);
        EXPECT_EQ(i,it->first);
        EXPECT_EQ(-i,it->second);
        for(int j = 10-i; j >= 0; --j) {
            EXPECT_NE(it,ttree.end());
            ++it;
        }
    }
}

TEST(BST,Iterator_Case1) {
    //  normal
    vi in = {30,20,40,10,25,35,50};
    vi sorted = {10,20,25,30,35,40,50};
    
    //  insert & check valid
    BinarySearchTree<int,int> ttree;
    for(auto&i:in)
        ttree.insert({i,-i});
    EXPECT_TRUE(verifyBST(ttree));
    for(auto&i:in)
        EXPECT_EQ(-i,ttree.find(i)->second);

    //  check inorder operator
    int i = 0;
    auto it = ttree.begin();
    while(it != ttree.end()) {
        EXPECT_EQ(-sorted[i],it->second);
        EXPECT_EQ(sorted[i],it->first);
        ++it;
        ++i;
    }
    EXPECT_EQ(i,in.size());
    EXPECT_FALSE(ttree.empty());
}

TEST(BST,Iterator_Case2) {
    //  normal
    vi in = {10,9,8,7,6,5,4,3,2,1};
    vi sorted = {1,2,3,4,5,6,7,8,9,10};
    
    //  insert & check valid
    BinarySearchTree<int,int> ttree;
    for(auto&i:in) {
        ttree.insert({i,-i});
        EXPECT_TRUE(verifyBST(ttree));
    }
    for(auto&i:in)
        EXPECT_EQ(-i,ttree.find(i)->second);

    //  check inorder operator
    int i = 0;
    auto it = ttree.begin();
    while(it != ttree.end()) {
        EXPECT_EQ(sorted[i],it->first);
        EXPECT_EQ(-sorted[i],it->second);
        ++it,
        ++i;
    }
    EXPECT_EQ(i,in.size());
    EXPECT_FALSE(ttree.empty());
}

TEST(BST,Iterator_Case3) {
    //  normal
    vi in = {1,2,3,4,5,6,7,8,9,10};
    vi sorted = {1,2,3,4,5,6,7,8,9,10};
    
    //  insert & check valid
    BinarySearchTree<int,int> ttree;
    for(auto&i:in) {
        ttree.insert({i,-i});
        EXPECT_TRUE(verifyBST(ttree));
    }
    for(auto&i:in)
        EXPECT_EQ(-i,ttree.find(i)->second);

    //  check inorder operator
    int i = 0;
    auto it = ttree.begin();
    while(it != ttree.end()) {
        EXPECT_EQ(sorted[i],it->first);
        EXPECT_EQ(-sorted[i],it->second);
        ++it,
        ++i;
    }
    EXPECT_EQ(i,in.size());
    EXPECT_FALSE(ttree.empty());
}

#endif

#if DO_BSTSTRESS

TEST(BST,Stress_Insert) {
    //  ~150 ms on my machine
    //  seed/vars
    srand(0xb000b1e5);
    std::set<int> s;
    BinarySearchTree<int,int> ttree;

    //  insert
    for(int i = 0; i < 100000; ++i) {
        int r = rand() % 1000000007;
        while(s.count(r))
            r = rand() % 1000000007;
        s.insert(r);
        ttree.insert({r,-r});
    }
    EXPECT_TRUE(verifyBST(ttree));
    EXPECT_FALSE(ttree.empty());

    //  check presence of w/ iterator
    int i = 0;
    auto s_it = s.begin();
    auto t_it = ttree.begin();
    while(t_it != ttree.end()) {
        EXPECT_EQ(*s_it,t_it->first);
        EXPECT_EQ(-(*s_it),t_it->second);
        ++t_it,
        ++s_it,
        ++i;
    }
    EXPECT_EQ(i,s.size());
}

TEST(BST,Stress_Insert_Dupe) {
    //  also ~150 ms on my machine
    //  seed/vars
    srand(0xdeadbeef);
    std::set<int> s;
    BinarySearchTree<int,int> ttree;

    //  insert
    for(int i = 0; i < 100000; ++i) {
        int r = rand() % 1000000007;
        s.insert(r);
        ttree.insert({r,-r});
    }
    EXPECT_TRUE(verifyBST(ttree));
    EXPECT_FALSE(ttree.empty());

    //  check presence of w/ iterator
    int i = 0;
    auto s_it = s.begin();
    auto t_it = ttree.begin();
    while(t_it != ttree.end()) {
        EXPECT_EQ(*s_it,t_it->first);
        EXPECT_EQ(-(*s_it),t_it->second);
        ++t_it,
        ++s_it,
        ++i;
    }
    EXPECT_EQ(i,s.size());
}

TEST(BST,Stress_Remove) {
    //  ~130 ms on my machine lmao
    //  seed/vars
    srand(0x6c278ab9);
    std::unordered_set<int> s;
    BinarySearchTree<int,int> ttree;

    //  insert
    for(int i = 0; i < 100000; ++i) {
        int r = rand() % 1000000007;
        while(s.count(r))
            r = rand() % 1000000007;
        s.insert(r);
        ttree.insert({r,-r});
    }
    EXPECT_TRUE(verifyBST(ttree));
    EXPECT_FALSE(ttree.empty());

    //  delete
    for(auto&i:s)
        ttree.remove(i);
    EXPECT_TRUE(ttree.empty());
}

TEST(BST,Stress_Remove_Dupe) {
    //  also ~130 ms on my machine lmao
    //  seed/vars
    srand(0x1ee71ee7);
    std::unordered_set<int> s;
    BinarySearchTree<int,int> ttree;

    //  insert
    for(int i = 0; i < 100000; ++i) {
        int r = rand() % 1000000007;
        s.insert(r);
        ttree.insert({r,-r});
    }
    EXPECT_TRUE(verifyBST(ttree));
    EXPECT_FALSE(ttree.empty());

    //  delete
    for(auto&i:s)
        ttree.remove(i);
    EXPECT_TRUE(ttree.empty());
}

#endif