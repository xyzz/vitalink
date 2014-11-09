int sceIoOpen(char *);

int random = 5;

int main(int argc, char *argv[]) {
	int uid = sceIoOpen("whatever");

	return random;
}