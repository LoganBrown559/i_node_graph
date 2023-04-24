Name: Logan Brown
Date: 4/23/2023
File: README.txt


DEPENDENCIES:

-Graphviz
	sudo apt install graphviz

-GCC
	sudo apt install gcc
	OR
	sudo apt install build-essential


HOW TO RUN:

This is simple, just run the "compile_and_run.sh" bash script, and it will start the program.

I decided to make the program interactive, so you will be prompted to input a directory (realative
or absolute, dealer's choice) and to input and output file end in .gv. This unfotunately will
not change the pdf name, but hey I'm proud of what I have.

Once the previously mentioned prompts are answered, the program will run its course, and the
bash script will produce a pdf named "i_node_graph.pdf".

Run the script anytime you wish to use the program, or run the binary that is spawned if
you rather not have everything done for you automatically.




CHALLENGES:

All things considered, this actually went fairly smooth. I did have slight hurdles
when it came to design choices, but ultimately it's nothing beyond the good old
fashioned problem solving that this line of work often presents. More than anything,
most of my time was looking up syntax for C. It has been a while since I've had to work
with files in C, and directory work is still extremely new to me using C.


LACKLUSTER FEATURES:

The file entry counter does not work. I toyed with it for a while, but I am clearly just missing something.
It will always say zero, and I haven't gotten that to change.

Looking back, I am not sure why I let the user pick the .gv file name. But hey, a good lesson to take on with me.


SOURCES:

I did use one website in particular, that broke down how directories and entry file types work.
This was much simpler to understand, and probably saved me a fair amount of time in research on
C syntax.

This one taught directory work.
https://c-for-dummies.com/blog/?p=3246

This one branched from the last, talking about entries.
https://c-for-dummies.com/blog/?p=3252

Again I can not stress enough, these were seriously good.
