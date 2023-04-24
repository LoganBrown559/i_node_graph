#! /bin/bash

rm -f *.gv

gcc -o iscan inode_scanner.c

wait $!

chmod 711 iscan

wait $!

./iscan

wait $!

dot -Tpdf *.gv -o i_node_graph.pdf

