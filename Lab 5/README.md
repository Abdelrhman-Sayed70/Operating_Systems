# Lab 5: Intel Memory Management III

# Store process in RAM steps

- Devide process into pages and RAM into Frams of fixed size (4 KB) -> paging
- Allocate some frames (not necessary to be consecutive)
- Map pages to frames (make pages points to some RAM frames) -> OS role

# Remove process from RAM steps

- 

# Frame_Info Struct

- I have struct stores info of the frame 
      
      name in code : Frame_Info
      info : number_of_references & pointer
            

- How to know if frame is empty or not ?
      
      if no pages points to it (e.g) number of reference of this frame = 0 

# Frames_Info array 

- I have array stores info of each frame in RAM 

       name in code : Frames_Info
       size of this array = number of frames in RAM (RAM size/frame size)
       size = num_of_frames -> use it in the code 
       this is array of Frame_Info struct (e.g) each element in this array is struct of type Frame_Info
       


# Free frame list

- Linked list points on free frames only in RAM ( number_of_references = 0 )
- Name in code : Free_Frame_List 
- Need pointer of struct 

    ![Screenshot 2022-11-19 102902](https://user-images.githubusercontent.com/99830416/202842175-c4033776-3dc6-40ba-95e3-3c9fa1ad3274.png)

      
     
