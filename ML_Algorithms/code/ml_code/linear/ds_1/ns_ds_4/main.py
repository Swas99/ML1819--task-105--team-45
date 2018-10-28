# -*- coding: utf-8 -*-
"""
Created on Fri Oct 26 00:09:29 2018

@author: Sahir
"""

import numpy as np
import pandas as pd
from pandas import DataFrame
import scipy.stats as stats
import matplotlib.pyplot as plt
import sklearn
import statsmodels.api as sm

import seaborn as sns
sns.set_style("whitegrid")
sns.set_context("poster")

# special matplotlib argument for improved plots
from matplotlib import rcParams

from sklearn.model_selection import train_test_split

from sklearn.linear_model import LinearRegression

import sklearn.cross_validation

import csv

with open("C:/Users/Sahir/Desktop/Machine Learning Group/Linear Regression/ds_1/ns_ds_1/boston.csv") as f:
    data=csv.reader(f, delimiter='\t')
    flag=0
    for rows in data:
        if(flag==0):
            Xinit=[rows]
            flag=1
        else:
            Xinit=np.append(Xinit,[rows],axis=0)
    Xinit=np.array(Xinit,dtype='float')
    print(X.shape)
    X=Xinit[:,:-1]
    Y=Xinit[:,-1]
    print(X.shape,y.shape)

X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size = 0.2)

lm = LinearRegression()
lm.fit(X_train, Y_train)


Y_pred = lm.predict(X_test)

fig, ax = plt.subplots(figsize=(12, 8))
ax.scatter(Y_test, Y_pred)
ax.set_xlabel("Prices: $Y_i$")
ax.set_ylabel("Predicted prices: $\hat{Y}_i$")
plt.title("Prices vs Predicted prices: $Y_i$ vs $\hat{Y}_i$")
fig.savefig('graph.png')

mse = sklearn.metrics.mean_squared_error(Y_test, Y_pred)
print(mse)

