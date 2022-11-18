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

