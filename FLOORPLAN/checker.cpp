#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <unordered_map>
using namespace std;


void flip(int x1, int y1, int rx, int ry, vector<vector<bool>>& grid) {
    for(int x = x1; x < x1+rx; ++x)
        for(int y = y1; y < y1+ry; ++y)
            grid[x][y] = !grid[x][y];
}

bool can_place(int x1, int y1, int rx, int ry, vector<vector<bool>>& grid) {
    //  oob
    if(x1+rx > (int)grid.size() || y1+ry > (int)grid[0].size())
        return 0;
    //  check rec space
    for(int x = x1; x < x1+rx; x++)
        for(int y = y1; y < y1+ry; y++)
            if(grid[x][y])
                return 0;
    return 1;
}

int main(int argc, char* argv[]) {
    if(argc < 4) {
        cerr << "NOT ENOUGH ARGS | NEED I/O FILES & TEST NUM" << endl;
        return -1;
    }
    
    FILE* file = fopen(argv[1],"r");                        //  get box dimensions
    if(!file) {
        cerr << "INVALID I FILE" << endl;
        return -1;
    }
    int x, y, num;
    fscanf(file,"%d %d %d\n",&x,&y,&num);
    fclose(file);

    FILE* filetuah = fopen(argv[2],"r");                    //  get & check soln
    if(!filetuah) {
        cerr << "INVALID O FILE" << endl;
        return -1;
    }

    int id, rx, ry, rl, rh;
    vector<vector<bool>> grid = vector<vector<bool>>(x,vector<bool>(y,0));

    const char* BAD = "No solution found.";
    char str[256];

    if(fgets(str,sizeof(str),filetuah) == nullptr) {
        cerr << "\033[31mFAILED TEST: " << argv[3] << " (file read error)\033[0m" << endl;
        fclose(filetuah);
        return -1;
    }

    if(strncmp(str,BAD,strlen(BAD)) == 0) {
        cerr << "\033[31mFAILED TEST: " << argv[3] << "\033[0m" << endl;
        fclose(filetuah);
        return -1;
    }

    sscanf(str,"%d %d %d %d %d",&id,&rx,&ry,&rl,&rh);
    if(can_place(rx,ry,rl,rh,grid)) {
        flip(rx,ry,rl,rh,grid);
    } else {
        cerr << "\033[31mFAILED TEST: " << argv[3] << "\033[0m" << endl;
        fclose(filetuah);
        return -1;
    }

    while (--num) {
        fscanf(filetuah,"%d %d %d %d %d",&id,&rx,&ry,&rl,&rh);
        if(can_place(rx,ry,rl,rh,grid)) {
            flip(rx,ry,rl,rh,grid);
        } else {
            cerr << "\033[31mFAILED TEST: " << argv[3] << "\033[0m" << endl;
            fclose(filetuah);
            return -1;
        }
    }

    cout << "\033[32mPASSED TEST: " << argv[3] << "\033[0m" << endl;
    fclose(filetuah);
    return 0;
}