# ft_container

## List

| element    | prototype         | description       | state |
| ---------  | ----------------- | ----------------- | ----- |
|constructor | list()            | default | :heavy_check_mark: |
| constructor| list(uint n, val) | fill constructor | :heavy_check_mark: |
| Modifier   | push_front()       | add el at end     | :x: |
| Modifier   | pop_front()        | delete el at end     | :x: |
| Modifier   | push_back()       | add el at end     | :x: |
| Modifier   | pop_back()        | delete el at end     | :x: |
### note
##### iterator
    const_iterator = iterator // OK
    iterator = const_iterator // KO
    
### link
    https://en.cppreference.com/w/cpp/iterator
    https://gcc.gnu.org/onlinedocs/gcc-11.1.0/libstdc++/api/a18648_source.html#l00450
    https://www.youtube.com/watch?v=xGl-VBmKr2E
