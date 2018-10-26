import os
import requests
import pandas as pd
import numpy as np
df = pd.read_csv("haberman.txt", header=None, names=["age_at_op","op_yr","nr_nodes","survival"])
FEATURES = df[["age_at_op","op_yr","nr_nodes"]]
TARGETS = df[["survival"]]

from sklearn import cross_validation as cv
splits = cv.train_test_split(FEATURES, TARGETS, test_size=0.2)
X_train, X_test, y_train, y_test = splits

from sklearn.metrics import classification_report

from sklearn.linear_model import LogisticRegression
model = LogisticRegression()
model.fit(X_train, y_train)
expected = y_test
predicted = model.predict(X_test)
print ("Logistic Regression Classifier \n Haberman survival dataset")
print (classification_report(expected, predicted, target_names=[">=5 years","<5 years"]))
