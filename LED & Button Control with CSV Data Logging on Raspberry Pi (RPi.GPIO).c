import RPi.GPIO as GPIO
import time
import csv
from datetime import datetime
from pathlib import Path

# === GPIO SETUP ===
GPIO.setmode(GPIO.BCM)
LED_PIN = 17
BUTTON_PIN = 27

GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# === CSV SETUP ===
csv_file = Path("led_button_log.csv")
file_exists = csv_file.exists() and csv_file.stat().st_size > 0

f = open(csv_file, mode="a", newline="")
writer = csv.writer(f)
if not file_exists:
    writer.writerow(["Timestamp", "Button State", "LED State"])
    f.flush()

print("=" * 43)
print(" LED Control with Button & CSV Logging")
print(" Logging to:", csv_file.resolve())
print(" Press CTRL+C to stop")
print("=" * 43)

try:
    while True:
        button_state = GPIO.input(BUTTON_PIN)

        if button_state == GPIO.LOW:   # pressed (pull-up -> LOW)
            GPIO.output(LED_PIN, GPIO.HIGH)
            led_state = "ON"
            button_text = "Pressed"
        else:
            GPIO.output(LED_PIN, GPIO.LOW)
            led_state = "OFF"
            button_text = "Not Pressed"

        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print(f"{timestamp} | Button: {button_text} | LED: {led_state}", end="\r")

        writer.writerow([timestamp, button_text, led_state])
        f.flush()  # ensure the row is written to disk

        time.sleep(0.5)  # sampling/logging interval
except KeyboardInterrupt:
    print("\nProgram stopped by user.")
finally:
    GPIO.cleanup()
    f.close()
