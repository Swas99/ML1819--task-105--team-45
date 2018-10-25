# -*- coding: utf-8 -*-
"""
Created on Wed Oct 24 00:02:48 2018

@author: Sahir
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import statsmodels.api as sm

def plotData(X,y):
  # plots the data points with o for the positive examples and x for the negative examples. output is saved to file graph.png
  fig, ax = plt.subplots(figsize=(12,8))
  
  positive = y>0
  negative = y<0
  
  ax.scatter(X[positive,0],X[positive,1],c='b',marker='o',label='Healthy')
  ax.scatter(X[negative,0],X[negative,1],c='r',marker='x',label='Not Healthy')

  ax.set_xlabel('Test 1')
  ax.set_ylabel('Test 2')  
  fig.savefig('graph.png') 
  
def predict(X,theta):
  hypo=np.dot(X,theta)
  pred=np.sign(hypo)
  return pred

def computeCost(X, y, theta):
  cost = 1/(len(y)) * np.sum ( np.log ( 1 + np.exp( (-y) * (X.dot(theta))) ) )
  return cost

def computeGradient(X,y,theta):
  m = len(y)
  grad = X.T.dot( (-y) * ((np.exp( (-y) * (X.dot(theta))))/(1 + np.exp( (-y) * (X.dot(theta)))))) / (len(y))
  return grad

def gradientDescent(X, y):
  # iteratively update parameter vector theta

  # initialize variables for learning rate and iterations
  alpha = 0.1
  iters = 10000
  cost = np.zeros(iters)
  (m,n)=X.shape
  theta= np.zeros(n)

  for i in range(iters):
    theta = theta - alpha * computeGradient(X,y,theta)
    cost[i] = computeCost(X, y, theta)

  return theta, cost

def normaliseData(x):
  # rescale data to lie between 0 and 1
  scale = x.max(axis=0)
  return (x/scale, scale)

def addQuadraticFeature(X):
  # Given feature vector [x_1,x_2] as input, extend this to
  # [x_1,x_2,x_1*x_1] i.e. add a new quadratic feature
  X = np.append(X, np.power(X[:, [0]], 2), axis=1)
  return X

def computeScore(X,y,preds):
  score = len(y) - np.count_nonzero(y-preds)
  return score

def plotDecisionBoundary(Xt,y,Xscale,theta):
  # plots the training data plus the decision boundary in the model
  fig, ax = plt.subplots(figsize=(12,8))
  # plot the data
  positive = y>0
  negative = y<0
  ax.scatter(Xt[positive,1]*Xscale[1], Xt[positive,2]*Xscale[2], c='b', marker='o', label='Healthy')
  ax.scatter(Xt[negative,1]*Xscale[1], Xt[negative,2]*Xscale[2], c='r', marker='x', label='Not Healthy')
  # calc the decision boundary
  x=np.linspace(Xt[:,2].min()*Xscale[2],Xt[:,2].max()*Xscale[2],50)
  if (len(theta) == 3):
    # linear boundary
    x2 = -(theta[0]/Xscale[0]+theta[1]*x/Xscale[1])/theta[2]*Xscale[2]
  else:
    # quadratic boundary
    x2 = -(theta[0]/Xscale[0]+theta[1]*x/Xscale[1]+theta[3]*np.square(x)/Xscale[3])/theta[2]*Xscale[2]
  # and plot it
  ax.plot(x,x2,label='Decision boundary')
  ax.legend()
  ax.set_xlabel('Test 1')
  ax.set_ylabel('Test 2')  
  fig.savefig('pred.png')   
  
def main():
  # load the training data
  n_samples=1797
  digit_images = np.loadtxt('digit_images.txt')
  digit_images = digit_images.reshape((n_samples, 8, 8))
  X = digit_images.reshape((n_samples, -1))
  y = np.loadtxt('digit_classes.txt')

  images_and_labels = list(zip(digit_images, y))
  fig, ax = plt.subplots(2, 4)
  for index, (image, label) in enumerate(images_and_labels[:8]):
      ax[index//4,index%4].axis('off')
      ax[index//4,index%4].imshow(image, cmap=plt.cm.gray_r, interpolation='nearest')
      ax[index//4,index%4].set_title('Training: %i' % label)
  fig.savefig('digits.png')

  #X = digits.reshape((n_samples, -1))
  
  from sklearn import linear_model
  model = linear_model.LogisticRegression(C=1)

  # split the data into training and test parts
  from sklearn.model_selection import train_test_split
  X_train, X_test, y_train, y_test = train_test_split(X,y,test_size=0.9)

  # now train the model ...
  model.fit(X_train,y_train)
  print(model.coef_.shape)
  
  from sklearn import metrics
  predicted = model.predict(X_test)
  print(metrics.classification_report(y_test, predicted))
  print(metrics.confusion_matrix(y_test, predicted))
 
  
if __name__ == '__main__':
  main()
