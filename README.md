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

ft::map map_all_rand ~ time :    
| std | ft | nbr | diff | cmp | 
| --- | -- | --- | ---- | --- |
| 105.44 | 141.08| 25M | x1.34 | default | 
| 64.51 | 88.56 | 15M | x1.37 | default |
| 34.8 | 49.8 | 10M | x1.4 | default |
| 16.5 | 20.3 | 5M | x1.2 | default |
| 9.34 | 11.5 | 500K | x0.8 | default |
| 0.17 | 0.13 | 50K | x0.7 | default |
    
### link ###
-https://en.cppreference.com/w/cpp/iterator<br>
-https://gcc.gnu.org/onlinedocs/gcc-11.1.0/libstdc++/api/a18648_source.html#l00450<br>
-https://www.youtube.com/watch?v=xGl-VBmKr2E
