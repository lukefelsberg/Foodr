import pandas as pd # pip install pandas
import json
import csv


with open(r"C:\Users\lukef\OneDrive\Desktop\UF\3.1\yelp_academic_dataset_business.json", encoding='utf-8-sig') as f_input:
    df = pd.read_json(f_input, lines=True)

df.to_csv('output.csv', encoding='utf-8', index=False)
