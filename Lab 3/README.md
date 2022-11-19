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
    
-------
```diff
- Note that this table will be updated soon ISA cause its values may be not correct 
```

|     | **Page** | **Page table** |
| --- | --- | --- |
| **Permissions**| deal with table entry | deal with directory entry |
| **Physical address** |  | (directory_entry >> 12) * PAGE_SIZE | 
| **Virtual address** | | using get_page_table function|
| **Frame number** |  table_entry >> 12 |directory_entry >> 12 |

## Share pages 
**if we want to share to pages (first page point to frame in memory we want to make the second page point to the same fram**

- get page table for first page if it is exist continue else terminate the process 
- get page table for the second page and it is not exist (create it if the question ask you to do that) 
- get first table entry and second table entry 
- point second table entry to the first one 



