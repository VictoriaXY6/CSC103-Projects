/*
 * CSc103 Project 3: Game of Life
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:https://blog.csdn.net/sjwl2012/article/details/54344670
 www.cnblogs.com/grandyang/p/4854466.html
 https://blog.csdn.net/u011809767/article/details/78399307

 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours:
 */
#include <iostream>
using std::cout;
using std::cin;
#include <cstdio>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::endl;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --oldworld,-w    FILE     store current oldworld in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM generations and quit.\n"
"   --help,-h              show this message and exit.\n";

size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename =  "/tmp/gol-world-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current"; /* read initial state from here. */

void display(vector<vector<char> > x);
size_t neighbor(vector<vector<char> >& vector, size_t x, size_t y);
void update(vector<vector<char> >& oldVector,vector<vector<char> >& newVector);
void fastforward(vector<vector<char> >& oldVector,vector<vector<char> >& newVector, size_t max_gen);
void dumpstate(FILE* fworld,vector<vector<char> >& newVector,size_t lastrow);

int main(int argc, char *argv[]) {
    // define long options
    static struct option long_opts[] = {
        {"seed",    required_argument, 0, 's'},
        {"oldworld",   required_argument, 0, 'w'},
        {"fast-fw", required_argument, 0, 'f'},
        {"help",    no_argument,       0, 'h'},
        {0,0,0,0}
    };
    // process options:
    char c;
    int opt_index = 0;
    while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index)) != -1) {
        switch (c) {
            case 'h':
                printf(usage,argv[0]);
                return 0;
            case 's':
                initfilename = optarg;
                break;
            case 'w':
                wfilename = optarg;
                break;
            case 'f':
                max_gen = atoi(optarg);
                break;
            case '?':
                printf(usage,argv[0]);
                return 1;
        }
    }
    // Open & Read a file
    FILE* f = fopen(initfilename.c_str(),"rb");

    vector<vector<char>> oldVector;

    oldVector.push_back(vector<char>());
    size_t rows = 0;
    while(fread(&c,1,1,f)){
        if(c=='\n'){
            rows++;
            oldVector.push_back(vector<char>());
        }
        else if (c=='.'){
            oldVector[rows].push_back('.');
        }
        else
        {
            oldVector[rows].push_back('O');
        }
    }
    fclose(f);
    oldVector.pop_back();

   vector<vector<char> > newVector = oldVector;

    if(wfilename=="-")
        fworld=stdout;
    else
        fworld=fopen(wfilename.c_str(),"wb");
    if (max_gen>0)
    {

        fastforward(oldVector,newVector,max_gen);

        dumpstate(fworld,newVector,rows);

        fclose(fworld);
    }
    else {

        sleep(1);
        update(oldVector,newVector);
        dumpstate(fworld,newVector,rows);
        sleep(1);

        while(true)
        {
            update(oldVector,newVector);
            dumpstate(fworld,newVector,rows);
            sleep(1);

        }
        fclose(fworld);
    }
    return 0;
}

void fastforward(vector<vector<char> >& oldVector,vector<vector<char> >& newVector, size_t max_gen) {
    for(size_t n = 0; n < max_gen; n++)
    {
        update(oldVector,newVector);
    }

}

void dumpstate(FILE* fworld,vector<vector<char> >& newVector,size_t lastrow) {
    char end='\n';
    rewind(fworld);

    for(size_t i =0;i<newVector.size();i++){
        for(size_t j=0;j<newVector[i].size();j++)
            fwrite(&newVector[i][j],1,1,fworld);
        fwrite(&end,1,1,fworld);
    }
}

size_t neighbor(vector<vector<char> >& vector, size_t x, size_t y)
{
    size_t counter = 0;
    for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i == 0 && j == 0)
                {
                    continue;
                }

                if (vector[(i+x+vector.size()) % vector.size()][(j+y+vector[0].size()) % vector[0].size()] == 'O')
                {
                    counter++;
                }
            }
        }
    return counter;
}

void update(vector<vector<char> >& oldVector,vector<vector<char> >& newVector)
{
    for(size_t i = 0; i < oldVector.size(); i++)
    {
        for(size_t j = 0; j < oldVector[i].size(); j++)
        {
            if(oldVector[i][j] == 'O')
            {
                if(neighbor(oldVector,i,j) > 3)
                    newVector[i][j] = '.';
                else if(neighbor(oldVector,i,j) < 2)
                    newVector[i][j] = '.';
            //    else if(neighbor(oldVector,i,j) == 3)
            //        newVector[i][j] = 'O';
            //    else if(neighbor(oldVector,i,j) == 2)
            //        newVector[i][j] = 'O';
            //    else
            //        newVector[i][j] = '.';
            }
            if(oldVector[i][j] == '.')
            {
                if(neighbor(oldVector,i,j) == 3)
                    newVector[i][j] = 'O';
            }
        }
    }

    oldVector = newVector;
}
