Get-ChildItem -Recurse -Include *.c,*.h | ForEach-Object {
    $header = @"
/**
 * @file ($($_.Name))
 * @author JosheeDev
 * @copyright KrashGL Game Library (c) JosheeDev
 */
"@

    $firstLines = Get-Content $_.FullName -TotalCount 5

    if ($firstLines -match "@file") {
        Write-Host "Skipping $($_.Name) (header already present)"
    }
    else {
        $content = Get-Content $_.FullName

        # Build new file content
        $newContent = $header -split "`n"

        # If the first line of the file body is not empty, insert a blank line
        if ($content.Length -gt 0 -and $content[0].Trim() -ne "") {
            $newContent += ""   # add blank line
        }

        $newContent += $content

        Set-Content $_.FullName -Value ($newContent -join "`n")
        Write-Host "Header added to $($_.Name)"
    }
}