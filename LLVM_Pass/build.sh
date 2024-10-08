# Сборка SDL
clang -g  ../SDL/*.c -o ../SDL/app.out -lSDL2

# Сборка LLVM плагина
clang++ -o customPass.so Pass_logger.cpp -fPIC -shared -I$(llvm-config --includedir)

# Сборка SDL с плагином и логгером
clang ../SDL/*.c -fpass-plugin=./customPass.so -lSDL2 -O2

# Запуск с плагином и вывод первых n строк
./a.out | head -n 1000 > log.txt

