# Lab 3 Intel Memory Management
## Page directory pointer (array) 

    type : uint32*

    name : ptr_page_directory

    notes : this pointer is declared in FOS . you can use it (ptr_page_directory)
      
-----------------------------------------------------

## Page table pointer (array)

    type : uint32*

    implement :

    uint32 *ptr_page_table = NULL;

    int ret = get_page_table(ptr_page_directory, KERNEL_BASE, &ptr_page_table);

    if (ret ==  TABLE_IN_MEMORY)   or    if (ptr_page_table != NULL)
    {
      cprintf("page table found at virtual address:%x\n", ptr_page_table);
    }
-----------------------------------------------------
## Create page table :

    implement :
    create_page_table(ptr_page_directory , VA) ;

-----------------------------------------------------
## Access page directory entry :

    type : uint32
    arr_name = ptr_page_directory
    index :
      type : uint32
      name : PDX(VA)
    uint32 page directory entry = ptr_page_directory[PDX(VA)]
-----------------------------------------------------
## Access page table entry :
    type : uint32
    arr_name = ptr_page_table
    index :
      type : uint32
      name : PTX(VA)
    uint32 page table entry = ptr_page_table [PTX(VA)]
-----------------------------------------------------
## Permissions 
    the last 12 bits permissions for table entry and directory entry


