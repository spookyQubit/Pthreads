#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	std::cout << "Hello" << std::endl;

	pid_t child1_pid, child2_pid;
	int status;

	if((child1_pid = fork()) < 0){
		std::cout << "fork call failed" << std::endl;
		exit(1);
	} else if(child1_pid == 0){
		std::cout << "in child" << std::endl;
		exit(0);
	} else {
		std::cout << "in parent" << std::endl;
	} 

	waitpid(child1_pid, &status, 0);

	std::cout << "status = " << status << std::endl; 

	return 0;
}