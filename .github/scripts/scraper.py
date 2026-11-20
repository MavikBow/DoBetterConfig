import os
import pandas as pd
import requests
import json
import sys
from datetime import date

# make a new dict elements from the data at the link

# Authenticated requests get a per-repo rate limit (1000/h) instead of the
# 60/h per-IP limit that GitHub's shared runners can exhaust.
headers = {"Accept": "application/vnd.github+json"}
token = os.environ.get("GITHUB_TOKEN")
if token:
    headers["Authorization"] = f"Bearer {token}"

response = requests.get('https://api.github.com/repos/mavikbow/dobetterconfig/releases', headers=headers, timeout=30)

if response.status_code == 200:
   data = response.json()
else:
    print(f"GitHub API request failed: HTTP {response.status_code}", file=sys.stderr)
    for h in ("x-ratelimit-limit", "x-ratelimit-remaining", "x-ratelimit-reset"):
        if h in response.headers:
            print(f"  {h}: {response.headers[h]}", file=sys.stderr)
    print(response.text[:500], file=sys.stderr)
    sys.exit(1)

todays_dict = {}
todays_dict["date"] = date.today().isoformat()

for item in data:
    version_name = item["tag_name"]
    counter = 0
    for unit in item["assets"]:
        counter += unit["download_count"]
    todays_dict[version_name] = int(counter)

# append the data to the whole dataset

df_today = pd.DataFrame([todays_dict])
df_existing = pd.read_csv('download_data.csv')

df_combined = pd.concat([df_existing, df_today])
df_combined = df_combined.drop_duplicates(subset='date', keep='first')

# Convert all numeric columns to integers
for col in df_combined.columns:
    if col != 'date':  # Skip non-numeric columns
        df_combined[col] = pd.to_numeric(df_combined[col], errors='coerce').astype('Int64')

df_combined.to_csv('download_data.csv', index=False)
