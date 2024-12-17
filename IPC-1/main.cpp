#include <iostream>
#include <unistd.h>
#include <csignal>

void new_handler(int signal, siginfo_t *info, void *extra_info){
	ucontext_t* context = (ucontext_t*)extra_info;
	pid_t sender_pid = info->si_pid; 
	struct passwd* pw = getpwuid(info->si_uid);
	std::cout << sender_pid;
	std::cout << info->si_uid;
	std::cout << pw->pw_name;

	std::cout << "EIP: " << context->uc_mcontext->gregs[REG_RIP];
	std::cout << "RAX: " << context->uc_mcontext->gregs[REG_RBX];


int main() {
	struct sigaction sig;
	sig.sa sigaction = new_handler;
	sigaction(10, &sig, nullptr);
	while(true){
		sleep(10);
	}


}
