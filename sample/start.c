int main(int argc, char *argv[]);
void sceKernelExitProcess(int);

#define NULL (void*)0

void module_start(void) {
	sceKernelExitProcess(main(1, (char*[]){"homebrew", NULL}));
}
