#include "Function.hpp"

using namespace std;

void startFunctionInThread(Function *func) {
	(*func)();
}

bool Function::run() {
    th = new thread(bind(&startFunctionInThread, this));
    return (th != NULL)? true : false;
}

bool Function::stop() 
{
	if(isRuning() && !loopEnd) 
	{
		loopEnd = true;
		for(int i = 0; i <10; i++) {
			if(loopEnded) {
				loopEnded = false;
				loopEnd = false;
				return true;
			}
			//sleep(1);
		}
		return false;
	}
	else 
	{
		return false;
	}
}

bool Function::isRuning() 
{
	return (th != NULL)? true : false;
}
	
bool Function::isEnabled() 
{
	return ((*configFile)["general_config"]["enable"] == "true")? true : false;
}


string Function::status() {
    return "STATUS";
}