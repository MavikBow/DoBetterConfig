import requests
import json
from datetime import date

# make a new dict elements from the data at the link

response = requests.get('https://api.github.com/repos/mavikbow/dobetterconfig/releases')

if response.status_code == 200:
   data = response.json()

todays_dict = {}
todays_dict["date"] = date.today().isoformat()

version_list = []
per_version_dict = {}

   
for item in data:
    per_version_dict["name"] = item["tag_name"]
    counter = 0
    for unit in item["assets"]:
        counter += unit["download_count"]
    per_version_dict["download_count"] = counter
    version_list.append(per_version_dict.copy())

todays_dict["versions"] = version_list

# read the list from the local json file and if not there, append it

with open("../download_data.json", 'r') as file:
    data_list = json.load(file)

if not any(item["date"] == todays_dict["date"] for item in data_list):
    data_list.append(todays_dict)

with open("../download_data.json", 'w') as file:
    json.dump(data_list, file, indent=2)
