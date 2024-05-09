import os

import html
import pandas as pd
from flask import Flask, request, render_template
from CRS import CRS

web = Flask(__name__, template_folder="templates", static_folder="static")
dir_path = os.path.dirname(os.path.realpath(__file__))
model_path = os.path.join(dir_path, 'car_rs')
car_data_path = os.path.join(dir_path, 'Car Dataset 2022.csv')
crs = CRS(model_path, car_data_path)


@web.route('/')
def home():
    return render_template('index.html')


@web.route('/bmw')
def bmw():
    return render_template('bmw.html')


@web.route('/honda')
def honda():
    return render_template('honda.html')


@web.route('/hyundai')
def hyundai():
    return render_template('hyundai.html')


@web.route('/perodua')
def perodua():
    return render_template('perodua.html')


@web.route('/toyota')
def toyota():
    return render_template('toyota.html')


@web.route('/more')
def more():
    return render_template('more.html')


@web.route('/recommend', methods=['POST', 'GET'])
def recommend():
    if request.method == 'POST':
        try:
            age = int(request.form["age"])
            gender = bool(request.form["gender"])
            budget = int(request.form["budget"])
            body_type = request.form["body type"]
            fuel = request.form["fuel type"]
            seats = int(request.form["seats"])
        except:
            return render_template('recommendation.html', result_text="Please fill in all attribute")

        data = [age, gender, budget, body_type, fuel, seats]

        output = crs.recommend(data)

        if output is None:
            return render_template('recommendation.html', result_text="There is no car matched")

        else:
            output = output.drop(columns=['Car ID']).reset_index(drop=True)
            print(output)
            try:
                html_table = output.to_html()
            except Exception as ex:
                print(ex)
            return render_template('recommendation.html', result_text="Your Recommended Car", tables=[html_table], titles=[''])
    else:
        return render_template('recommendation.html', result_text="")

if __name__ == '__main__':
    web.run(debug=True)

