#include "Tests.h"


void Tests::runTests(){
	for(int i=0;i<tests.size();++i){
		tests[i]->runTest();
	}
}
