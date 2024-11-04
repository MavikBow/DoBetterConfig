import json

# Read the JSON file
with open('download_data.json', 'r') as file:
    data = json.load(file)

# Initialize total download count
total_download_count = 0

last_day = data[-1]

# Sum up all the download counts
for version in last_day['versions']:
    total_download_count += version['download_count']

# Print the total download count
print(total_download_count)
