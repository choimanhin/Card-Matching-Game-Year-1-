#include <stdio.h>
#include<stdlib.h>
#include<time.h>
/* given TypeCard structure definition */
typedef struct card {
	char suit;   // 'S'pade / 'H'eart / 'C'lub / 'D'iamond
	int  rank;   // A (1) / 2 - 10 / J (11) / Q (12) / K (13);
	int  status; // covered (0) or flipped (1) or chosen (-1), or flipped by computer/com1 (-9), or com2 (-19).
} TypeCard;

void startmenu(){
	printf("Please choose a mode of the game:\n1. Human vs. Computer\n2. Computer vs. Computer\n0. Quit\nYour choice: ");
}

void printCard(TypeCard   aCard)
{
	if (aCard.status == 0)
		printf("XXX");

	else
	{
		/* display suit of a card */
		switch (aCard.suit) {
		case 'S':
		case 'H':
		case 'C':
		case 'D':
			printf("%c", aCard.suit);
			break;
		default:
			printf("?");
		}


		if (aCard.rank != 10)printf(" ");
		/* display rank of a card */
		if ((aCard.rank > 10) || (aCard.rank == 1)) {
			if (aCard.rank == 11) { printf("J"); }
			else if (aCard.rank == 1) { printf("A"); }
			else if (aCard.rank == 12) { printf("Q"); }
			else if (aCard.rank == 13) { printf("K"); }
		}
		else { printf("%d", aCard.rank); }



	}
	//printf(" %d",aCard.status);
	return;
}



void showDesktop(TypeCard   desktop[4][14])
{	/* show all 4 x 13 cards in the desktop 2D TypeCard array */
	printf("\n");
	int i, j,total=0,player=0,compu=0;
	for (i = 0; i < 4; i++) {
		for (j = 1; j < 14; j++) {
            if((desktop[i][j].status==1)||((desktop[i][j].status==-9))){
                    total++;
                    if(desktop[i][j].status==1)player++;
                    if(desktop[i][j].status==-9)compu++;
            }
			printCard(desktop[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	printf("\n");
	printf("Flipped cards: %d; You: %d; Computer: %d;\n",total,player,compu);
	printf("\n");
}



void showResults(TypeCard desktop[4][14]){ // showDesktop function but only show total flipped cards
                                        // and do not print all the cards
    int i, j,total=0,com1=0,com2=0;
	for (i = 0; i < 4; i++) {
		for (j = 1; j < 14; j++) {
            if((desktop[i][j].status==-19)||(desktop[i][j].status==-9)){
                    total++;
                    if(desktop[i][j].status==-9){com1++;}
                    else if(desktop[i][j].status==-19){com2++;}
            }


		}

	}
	printf("Flipped cards: %d; Computer 1: %d; Computer 2: %d;\n",total,com1,com2);
	printf("\n");
}



void flipCard(TypeCard desktop[4][14]) { // player input>check valid>input 2nd card>check valid>if same then change status
    int r1,c1,r2,c2;
    //1 ST
    printf("Please input 1st card: ");
    scanf("%d %d",&r1,&c1);
    while(((r1>3)||(r1<0)||(c1<1)||(c1>13))||(desktop[r1][c1].status==1)||(desktop[r1][c1].status==-9))
    {
        if((r1>3)||(r1<0)||(c1<1)||(c1>13)){ printf("Row and column must be within 0 - 4 and 1 - 13\n");
                                            printf("Please input 1st card: ");
                                            scanf("%d %d",&r1,&c1);
                                                }
    if((desktop[r1][c1].status==1)||(desktop[r1][c1].status==-9)){printf("The card must not be flipped already\nPlease input 1st card: ");scanf("%d %d",&r1,&c1);}
    }

    desktop[r1][c1].status=-1;
	printf("You chose 1st card (%d,", r1);
	if (c1 < 10) { printf(" "); }
	printf("%d) and it is ", c1);
	printCard(desktop[r1][c1]);
	printf("\n");
	desktop[r1][c1].status=0;
	//2 ND
	printf("Please input 2nd card: ");
    scanf("%d %d",&r2,&c2);
    while(((r2>3)||(r2<0)||(c2<1)||(c2>13))||(desktop[r2][c2].status==1)||(desktop[r2][c2].status==-9)||((r1==r2)&&(c1==c2)))
    {
        if((r2>3)||(r2<0)||(c2<1)||(c2>13)){ printf("Row and column must be within 0 - 4 and 1 - 13\n");
                                            printf("Please input 2nd card: ");
                                            scanf("%d %d",&r2,&c2);
                                                }
    if((desktop[r2][c2].status==1)||(desktop[r2][c2].status==-9)){printf("The card must not be flipped already\nPlease input 2nd card: ");scanf("%d %d",&r2,&c2);}
    if((r1==r2)&&(c1==c2)){  printf("The second card cannot be the same as first\n");
                                printf("Please input 2nd card: ");
                                scanf("%d %d",&r2,&c2);
                                }
    }

    desktop[r2][c2].status=-1;
	printf("You chose 2nd card (%d,", r2);
	if (c2 < 10) { printf(" "); }
	printf("%d) and it is ", c2);
	printCard(desktop[r2][c2]);
	printf("\n");
	desktop[r2][c2].status=0;

	if(desktop[r2][c2].rank==desktop[r1][c1].rank){desktop[r2][c2].status=1;desktop[r1][c1].status=1;printf("You got a matched pair!\n");}
}
void comFlip(TypeCard desktop[4][14]){  //flipCard function but no alert
    int r1,c1,r2,c2;
    //r=rand()%4;c=1+rand()%13;

    r1=rand()%4;c1=1+rand()%13;
    while((desktop[r1][c1].status==1)||(desktop[r2][c2].status==-9))
    {
    printf("%d %d\n",r1,c1);
        r1=rand()%4;c1=1+rand()%13;
    }

    desktop[r1][c1].status=-1;
	printf("Computer chose 1st card (%d,", r1);
	if (c1 < 10) { printf(" "); }
	printf("%d) and it is ", c1);
	printCard(desktop[r1][c1]);
	printf("\n");
	desktop[r1][c1].status=0;
	//2 ND
	r2=rand()%4;c2=1+rand()%13;
    while((desktop[r2][c2].status==1)||(desktop[r2][c2].status==-9)||((r1==r2)&&(c1==c2)))
    {
    printf("%d %d\n",r2,c2);
        if((desktop[r2][c2].status==1)||(desktop[r2][c2].status==-9)){r2=rand()%4;c2=1+rand()%13;}
        if((r1==r2)&&(c1==c2)){r2=rand()%4;c2=1+rand()%13;}

    }



    desktop[r2][c2].status=-1;
	printf("Computer chose 2nd card (%d,", r2);
	if (c2 < 10) { printf(" "); }
	printf("%d) and it is ", c2);
	printCard(desktop[r2][c2]);
	printf("\n");
	desktop[r2][c2].status=0;

	if(desktop[r2][c2].rank==desktop[r1][c1].rank){desktop[r2][c2].status=-9;desktop[r1][c1].status=-9;printf("Computer got a matched pair!\n");}

}

void com1Flip(TypeCard desktop[4][14]){ // comFlip function but in mode 2
    int r1,c1,r2,c2;
    //r=rand()%4;c=1+rand()%13;

    r1=rand()%4;c1=1+rand()%13;
    while((desktop[r1][c1].status==-9)||(desktop[r1][c1].status==-19))
    {
        //printf("%d %d\n",r1,c1);
       r1=rand()%4;c1=1+rand()%13;
    }

    desktop[r1][c1].status=-1;
	printf("Computer 1 chose 1st card (%d,", r1);
	if (c1 < 10) { printf(" "); }
	printf("%d) and it is ", c1);
	printCard(desktop[r1][c1]);
	printf("\n");
	desktop[r1][c1].status=0;
	//2 ND
	r2=rand()%4;c2=1+rand()%13;
    while((desktop[r2][c2].status==-9)||(desktop[r2][c2].status==-19)||((r1==r2)&&(c1==c2)))
    {

    //printf("%d %d\n",r2,c2);
        if((desktop[r2][c2].status==-9)||(desktop[r2][c2].status==-19)){r2=rand()%4;c2=1+rand()%13;}
        if((r1==r2)&&(c1==c2)){r2=rand()%4;c2=1+rand()%13;}

    }

    desktop[r2][c2].status=-1;
	printf("Computer 1 chose 2nd card (%d,", r2);
	if (c2 < 10) { printf(" "); }
	printf("%d) and it is ", c2);
	printCard(desktop[r2][c2]);
	printf("\n");
	desktop[r2][c2].status=0;

	if((desktop[r2][c2].rank==desktop[r1][c1].rank)&&(desktop[r2][c2].status!=-9)&&(desktop[r2][c2].status!=-19)){
            desktop[r2][c2].status=-9;
            desktop[r1][c1].status=-9;
            printf("Computer 1 got a matched pair!\n");}

}

void com2Flip(TypeCard desktop[4][14]){ //com1 function
    int r1,c1,r2,c2;
    //r=rand()%4;c=1+rand()%13;

    r1=rand()%4;c1=1+rand()%13;
    while((desktop[r1][c1].status==-9)||(desktop[r1][c1].status==-19))
    {
    //printf("%d %d\n",r1,c1);
       r1=rand()%4;c1=1+rand()%13;
    }

    desktop[r1][c1].status=-1;
	printf("Computer 2 chose 1st card (%d,", r1);
	if (c1 < 10) { printf(" "); }
	printf("%d) and it is ", c1);
	printCard(desktop[r1][c1]);
	printf("\n");
	desktop[r1][c1].status=0;
	//2 ND
	r2=rand()%4;c2=1+rand()%13;
    while((desktop[r2][c2].status==-9)||(desktop[r2][c2].status==-19)||((r1==r2)&&(c1==c2)))
    {
    //printf("%d %d\n",r2,c2);
        if((desktop[r2][c2].status==-9)||(desktop[r2][c2].status==-19)){r2=rand()%4;c2=1+rand()%13;}
        if((r1==r2)&&(c1==c2)){r2=rand()%4;c2=1+rand()%13;}

    }
    desktop[r2][c2].status=-1;
	printf("Computer 2 chose 2nd card (%d,", r2);
	if (c2 < 10) { printf(" "); }
	printf("%d) and it is ", c2);
	printCard(desktop[r2][c2]);
	printf("\n");
	desktop[r2][c2].status=0;

	if((desktop[r2][c2].rank==desktop[r1][c1].rank)&&(desktop[r2][c2].status!=-9)&&(desktop[r2][c2].status!=-19)){
            desktop[r2][c2].status=-19;
            desktop[r1][c1].status=-19;
            printf("Computer 2 got a matched pair!\n");}

}

int checkend(TypeCard desktop[4][14]){ //check if all cards are flipped(break when unflipped cards detected)
int i,j,x=1 ;
for(i=0;i<4;i++){
    for(j=1;j<=13;j++){
        if (desktop[i][j].status==0){x= 0;i=4;j=14;}

    }
}
return x;
}

void winner1(TypeCard desktop[4][14]){ // count the flipped cards of player and com>winner
int i,j,compu=0,player=0;
for(i=0;i<4;i++){
    for(j=1;j<=13;j++){
        if (desktop[i][j].status==1){player++;}
        if  (desktop[i][j].status==-9){compu++;}

    }
}
if(player>compu){printf("Player win\n\n");}
else if (compu>player){printf("Computer win\n\n");}
else printf("Draw\n\n");
}



void winner2(TypeCard desktop[4][14]){ //winner1 function but is 2 com
int i,j,comp1=0,comp2=0;
printf("\nEnd of game!\n\n");
for(i=0;i<4;i++){
    for(j=1;j<=13;j++){
        if (desktop[i][j].status==-9){comp1++;}
        if  (desktop[i][j].status==-19){comp2++;}
        printCard(desktop[i][j]);
        printf("\t");

    }
    printf("\n");
}
printf("\n");
int total=comp1+comp2;
printf("Flipped cards: %d; Computer 1: %d; Computer 2: %d;\n",total,comp1,comp2);
	printf("\n");
//printf("\nEnd of game!\n");
//printf("%d %d\n",comp1,comp2);
if(comp1>comp2){printf("Computer 1 wins!\n\n");}
else if (comp2>comp1){printf("Computer 2 wins!\n\n");}
else printf("Draw\n\n");
}

void mode1(TypeCard desktop[4][14]){ // player flip card>show cards>com flip card>show cards>check if all flipped>if all flipped then find winner
    while(1)
    {
    flipCard(desktop);
    showDesktop(desktop);
    comFlip(desktop);
    showDesktop(desktop);

    if(checkend(desktop)==1){break;}
    }
    winner1(desktop);
}
//mode 2: test for loops
void mode2(TypeCard desktop[4][14]){ //mode1 but is 2 com and only show cards once in one loop
    //for(int i=0;i<30;i++)
    while(1)
    {
    com1Flip(desktop);
    if(checkend(desktop)==1){break;}
    else{showResults(desktop);}


    com2Flip(desktop);

    //showResults(desktop);

    if(checkend(desktop)==1){break;}
    else{showResults(desktop);}
    }

    winner2(desktop);

}

/* starting point of this C program */
int main(void)
{

    //intro
    char m;
	printf("*****************************\n* Welcome to Concentration! *\n*****************************\n");
	srand((unsigned)time(NULL));

    while(1){

	startmenu();
    //(GENERATE NEW DESKTOP)
    TypeCard desktop[4][14] = {
		/* the first element (column 0) of each row is UNUSED */
		/* row: 0 - 3; col: 1 - 13 */
		{{}, {'S', 1}, {'S', 2}, {'S', 3}, {'S', 4}, {'S', 5}, {'S', 6}, {'S', 7}, {'S', 8}, {'S', 9}, {'S', 10}, {'S', 11}, {'S', 12}, {'S', 13}},
		{{}, {'H', 1}, {'H', 2}, {'H', 3}, {'H', 4}, {'H', 5}, {'H', 6}, {'H', 7}, {'H', 8}, {'H', 9}, {'H', 10}, {'H', 11}, {'H', 12}, {'H', 13}},
		{{}, {'C', 1}, {'C', 2}, {'C', 3}, {'C', 4}, {'C', 5}, {'C', 6}, {'C', 7}, {'C', 8}, {'C', 9}, {'C', 10}, {'C', 11}, {'C', 12}, {'C', 13}},
		{{}, {'D', 1}, {'D', 2}, {'D', 3}, {'D', 4}, {'D', 5}, {'D', 6}, {'D', 7}, {'D', 8}, {'D', 9}, {'D', 10}, {'D', 11}, {'D', 12}, {'D', 13}}
	};
	int i,j,indexi,indexj;
	char tempesuit;
	int temperank;
	for(i=0;i<4;i++){  //swap cards randomly
        for(j=1;j<=13;j++){
            tempesuit=desktop[i][j].suit;
            temperank=desktop[i][j].rank;
            indexi=rand()%4;
            indexj=1+rand()%13;
            desktop[i][j].suit=desktop[indexi][indexj].suit;
            desktop[i][j].rank=desktop[indexi][indexj].rank;
            desktop[indexi][indexj].suit=tempesuit;
            desktop[indexi][indexj].rank=temperank;

        }
	}

    m = getchar();//m = mode of game
    printf("\n");

    switch(m){
    case '1':
        mode1(desktop); //single player
        break;
    case '2':
        mode2(desktop); //computer
        break;
    case '0': //end
        _Exit(0);
        break;
    case '9': //check desktop
        for(int row=0;row<4;row++){
        for(int col=1;col<=13;col++){
            desktop[row][col].status = 1;
        }
    }
        showDesktop(desktop);
        break;
    default:
        printf("ERROR\n\n");
        break;

    }

    }

	return 0;
}
