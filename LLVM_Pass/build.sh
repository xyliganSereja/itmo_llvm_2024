clang++ Pass_logger.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -fpass-plugin=./libPass.so ../SDL/*.c -O2 -emit-llvm -S
clang -fpass-plugin=./libPass.so ../SDL/*.c log.c -lSDL2
./a.out
