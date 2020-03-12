#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb 27 09:14:40 2020

@author: suman
"""

import numpy as np

a=np.array([[1.0,0.67,0.33],[0.45,1.0,0.55],[0.67,0.33,1.0]]) #given matrix
b=np.array([2.0,2.0,2.0])
x=np.linalg.solve(a,b) #solution using numpy function
print("The solution of given equation",x) #print the solution as an array
