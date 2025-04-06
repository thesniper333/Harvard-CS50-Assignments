// Initialize the map
var map = L.map('map').setView([0, 0], 13);

// Add OpenStreetMap tiles
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; OpenStreetMap contributors'
}).addTo(map);

// Add a marker for the user's location
var marker = L.marker([0, 0]).addTo(map);

// Update the location using the Geolocation API
function updateLocation() {
    if (navigator.geolocation) {
        navigator.geolocation.watchPosition(
            function (position) {
                var lat = position.coords.latitude;
                var lng = position.coords.longitude;
                var accuracy = position.coords.accuracy;

                marker.setLatLng([lat, lng]);
                map.setView([lat, lng], 15);
                var circle = L.circle([lat, lng], {
                    color: 'red',
                    fillColor: '#f03',
                    fillOpacity: 0.3,
                    radius: 50
                }).addTo(map);

                
            },
            function (error) {
                console.error("Error obtaining location:", error);
            },
            {
                enableHighAccuracy: true,
                timeout: 10000,
                maximumAge: 0
            }
        );
    } else {
        alert("Geolocation is not supported by this browser.");
    }
}

updateLocation();