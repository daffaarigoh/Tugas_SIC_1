from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['POST'])
def sensor_data():
    try:
        data = request.get_json()
        if data is None:
            return jsonify({"error": "Request body must be JSON"}), 400

        temperature = data.get('temperature')
        humidity = data.get('humidity')
        air_quality = data.get('air_quality')

        if temperature is None or humidity is None or air_quality is None:
            return jsonify({"error": "Missing temperature, humidity, or air quality data"}), 400

        # Log the received data
        print(f"Received data - Temperature: {temperature} °C, Humidity: {humidity} %, Air Quality: {air_quality}")

        # Here you can process the data or store it in a database

        return jsonify({"message": "Data received successfully!"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
