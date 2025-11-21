find . -type f \( -name "*.c" -o -name "*.h" -name "*.inl" \) | while read -r file; do
    if head -n 5 "$file" | grep -q "@file"; then
        echo "Skipping $file (header already present)"
    else
        filename=$(basename "$file")
        header="/**
 * @file ($filename)
 * @author JosheeDev
 * @copyright KrashGL Game Library (c) JosheeDev
 */"

        # Check if first line is empty
        firstline=$(head -n 1 "$file")
        tmpfile=$(mktemp)

        if [ -n "$firstline" ]; then
            # First line not empty → add blank line after header
            echo "$header" > "$tmpfile"
            echo "" >> "$tmpfile"
            cat "$file" >> "$tmpfile"
        else
            # First line empty → no extra blank line
            echo "$header" > "$tmpfile"
            cat "$file" >> "$tmpfile"
        fi

        mv "$tmpfile" "$file"
        echo "Header added to $file"
    fi
done