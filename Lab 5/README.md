# Lab 5: Intel Memory Management III

# Store process in RAM steps

- Devide process into pages and RAM into Frams of fixed size (4 KB) -> paging
- Allocate some frames (not necessary to be consecutive)
- Map pages to frames (make pages points to some RAM frames) -> OS role


# Frame_Info Struct

- I have struct stores info of the frame 
      
      name in code : Frame_Info
      info : references & pointer
            

- How to know if frame is empty or not ?
      
      if no pages points to it (e.g) number of reference of this frame = 0 

# Frames_Info array 

- I have array stores info of each frame in RAM 

       name in code : Frames_Info
       size of this array = number of frames in RAM (RAM size/frame size)
       size = number_of_frames -> use it in the code 
       type : array of Fram_Info struct (e.g) each element in this array is struct of type Frame_Info
       


# Free_Frame_List

- Linked list points on free frames only in Frames_Info array ( number_of_references = 0 )
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
   int ret  = allocate_frame(&ptr) ; // it is element in list but i need the physical address in RAM so 
   if (ret != E_NO_MEM){
      uint32 physical_address = to_physical_address(ptr) ; // (start address of the list - ptr ) / entry size 
   }
   else{
      cprintf("NO Mem") ;
   }
   ```
   
- Free Frame 
     
      - occure when references of block = 0 
      - so i should add it to Free_Frame_List

- Free Frame code

   ```c
      uint32 physical_address = 0x100000 ;
      struct FrameInfo *ptr_frame_info ;  
      ptr_frame_info = to_frame_info(physical_address) ;  // this return pointer to Frame_Info Struct        
      free_frame(ptr_frame_info);     
   ```



# Map

`means to set virtual address in directory table and page table and connect virtual address to the allocated frame`

## Map new Page 
`means that the virtual addrees does not connected to frame`

- Get its page table and connect the page to its page table 
- Store frame number in directory table 
- store frame number of **page its self** in page table 
- increment frame references.

   
## Map exsiting page 
`means that the virtual address connected with frame so i will remove this connection and map to new frame`

`i'm sure that this page is stored in page table`

- Unmap the old frame 
- store frame number in page table 
- increment frame references

## Mapping code
      
   ```c
   map_frame(ptr_page_directory, ptr_Frame_Info, virtual_address, permissions) ; // permissions of page table entry 
   ```

# UnMap

- Remove entry from page table (e.g) remove connection between page and frame in RAM  
- Decrement references of the frame 
- if ref became 0 then it became free frame and should be added to free frame list. we need to call free frame function
- Code  

  ```c 
  umnmap_frame(ptr_page_directory, virtual_address) ; 
  ```
# get_frame_info

- show if this virtual address is mapped to ptr_Frame_Info 
- return ptr_page_table of the virtual_address 

  ```c
  uint32 *ptr_page_table = NULL ; 
  struct Fram_Info *ptr_Frame_Info = get_frame_info(ptr_page_directory, virtual_address, &ptr_page_table) ;
  if (ptr_Frame_Info == NULL) {// this virtual address is not mapped to any frame   }
  else {// this virtual_address is mapped to this ptr_Frame_Info}
  ```


 # to_frame_info
 
 - this function retun ptr_Frame_info 
 - take physical_address 
 
 ```c
struct FrameInfo * ptr_frame_info ;
ptr_frame_info = to_frame_info(physical_address); 
 ```
 
# Alloc page for virtual address

- Check whether the page is mapped or not
- if not, then, allocate a single frame from the free frame list
- Map this frame to the given user virtual address 

# Free Page for virtual address

# NOTES

- Note : Directory table & page table of size = (2 power 10) * 4B = 4KB (frame size) this means that each of dir and page table stored in 1 frames in RAM. each of  them need frame from Free_Frame_list


