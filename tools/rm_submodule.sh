#!/usr/bin/env bash
# $@ = path_to_submodule
git rm -f $@
git config --remove-section submodule.$@
rm -rf .git/modules/$@
