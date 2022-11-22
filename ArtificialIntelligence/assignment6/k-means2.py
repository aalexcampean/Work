import csv
import time

import numpy as np
from scipy.spatial.distance import cdist
from sklearn.decomposition import PCA
from tqdm import trange
import matplotlib.pyplot as plt


def k_means(x, k, no_of_iterations, real_labels):
    cid = np.random.choice(len(x), k, replace=False)
    # choose random centroids
    centroids = x[cid, :]
    # plt.scatter(centroids[:, 0], centroids[:, 1], c='r', s=10)
    # plt.show()

    # distance between centroids and all the data points
    distances = cdist(x, centroids, 'euclidean')

    # Cluster ID assign to data
    points_cid = np.array([np.argmin(distance) for distance in distances])

    for _ in trange(no_of_iterations):
        new_centroids = []
        for cid in range(k):
            # updating centroids by taking mean of cluster it belongs to
            clustered_points = []
            for i in range(len(points_cid)):
                if points_cid[i] == cid:
                    clustered_points.append(x[i])
            temp_cent = np.array(clustered_points).mean(axis=0)
            new_centroids.append([temp_cent[0], temp_cent[1]])

        # updated centroids
        centroids = np.unique(np.array(new_centroids), axis=0)
        distances = cdist(x, centroids, 'euclidean')
        points_cid = np.array([np.argmin(distance) for distance in distances])
        # print()

        # plt.scatter(x[:, 0], x[:, 1], c=points_cid)
        # plt.scatter(centroids[:, 0], centroids[:, 1], c='r', s=42)
        # time.sleep(1)
        # plt.show()

        display_results(x, centroids, real_labels, points_cid)

    return centroids, points_cid


def eval_labels(real_labels, computed_labels):
    label_count = len(real_labels)
    matched_labels = 0
    for i in range(label_count):
        if real_labels[i] == computed_labels[i]:
            matched_labels = matched_labels + 1

    accuracy = matched_labels / label_count

    precisions = {}
    rappel_data = {}
    score = {}

    for label in range(4):
        correct_count = 0
        precision_count = 0
        rappel_count = 0

        for realLabel, computedLabel in zip(real_labels, computed_labels):
            if realLabel == computedLabel == label:
                correct_count += 1
            if computedLabel == label:
                precision_count += 1
            if realLabel == label:
                rappel_count += 1

        precision = correct_count / precision_count
        rappel = correct_count / rappel_count

        precisions[label] = precision
        rappel_data[label] = rappel
        if precision == 0 and rappel == 0:
            score[label] = 0
        else:
            score[label] = 2 * precision * rappel / (precision + rappel)

    return {"accuracy": accuracy, "precision": precisions, "rappel": rappel_data, "score": score}


def display_results(x, computed_labels, real_labels, points_cid):
    # u_computed_labels = np.unique(computed_labels, axis=0)
    # distances = cdist(x, u_computed_labels, 'euclidean')
    # points_cid_2 = np.array([np.argmin(distance) for distance in distances])

    plt.scatter(df[:, 0], df[:, 1], c=points_cid)
    plt.scatter(computed_labels[:, 0], computed_labels[:, 1], c='r', s=42)
    plt.show()
    time.sleep(0.5)

    for k, v in eval_labels(real_labels, points_cid).items():
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

    # load data
    data, real_labels_1 = read_points()

    # Use skikit learns PCA s
    pca = PCA(2)

    # transform the data aka fit the model with X and apply the dimensionality reduction on X
    df = pca.fit_transform(data)

    # data = np.array(data)
    # plt.scatter(data[:, 0], data[:, 1])
    # plt.show()

    computed_labels_1, points_cid_1 = k_means(df, 4, 10, real_labels_1)
    u_computed_labels = np.unique(computed_labels_1, axis=0)

    display_results(df, u_computed_labels, real_labels_1, points_cid_1)
