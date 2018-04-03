p1314:
Data Structure: Using suffix array and change a little bit.
Difference with suffix array: When doing string compare,the shorter string goes to the index which is larger than the string length, then count (index-length) from the string begining rather than stop comparing.( Using this to realize ordering the shifted string)
Algorithm: Using the modified suffix array, to find the position which lexicographical order is the smallest. Since it is the cyclic one-letter left shifts string, it might have the several smallest lexicographical order positions. Output the smallest index one of them.

p10010:
1. The border of the grid(fix x=0 or N, or y=0 or M) is used as the the starting points of each direction. From these starting points, walk to 8 different direction to form a string, until reach the border. Concatenate all these strings with '$' in the end. For each character, mark the its position in the grid.
2. For each word to be searched, concatenate two copies (s+'#'+s+'^') to the former string.
3. Use the string with the grid and two copies of each word to build a suffix array.
4. For each word, find the position of the begining of first copy and second copy in the suffix array. All suffix between these two points contains the word as a prefix. Loop through these suffix, to find the first occurance in the grid for each word.


p11512:
1. Make a suffix array with the sinput string.
2. For every adjacent suffix in the suffix array, calculate their longest common prefix. Find the largest one among them, and count how many times it appears, by looking for how many longest common prefix are the same starting from this point.


p11107:
Data Structure:
Use generalized suffix array: 
- add # to the tail of each life form's DNA string 
- concatenate all the strings
- compute the suffix array of the new generated string
Algorithm:
Implement a generalized suffix array.
Each time find (n/2)+1 different kinds of life forms in the array.
Compute the longest common prefix of the first and last of each (n/2)+1 different kinds of life forms in the suffix array.
Find the maximum of the longest common prefix. If many, output all of them. If no common prefix, output "?"