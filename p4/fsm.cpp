/*
 * CSc103 Project 4: Syntax highlighting, part one.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:http://www.drdobbs.com/cpp/state-machine-design-in-c/184401236
 https://baike.baidu.com/item/ENUM/10934073
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 8
 */

#include "fsm.h"
using namespace cppfsm;
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// make sure this function returns the old state.  See the header
// file for details.
int cppfsm::updateState(int& state, char c) {
	// TODO:  write this function.
 int oldState= state;
		if(state==start) {
			if (INSET(c,iddelim))
			{
				return oldState;
			}
			else if(c=='"'){
				state = strlit;
				return oldState;
			}
			else if (INSET(c,num))
			{
				state=scannum;
				return oldState;
			}
			else if (INSET(c,ident_st))
			{
				state=scanid;
				return oldState;
			}
			else if (c=='/')
			{
				state=readfs;
				return oldState;
			}
     }

		if(state == scanid) {
			if (INSET(c,ident_st))
			{
				return state;
			}
			else if (INSET(c,iddelim))
			{
				state=start;
				return oldState;
			}
			else if (c=='/')
			{
				state= readfs;
				return oldState;
			}
			else if (c=='"')
			{
				state = strlit;
				return oldState;
			}
     }

		if(state == comment) {
			return state;
    }

		if(state == strlit) {
			if (c=='\\')
			{
				state=readesc;
				return oldState;
			}
			else if (c=='"')
			{
				state = start;
				return oldState;
			}
			else return state;
     }

		if(state == readfs) {
			if (c=='/')
			{
				state = comment;
				return oldState;
			}
			else if (c=='"')
			{
				state = strlit;
				return oldState;
			}
			else if (INSET(c,num))
			{
				state = scannum;
				return oldState;
			}
			else if (INSET(c,ident_st))
			{
				state=scanid;
				return oldState;
			}
     }

		if(state == readesc) {
			if (INSET(c, escseq))
			{
				state = strlit;
				return oldState;
			}
			else {
				state = error;
				return oldState;
			}
     }

		if(state == scannum) {
			if (c=='/')
			{
				state = readfs;
				return oldState;
			}
			else if (INSET(c, num))
			{
				return state;
			}
			else if (INSET(c,iddelim))
			{
				state = start;
				return oldState;
			}
			else{
				state = error;
				return oldState;
			}
     }

		if(state == error) {
			return state;
    }
 return start;
   }

