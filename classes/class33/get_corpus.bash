#!/bin/bash

test -e Frankenstein.txt || curl -k https://www.gutenberg.org/cache/epub/84/pg84.txt -o Frankenstein.txt
test -e PridePrejudice.txt || curl -k https://www.gutenberg.org/cache/epub/1342/pg1342.txt -o PridePrejudice.txt
test -e Dracula.txt || curl -k https://www.gutenberg.org/cache/epub/345/pg345.txt -o Dracula.txt
test -e LittleWomen.txt || curl -k https://www.gutenberg.org/cache/epub/37106/pg37106.txt -o LittleWomen.txt
test -e RoomWithView.txt || curl -k https://www.gutenberg.org/cache/epub/2641/pg2641.txt -o RoomWithView.txt
test -e Middlemarch.txt || curl -k https://www.gutenberg.org/cache/epub/145/pg145.txt -o Middlemarch.txt
test -e EnchantedApril.txt || curl -k https://www.gutenberg.org/cache/epub/16389/pg16389.txt -o EnchantedApril.txt
test -e MobyDick.txt || curl -k https://www.gutenberg.org/files/2701/2701-0.txt -o MobyDick.txt
test -e AliceWonderland.txt || curl -k https://www.gutenberg.org/cache/epub/11/pg11.txt -o AliceWonderland.txt

tail -n +71 Frankenstein.txt | head -n 7316 > corpus.txt
tail -n +98 PridePrejudice.txt | head -n 14449 >> corpus.txt
tail -n +119 Dracula.txt | head -n 15310 >> corpus.txt
tail -n +666 LittleWomen.txt | head -n 21189 >> corpus.txt
tail -n +76 RoomWithView.txt | head -n 8675 >> corpus.txt
tail -n +156 Middlemarch.txt | head -n 33150 >> corpus.txt
tail -n +70 EnchantedApril.txt | head -n 8661 >> corpus.txt
tail -n +847 MobyDick.txt | head -n 21114 >> corpus.txt
tail -n +58 AliceWonderland.txt | head -n 3345 >> corpus.txt
