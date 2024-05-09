import os
import numpy as np # == 1.21.6
import pandas as pd # == 1.3.5
import tensorflow as tf # == 2.9.2
from CRS import CRS

dir_path = os.path.dirname(os.path.realpath(__file__))
model_path = os.path.join(dir_path, 'car_rs')
car_data_path = os.path.join(dir_path, 'Car Dataset 2022.csv')
car = pd.read_csv(car_data_path)


crs = CRS(model_path, car_data_path)
results = crs.recommend([23, True, 150000, 'Sedan', 'Petrol', 5])

print(results)
