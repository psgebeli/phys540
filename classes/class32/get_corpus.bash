#!/bin/bash

curl -k https://www.gutenberg.org/cache/epub/84/pg84.txt -o Frankenstein.txt
tail -n +71 Frankenstein.txt > corpus.txt
