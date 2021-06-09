windres grafics/icon.rc -O coff -o grafics/icon.res
gcc *.c -I./include grafics/icon.res -lpsapi -lcomdlg32 -o "Whatsapp Analyser.exe"