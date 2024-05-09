# import library
# python == 3.8.16
import tensorflow as tf  # == 2.9.2
import numpy as np  # == 1.21.6
import pandas as pd  # == 1.3.5


# class for recommender
class CRS:
    def __init__(self, model_path, car_data_path):
        self.age = None
        self.gender = None
        self.budget = None
        self.body_type = None
        self.fuel = None
        self.seat_num = None
        self.output = 5
        self.car_recommended = None
        self.car_id = None
        self.cars = pd.read_csv(car_data_path)  # get car data
        self.model = tf.saved_model.load(model_path)  # get nn model
        self.result_car_name = []
        self.result_car_id = []
  
    # simple filter
    def filter_car(self):
        filtered = self.cars[(self.cars['Price (RM)'] <= self.budget) & (self.cars['Body Type'] == self.body_type) &
                             (self.cars['Fuel'] == self.fuel) & (self.cars['Seats'] == self.seat_num)]
        # filtered = filtered.sort_values(by=['Rating'], ascending=False)
        filtered = filtered.sample(frac=1).reset_index(drop=True)
        if len(filtered) > 0:
            return filtered
        else:
            return None

    # prediction
    def predict(self):
        _, prediction = self.model({
          "car_id": np.array([int(self.car_id)]),
          "gender": np.array([bool(self.gender)]),
          "age": np.array([int(self.age)])
        })
        return prediction[0]

    # to list
    def to_list(self):
        self.result_car_name = list()
        r_cars = f"{self.car_recommended}"
        for c in r_cars.split("'"):
            if len(c) > 5:
                self.result_car_name.append(c.strip())

        return self.to_df()

    def to_df(self):
        self.result_car_id = list()
        for cn in self.result_car_name[:self.output]:
            self.result_car_id.append(self.cars.index[self.cars["Car Name"] == cn].tolist()[0])
            print(self.result_car_id)
        return self.cars.loc[self.result_car_id]

    # caller function
    def recommend(self, data_list, output=5):
        self.age = data_list[0]
        self.gender = data_list[1]
        self.budget = data_list[2]
        self.body_type = data_list[3]
        self.fuel = data_list[4]
        self.seat_num = data_list[5]
        self.output = output
        try:
            self.car_id = self.filter_car().iloc[0]['Car ID']
        except:
            return None
        self.car_recommended = self.predict()
        # return self.car_recommended
        return self.to_list()
