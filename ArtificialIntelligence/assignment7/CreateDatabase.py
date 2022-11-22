import math

import torch

from Constants import *


def ComputeFunctionValue(x):
    return torch.sin(x[:, 0] + (x[:, 1] / math.pi))


def CreateDatabase():
    # generating a random distribution (1000 of 2)
    generatedDistribution = (DOMAIN_MIN - DOMAIN_MAX) * torch.rand(INPUT_SIZE, NUMBER_OF_DIMENSIONS) + DOMAIN_MAX
    # computing the output for each data set
    functionOutputs = ComputeFunctionValue(generatedDistribution)

    # associating the output to each data set
    return torch.column_stack((generatedDistribution, functionOutputs))


def GenerateDatabaseFile():
    # generating the database file
    torch.save(CreateDatabase(), DATA_PATH)
