set -e
echo "INFO: Recompiling dwm ./bin/dwm"
make

if [ ! -f /usr/share/xsessions/dwm.desktop ]; then
    set /usr/share/xsessions/dwm.desktop 
    echo [Desktop Entry] > $1
    echo Name=dwm >> $1
    echo Comment=dwm is hot >> $1
    echo Exec=dwm >> $1
    echo Type=Aplication >> $1
    echo "INFO: Created desktop /usr/share/xsessions/dwm.desktop"
fi

cp -f bin/dwm /usr/local/bin
echo "INFO: Copied ./bin/dwm into /usr/local/bin"
