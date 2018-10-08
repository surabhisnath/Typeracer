//HEADER FILES
#include <iostream.h>
#include <fstream.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

//FUNCTION PROTOTYPES
void get_help();
void get_passage(char passage[], int choice);
int get_input(char passage_input[], char passage[]);
int str_length(char passage[]);
int num_words(char passage[], int size);
float accuracy_calc(char passage_input[], char passage[], int size, int size_input);
int output(int no_words, int time_elapsed, float accuracy);

//MAIN FUNCTION
int main()
{
	clrscr();
	randomize();

	int retry = 1;
	int choice;
	get_help();

	while(retry==1)
	{
		char passage[1000];
		choice = 1 + random(15);
		get_passage(passage, choice);

		char passage_input[1000];
		int time_elapsed = get_input(passage_input, passage);

		int size = str_length(passage);
		int size_input = str_length(passage_input);

		int no_words = num_words(passage_input, size_input);
		float accuracy = accuracy_calc(passage_input, passage, size, size_input);

		retry = output(no_words, time_elapsed, accuracy);
	}

	cout<<"Exiting . . .";
	delay(3000);
	return 0;
}

void get_help() //To display rules of the game if desired by the user
{
	cout<<"\t\t******* SURABHI'S TYPERACER GAME *******"<<endl<<endl;
	cout<<"Do you want to learn the rules of the game? (y/n): ";
	char x;
	cin>>x;
	cin.ignore();
	if(x=='y' || x=='Y')
	{
		cout<<endl<<"SURABHI'S TYPERACER GAME"<<endl<<endl;
		cout<<"This game measures your typing speed (in words per minute) and accuracy by asking you to type in a passage and analyzing your input. Hope you have fun!";
		cout<<endl<<endl;
	}
	else if(x=='n' || x=='N')
		cout<<endl;
	else
	{
		cout<<"Incorrect choice. Showing rules anyway . . ."<<endl;
		cout<<endl<<"SURABHI'S TYPERACER GAME"<<endl<<endl;
		cout<<"This game measures your typing speed (in words per minute) and accuracy by asking you to type in a passage and analyzing your input. Hope you have fun!";
		cout<<endl<<endl;
	}
	cout<<"Press any key to start the game: ";
	getch();
	cout<<endl<<endl;
}

void get_passage(char passage[], int choice) //to randomly choose and read passage from file
{
	char fname[15];
	sprintf(fname,"Pas%d.txt", choice);

	ifstream fin;
	fin.open(fname);
	fin.getline(passage, 1000);

	fin.close();
}

int get_input(char passage_input[], char passage[]) //to get input passage from user
{
	time_t time_start;
	time_t time_end;
	cout << "Please type the following passage:\n\n";
	puts(passage);
	cout<<endl<<"Get ready to start typing...";
	for(int i=10;i>=0;i--)
	{
		if(i>0)
		{
			cout<<i<<"...";
			delay(1000);
		}
		else
		{
			cout<<"START!"<<endl;
		}
	}
	time(&time_start);
	gets(passage_input);
	time(&time_end);
	return (time_end - time_start);
}

int str_length(char passage[]) //to find the size of a passage
{
	int i = 0;
	int size = 0;
	while(passage[i]!='\0')
	{
		size++;
		i++;
	}
	return size;
}

int num_words(char passage[], int size = 1000) //to find the number of words in a passage
{
	int i = 0;
	int count = 0;
	while(i<size)
	{
		if(passage[i] == ' ')
			count++;
		i++;
	}
	count++;
	return count;
}

float accuracy_calc(char passage_input[], char passage[], int size, int size_input) //to find the correctness of the input passage vis-a-vis actual passage
{

	int i, j, k;
	int count_char_corr = 0;
	int count_words_corr = 0;
	int pos_a = 0;
	int pos_b = 0;
	char s1[100][20];
	char s2[100][20];
	passage[size]='\0';
	passage_input[size_input]='\0';

	for(i = 0; i<=size_input; i++)
	{
		if(passage_input[i]==' ' || passage_input[i]=='\0')
		{
			j = i-1;
			k = 0;
			while(passage_input[j]!=' ' && j>=0)
			{
				s1[pos_a][k] = passage_input[j];
				k++;
				j--;
			}
			s1[pos_a][k]='\0';
			pos_a++;
		}
	}

	for(i = 0; i<=size; i++)
	{
		if(passage[i]==' ' || passage[i]=='\0')
		{
			j = i-1;
			k = 0;
			while(passage[j]!=' ' && j>=0)
			{
				s2[pos_b][k] = passage[j];
				k++;
				j--;
			}
			s2[pos_b][k]='\0';
			pos_b++;
		}
	}

	for(i = 0; i<pos_a; i++)
	{
		j = 0;
		count_char_corr = 0;
		while(s1[i][j]!='\0' && s2[i][j]!='\0')
		{
			if(s1[i][j]==s2[i][j])
				count_char_corr++;
			j++;
		}
		if(count_char_corr==j)
			count_words_corr++;
	}

	cout<<"\nNo. of words: "<<pos_b<<endl;
	cout<<"No. of correct words: "<<count_words_corr<<endl;
	float accuracy = float(100*count_words_corr)/(pos_b);

	return accuracy;
}

int output(int no_words, int time_elapsed, float accuracy) //to display typing speed and accuracy
{
	float typing_speed = 60*no_words/float(time_elapsed);
	cout<<"Your typing speed is "<<typing_speed<<" words per minute and your accuracy is "<<accuracy<<"%."<<endl<<endl;
	cout<<"Try again? (y/n): ";
	char x;
	int label;
	label:
	int res = 0;
	cin>>x;
	cin.ignore();
	if(x == 'y' || x == 'Y')
		res = 1;
	else if(x =='n' || x == 'N')
		res = 0;
	else
	{
		cout<<"Incorrect choice. Want to try the game again? (y/n): ";
		goto label;
	}
	return res;
}