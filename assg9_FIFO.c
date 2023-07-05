#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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
            frame_array[(page_faults-1)%frames] = refrence_string[i];
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