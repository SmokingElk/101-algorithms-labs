#!/bin/sh

# задаю путь содержащий файлы для конкатенации
directory="/Users/zmskv/..."

# задаю размер блока устройства
block_size=8

# создаю результирующий файл 
result_file="result.txt"
> "$result_file"

# получаю список файлов из директории
files=$(ls "$directory")

# перебираю файлы и конкатенирую их пока размер результирующего файла не превысит размеру блока
for file in $files; do
  # размер текущего файла
  file_size=$(du "$directory/$file" | awk '{print $1}')

  # условие проверки
  result_size=$(du "$result_file" | awk '{print $1}')
  if [ `expr $result_size + $file_size` -gt "$block_size" ]; then
  	echo "memory overflow"
  	exit 1
    break
  fi

  # Конкатенируйте текущий файл с результирующим файлом
  cat "$directory/$file" >> "$result_file"
done
