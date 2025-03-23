# Smart Farm with IoT_Basic

A real-time IoT-based smart farming solution that monitors environmental conditions and provides actionable insights for crop health. This project integrates sensors, cloud storage, and a Flask web application to deliver live data and intelligence to farmers in an easy-to-understand format.

---
![Basic Smart Farm Project Visual](https://i.postimg.cc/8PCx8TqZ/banner.jpg)

## Project Overview

"Smart Farm with IoT_Basic" uses IoT sensors to collect environmental data such as **temperature**, **humidity**, **light intensity**, and **soil moisture**. The data is uploaded to a Google Sheet using Google Apps Script, then retrieved and displayed live on a Flask-based website. The website offers:
- **Live Data Visualization**: Real-time sensor readings.
- **Crop-Specific Insights**: Descriptive text explaining if conditions are ideal for a selected crop or what’s wrong (e.g., "Too humid for tomatoes, consider ventilation").
- **Manual Input Option**: Enter custom values to get instant insights without sensor data.

---

## Features
- **Sensor Integration**: Collects temperature, humidity, light intensity, and soil moisture.
- **Cloud Storage**: Stores data in Google Sheets via Apps Script.
- **Live Website**: Flask app displays data and insights in real-time.
- **Intelligent Insights**: Analyzes conditions for specific crops and provides easy-to-read advice.
- **Manual Mode**: Input values manually to get crop health feedback.

---

## Tech Stack
- **Hardware**: IoT sensors (e.g., DHT11 for temperature/humidity, LDR for light, soil moisture sensor), microcontroller (e.g., ESP32/ESP8266).
- **Cloud**: Google Sheets with Google Apps Script.
- **Backend**: Flask (Python).
- **Frontend**: HTML/CSS/JavaScript (basic Flask templates).
- **Data Flow**: Sensors → Google Sheets → Flask → Website.

---

## How It Works
1. **Data Collection**:
   - Sensors measure environmental parameters.
   - Microcontroller sends data to Google Sheets via Apps Script.

2. **Cloud Storage**:
   - Google Apps Script logs sensor data into a spreadsheet.

3. **Web Application**:
   - Flask app fetches live data from Google Sheets.
   - Displays values on the website.
   - Analyzes data against crop-specific thresholds (e.g., ideal temp for tomatoes: 20-30°C).
   - Generates descriptive insights (e.g., "Soil too dry, water your lettuce").

4. **Manual Input**:
   - Users can enter values via a form to get insights without sensors.

---

## Setup Instructions

### Prerequisites
- Python 3.x
- Flask (`pip install flask`)
- Google Cloud project with Sheets API enabled
- IoT hardware (sensors + microcontroller)
- Git (`brew install git` on macOS)

### Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/Smart-Farm-with-IoT_Basic.git
   cd Smart-Farm-with-IoT_Basic
