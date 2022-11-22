import csv
import time

import numpy as np
import pandas as pd
from scipy.spatial.distance import cdist
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from tqdm import trange
import matplotlib.pyplot as plt


def KMeans(x, k, no_of_iterations):
    # Generating 4 random values from x
    cid = np.random.choice(len(x), k, replace=False)
    # Choosing random 4 centroids
    # Getting all values from the random values (: => we have both x and y values from the np array)
    centroids = x[cid, :]

    # Visualizing the initial centroids
    # plt.scatter(centroids[:, 0], centroids[:, 1], c='r', s=10)
    # plt.show()

    # Computing the distance between the initial centroids and all the data points
    distances = cdist(x, centroids, 'euclidean')

    # Centroid with the minimum distance
    # argmin => the indices of the minimum value
    # Finding the closest centroid to every point and taking the indices of that distance
    points = np.array([np.argmin(distance) for distance in distances])

    # Iterating until the centroids do not move to a better approximation (mean)
    # In our case we have a predefined number of iterations
    for _ in trange(no_of_iterations):
        newCentroids = []
        for cid in range(k):
            # updating centroids by taking mean of cluster it belongs to
            clusteredPoints = []
            for i in range(len(points)):
                if points[i] == cid:
                    clusteredPoints.append(x[i])
            temp_centroid = np.array(clusteredPoints).mean(axis=0)
            newCentroids.append([temp_centroid[0], temp_centroid[1]])

        # updated centroids
        centroids = np.unique(np.array(newCentroids), axis=0)
        # Recomputing the distance between the centroids and all the data points
        distances = cdist(x, centroids, 'euclidean')
        # Remapping all points to the closest centroid
        points = np.array([np.argmin(distance) for distance in distances])

    return points, centroids


def evaluateLabeling(realLabels, foundLabels):
    labelCount = len(realLabels)
    matched_labels = 0
    for i in range(labelCount):
        if realLabels[i] == foundLabels[i]:
            matched_labels = matched_labels + 1

    accuracy = matched_labels / labelCount

    precisions = {}
    rappel_data = {}
    score = {}

    for label in range(4):
        correctLabelsCount = 0
        precisionCount = 0
        recallCount = 0

        for realLabel, computedLabel in zip(realLabels, foundLabels):
            if realLabel == computedLabel == label:
                correctLabelsCount += 1
            if computedLabel == label:
                precisionCount += 1
            if realLabel == label:
                recallCount += 1

        precision = correctLabelsCount / precisionCount
        rappel = correctLabelsCount / recallCount

        precisions[label] = precision
        rappel_data[label] = rappel
        if precision == 0 and rappel == 0:
            score[label] = 0
        else:
            score[label] = 2 * precision * rappel / (precision + rappel)

    return {"Accuracy": accuracy, "Precision": precisions, "Recall": rappel_data, "Score": score}


def display(x, realLabels, foundLabels, foundPoints):
    colorsDict = {0: '#EB5E28', 1: '#008000', 2: '#6666FF', 3: '#1ABCC1'}

    plt.scatter(x[:, 0], x[:, 1], c=[colorsDict[point] for point in foundPoints])
    plt.scatter(foundLabels[:, 0], foundLabels[:, 1], c='r', s=42)
    plt.show()
    time.sleep(0.5)

    for k, v in evaluateLabeling(realLabels, foundPoints).items():
        print(k, end=": ")
        print(v)

    print()


def read_points():
    points = []
    labels = []
    label_dict = {'A': 0, 'B': 2, 'C': 3, 'D': 1}

    with open('dataset.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        next(csv_reader)
        for row in csv_reader:
            labels.append(label_dict[row[0]])
            # Complete appending point (row1, row2) to points list
            points.append([row[1], row[2]])
    return points, labels


if __name__ == "__main__":
    # load data => does not work for some reason
    # data = pd.read_csv('dataset.csv', names=['letter', 'X', 'Y'], skiprows=1)
    #
    # initialPoints = data.loc[:, ['X', 'Y']].values
    # initialLabels = data.loc[:, ['letter']].values

    # load data
    initialPoints, initialLabels = read_points()

    # Use skikit learns PCA s
    # Using 2 as it has 2 features that represent the data
    pca = PCA(2)

    # transform the data aka fit the model with X
    # Applying the dimensionality reduction on X
    df = pca.fit_transform(initialPoints)

    points, foundCentroids = KMeans(df, 4, 10)
    display(df, initialLabels, foundCentroids, points)
