# 1. Importing Libraries
<img width="339" alt="image" src="https://user-images.githubusercontent.com/121603164/236640720-aebd3d4f-b1b0-4cb7-985a-19733f7b87f9.png">

First, we will import the dataset of World Energy Consumption that is obtained from Kaggle and we will upload it into Google Colab. Run the program and it will read the CSV file data.


# 2. Importing the dataFrame

<img width="681" alt="image" src="https://user-images.githubusercontent.com/121603164/236640856-402cb1dc-00e7-40b3-b26d-f39ac2c01a4a.png">
<img width="874" alt="image" src="https://user-images.githubusercontent.com/121603164/236640836-67d8424a-fd45-4bf7-a3c3-36559738f93d.png">

The program will show the list of the first 10 dataset of country in descending order from the World Energy Consumption data and display it with all the selected attributes. The attributes are 'country','year','coal_production','electricity_generation','biofuel_electricity','coal_electricity','fossil_electricity','gas_electricity','hydro_electricity','nuclear_electricity','oil_electricity'      'renewables_electricity','oil_production','population','gdp','solar_electricity','wind_electricity','energy_per_gdp','energy_per_capita','fossil_share_elec','gas_share_elec','gas_production','low_carbon_share_elec'

# 3. Heatmap Matrix Correlation
Figure below shows the heatmap matrix correlation between the attributes. This correlation heatmap is used for us to find potential relationships between variables and to understand the strength of these relationships.

<img width="676" alt="image" src="https://user-images.githubusercontent.com/121603164/236640973-767be2a3-d6c8-4418-a30d-58dce10dde26.png">

The higher correlation has blue shade whereas lower correlation is in the pink shade. For example, low carbon share electricty has highest correlation with the attribute carbon intensity electricity.

![alt text](https://user-images.githubusercontent.com/121603164/236641001-fdf564c7-0a10-49ad-a809-447df8ea6911.png)


# 4. Cleaning the data
Data cleaning is done on the dataset to remove redundant and null values.

Before:

<img width="192" alt="image" src="https://user-images.githubusercontent.com/121603164/236641018-715d5c76-d1b4-4218-8a97-d868edb09e8c.png">
<img width="99" alt="image" src="https://user-images.githubusercontent.com/121603164/236641034-aa1977d3-f0a7-4d77-b737-fdd76b1c618f.png">

After:

<img width="424" alt="image" src="https://user-images.githubusercontent.com/121603164/236641205-5663e06c-8537-478e-b120-8e09824ab2d8.png">
<img width="94" alt="image" src="https://user-images.githubusercontent.com/121603164/236641225-2207885b-17c5-4d97-97f4-bf5a9ac0eb5d.png">

# 5. Training the data

The important libraries have been imported to enable the coding to make code in one module available in another and also for structuring the code effectively.

![image](https://user-images.githubusercontent.com/121591873/236680375-b17d15ca-558d-4b88-9993-089f1573d9b8.png)

Then we load the csv file of the dataset for the panda to read the dataframe.

![image](https://user-images.githubusercontent.com/121591873/236680413-d265cf80-ee67-492f-b1b0-5ec32e17b289.png)

The important features are then split into x and y for testing and training purposes.

![image](https://user-images.githubusercontent.com/121591873/236680500-7137aa97-bc52-424f-ba52-c79640f05d2a.png)

![image](https://user-images.githubusercontent.com/121591873/236680525-517411f0-0b87-46c7-83ca-e57794460da1.png)

![image](https://user-images.githubusercontent.com/121591873/236680548-7c05004d-385e-4a67-a044-2d9925c563af.png)

![image](https://user-images.githubusercontent.com/121591873/236680579-1c104a54-0715-4929-bbd1-1c1e6271f81a.png)![image](https://user-images.githubusercontent.com/121591873/236680619-66fb7312-2209-4bce-8e8e-0b6481cd0eaf.png)

Multiple linear regression machine algorithm has been implemented to train the data and the training set R2 has an accuracy score of 0.3192718568885481. For the testing set, the accuracy is 0.3145148369408486.
 
![image](https://user-images.githubusercontent.com/121591873/236680781-1b3a99ba-440a-443d-a7ef-32e6fa1c5e8b.png)



# 6. Selecting the color scheme
<img width="138" alt="image" src="https://user-images.githubusercontent.com/121603164/236641252-489abe3d-1d47-41f0-83ed-95824f8fa290.png">

![image](https://user-images.githubusercontent.com/121603164/236641273-737e5f02-03cc-406c-91bc-bebdd9d573a8.png)

Select the color scheme pallete for the visualization of data.

# 7. GDP Vs Population Trends
<img width="631" alt="image" src="https://user-images.githubusercontent.com/121603164/236641305-a2d5f695-5422-4dcd-a2a4-0e3f5f50d398.png">

![image](https://user-images.githubusercontent.com/121603164/236641322-4dc74d67-6fb9-4c98-92cc-f9c8399f631e.png)

Based on the graph, USA has shown an increasing trend and has the highest GDP per capita. China follows the USA with being the second most highest GDP oer capitaa. These two countries monopolized the graph as both countries have high population.

# 8. Slicing through the years for 2010-2015 VS 2016-2020

<img width="557" alt="image" src="https://user-images.githubusercontent.com/121603164/236641497-1f8e6125-4b0f-418b-94e1-e4abb4c220e3.png">
<img width="524" alt="image" src="https://user-images.githubusercontent.com/121603164/236641474-8de1746b-0e0c-40c7-86e9-e24883144d3b.png">


![alt text](![image](https://user-images.githubusercontent.com/122136926/236682517-3cff2f51-5c11-4a06-9481-feec8f22b93a.png)

Visualize the comparison graph of GDP, Population and GDP per capita each country in the year of 2010-2015 and 2015-2020

# 9. Electricty source distribution in Japan

The chart below shows Japan's electricity source distribution over the years. It consists of 7 sources of energy, which are "coal electricity," "oil electricity," "gas electricity," "hydroelectricity," "nuclear electricity," "wind electricity," and "solar electricity." The linear plot is being used to visualise the trends of each source over the years. We also do a comparison of electricity distribution in 2000 and 2020 and visualise it in the pie charts.

<img width="443" alt="image" src="https://user-images.githubusercontent.com/121603164/236679392-94f5a4a1-c661-4005-8bdb-c5e5cbb7826a.png">

The output below illustrates Japan's electricity source distribution from 1990 to 2020. In 2011, there were significant changes in nuclear, oil, gas, and coal. This is due to the Great East Japan Earthquake.

![image](https://user-images.githubusercontent.com/121603164/236679527-b0fdb6bb-3b65-4b2a-83a7-9c974bcddb64.png)

# 10. Electricty source distribution in India
<img width="472" alt="image" src="https://user-images.githubusercontent.com/121603164/236679222-f898e252-6d43-492e-b01e-b77c8f9ea71c.png">

The pie chart for India's electrcity indicate changes especially for the use of wind electricity and solar electricity starting from year 2010 onwards.

![India](https://github.com/SmoothCriminal08/World-Energy-Consumption/blob/main/Images/India.png)

# 11. Electricty source distribution in Malaysia 

<img width="580" alt="image" src="https://user-images.githubusercontent.com/122136926/236666505-1a817eef-20d2-4755-93b5-b73cd9475962.png">

Pie chart below shows the comparison of electricity generation in Malaysia within past years with insights that causes impacts on the trend of electricity generation in Malaysia. It can be seen coal, gas and oil are the important sources of electricity in Malaysia. On the other hand, the solar electricity and hydro electricity is a growing source in electricity generation in Malaysia. 

![Malaysia](https://github.com/SmoothCriminal08/World-Energy-Consumption/blob/main/Images/Malaysia.png)


