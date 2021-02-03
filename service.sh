#!/bin/bash

MAIN_FOLDER=/usr/bin/backend-monitoring/

BINARY_NAME=backend-monitoring
DOT_SERVICE_NAME=backend-monitoring.service
XML_CONFIG_NAME=xgconsole.xml

DOT_SERVICE_ORIG=/lib/systemd/system/$DOT_SERVICE_NAME
DOT_SERVICE_SYMLINK=/etc/systemd/system/$DOT_SERVICE_NAME

BINARY_DEST=$MAIN_FOLDER$BINARY_NAME
XML_CONFIG_DEST=$MAIN_FOLDER$XML_CONFIG_NAME

install()
{
    PARENT_PATH=$( cd "$(dirname "${BASH_ORIG[0]}")" ; pwd -P )
    cd "$PARENT_PATH"

    mkdir $MAIN_FOLDER
    cp ./Server/Server $BINARY_DEST
    cp xgconsole.xml $XML_CONFIG_DEST

    cp ./Server/BackEndMonitoring.service $DOT_SERVICE_ORIG
    ln -s $DOT_SERVICE_ORIG $DOT_SERVICE_SYMLINK

    systemctl enable $DOT_SERVICE_NAME
    systemctl start $DOT_SERVICE_NAME
}

uninstall()
{
    systemctl stop $DOT_SERVICE_NAME
    systemctl disable $DOT_SERVICE_NAME

    rm $DOT_SERVICE_ORIG
    rm -r $MAIN_FOLDER
}

start()
{
    systemctl start $DOT_SERVICE_NAME
}

stop()
{
    systemctl stop $DOT_SERVICE_NAME
}

handle_cmd()
{
    if [ $1 = "-install" ]
    then
        install

    elif [ $1 = "-uninstall" ]
    then
        uninstall

    elif [ $1 = "-start" ]
    then
        start

    elif [ $1 = "-stop" ]
    then
        stop

    else 
        echo "Invalid flag"
        
    fi
}

handle_cmd $1
