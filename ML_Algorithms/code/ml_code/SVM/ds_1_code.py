# -*- coding: utf-8 -*-
"""
Created on Wed Oct 24 21:41:17 2018

@author: Neil-PC
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_breast_cancer
from random import randint
from sklearn.model_selection import train_test_split

def predict(X,theta):
  ##### replace the next line with your code #####
  pred=np.sign(np.dot(X,theta))
  return pred

def computeCost(X, y, theta, lambd):
  # function calculates the cost J(theta) and returns its value
  ##### replace the next line with your code #####
  redundant=0;
  redundant=lambd*np.dot(theta.T,theta);
  cost = 1/len(y)*np.sum(np.maximum(np.zeros(len(y)),np.ones(len(y))-y*np.dot(X,theta)))+redundant
  return cost

def computeGradient(X,y,theta,lambd):
  # calculate the gradient of J(theta) and return its value
  ##### replace the next lines with your code #####
  redundant=0;
  redundant=2*lambd*theta;
  grad = redundant-1/len(y)*np.dot(y*(y*np.dot(X,theta)<=1),X)
  return grad

def gradientDescent(X, y, theta,lambd):
  # iteratively update parameter vector theta
  
  # initialize variables for learning rate and iterations
  alpha = 0.02
  iters = 5000
  cost = np.zeros(iters)
  (m,n)=X.shape
  theta= np.zeros(n)
  # let's use a reasonable starting point for theta (the value we obtained in the logistic regression assignment)
  #theta=[3.08,2.97,3.69,-5.36]
  for i in range(iters):
    theta = theta - alpha * computeGradient(X,y,theta,lambd)
    cost[i] = computeCost(X, y, theta,lambd)
  return theta, cost

def normaliseData(x):
  # rescale data to lie between 0 and 1
  scale = x.max(axis=0)
  return (x/scale, scale)

def addQuadraticFeature(X):
  # Given feature vector [x_1,x_2] as input, extend this to
  # [x_1,x_2,x_1*x_1] i.e. add a new quadratic feature
  ##### insert your code here #####
  x1=np.reshape(X[:,0]**2,(len(X), 1))
  X=np.append(X,x1,axis=1)
  return X

def computeScore(X,y,preds):
  # for training data X,y it calculates the number of correct predictions made by the model
  ##### replace the next line with your code #####
  score=sum(y==preds)
  return score

def main():
  # load the training data
  data=load_breast_cancer()#np.loadtxt('health.csv',delimiter=",")
  X=data.data
  y=data.target
  for i in range(len(y)):
      if (y[i]==0):
          y[i]=-1
  #X=addQuadraticFeature(X)  
  
  # add a column of ones to input data
  m=len(y)
  Xt = np.column_stack((np.ones((m, 1)), X))
  (m,n)=Xt.shape # m is number of data points, n number of features

  # rescale training data to lie between 0 and 1
  (Xt,Xscale) = normaliseData(Xt)
  
  lambd=0
  X_train, X_test, y_train, y_test = train_test_split(Xt, y, test_size=0.2)
  print (X_train.shape, y_train.shape)
  print (X_test.shape, y_test.shape)
  theta=np.zeros(n)
  theta, cost = gradientDescent(X_train, y_train, theta,lambd)
  
  preds = predict(X_test,theta)
  score = computeScore(X_test,y_test,preds)
  print('accuracy = {0:.2f}%'.format(score/len(y_test)*100))

  # plot how the cost varies as the gradient descent proceeds
  fig2, ax2 = plt.subplots(figsize=(12, 8))
  ax2.semilogy(cost,'r')
  ax2.set_xlabel('iteration')
  ax2.set_ylabel('cost')
  fig2.savefig('cost.png')

if __name__ == '__main__':
  main()