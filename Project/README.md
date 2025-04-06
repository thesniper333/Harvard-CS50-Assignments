# Tesseract
### A Chrome Extension Dashboard Homepage.

## Description:
This project is a chrome extension dashboard which incorporates several widgets like Analog clock, google calendar, weather,
map, gmail inbox, to-do list, stocks. All of these feature's source code is given assets folder.
    This project uses API/Credentials for two widgets, weather and gmail inbox widget.

#### Analog Clock
It is just a simple anal;og clock made with html, css and js. This clock
comprises numbers to mark time, it is created and embedded dynamically using js by calculating angles.
It also has three hands for hours, minutes and seconds. Seconds hand rotates every second by a certain degree, minutes and hour
hands depend upon seconds hand for it's rotation angle.

#### Google Calendar
It is embedded via iframe directly and I made it fit inside our project using CSS only it does not require any external js script.

#### Weather Widget
It is created with help of js, it's script calculates the location via geolocation IP address. Geolocation returns longitude and latitude coordinates
js function determines the weather condition for this returned coordinates using Openweather API. It shows several other informations like AQI, hourly
and weekly forecast. This widget refreshes it self to update the weather.

#### Map
It is embedded via openstreetmap which requires leaflet script to work. It also locates the device using IP address, it does not require any API.

#### Gmail inbox widget.
It uses google API, Client ID and Client Secret for user authentication which is done via goole OAuth.
There are placeholder as input field for these three credentials at the bottom of the gmail widget.
All the recent(unread) emails will be reflected in the widget, they are clickable, if you click
on an particluar emails message you will be redirected to the actual message on gmail.com on new tab.
This widget refreshes itself to fetch the newer messages.

#### To-do List
It is created using html, css and js.

#### Stocks widget
This reflects the price dynamically using the tradingview chart provided via iframe directly it also does not requrie external js file.

#### Search Bar
It comprises three search engines Google, DuckDuckGo and Bing.

#### Background Changer
It is a button to change the background.

