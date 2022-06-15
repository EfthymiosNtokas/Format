#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
using namespace std;
char text[2000000];
long long int m = 0;
void define_the_gaps(int length, int gap_lengths[51], int num_wrds){
    //the gaps are 1,2,..,num_wrds-1
    int run_index = num_wrds-1;
    while(length < 60){
        gap_lengths[run_index--]+= 1;
        if(run_index == 0) {run_index = num_wrds-1;}
        length++;
    }
}
void print_the_line(int length, int gap_lengths[51], int num_wrds, int gap_places[51], char line[64]){
    int i = 1;
    for(int k = 1; k <= num_wrds-1;k++){
        while(i < gap_places[k]){
            text[m++] = line[i++];
        }
        for(int f = 1; f<= gap_lengths[k]; f++){
            text[m++] = ' ';
        }
        i++; //increasing to get past_the space
    }
    while(i <= length){
        text[m++] = line[i++];
    }
    text[m++] ='\n';
}
int main()
{
    FILE *f, *g;

    f=fopen("inputfilepath", "rt"); //input file
    g=fopen("outputfilepath", "wt");//output file
    if(f==nullptr||g==nullptr){
        printf("The file paths are not valid");
        return 0;
    }
    int c, counter = 1, held_chars = 0, gap_places[51], gap_lengths[51], last_word[23], previous = 0;
    int num_wrds = 1; int last_gap; int length; char line[64];//careful to substract one
    while((c=fgetc(f))!= EOF){
        if(c!= '\n' && c!= ' '){
            if(counter < 60){
                line[counter++] = c; previous = 1;
            }else if(counter == 60){
                char n = fgetc(f);
                if(n == EOF || (n == ' ' || n == '\n')){
                    length = 60; line[counter] = c;
                    define_the_gaps(length, gap_lengths, num_wrds);
                    print_the_line(length ,gap_lengths, num_wrds, gap_places, line);
                    previous = 0; counter = 1; num_wrds = 1;
                }else {
                    line[counter] = c;
                    length = last_gap-1; num_wrds--;
                    define_the_gaps(length, gap_lengths, num_wrds);
                    print_the_line(length ,gap_lengths, num_wrds, gap_places, line);
                    for(int j = last_gap+1; j <= counter; j++){
                        last_word[++held_chars] = line[j];
                    }
                    last_word[++held_chars] = n;
                    for(int s = 1; s <= held_chars; s++) line[s] = last_word[s];
                    previous = 1; counter = held_chars+1; //held_chars?
                    held_chars = 0; num_wrds = 1;
                }
            }
        }else{
            if(previous == 1){
                if(counter < 60){
                    last_gap=counter; gap_places[num_wrds] = counter; gap_lengths[num_wrds] = 1; //num_wrds 1_2_
                    num_wrds++; previous = 0; line[counter++] =' ';//remember to substract

                }else if(counter == 60)
                {
                    //we are fine
                    length = 59;
                    define_the_gaps(length, gap_lengths, num_wrds);
                    print_the_line(length ,gap_lengths, num_wrds, gap_places, line);
                    previous = 0; held_chars = 0; counter = 1; num_wrds = 1;
                }
            }
        }
    }
    for(long long int i = 0; i < m; i++){
        fputc(text[i],g);
    }
    for(int j = 1; j <= counter-2; j++)
    {
        fputc(line[j],g);
    }fputc('\n',g);
    fclose(f); fclose(g);
    return 0;
}
