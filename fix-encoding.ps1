<#
============================================================
 fix-encoding.ps1 — нормализует кодировку исходников UE
 в UTF-8 с BOM (требование MSVC для файлов с не-ASCII)

 БЕЗОПАСЕН: определяет текущую кодировку каждого файла,
 файлы уже в UTF-8 BOM пропускает, ничего не портит.

 Запуск:
   cd "C:\Dev\MegaBonkLearn"
   powershell -ExecutionPolicy Bypass -File "<путь>\fix-encoding.ps1"

 Сухой прогон (ничего не меняет, только показывает):
   powershell -ExecutionPolicy Bypass -File "<путь>\fix-encoding.ps1" -WhatIf
============================================================
#>

param(
    [switch]$WhatIf,
    [string]$Root = "Source"
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path $Root)) {
    Write-Host "Папка '$Root' не найдена. Запускай скрипт из КОРНЯ проекта" -ForegroundColor Red
    Write-Host "(там, где лежит .uproject)"
    exit 1
}

$utf8Bom   = New-Object System.Text.UTF8Encoding($true)    # с BOM
$utf8NoBom = New-Object System.Text.UTF8Encoding($false, $true)  # строгий: бросает исключение на невалидном UTF-8
$cp1251    = [System.Text.Encoding]::GetEncoding(1251)

$changed = 0
$skipped = 0

Get-ChildItem -Path $Root -Recurse -Include *.h, *.hpp, *.cpp, *.cs, *.inl -File | ForEach-Object {
    $file  = $_
    $bytes = [System.IO.File]::ReadAllBytes($file.FullName)

    # --- 1. Уже UTF-8 с BOM? Тогда не трогаем ---
    if ($bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF) {
        Write-Host ("  SKIP   {0}  (уже UTF-8 BOM)" -f $file.Name) -ForegroundColor DarkGray
        $script:skipped++
        return
    }

    # --- 2. Пробуем прочитать как строгий UTF-8 ---
    $text   = $null
    $source = $null
    try {
        $text   = $utf8NoBom.GetString($bytes)
        $source = "UTF-8 без BOM"
    } catch {
        # Не валидный UTF-8 → почти наверняка cp1251 (русская локаль Windows)
        $text   = $cp1251.GetString($bytes)
        $source = "cp1251 (Windows-1251)"
    }

    Write-Host ("  FIX    {0}  [{1} -> UTF-8 BOM]" -f $file.Name, $source) -ForegroundColor Yellow
    $changed++

    if (-not $WhatIf) {
        [System.IO.File]::WriteAllText($file.FullName, $text, $utf8Bom)
    }
}

Write-Host ""
if ($WhatIf) {
    Write-Host ("СУХОЙ ПРОГОН: было бы изменено {0}, пропущено {1}" -f $changed, $skipped) -ForegroundColor Cyan
    Write-Host "Запусти без -WhatIf, чтобы применить."
} else {
    Write-Host ("Готово: изменено {0}, пропущено {1}" -f $changed, $skipped) -ForegroundColor Green
    Write-Host ""
    Write-Host "Дальше:" -ForegroundColor Cyan
    Write-Host "  git status"
    Write-Host "  git add Source/ .editorconfig"
    Write-Host "  git commit -m `"chore(m0): normalize source encoding to UTF-8 BOM`""
    Write-Host "  git push"
    Write-Host "  git show --stat HEAD    # контроль: что реально ушло"
}
