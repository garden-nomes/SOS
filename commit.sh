#!/bin/bash
git commit -m "$(head -$((${RANDOM} % `wc -l < commit_messages.txt` + 1)) commit_messages.txt | tail -1)"
git push