import numpy as np
import pandas as pd
import pickle

dataset_path = 'C:/Users/PC/Documents/Piranti Cerdas/Tugas 5/dataset/dataset_pc.csv'

#Load the data and finish the cleaning process
train = pd.read_csv(dataset_path)

print(train.head())
print(train.shape)

feat_labels = list(train.columns)
print(feat_labels)

from sklearn import preprocessing
le = preprocessing.LabelEncoder()

X_train = train.drop(columns=['Label'])
y_train = train['Label']

X_train = X_train.apply(le.fit_transform)
y_train = le.fit_transform(y_train)

#choose algorithm and model fitting
from sklearn.tree import DecisionTreeClassifier
from sklearn import tree

clf = tree.DecisionTreeClassifier(criterion='entropy',max_depth=3)
clf.fit(X_train,y_train)

filename = "dtc.sav"
pickle.dump(clf, open(filename, 'wb'))
