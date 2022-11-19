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
       


# Free_Frame_List

- Linked list points on free frames only in RAM ( number_of_references = 0 )
- Name in code : Free_Frame_List 
- Need pointer of Frame_Info struct 

    ![Screenshot 2022-11-19 102902](https://user-images.githubusercontent.com/99830416/202842175-c4033776-3dc6-40ba-95e3-3c9fa1ad3274.png)

- Operations on this linked list 

      - Allocate frame (give me free frame to store page) 
      - Free frame (i give you free frame)
      
- Allocate frame 

      - Take one item form linked list 
      - Remove it from linked list 
      - the functions shlould return pointer to Frame_Info struct 

- Allocate frame code 
      
   ```c
   struct Frame_info *ptr  = NULL ; 
   uint32 ret  = allocate_frame(&ptr) ; // it is element in list but i need the physical address in RAM so 
   if (ret != E_NO_MEM){
      uint32 physical_addres = to_physical_address(ptr) ; // (start address of the list - ptr ) / entry size 
   }
   esle{
      cprintf("NO Mem") ;
   }
   ```
   
- Free Frame 
     
      - occure when number_of_references of block = 0 
      - so i should add it to Free_Frame_List

- Free Frame code

   ```c
      uint32 physical_address = 0x100000 ;
      struct FrameInfo *ptr_frame_info ;  
      ptr_frame_info = to_frame_info(physical_address) ;          
      free_frame(ptr_frame_info);     
   ```
