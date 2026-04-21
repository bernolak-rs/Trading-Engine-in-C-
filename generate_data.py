#!/usr/bin/env python3
import csv
from datetime import datetime, timedelta
import random

# read existing data
existing_data = []
try:
    with open('data/SPY.csv', 'r') as f:
        reader = csv.DictReader(f)
        existing_data = list(reader)
except Exception as e:
    print(f"Error reading existing data: {e}")

# parse last date
if existing_data:
    last_date_str = existing_data[-1]['Date']
    last_date = datetime.strptime(last_date_str, '%Y-%m-%d')
    last_close = float(existing_data[-1]['Close'])
else:
    # default start date if no data exists
    last_date = datetime(2024, 4, 10)
    last_close = 515.72

# generate new data - 200+ trading days (roughly 9-10 months)
new_data = []
current_date = last_date + timedelta(days=1)
current_price = last_close

# skip weekends
while len(new_data) < 200:
    # skip weekends (5=Saturday, 6=Sunday)
    if current_date.weekday() < 5:
        # generate realistic data
        # daily change between -2% and +2%
        daily_change_pct = random.uniform(-0.02, 0.02)
        open_price = current_price * (1 + random.uniform(-0.005, 0.005))
        close_price = current_price * (1 + daily_change_pct)
        
        # High and Low around Open and Close
        high_price = max(open_price, close_price) * (1 + abs(random.uniform(0.001, 0.01)))
        low_price = min(open_price, close_price) * (1 - abs(random.uniform(0.001, 0.01)))
        
        # realistic volume (50M to 150M shares)
        volume = random.randint(50000000, 150000000)
        
        new_data.append({
            'Date': current_date.strftime('%Y-%m-%d'),
            'Open': f"{open_price:.2f}",
            'High': f"{high_price:.2f}",
            'Low': f"{low_price:.2f}",
            'Close': f"{close_price:.2f}",
            'Adj Close': f"{close_price:.2f}",
            'Volume': str(volume)
        })
        
        current_price = close_price
    
    current_date += timedelta(days=1)

# append at the end of CSV file
with open('data/SPY.csv', 'a') as f:
    writer = csv.DictWriter(f, fieldnames=['Date', 'Open', 'High', 'Low', 'Close', 'Adj Close', 'Volume'])
    writer.writerows(new_data)

print(f"Generated and appended {len(new_data)} new data rows")
print(f"Total data points now: {len(existing_data) + len(new_data)}")
print(f"Date range: {existing_data[0]['Date']} to {new_data[-1]['Date']}")
