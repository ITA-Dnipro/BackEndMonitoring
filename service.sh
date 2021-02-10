#!/bin/bash

XML_CONFIG_NAME=config.xml

SERVICE_NAME=$(grep -o -P '(?<=<servicename> ").*(?="</servicename>)' $XML_CONFIG_NAME)
SERVICE_DESC=$(grep -o -P '(?<=<servicedesc> ").*(?="</servicedesc>)' $XML_CONFIG_NAME)

MAIN_FOLDER=/usr/bin/$SERVICE_NAME/
BINARY_NAME=$SERVICE_NAME
DOT_SERVICE_NAME=$SERVICE_NAME.service

DOT_SERVICE_ORIG=/lib/systemd/system/$DOT_SERVICE_NAME
DOT_SERVICE_SYMLINK=/etc/systemd/system/$DOT_SERVICE_NAME

BINARY_DEST=$MAIN_FOLDER$BINARY_NAME
XML_CONFIG_DEST=$MAIN_FOLDER$XML_CONFIG_NAME

main()
{
    check_sudo
    handle_cmd $1
}

handle_cmd()
{
    if [ "$1" = "-h" ] || [ "$1" = "--help" ] || [ "$1" = "" ]
    then
        show_help

    elif [ "$1" = "-i" ] || [ "$1" = "--install" ]
    then
        install

    elif [ "$1" = "-u" ] || [ "$1" = "--uninstall" ]
    then
        uninstall

    elif [ "$1" = "--start" ]
    then
        start

    elif [ "$1" = "--stop" ]
    then
        stop

    elif [ "$1" = "--status" ]
    then
        status

    else 
        echo "Invalid flag"
        
    fi
}

install()
{
    PARENT_PATH=$( cd "$(dirname "${BASH_ORIG[0]}")" ; pwd -P )
    cd "$PARENT_PATH"

    mkdir $MAIN_FOLDER
    
    cp ./Server/Server $BINARY_DEST
    cp $XML_CONFIG_NAME $XML_CONFIG_DEST

    generate_dot_service
    ln -s $DOT_SERVICE_ORIG $DOT_SERVICE_SYMLINK

    systemctl enable $DOT_SERVICE_NAME
    start
}

uninstall()
{
    stop
    systemctl disable $DOT_SERVICE_NAME

    rm $DOT_SERVICE_ORIG
    rm -r $MAIN_FOLDER
}

status()
{
    systemctl status $DOT_SERVICE_NAME
}

start()
{
    systemctl start $DOT_SERVICE_NAME
}

stop()
{
    systemctl stop $DOT_SERVICE_NAME
}

check_sudo()
{
    if [ $(/usr/bin/id -u) -ne 0 ]
    then
        echo "sudo required"
        exit
    fi
}

show_help()
{
    echo "Backend monitoring server"
    echo "Usage:"
    echo "-i / --install   - install and start the service"
    echo "-u / --uninstall - stop and uninstall the service"
    echo "--start          - start the service"
    echo "--stop           - stop the service"
    echo "--status         - show current status"
}

generate_dot_service()
{
    touch $DOT_SERVICE_ORIG

    echo "[Unit]" >> $DOT_SERVICE_ORIG
    echo "Description=$SERVICE_DESC" >> $DOT_SERVICE_ORIG
    echo "After=network.target" >> $DOT_SERVICE_ORIG
    echo "[Service]" >> $DOT_SERVICE_ORIG
    echo "ExecStart=$BINARY_DEST" >> $DOT_SERVICE_ORIG
    echo "[Install]" >> $DOT_SERVICE_ORIG
    echo "WantedBy=multi-user.target" >> $DOT_SERVICE_ORIG
}

main $1
