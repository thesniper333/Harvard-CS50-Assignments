// WEATHER SCRIPT

// Checks if API Key is present in local storage
if (localStorage.getItem("weatherApiKey")) {
    document.getElementById("weather-api-container").style.display = "none";
    document.getElementById("change-weather-api").style.display = "block";
    getLocation(); 
}


// Save API Key to local storage
document.getElementById("save-weather-api").addEventListener("click", function () { 
    const apiKey = document.getElementById("weather-api").value.trim();
    if (apiKey) {
        localStorage.removeItem("weatherApiKey")
        localStorage.setItem("weatherApiKey", apiKey);
        document.getElementById("weather-api-container").style.display = "none";
        document.getElementById("change-weather-api").style.display = "block";
        location.reload();
    };
});



// Hide API Key input when clicked outside
 document.addEventListener("click", function (event) {
    const apiKeyContainer = document.getElementById("weather-api-container");
    const changeApiKeyButton = document.getElementById("change-weather-api");

    if (apiKeyContainer.style.display === "block" &&  
        event.target !== changeApiKeyButton &&  
        !apiKeyContainer.contains(event.target)) {
        apiKeyContainer.style.display = "none";
        changeApiKeyButton.style.display = "block";
    }
});

 // Reset API Key
 document.getElementById("change-weather-api").addEventListener("click", function () {
    document.getElementById("weather-api-container").style.display = "block";
    document.getElementById("change-weather-api").style.display = "none";
    
});




// Fetch weather data

async function getWeather(lat, lon) {
    const apiKey = localStorage.getItem("weatherApiKey"); // Get API Key from local storage
    if (!apiKey) {
        document.getElementById("weather-api-container").style.display = "block";
        return;
    }
    const currentWeatherUrl = `https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&appid=${apiKey}&units=metric`;
    const forecastUrl = `https://api.openweathermap.org/data/2.5/forecast?lat=${lat}&lon=${lon}&appid=${apiKey}&units=metric`;
    const aqiUrl = `https://api.openweathermap.org/data/2.5/air_pollution?lat=${lat}&lon=${lon}&appid=${apiKey}`;

    try {
        // Fetch current weather
        const response = await fetch(currentWeatherUrl);
        const data = await response.json();

        if (data.cod === 200) {
            const iconCode = data.weather[0].icon;
            document.getElementById("weather-text").innerHTML = 
                `${data.name}: ${data.main.temp}°C, ${data.weather[0].description}`;
            document.getElementById("weather-icon").src = `https://openweathermap.org/img/wn/${iconCode}@2x.png`;
            document.getElementById("weather-icon").style.display = "inline";

            // Feels like and Humidity
            document.getElementById("feels-like").innerHTML = `Feels like: ${Math.round(data.main.feels_like)}°C`;
            document.getElementById("humidity").innerHTML = `Humidity: ${data.main.humidity}%`;
        }

        // Fetch hourly forecast
        const forecastResponse = await fetch(forecastUrl);
        const forecastData = await forecastResponse.json();

        if (forecastData.cod === "200") {
            const hourlyForecast = document.getElementById("hourly-forecast");
            hourlyForecast.innerHTML = ""; // Clear previous data

            for (let i = 0; i < 5; i++) { // Show next 5 hours
                const hourData = forecastData.list[i];
                const date = new Date(hourData.dt * 1000);

                // Convert to 12-hour format
                let hours = date.getHours();
                const ampm = hours >= 12 ? "PM" : "AM";
                hours = hours % 12 || 12; // Convert 0 to 12

                const temp = Math.round(hourData.main.temp);
                const icon = hourData.weather[0].icon;
                
                hourlyForecast.innerHTML += `
                    <div class="hour">
                        <p>${hours} ${ampm}</p>
                        <img src="https://openweathermap.org/img/wn/${icon}.png">
                        <p>${temp}°C</p>
                    </div>
                `;
            }
        }

        // Fetch AQI
        const aqiResponse = await fetch(aqiUrl);
        const aqiData = await aqiResponse.json();

        if (aqiData.list && aqiData.list.length > 0) {
            const aqiIndex = aqiData.list[0].components.pm2_5; // Get PM2.5 AQI value

            let aqiCategory = "";
            let aqiClass = "";
            if (aqiIndex <= 50) {
                aqiCategory = "Good 🌿";
                aqiClass = "aqi-good";
            } else if (aqiIndex <= 100) {
                aqiCategory = "Moderate 🙂";
                aqiClass = "aqi-moderate";
            } else if (aqiIndex <= 150) {
                aqiCategory = "Unhealthy for Sensitive Groups 😐";
                aqiClass = "aqi-unhealthy";
            } else if (aqiIndex <= 200) {
                aqiCategory = "Unhealthy 😷";
                aqiClass = "aqi-unhealthy";
            } else if (aqiIndex <= 300) {
                aqiCategory = "Very Unhealthy 🚨";
                aqiClass = "aqi-hazardous";
            } else {
                aqiCategory = "Hazardous ☠️";
                aqiClass = "aqi-hazardous";
            }

            document.getElementById("aqi").innerHTML = `AQI: ${aqiIndex.toFixed(0)} (${aqiCategory})`;
            document.getElementById("aqi").className = aqiClass;
        }

        // Fetch Weekly Forecast
        const weeklyForecast = forecastData.list.filter(item => item.dt_txt.includes("12:00:00"));
        const weeklyForecastElement = document.getElementById("weekly-forecast");
        weeklyForecastElement.innerHTML = ""; // Clear previous weekly data

        weeklyForecast.forEach(item => {
            const date = new Date(item.dt * 1000);
            const day = date.toLocaleDateString('en-GB', { weekday: 'short' });
            const temp = Math.round(item.main.temp);
            const icon = item.weather[0].icon;

            weeklyForecastElement.innerHTML += `
                <div class="week-day">
                    <p>${day}</p>
                    <img src="https://openweathermap.org/img/wn/${icon}.png">
                    <p>${temp}°C</p>
                </div>
            `;
        });
        
    } catch (error) {
        document.getElementById("weather-text").innerHTML = "Error fetching weather data.";
    }
}

function getLocation() {
    
    if (navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(
            (position) => {
                const lat = position.coords.latitude;
                const lon = position.coords.longitude;
                getWeather(lat, lon);
                
            },
            () => {
                document.getElementById("weather-text").innerHTML = "Location access denied.";
            }
        );
        
    } else {
        document.getElementById("weather-text").innerHTML = "Geolocation not supported.";
    }
}

setInterval(getLocation, 300000); // Update weather every 5 minutes







