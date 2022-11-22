import torch
import torch.nn.functional as functional


class Net(torch.nn.Module):
    # the class for the network

    def __init__(self, n_feature, n_hidden, n_output):
        # we have two layers: a hidden one and an output one
        super(Net, self).__init__()
        # specify the number of hidden layers
        self.hidden = torch.nn.Linear(n_feature, n_hidden)
        # specify the number output
        self.output = torch.nn.Linear(n_hidden, n_output)

    def forward(self, x):
        # a function that implements the forward propagation of the signal
        # observe the ReLU function applied on the output of the hidden layer
        x = functional.relu(self.hidden(x))
        # x = self.hidden(x)
        x = self.output(x)

        return x
