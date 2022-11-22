import math
import torch
from Constants import *
import MyModel


# loading the Trained model
ann = MyModel.Net(NUMBER_OF_DIMENSIONS, NUMBER_OF_HIDDEN_LAYERS, OUTPUT_SIZE)
ann.load_state_dict(torch.load(TRAINED_MODEL_PATH))
ann.eval()

# visualising the parameters for the ann (aka weights and biases)
print("ANN parameters:")
for name, param in ann.named_parameters():
    if param.requires_grad:
        print(name, param.data)

print("^ ^ ^ ANN parameters ^ ^ ^")

print("\nf(x1, x2) = sin(x1 + x2/pi)")
x1 = float(input("x1 = "))
x2 = float(input("x2 = "))
x = torch.tensor([x1, x2])
print("Predicted: ", ann(x).tolist()[0])
print("Real: ", math.sin(x1 + (x2 / math.pi)))
