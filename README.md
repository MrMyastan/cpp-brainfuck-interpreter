# cpp-brainfuck-interpreter
a brainfuck interpreter written in C++, made as part of my project to make a brainfuck-equivalent language.
You can feel free to modify the code for your own use (just make sure to credit me for my code)!
Feedback is welcome, I'm always looking to improve! (suggestions for a better name would also be highly appreciated)
## Implementation Notes
- all cells are 8-bit and overflow/underflow wrap
- there are 30,000 cells
- no cells to the left of the starting cell
- I'm on honestly not exactly sure how it's handling EOF right now
- I believe OS newlines are converted to 10s on input and 10s are converted to OS newlines on output, but don't quote me on it
- character set is just whatever an unsigned char can hold, which I think is ASCII extended
- I don't know if you can tell, but I'm kinda new to C++
## To-Do
- [x] add better error messages (line + column number of bad characters)
- [ ] fix signed/unsigned comparison when making sure pointer is still in array bounds
- [x] maybe put some stuff into functions?
- [ ] comment my gosh darn code
