g++ main.cpp -o main.exe -static -static-libgcc -static-libstdc++ -std=c++17

cp main.exe ../release/main.exe

rm main.exe

