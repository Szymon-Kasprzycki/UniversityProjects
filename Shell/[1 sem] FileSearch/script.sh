#!/bin/bash
WORK=1
OPTION=1
NAME=""
DIRECTORY=""
CONTENT=""
COMMAND=""
SIZE=""
TIME=""
USER=""
OUTPUT=""

function showMenu(){
zenity --forms --title="Search for the file" \
	--text="Please specify information about the file." \
	--separator="," \
	--add-entry="Name" \
	--add-entry="Directory" \
	--add-entry="Belongs to user (name)" \
	--add-entry="Days after last modify" \
	--add-entry="File smaller than"\
	--add-entry="Content"
}

while [ $WORK -eq 1 ]
do
	OUTPUT=$(showMenu)
	case $? in
		0) zenity --notification\
				--window-icon="info" \
				--text="Searching..."
			NAME=$(echo $OUTPUT | cut -d "," -f 1)
			DIRECTORY=$(echo $OUTPUT | cut -d "," -f 2)
			USER=$(echo $OUTPUT | cut -d "," -f 3)
			TIME=$(echo $OUTPUT | cut -d "," -f 4)
			SIZE=$(echo $OUTPUT | cut -d "," -f 5)
			CONTENT=$(echo $OUTPUT | cut -d "," -f 6)
			if [ -n "$DIRECTORY" ];
		    then
			    COMMAND=$COMMAND'  '$DIRECTORY
		    fi

		    if [ -n "$NAME" ];
		    then
		 	   COMMAND=$COMMAND' -name '$NAME
		    fi

		    if [ -n "$USER" ];
		    then
		 	   COMMAND=$COMMAND' -user '$USER
		    fi

		    if [ -n "$TIME" ];
		    then
			   COMMAND=$COMMAND' -mtime '$TIME
		    fi
			
		    if [ -n "$SIZE" ];
		    then
		 	   COMMAND=$COMMAND' -size '$SIZE
		    fi
		   
		    if [ -n "$CONTENT" ];
		    then
			    COMMAND=$COMMAND' -exec grep -l '$CONTENT'  '$NAME
			    COMMAND=$COMMAND'  {}  ;'
		    fi
			RESULTS=$(echo `find $COMMAND` |  tr " " "\n")
			zenity --list \
			  --title="Results:" \
			  --column="Files" \
			  --width=500 \
			  --height=250 \
			  --print-column=1 $RESULTS
			;;
		1)
			WORK=0
			zenity --notification\
				--window-icon="info" \
				--text="Closing script..."
			;;
		-1) WORK=0 
			zenity --notification\
				--window-icon="info" \
				--text="An unexpected error has occurred"
			;;
	esac
	
done
