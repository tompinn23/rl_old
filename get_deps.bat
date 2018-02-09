powershell -Command "(New-Object Net.WebClient).DownloadFile('https://www.lua.org/ftp/lua-5.3.4.tar.gz', 'lua.tar.gz')"
cd src
cmake -E tar xvf ../lua.tar.gz
cd ..
del lua.tar.gz
