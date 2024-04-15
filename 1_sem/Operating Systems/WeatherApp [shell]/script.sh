#!/bin/bash
# Author           : Szymon Kasprzycki (szymon.kasprzycki@gmail.com)
# Created On       : 02.2023
# Last Modified By : Szymon Kasprzycki (szymon.kasprzycki@gmail.com)
# Last Modified On : 04.2024
# Version          : 1.0
#
# Description : Weather app with GUI for Linux
# 
#
# Licensed under GPL (see /usr/share/common-licenses/GPL for more
# details or contact the Free Software Foundation for a copy)

# Declare variables
WORK=1
API_KEY="" # should be filled with your API key
ENDPOINT="https://api.weatherbit.io/v2.0/current"
CITY=""
COUNTRY=""
MODE=0
LOCATION=""

#Check if `jq` package is installed (works for fedora)
function checkJQ() {
	PACKAGE="jq"
	COMMAND=$(rpm -q $PACKAGE)
	NOTINSTALLED="package $PACKAGE is not installed"
	if [[ $COMMAND == $NOTINSTALLED ]]; then
		echo "JQ package is not installed, performing installation..."
		sudo yum install $PACKAGE
	else
		echo "JQ package is already installed, no needed to install..."
	fi
}

#Replace polish letters with english ones
function replacePolishLetters() {
	REPLACED=$(echo $1 | sed 's/ż/z/g;s/ź/z/g;s/ć/c/g;s/ń/n/g;s/ą/a/g;s/ś/s/g;s/ł/l/g;s/ę/e/g;s/ó/o/g;s/Ż/Z/g;s/Ź/Z/g;s/Ć/C/g;s/Ń/N/g;s/Ą/A/g;s/Ś/S/g;s/Ł/L/g;s/Ę/E/g;s/Ó/O/')
	echo $REPLACED
}

#Replace dash with \dash
function replaceDash() {
	REPLACED=$(echo $1 | sed 's/-/\\-/g')
	echo $REPLACED
}

# Create zenity window for weather app form
function weather_app_form() {
    zenity --forms --title="Weather App" --text="Enter a location" --add-entry="City" --add-entry="Country" --ok-label="Search" --cancel-label="Exit"
}

# Setup API endpoint address
function setupApiEndpoint() {
    ENDPOINT+="?key=$API_KEY"
	GOODCITY=$(replacePolishLetters $CITY)
    ENDPOINT+="&city=$GOODCITY"
    ENDPOINT+="&country=$COUNTRY"
}

function setupApiEndpointLocation() {
    ENDPOINT+="?key=$API_KEY"
	GOOD_LOCATION=$(replacePolishLetters $LOCATION)
    ENDPOINT+="&city=$LOCATION"
}

# Get information about weather from API
function getApiResponse() {
    curl -s $ENDPOINT
}

# Reset endpoint
function resetApiEndpoint() {
	ENDPOINT="http://api.weatherbit.io/v2.0/current"
	CITY=""
	COUNTRY=""
	INFORMATION=""
    LOCATION=""
}

function showHelp() {
	echo ""
	echo "Open the script without any argument to check its work."
	echo "You have to enter the city and country to check weather."
	echo "If city name would not match - script would ask You again for city."
	echo "Country name doesn't have to be full name, it can be short version like \"PL\" instead of \"Poland\"."
	echo "Script downloads data from WeatherBit API using my access key."
	echo "API is limited to 50 requests per day, that may cause some issues"
	echo "I didn't find any better API provider"
	echo ""
	echo "** OPTIONS **"
	echo "-h, --help -> show help for the script"
	echo "-v, --version -> show version and author information"
	echo ""
}

function showVersion() {
	echo ""
	echo "********************"
	echo "Version v1.1"
	echo "Made by"
	echo "Szymon Kasprzycki 193065"
	echo "********************"
	echo ""
}

# Check if city from api response match wanted city
function checkCity() {
	FOUNDCITY=$(echo $INFORMATION | jq '.city_name' | tr -d '"' | tr '[:upper:]' '[:lower:]')
	ANSWEREDCITY=$(echo $CITY | tr '[:upper:]' '[:lower:]')
	if [ "$FOUNDCITY" = "$ANSWEREDCITY" ]; then
		echo 1
	else
		echo 0
	fi
}

while [[ $# -gt 0 ]]; do
  case $1 in
    -v|--version)
      MODE=1
	  break
      ;;
    -h|--help)
      MODE=2
	  break
      ;;
	-l|--location)
	  MODE=3
	  LOCATION=$2
	  break
	  ;;
    *)
      echo "Unknown option $1"
      exit 1
      ;;
  esac
done

if [ $MODE -eq 0 ]; then
	checkJQ
	while [[ $WORK -eq 1 ]]
	do
		# Get user input
		INPUT=$(weather_app_form)
		case $? in
			0) # User clicked OK
				# Get city and country from user input
				CITY=$(echo $INPUT | cut -d "|" -f 1)
				COUNTRY=$(echo $INPUT | cut -d "|" -f 2)

				# Setup API endpoint address
				setupApiEndpoint

				# Get weather information from API
				API_RESPONSE=$(getApiResponse)
				
				INFORMATION=$(echo $API_RESPONSE | jq '.data[]')
				
				CHECKED=$(checkCity)
				
				if [ $CHECKED -gt 0 ]; then
					# Display weather information
					DESC=$(echo $INFORMATION | jq '.weather.description' | tr -d '"')
					ACTUAL=$(echo $INFORMATION | jq '.ob_time' | tr -d '"')
					TEMP=$(echo $INFORMATION | jq '.temp')
					TEMP+="°C"
					APPTEMP=$(echo $INFORMATION | jq '.app_temp')
					APPTEMP+="°C"
					PRESSURE=$(echo $INFORMATION | jq '.pres')
					PRESSURE=$(echo $PRESSURE | awk '{printf("%.2f",$PRESSURE)}')
					PRESSURE+="hPa"
					CLOUDNESS=$(echo $INFORMATION | jq '.clouds')
					CLOUDNESS+="%"
					HUMIDITY=$(echo $INFORMATION | jq '.rh')
					HUMIDITY+="%"
					SUNRISE=$(echo $INFORMATION | jq '.sunrise' | tr -d '"')
					SUNSET=$(echo $INFORMATION | jq '.sunset' | tr -d '"')
					WINDSPD=$(echo $INFORMATION | jq '.wind_spd')
					WINDSPD=$(echo $WINDSPD | awk '{printf("%.2f",$WINDSPD)}')
					WINDSPD+="m/s"
					WINDDIR=$(echo $INFORMATION | jq '.wind_cdir_full' | tr -d '"')
					UV=$(echo $INFORMATION | jq '.uv')
					UV=$(echo $UV | awk '{printf("%.3f",$UV)}')
					AIRQUALITY=$(echo $INFORMATION | jq '.aqi')
					
					zenity --list \
					--title="Current weather for $CITY, $COUNTRY" \
					--ok-label="New search" --cancel-label="Exit" \
					--width=500 \
					--height=250 \
					--column="Item" --column="Value" \
					"Last Update" " $ACTUAL" \
					"Weather description" " $DESC" \
					"Temperature" " $TEMP"  \
					"Feels like temperature" " $APPTEMP" \
					"Pressure" " $PRESSURE"  \
					"Cloudness" " $CLOUDNESS" \
					"Humidity" " $HUMIDITY" \
					"Wind speed" " $WINDSPD" \
					"Wind direction" " $WINDDIR" \
					"Sunrise" " $SUNRISE" \
					"Sunset" " $SUNSET" \
					"UV index" " $UV" \
					"Air quality index" " $AIRQUALITY"
					
					case $? in
					0)
						WORK=1
						;;
					1)
						WORK=0
						;;
					-1)
						zenity --error --title="Weather App" --text="An unexpected error has occurred."
						;;
					esac
					
				else
					zenity --error --title="City is not supported" --text="Please try with another city name."
				fi
				resetApiEndpoint
				;;
			1) # User clicked Cancel
				WORK=0
				;;
			-1) # An error occurred
				zenity --error --title="Weather App" --text="An unexpected error has occurred."
				WORK=0
				;;
		esac
	done
elif [ $MODE -eq 1 ]; then
	showVersion
elif [ $MODE -eq 2 ]; then
	showHelp
fi