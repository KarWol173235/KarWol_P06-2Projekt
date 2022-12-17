#include<stdio.h>
#include<time.h>
#include <stdlib.h>

void odwrocenie(int tab[], int n){ //odwracamy tablice potrzebna do sortowania tablicy odwrotnie posortowanej
    int t[n];
 
    for (int i = 0; i < n; i++) {
        t[n - 1 - i] = tab[i];
    }
 
    for (int i = 0; i < n; i++) {
        tab[i] = t[i];
    }
}

void swap(int *a, int *b){ //zamieniamy dwie tablice ze sobą do quicksort
	int t = *a;
	*a= *b;
	*b=t;
}

//funkcja sortowania szybkeigo:
int quicksort(int tab[], int lewy, int prawy) {
	int i,j,piwot;


  i = (lewy + prawy) / 2;
  piwot = tab[i]; tab[i] = tab[prawy];
  for(j = i = lewy; i < prawy; i++)
  if(tab[i] < piwot)
  {
  	swap(&tab[i], &tab[j]); //funkcja zamieniajaca tablice

    j++;
  }
  tab[prawy] = tab[j]; tab[j] = piwot;
  if(lewy < j - 1)  quicksort(tab,lewy, j - 1);
  if(j + 1 < prawy) quicksort(tab,j + 1, prawy);


  return 0;
}
//funkcja sortowania przez wstawianie:
int wstawianie(int tab[], int N, double elapsed){
	
    // zaczynamy mierzyc czas
    clock_t start, end, duration;
    start = clock();
	
	int i,j,x;
	for(j = N - 2; j >= 0; j--){
    	x = tab[j];
    	i = j + 1;
   		while((i < N) && (x > tab[i]))
    	{
      		tab[i - 1] = tab[i];
      		i++;
    	}
   		tab[i - 1] = x;
	}
  
  // przestajemy mierzyć czas i obliczamy roznice
    end = clock();
    duration= end-start;
    elapsed = (float)duration/CLOCKS_PER_SEC;     
    
    //wyswietlamy zmierzony czas
    printf("zmierzony czas: %.16f sekund.\n", elapsed);
  
  return 0;
}


int main(){
    int z;
	printf("aby wybrac sortowanie przez wybieranie wcisnij 1, jesli quicksort wcisnij 0: ");
	scanf("%d", &z);

	double elapsed=0;
	clock_t start, end, duration;
	int i,m,N;
	printf("podaj rozmiar tablicy: ");
	scanf("%d", &N);
	int tab[256000];
	printf("podaj przedzial liczb od 1 do: ");
	scanf("%d", &m);
	srand((unsigned)time(NULL));

  for(i = 0; i < N; i++) tab[i] = rand() % m+1; //losujemy elementy tablicy

  
  FILE *plik; 
	if((plik=fopen("czasy.txt", "w"))==NULL){
		printf("cos poszlo nie tak");
		exit(1);
	}

	printf("\n");
	if(z==1){
		printf("sortowanie przez wstawianie");
		fprintf(plik,"sortowanie przez wstawianie\n");	
	} 
	
	else {
		fprintf(plik,"Quicksort\n");	
		printf("Quicksort");
	}
	printf("\n");
	printf("czas sortowania tablicy losowej: ");
	if(z==1) wstawianie(tab,N,elapsed);	
	else{
 		// zaczynamy mierzyc czas
    	start = clock();
		quicksort(tab,0,N-1);
		// przestajemy mierzyć czas i obliczamy roznice
    	end = clock();
    	duration= end-start;
    	elapsed = (float)duration/CLOCKS_PER_SEC;     
    	//wyswietlamy zmierzony czas
    	printf("%.6f sekund.\n", elapsed);
	}

	fprintf(plik, "\n czas wykonania algorytmu dla LOSOWEJ tablicy o rozmiarze %d to %.6f \n ",N, elapsed);//zapisujemy czas sortowania do pliku 
	printf("czas sortowania tablicy posortowanej: ");
	if(z==1) wstawianie(tab,N,elapsed);	
	else {
		// zaczynamy mierzyc czas
    	start = clock();
		quicksort(tab,0,N-1);
		// przestajemy mierzyć czas i obliczamy roznice
    	end = clock();
    	duration= end-start;
    	elapsed = (float)duration/CLOCKS_PER_SEC;         
    	//wyswietlamy zmierzony czas
    	printf("%.6f sekund.\n", elapsed);
	}
	fprintf(plik, "czas wykonania algorytmu dla POSORTOWANEJ tablicy o rozmiarze %d to %.6f  \n",N, elapsed); //zapisujemy do pliku
	odwrocenie(tab, N); //odwracamy tablice aby uzyskac odwrotnie posortowana

	printf("czas sortowania tablicy odwrotnej: ");
	if(z==1) wstawianie(tab,N,elapsed);	
	else {	
		//	zaczynamy mierzyc czas
    	start = clock();  
		quicksort(tab,0,N-1);	
		// przestajemy mierzyć czas i obliczamy roznice
    	end = clock();
   	 	duration= end-start;
    	elapsed = (float)duration/CLOCKS_PER_SEC;     
    	//wyswietlamy zmierzony czas
    	printf("%.6f sekund.\n", elapsed);
	}
	fprintf(plik," czas wykonania algorytmu dla ODWROTNIE POSORTOWANEJ tablicy o rozmiarze %d to %.6f\n\n  ",N, elapsed); 
	for(int i=0;i<N;i++){
  		fprintf(plik, "%d ", tab[i]);//zapisujemy tablice do pliku
  	}
	fclose(plik);
	printf("\n posortowana tablica:");
	for(int i=0;i<N;i++){
  		printf("%d ", tab[i]);
	}
return 0;
}


