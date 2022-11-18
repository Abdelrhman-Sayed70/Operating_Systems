
|     | **Page** | **Page table** |
| --- | --- | --- |
| **Permissions**| deal with table entry | deal with directory entry |
| **Physical address** | (table entry >> 12) * PAGE_SIZE | directory_entry | 
| **Virtual address** | | using get_page_table function|
| **Frame number** |  table_entry >> 12 |directory_entry >> 12 |
