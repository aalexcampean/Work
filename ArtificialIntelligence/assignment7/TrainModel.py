import torch
import torch.nn.functional as F
import matplotlib.pyplot as plt
import numpy as np

import MyModel
from Constants import *
from CreateDatabase import GenerateDatabaseFile

GenerateDatabaseFile()

data = torch.load(DATA_PATH)
x = data[:, 0:2]
y = data[:, 2:3]

# we set up the lossFunction as the mean square error
lossFunction = torch.nn.MSELoss()

# we create the ANN
# 2 dimension because we have 2 features
createdANN = MyModel.Net(n_feature=NUMBER_OF_DIMENSIONS, n_hidden=NUMBER_OF_HIDDEN_LAYERS, n_output=OUTPUT_SIZE)

# print(ann)

# we use an optimizer that implements stochastic gradient descent (backward)
# lr = learning rate (the bigger the step the more likely it is to lose details)
# it needs to be small but not to small such that you can get stuck in a local minimum
batchOptimizer = torch.optim.SGD(createdANN.parameters(), lr=0.004213)

# Backward Propagation = depending on the loss function (how far from the actual result we are),
# we ha back and recompute the weights and biases such that the future result will be closer to the truth

# we memorize the losses for some graphics
listOfLosses = []
listOfAverageLosses = []

# we set up the environment for training in batches  
batchSize = 13
numberOfBatches = int(INPUT_SIZE / batchSize)
print("N_Batches: {}", numberOfBatches)

for epoch in range(2000):

    for batch in range(numberOfBatches):
        # we prepare the current batch  -- please observe the slicing for tensors

        batchOfValues, batchOfActualOutputs = x[batch * batchSize:(batch + 1) * batchSize, ], \
                                              y[batch * batchSize:(batch + 1) * batchSize, ]

        # we compute the output for this batch
        prediction = createdANN(batchOfValues)

        # we compute the loss for this batch
        loss = lossFunction(prediction, batchOfActualOutputs)

        # we save it for graphics
        listOfLosses.append(loss)

        # we set up the gradients for the weights to zero (important in pytorch)
        batchOptimizer.zero_grad()

        # we compute automatically the variation for each weight (and bias) of the network
        # compute the derivatives with respect to the weights
        loss.backward()

        # we compute the new values for the weights
        # actually modify the weights
        batchOptimizer.step()

    # printing the loss for all the dataset for each 100th epoch
    if epoch % 100 == 99:
        y_pred = createdANN(x)
        loss = lossFunction(y_pred, y)
        print('\repoch: {}\tLoss =  {:.5f}'.format(epoch, loss))

# saving the model to file
torch.save(createdANN.state_dict(), TRAINED_MODEL_PATH)

# plt.plot(loss_list, 'r')

# visualise the parameters for the ann (aka weights and biases)
# for name, param in ann.named_parameters():
#     if param.requires_grad:
#         print(name, param.data)
