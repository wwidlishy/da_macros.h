# da_macros.h
dynamic array macros for c89+ with good documentation.  

1. create a struct for array type
     ```c
     da_type(name, type), ex: da_type(string, char)
     ```
2. append to an array
     ```c
     da_append(array_name, value), ex: da_append(message, 'J');
     ```
3. initialise an array from an array:
     ```regex
     da_f?set(cpy|ref)(_ex)?(dst_array, (src_arr)|(src_ptr, src_capacity, src_count))
     ```
     f - free previous content  
     cpy - set to a copy of source  
     ref - set to a reference of source (only data)  
     _ex - manual array instead of struct  
     args:
     - source array struct | ptr  
     - capacity?  
     - count?  

4. free and reset struct - da_free(name)
5. reset struct without free - da_reset(name)
