#include "check_avl.h"

#include <gtest/gtest.h>

#include <set>

TEST(AVL_SAMPLE, SampleCase)
{
	//Initialize tree
	AVLTree<std::string, std::string> testTree;

	//Perform operations on the tree
	testTree.insert(std::make_pair("test", "value"));

	//Checks the structure of the tree
	EXPECT_TRUE(verifyAVL(testTree));

	//Perform additional checks
	EXPECT_EQ("value", testTree.find("test")->second);
}

TEST(AVL_SAMPLE, Random50InsertRemove)
{
	srand(0);

	AVLTree<int, int> testTree;
	std::set<int> items;

	//Add 50 items
	for(size_t counter = 0; counter < 50; counter++)
	{
		int random = rand();
		testTree.insert(std::make_pair(random, random));
		items.insert(random);
	}

	//Verify tree
	EXPECT_TRUE(verifyAVL(testTree));
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
	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.empty());

}

/************************ ==== ************************
 |                        SELF                        |
 ************************ ==== ************************/

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#define DO_AVLSTRESS 0
#define DO_NOROTATION 1
#define DO_ROTATION 1

#ifndef VMAC
#define VMAC
#define vcA template<class A
vcA> using V = std::vector<A>;
vcA> using MAT = V<V<A>>;
using vi = V<int>;
using mat = V<vi>;
#endif

#ifndef BFS_VDN
#define BFS_VDN
bool eq(vi a, vi b) {
    int len = a.size();
    if((int)b.size() < len)
        len = b.size();
    for(int i = 0; i < len; ++i)
        if(a[i] != b[i])
            return 0;
    return 1;
}

vi bfs(AVLTree<int,int>& t) {
    vi ret(15,-1);
    V<AVLNode<int,int>*> b(15,nullptr);
    b[0] = static_cast<AVLNode<int,int>*>(t.root_);
    for(int i = 0; i < 7; ++i) {
        if(b[i]) {
            b[i*2+1] = b[i]->getLeft();
            b[i*2+2] = b[i]->getRight();
        }
    }
    for(int i = 0; i < 15; ++i)
        if(b[i])
            ret[i] = b[i]->getKey();
    return ret;
}

vi bfs_par(AVLTree<int,int>& t) {
    vi ret(15,-1);
    V<AVLNode<int,int>*> b(15,nullptr);
    b[0] = static_cast<AVLNode<int,int>*>(t.root_);
    for(int i = 0; i < 7; ++i) {
        if(b[i]) {
            b[i*2+1] = b[i]->getLeft();
            b[i*2+2] = b[i]->getRight();
        }
    }
    for(int i = 0; i < 15; ++i)
        if(b[i] && b[i]->getParent())
            ret[i] = b[i]->getParent()->getKey();
    return ret;
}
#endif

#if DO_NOROTATION

TEST(AVL_B,Iterator_All) {
    //  in
    vi in = {4,2,6,1,3,5,7};
    vi sorted = {1,2,3,4,5,6,7};
    AVLTree<int,int> ttest;

    //  ins all
    for(auto&i:in) {
        ttest.insert({i,-i});
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL CHECK WHEN INSERTING: " << i << "\n\033[0m";
    }
    EXPECT_FALSE(ttest.empty()) << "\n\033[31mTREE IS EMPTY\n\033[0m";

    //  test inorder iter
    auto it = ttest.begin();
    int i = 0;
    while(it != ttest.end()) {
        EXPECT_EQ(-sorted[i],it->second) << "\n\033[31mMISMATCH VALUE: " << it->second << " WITH EXPECTED KEY: " << -sorted[i] << "\n\033[0m";
        EXPECT_EQ(sorted[i],it->first) << "\n\033[31m:MISMATCH KEY: " << it->first << " WITH EXPECTED KEY: " << sorted[i] << "\n\033[0m";
        ++it;
        ++i;
    }
    EXPECT_EQ(i,sorted.size()) << "\n\033[31mEXP SIZE = 7, ACTUAL SIZE = " << i << "\n\033[0m";

    //  random access
    for(auto&i:sorted) {
        auto r_it = ttest.find(i);
        for(int j = 0; j < (7-i); ++j) {
            EXPECT_NE(r_it,ttest.end()) << "\n\033[31mITERATOR FAILS TO REACH END IN EXACTLY 7-i STEPS STARTING FROM: " << i << "\n\033[0m";
            ++r_it;
        }
    }
}

TEST(AVL_B,Remove_Empty) {
    AVLTree<int,int> ttest;
    for(int i = 0; i < 10; ++i) {
        ttest.remove(rand());
        EXPECT_TRUE(ttest.empty()) << "\n\033[31mTREE IS NOT EMPTY SOMEHOW\n\033[0m";
    }
}

TEST(AVL_B,Remove_Root) {
    AVLTree<int,int> ttest;
    ttest.insert({1,-1});
    EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED INSERT 1 NODE: {1,-1} PLEASE PASS NEXT TIME :(\n\033[0m";
    ttest.remove(1);
    EXPECT_TRUE(ttest.empty()) << "\n\033[31mEXPECTED TREE EMPTY, BUT IT IS NOT\n\033[0m";
}

TEST(AVL_B,Remove_DNE) {
    //  in
    vi in = {4,2,6,1,3,5,7};
    AVLTree<int,int> ttree;

    //  ins
    for(auto&i:in) {
        ttree.insert({i,-i});
        EXPECT_TRUE(verifyAVL(ttree)) << "\n\033[31mINSERT REQUIRES NO ROTATIONS, DO NOT FAIL AGAIN. FAILED AVL VERIFY AFTER INSERTING: " << i << "\n\033[0m";
    }
    
    //  rem
    for(int i = 8; i <= 50; ++i)
        ttree.remove(i);
    for(auto&i:in) {
        EXPECT_NE(ttree.end(),ttree.find(i)) << "\n\033[31mDID NOT FIND NODE (ALSO VALUE): " << i << "\n\033[0m";
    }
    EXPECT_FALSE(ttree.empty()) << "\n\033[31mEXPECTED TREE TO BE NOT EMPTY\n\033[0m";
}

TEST(AVL_B,Insert_Dupes) {
    //  in (no rotation)
    vi in = {4,2,6,1,3,5,7};
    vi out = {7,5,3,1,6,2,4};
    AVLTree<int,int> ttest;

    //  insert
    for(auto&i:in) {
        ttest.insert({i,-i});
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY AFTER INSERTING: " << i << "\n\033[0m";
    }
    for(auto&i:in)
        EXPECT_EQ(-i,ttest.find(i)->second) << "\n\033[31mWRONG VALUE FOR KEY: " << i << "\n\033[0m";

    //  insert dupes
    for(auto&i:in) {
        ttest.insert({i,i});
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY AFTER INSERTING DUPE: " << i << "\n\033[0m";
    }
    for(auto&i:in)
        EXPECT_EQ(i,ttest.find(i)->second) << "\n\033[31mWRONG VALUE FOR KEY: " << i << "\n\033[0m";
    
    //  remove all
    for(auto&i:out) {
        ttest.remove(i);
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY AFTER REMOVING: " << i << "\n\033[0m";
    }
    EXPECT_TRUE(ttest.empty()) << "\n\033[31mTREE IS NOT EMPTY\n\033[0m";
}

TEST(AVL_B,Simple_Remove_Case1) {
    //  1. remove non-root (remove 1,3)
    //  2. remove root (remove 2)
    //  in
    vi in = {2,1,3};
    vi out = {1,3,2};
    AVLTree<int,int> ttest;
    
    //  insert
    for(auto&i:in) {
        ttest.insert({i,-i});
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY AFTER INSERTING: " << i << "\n\033[0m";
    }

    //  rem
    for(auto&i:out) {
        ttest.remove(i);
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY AFTER REMOVING: " << i << "\n\033[0m";
    } 

    //  valid
    EXPECT_TRUE(ttest.empty());
}

TEST(AVL_B,Simple_Remove_Case2) {
    //  1. remove with left child (remove 2)
    //  2. remove with left child (remove 4)
    //  3. remove node with left child (remove 3)
    //  in
    vi in = {3,2,4,1,5};
    vi out = {2,4,5,3,1};
    AVLTree<int,int> ttest;
    
    //  insert
    for(auto&i:in) {
        ttest.insert({i,-i});
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY AFTER INSERTING: " << i << "\n\033[0m";
    }

    //  rem
    for(auto&i:out) {
        ttest.remove(i);
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY AFTER REMOVING: " << i << "\n\033[0m";
    } 

    //  valid
    EXPECT_TRUE(ttest.empty());
}

TEST(AVL_B,Simple_Remove_Case3) {
    //  in
    vi in = {3,2,5,1,4,6};
    vi out = {5,3};
    vi pre1 = {3,2,4,1,-1,-1,6};
    vi suc1 = {3,2,6,1,-1,4,-1};
    vi pre2 = {2,1,4,-1,-1,-1,6};
    vi suc2 = {4,2,6,1};
    AVLTree<int,int> ttest;

    //  insert
    for(auto&i:in) {
        ttest.insert({i,-i});
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY AFTER INSERTING: " << i << "\n\033[0m";
    }

    //  delete 1
    ttest.remove(out[0]);
    EXPECT_TRUE(eq(pre1,bfs(ttest))|eq(suc1,bfs(ttest))) << "\n\033[31mFAILED BOTH PREDECESSOR & SUCCESSOR TEST AFTER REMOVING: " << out[0] << "\n\033[0m";

    //  delete second
    ttest.remove(out[1]);
    EXPECT_TRUE(eq(pre2,bfs(ttest))|eq(suc2,bfs(ttest))) << "\n\033[31mFAILED BOTH PREDECESSOR & SUCCESSOR TEST AFTER REMOVING: " << out[1] << "\n\033[0m";

    //  valid
    EXPECT_FALSE(ttest.empty());
}

#endif

#if DO_ROTATION

TEST(AVL_R,Simple_LeftOnly) {
    //  in
    mat in = {{1,2,3,4,5},
              {1,2,3},
              {4,2,6,1,3,5,7,8,9}};
    mat b = {{2,1,4,-1,-1,3,5},             //  exp bfs config
             {2,1,3},
             {4,2,6,1,3,5,8,-1,-1,-1,-1,-1,-1,7,9}};
    AVLTree<int,int> ttest;

    //  for all subtests
    for(int j = 0; j < (int)in.size(); ++j) {
        //  ins all
        for(auto&i:in[j]) {
            ttest.insert({i,-i});
            EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY ON SUBTEST: " << j << " INSERTING KEY: " << i << "\n\033[0m";
        }

        //  bfs check
        EXPECT_TRUE(eq(b[j],bfs(ttest))) << "\n\033[31mFAILED BFS CHECK: SUBTEST " << j << "\n\033[0m";

        //  clear
        for(auto&i:in[j]) {
            ttest.remove(i);
            EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY ON SUBTEST: " << j << " REMOVING KEY: " << i << "\n\033[0m";
        }
        EXPECT_TRUE(ttest.empty()) << "\n\033[31mEXPECTED COMPLETE REMOVAL ON SUBTEST: " << j << "\n\033[0m";
    }
}

TEST(AVL_R,Simple_RightOnly) {
    //  in
    mat in = {{3,2,1},
              {4,3,5,2,1},
              {6,4,8,3,5,7,9,2,1}};
    mat b = {{2,1,3},                       //  exp bfs config
             {4,2,5,1,3},
             {6,4,8,2,5,7,9,1,3}}; 
    AVLTree<int,int> ttest;

    //  for all subtests
    for(int j = 0; j < (int)in.size(); ++j) {
        //  ins all
        for(auto&i:in[j]) {
            ttest.insert({i,-i});
            EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY ON SUBTEST: " << j << " INSERTING KEY: " << i << "\n\033[0m";
        }

        //  bfs check
        EXPECT_TRUE(eq(b[j],bfs(ttest))) << "\n\033[31mFAILED BFS CHECK: SUBTEST " << j << "\n\033[0m";

        //  clear
        for(auto&i:in[j]) {
            ttest.remove(i);
            EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY ON SUBTEST: " << j << " REMOVING KEY: " << i << "\n\033[0m";
        }
        EXPECT_TRUE(ttest.empty()) << "\n\033[31mEXPECTED COMPLETE REMOVAL ON SUBTEST: " << j << "\n\033[0m";
    }
}

TEST(AVL_R,Simple_LeftRight) {
    //  in
    mat in = {{3,1,2},
              {4,3,5,1,2},
              {4,3,7,1,2,5,6}};
    mat b = {{2,1,3},                       //  exp bfs config
             {4,2,5,1,3},
             {4,2,6,1,3,5,7}};
    AVLTree<int,int> ttest;

    //  for all subtests
    for(int j = 0; j < (int)in.size(); ++j) {
        //  ins all
        for(auto&i:in[j]) {
            ttest.insert({i,-i});
            EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY ON SUBTEST: " << j << " INSERTING KEY: " << i << "\n\033[0m";
        }

        //  bfs check
        EXPECT_TRUE(eq(b[j],bfs(ttest))) << "\n\033[31mFAILED BFS CHECK: SUBTEST " << j << "\n\033[0m";

        //  clear
        for(auto&i:in[j]) {
            ttest.remove(i);
            EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY ON SUBTEST: " << j << " REMOVING KEY: " << i << "\n\033[0m";
        }
        EXPECT_TRUE(ttest.empty()) << "\n\033[31mEXPECTED COMPLETE REMOVAL ON SUBTEST: " << j << "\n\033[0m";
    }
}

TEST(AVL_R,Simple_RightLeft) {
    //  in
    mat in = {{1,3,2},
              {2,1,3,5,4},
              {4,1,5,3,2,7,6}};
    mat b = {{2,1,3},
             {2,1,4,-1,-1,3,5},
             {4,2,6,1,3,5,7}};
    AVLTree<int,int> ttest;

    //  for all subtests
    for(int j = 0; j < (int)in.size(); ++j) {
        //  ins all
        for(auto&i:in[j]) {
            ttest.insert({i,-i});
            EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY ON SUBTEST: " << j << " INSERTING KEY: " << i << "\n\033[0m";
        }

        //  bfs check
        EXPECT_TRUE(eq(b[j],bfs(ttest))) << "\n\033[31mFAILED BFS CHECK: SUBTEST " << j << "\n\033[0m";

        //  clear
        for(auto&i:in[j]) {
            ttest.remove(i);
            EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL VERIFY ON SUBTEST: " << j << " REMOVING KEY: " << i << "\n\033[0m";
        }
        EXPECT_TRUE(ttest.empty()) << "\n\033[31mEXPECTED COMPLETE REMOVAL ON SUBTEST: " << j << "\n\033[0m";
    }
}

TEST(AVL_R,InsertDelete100) {
    //  get in
    srand(0xf00df00d);
    mat in;
    AVLTree<int,int> ttest;
    for(int i = 0; i < 100; ++i)
        in.push_back({i+1,rand(),rand()});
    sort(begin(in),end(in),[&](vi& a, vi& b){ return a[1] < b[1]; });
    
    //  ins
    for(auto&v:in) {
        ttest.insert({v[0],-v[0]});
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL CHECK WHEN INSERTING: " << v[0] << "\n\033[0m";
    }
    EXPECT_FALSE(ttest.empty()) << "\n\033[31mTREE SHOULD NOT BE EMPTY\n\033[0m";

    //  rem
    sort(begin(in),end(in),[&](vi& a, vi& b){ return a[2] < b[2]; });
    for(auto&v:in) {
        ttest.remove(v[0]);
        EXPECT_TRUE(verifyAVL(ttest)) << "\n\033[31mFAILED AVL CHECK WHEN REMOVING: " << v[0] << "\n\033[0m";
    }
    EXPECT_TRUE(ttest.empty()) << "\n\033[31mTREE SHOULD BE EMPTY\n\033[0m";
}

#endif

#if DO_AVLSTRESS

TEST(AVL_R,Stress_Insert) {
    //  ~80ms local (no verify per 1k)
    //  in
    srand(0x5499fb55);
    AVLTree<int,int> ttest;
    
    //  ins
    for(int i = 0; i < 100000; ++i) {
        ttest.insert({i+1,-(i+1)});
        /*
        if(!(i%1000)) {
            EXPECT_TRUE(verifyAVL(ttest));
        }
        */
    }
    EXPECT_TRUE(verifyAVL(ttest));
    EXPECT_FALSE(ttest.empty());
}

TEST(AVL_R,Stress_Iterator) {
    //  ~80ms local (no verify per 1k)
    //  in
    srand(0xeb61803c);
    AVLTree<int,int> ttest;
    
    //  ins
    for(int i = 0; i < 100000; ++i) {
        ttest.insert({i+1,-(i+1)});
        /*
        if(!(i%1000)) {
            EXPECT_TRUE(verifyAVL(ttest));
        }
        */
    }
    EXPECT_TRUE(verifyAVL(ttest));
    EXPECT_FALSE(ttest.empty());

    //  iter
    auto it = ttest.begin();
    for(int i = 1; i <= 100000; ++i) {
        EXPECT_EQ(it->first,i);
        EXPECT_EQ(it->second,-i);
        ++it;
    }
    EXPECT_EQ(it,ttest.end());
}

TEST(AVL_R,Stress_InsertDelete) {
    //  ~few hundred ms local (no verify per 1k)
    //  in
    srand(0x5700b135);
    mat in;
    AVLTree<int,int> ttest;
    for(int i = 0; i < 100000; ++i)
        in.push_back({i+1,rand(),rand()});
    sort(begin(in),end(in),[&](vi& a, vi& b){ return a[1] < b[1]; });

    //  ins
    for(int i = 0; i < 100000; ++i) {
        ttest.insert({in[i][0],-(in[i][0])});
        /*
        if(!(i%1000)) {
            EXPECT_TRUE(verifyAVL(ttest));
        }
        */
    }
    EXPECT_TRUE(verifyAVL(ttest));
    EXPECT_FALSE(ttest.empty());
    
    //  rem
    sort(begin(in),end(in),[&](vi& a, vi& b){ return a[2] < b[2]; });
    for(int i = 0; i < 100000; ++i) {
        ttest.remove(in[i][0]);
        /*
        if(!(i%1000)) {
            EXPECT_TRUE(verifyAVL(ttest));
        }
        */
    }
    EXPECT_TRUE(ttest.empty());
}

TEST(AVL_R,Stress_InsertDeleteIterator_Dupes) {
    //  ~few hundred ms local (no verify per 1k)
    //  in
    srand(0x9a11b1ad);
    std::unordered_map<int,int> m;
    AVLTree<int,int> ttest;
    
    //  ins
    for(int i = 0; i < 100000; ++i) {
        int ins = rand();
        ++m[ins];
        ttest.insert({ins,m[ins]});
        /*
        if(!(i%1000)) {
            EXPECT_TRUE(verifyAVL(ttest));
        }
        */
    }
    EXPECT_TRUE(verifyAVL(ttest));
    EXPECT_FALSE(ttest.empty());

    //  iterator
    auto it = ttest.begin();
    int ct = 0;
    while(it != ttest.end()) {
        EXPECT_EQ(it->second,m[it->first]) << "\n\033[31mFAILED OVERWRITE: " << it->first << "\n\033[0m";
        ++it;
        ++ct;
    }
    EXPECT_EQ(ct,m.size()) << "\n\033[31mMISSING VALUES\n\033[0m";
    
    //  rem
    for(auto&i:m)
        ttest.remove(i.first);
    EXPECT_TRUE(ttest.empty());
}

#endif