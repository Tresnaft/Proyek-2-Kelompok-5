int main () {
	address first = NULL;
	address last = NULL;
	char arr[500]; 
	char arrnew[500];
	//{'H', 'A', 'N', 'I', 'F', 'A', 'H', 'M', 'A', 'D'};
	printf("Masukkan pesan:");
	scanf("%[^\n]s", arr);
	int len = strlen(arr);
	if(len%2 == 1){
    	arr[len] = 32; 	
	}
	for (int i = 0; i < len; i++) {
		if (arr[i] =='\0') {
			arr[i] = ' ';
		}
	}
	insertAkhir(arr, &first, &last);
	printf("\n");
	insertGenap(&first, arr);
	
	address awal = first;
	while (awal != NULL) {
		printf("| %c | -> ", awal->info);
		awal = awal->next;
	}
	linkedtoarr(arrnew, arr, &first, &last);
	puts("");
	printf("%s", arrnew);
}