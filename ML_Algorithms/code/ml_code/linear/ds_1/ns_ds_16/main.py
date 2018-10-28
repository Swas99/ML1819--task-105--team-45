# -*- coding: utf-8 -*-
"""
Created on Fri Oct 26 00:09:29 2018

@author: Sahir
"""

import numpy as np
import pandas as pd
import scipy.stats as stats
import matplotlib.pyplot as plt
import sklearn
import statsmodels.api as sm

import seaborn as sns
sns.set_style("whitegrid")
sns.set_context("poster")

# special matplotlib argument for improved plots
from matplotlib import rcParams

from sklearn.datasets import load_boston

from sklearn.linear_model import LinearRegression

import sklearn.cross_validation

boston = load_boston()

print(boston.keys())

print(boston.data.shape)

print(boston.feature_names)

print(boston.DESCR)

bos = pd.DataFrame(boston.data)
print(bos.head())

bos.columns = boston.feature_names
print(bos.head())

print(boston.target.shape)

bos['PRICE'] = boston.target
print(bos.head())

print(bos.describe())

X = bos.drop('PRICE', axis = 1)
Y = bos['PRICE']

X_train, X_test, Y_train, Y_test = sklearn.cross_validation.train_test_split(X, Y, test_size = 0.33, random_state = 5)
print(X_train.shape)
print(X_test.shape)
print(Y_train.shape)
print(Y_test.shape)

lm = LinearRegression()
lm.fit(X_train, Y_train)

Y_pred = lm.predict(X_test)

plt.scatter(Y_test, Y_pred)
plt.xlabel("Prices: $Y_i$")
plt.ylabel("Predicted prices: $\hat{Y}_i$")
plt.title("Prices vs Predicted prices: $Y_i$ vs $\hat{Y}_i$")

mse = sklearn.metrics.mean_squared_error(Y_test, Y_pred)
print(mse)

