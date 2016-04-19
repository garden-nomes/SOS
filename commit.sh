#!/bin/bash
git commit -m $(head -$((${RANDOM} % `wc -l < file` + 1)) file | tail -1)