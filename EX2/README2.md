**Q2**. Escreva um programa **txt2epub** que dada uma lista de n ficheiros em texto - f1.txt,
f2.txt, ..., fn.txt - na linha de comando, aplique o programa pandoc a cada um dos
ficheiros gerando versões EPUB dos mesmos:

pandoc f1.txt -o f1.epub\
...\
pandoc fn.txt -o fn.epub

A conversão dos ficheiros .txt nos respectivos .epub deve ser feita em paralelo por n\
processos criados para o efeito. Cada processo obt´em um nome de um ficheiro de argv[] e\
converte-o como descrito. Depois dos processos terminarem de converter todos os ficheiros\
o último passo do programa txt2epub será a geração de um ficheiro .zip como os n ficheiros\
em formato EPUB.

zip ebooks.zip f1.epub ... fn.epub

Por exemplo:

$ txt2epub iliada.txt odisseia.txt eneida.txt ... metamorfoses.txt\
[pid2751] converting iliada.txt ...\
[pid2749] converting metamorfoses.txt ...\
[pid2752] converting odisseia.txt ...\
...\
$ ls\
ebooks.zip\
eneida.epub\
iliada.epub\
metamorfoses.epub\
odisseia.epub

Sugestão: obtenha um conjunto de livros em formato .txt a partir da Internet. Use apenas
cópias legais de livros. Veja aqui por exemplo: Projecto Gutenberg.
