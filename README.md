# Hướng dẫn biên dịch:  
## Bước 1: Tạo thư mục build  
mkdir buid  
cd build  
## Bước 2: Biên dịch từng file  
g++ -c ../FileHandle/FileHandler.cpp -o FileHandler.o  
g++ -c ../Pet/Pet.cpp -o Pet.o  
g++ -c ../PetManager/PetManager.cpp -o PetManager.o   
g++ -c ../main.cpp -o main.o
## Bước 3: Liên kết cà file sau khi biên dịch  
g++ FileHandler.o Pet.o PetManager.o main.o -o DO_AN  
## Bước 4: Chạy file  
./DO_AN

