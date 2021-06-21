# ft_container #

## List ##

| element    | prototype         | description       | state |
| ---------  | ----------------- | ----------------- | ----- |
|constructor | list()            | default | 4/4 |
| acces| -front() -back()| acces to element| 2/2 |
| Modifier   | push_front()       | add el at end     | :x: |
| Modifier   | pop_front()        | delete el at end     | :x: |
| Modifier   | push_back()       | add el at end     | :x: |
| Modifier   | pop_back()        | delete el at end     | :x: |
### note ###

#### iterator ####

    const_iterator = iterator // OK
    iterator = const_iterator // KO

    list<type>::sort ~ time to see

    | std | ft | nbr | type | cmp |
    | --- | -- | --- | ---- | --- |
    | 30.2 | 39.6 | 3M | int | default |
    | 19.8 | 24.5 | 2M | int | default |
    | 9.34 | 11.5 | 1M | int | default |
    | 0.04 | 0.05 | 100m | int | default |
    | ~0.003 | ~0.003 | 1000 | int | default |
    
### link ###
    https://en.cppreference.com/w/cpp/iterator
    https://gcc.gnu.org/onlinedocs/gcc-11.1.0/libstdc++/api/a18648_source.html#l00450
    https://www.youtube.com/watch?v=xGl-VBmKr2E
