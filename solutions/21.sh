# Замена для всех файлов, имеющих размер меньше заданного, суффиксов имен на первые литеры имен файлов

min_size=1000

for file in *; do
    if [ -f "$file" ]; then
        size=$(wc -c < "$file")
        if [ $size -lt $min_size ]; then
            new_name="${file%%.*}_$(echo $file | head -c 1)"
            mv "$file" "$new_name"
            echo "Файл $file переименован в $new_name"
        fi
    fi
done
