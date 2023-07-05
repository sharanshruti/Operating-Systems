#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int largest(int arr[], int n)
{
    int max = arr[0];
    int max_index = 0;
    for (int i = 1; i < n; i++){
        if (arr[i] > max){
            max = arr[i];
            max_index = i;
        }
    }
    return max_index;
}

int main(int argc,char *argv[]){

    int refrence_string[20], frames, references = 20, page_faults = 0, flag = 0, track = -1;
    frames = atoi(argv[1]); //taking frame no as cmd line input
    printf("No of frames: %d\n",frames);
    srand(time(0));
    int l = 0,u = 9;
    //randomly generating numbers in 0-9 and storng in refrence string
    for(int i = 0;i < references; ++i){
        int page_no = (rand() % (u - l + 1)) + l;
        refrence_string[i] = page_no;
    }
    printf("Reference String Generated:\n");
    for(int i = 0;i < references; ++i){
        printf("%d ",refrence_string[i]);
    }
    printf("\n");
    //Initializing frame array as -1
    int frame_array[frames];
    for(int i = 0;i < frames; ++i){
        frame_array[i] = -1;
    }

    int demand[frames];
    

    //array to store the demand of the element in ref string in
    // future as its index in ref string
    for(int i = 0;i < references; ++i){
        flag = 0;
        for(int j = 0;j < frames; ++j){
            if(refrence_string[i] == frame_array[j]){
                flag = 1;
                page_faults--;
            }
        }
        page_faults++; 
        if((page_faults <= frames) && flag == 0){
            for(int j = 0;j < frames; ++j){
                if(frame_array[j] == -1){
                frame_array[j] = refrence_string[i];
                break;
                }
            }
        }else if(flag == 0){ //all the frames are already occupied and replacement is required
            for(int i = 0;i < frames; ++i){
                demand[i] = references;
            }
            for(int j = 0;j < frames; ++j){
                for(int k = i + 1;k < references; ++k){
                    if((frame_array[j] == refrence_string[k])){
                        demand[j] = k;
                        break;
                    }
                }
            }
            int replace = largest(demand,frames);
            frame_array[replace] = refrence_string[i];
        }
         printf("\n");
         //printing the frame array after each iteration through reference string
        for(int k = 0; k < frames; ++k)
       {     
         printf("%d\t", frame_array[k]);
       }
    }
    printf("\nTotal Page Faults:%d\n", page_faults);
    return 0;
}