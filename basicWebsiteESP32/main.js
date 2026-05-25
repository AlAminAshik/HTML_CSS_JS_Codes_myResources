const esp32url = "http://192.168.0.106/mystatus"; // Replace with your ESP32 IP address
const box = document.getElementById("statusBox");

async function fetchSwitchStatus() {
    try {
        const response = await fetch(esp32url);
        const data = await response.text();
        box.value = data;
    } catch (error) {
        box.value = "Error";
        console.error("Error fetching switch status:", error);
    }
}

setInterval(fetchSwitchStatus, 100); // Fetch status every 500 milliseconds
