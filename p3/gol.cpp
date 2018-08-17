/*
 * CSc103 Project 3: Game of Life
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 
 */
#include <iostream>
using std::cout;
using std::cin;
#include <cstdio>
#include <stdlib.h> // for exit();
#include <getopt.h> // to parse long arguments.
#include <unistd.h> // sleep
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
string wfilename =  "/tmp/gol-oldworld-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-oldworld-current"; /* read initial state from here. */

void display(vector<vector<char> > x);
size_t neighbor(vector<vector<char> > vec, size_t x, size_t y);
void update(vector<vector<char> > oldVec,vector<vector<char> >& newVec);
void fastforward(vector<vector<char> > oldVec,vector<vector<char> >& newVec, size_t max_gen);
void dumpstate(FILE* fworld,vector<vector<char> >& newVec,size_t lastrow);

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
	if (!f) 
		exit(1);
	long filesize;
	fseek(f,0,SEEK_END);
	filesize = ftell(f);
	rewind(f);
	char cell[filesize];
	size_t line=1;
	string firstline = fgets(cell,filesize,f);
	while (fgets(cell,filesize,f)) {
		line++;
	}
	size_t ROWS = line;
	size_t COLS = firstline.length()-1;
	vector<vector<char> > oldVec(ROWS, vector<char>(COLS,'.'));
    vector<vector<char> > newVec(ROWS, vector<char>(COLS,'.'));
	rewind(f);
	char a;
	for (size_t x=0; x<ROWS; x++) {
		for (size_t y=0; y<COLS+1; y++) {
			fread(&a,1,1,f);
			if (a=='O')
				oldVec[x][y]=a;
		}
	}
	fclose(f);	

	if (max_gen>0)
	{
		update(oldVec,newVec);
		fastforward(oldVec,newVec,max_gen);
		fworld=fopen(wfilename.c_str(),"wb");
		dumpstate(fworld,newVec,ROWS);
		fclose(fworld);
	}
	else {
		display(oldVec);
		sleep(1);
		update(oldVec,newVec);
		system("clear");
    	display(newVec);
		fworld=fopen(wfilename.c_str(),"wb");
		dumpstate(fworld,newVec,ROWS);
		sleep(1);
		system("clear");	
		while(true)
		{
			update(newVec,newVec);
       		display(newVec);
			dumpstate(fworld,newVec,ROWS);
        	sleep(1);
        	system("clear");
    	}
		fclose(fworld);
	}
	return 0;
}

void fastforward(vector<vector<char> > oldVec,vector<vector<char> >& newVec, size_t max_gen) {
	for(size_t n = 0; n < max_gen-1; n++)
	{
        update(newVec,newVec);
    }
	display(newVec);
}

void dumpstate(FILE* fworld,vector<vector<char> >& newVec,size_t lastrow) {
	char end='\n';
	rewind(fworld);
    for(size_t i = 0; i < newVec.size(); i++)
    {
		if (newVec[i].size()>0)	
			fwrite(&newVec[i][0],1,newVec[i].size(),fworld);
		fwrite(&end,1,1,fworld);
	}
} 

void display(vector<vector<char> > x)
{
    for(size_t i = 0; i < x.size(); i++)
    {
        for(size_t j = 0; j < x[i].size(); j++)
        {
            cout << x[i][j];
        }
        cout<<endl;
    }
}

size_t neighbor(vector<vector<char> > vec, size_t x, size_t y)
{
    size_t counter = 0;

    if(vec[(x-1+vec.size()) % vec.size()][(y-1+vec[x].size()) % vec[x].size()] == 'O')
        counter++;
    if(vec[(x-1+vec.size()) % vec.size()][y] == 'O')
        counter++;
    if(vec[(x-1+vec.size()) % vec.size()][(y+1) % vec[x].size()] == 'O')
        counter++;
    if(vec[x][(y-1+vec[x].size()) % vec[x].size()] == 'O')
        counter++;
    if(vec[x][(y+1) % vec[x].size()] == 'O')
        counter++;
    if(vec[(x+1) % vec.size()][(y-1+vec[x].size()) % vec[x].size()] == 'O')
        counter++;
    if(vec[(x+1) % vec.size()][y] == 'O')
        counter++;
    if(vec[(x+1) % vec.size()][(y+1) % vec[x].size()] == 'O')
        counter++;

    return counter;
}

void update(vector<vector<char> > oldVec,vector<vector<char> >& newVec)
{
    for(size_t i = 0; i < oldVec.size(); i++)
    {
        for(size_t j = 0; j < oldVec[i].size(); j++)
        {
            if(oldVec[i][j] == 'O')
            {
                if(neighbor(oldVec,i,j) > 3)
                    newVec[i][j] = '.';
                else if(neighbor(oldVec,i,j) < 2)
                    newVec[i][j] = '.';
                else if(neighbor(oldVec,i,j) == 3)
                    newVec[i][j] = 'O';
                else if(neighbor(oldVec,i,j) == 2)
                    newVec[i][j] = 'O';
                else
                    newVec[i][j] = '.';
            }
            if(oldVec[i][j] == '.')
            {
                if(neighbor(oldVec,i,j) == 3)
                    newVec[i][j] = 'O';
            }
        }
    }

    oldVec = newVec;
}