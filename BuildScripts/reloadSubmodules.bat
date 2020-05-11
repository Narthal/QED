cd ../
git submodule update --init --recursive
REM git submodule foreach git pull origin master
git pull --recurse-submodules --jobs=10
git submodule update --remote