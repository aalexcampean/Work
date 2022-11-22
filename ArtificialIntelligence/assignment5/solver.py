# -*- coding: utf-8 -*-
"""
In this file your task is to write the solver function!

"""


def solver(t, w):
    """
    Parameters
    ----------
    t : TYPE: float
        DESCRIPTION: the angle theta
    w : TYPE: float
        DESCRIPTION: the angular speed omega

    Returns
    -------
    F : TYPE: float
        DESCRIPTION: the force that must be applied to the cart
    or
    
    None :if we have a division by zero

    """
    # [x, y, z] :
    # x - lower limit
    # y - upper limit
    # z - peak value

    theta = {"NVB": [-50, -25, -40], "NB": [-40, -10, -25], "N": [-20, 0, -10], "ZO": [-5, 5, 0], "P": [0, 20, 10],
             "PB": [10, 40, 25], "PVB": [25, 50, 40]}

    omega = {"NB": [-10, -3, -8], "N": [-6, 0, -3], "ZO": [-1, 1, 0], "P": [0, 6, 3], "PB": [3, 10, 8]}

    force = {'NVB+NB': 'NVVB', 'NVB+N': 'NVVB', 'NVB+ZO': 'NVB', 'NVB+P': 'NB', 'NVB+PB': 'N',
             'NB+NB': 'NVVB', 'NB+N': 'NVB', 'NB+ZO': 'NB', 'NB+P': 'N', 'NB+PB': 'Z', 'N+NB': 'NVB', 'N+N': 'NB',
             'N+ZO': 'N',
             'N+P': 'Z', 'N+PB': 'P', 'ZO+NB': 'NB', 'ZO+N': 'N', 'ZO+ZO': 'Z', 'ZO+P': 'P', 'ZO+PB': 'PB',
             'P+NB': 'N', 'P+N': 'Z', 'P+ZO': 'P', 'P+P': 'PB', 'P+PB': 'PVB', 'PB+NB': 'Z', 'PB+N': 'P', 'PB+ZO': 'PB',
             'PB+P': 'PVB', 'PB+PB': 'PVVB', 'PVB+NB': 'P', 'PVB+N': 'PB', 'PVB+ZO': 'PVB', 'PVB+P': 'PVVB',
             'PVB+PB': 'PVVB'}

    weights = {'NVVB': -32, 'NVB': -24, 'NB': -16, 'N': -8, 'Z': 0, 'P': 8, 'PB': 16, 'PVB': 24, 'PVVB': 32}

    fuzzyTheta = {}
    fuzzyOmega = {}
    forces = {}

    # fuziffying the crisp input into fuzzy variables
    # computing the membership degrees for θ and ω
    for key in theta:
        fuzzyTheta[key] = 0
        if theta[key][0] <= t <= theta[key][1]:
            fuzzyTheta[key] = max(0, min((t - theta[key][0]) / (theta[key][2] - theta[key][0]), 1,
                                     (theta[key][1] - t) / (theta[key][1] - theta[key][2])))

    for key in omega:
        fuzzyOmega[key] = 0
        if omega[key][0] <= w <= omega[key][1]:
            fuzzyOmega[key] = max(0, min((w - omega[key][0]) / (omega[key][2] - omega[key][0]), 1,
                                     (omega[key][1] - w) / (omega[key][1] - omega[key][2])))

    # computing the membership degree of F according to Table 1 to each set
    for key in theta:
        for key2 in omega:
            newValue = min(fuzzyTheta[key], fuzzyOmega[key2])
            newKey = key + '+' + key2
            if force[newKey] in forces:
                forces[force[newKey]] = max(forces[force[newKey]], newValue)
            else:
                forces[force[newKey]] = newValue

    # defuziffying the result into crisp output
    # using a weighted average of the membership degrees and the b values of the sets
    sum = 0
    product = 0
    for key in forces:
        sum += forces[key]
        product += (forces[key] * weights[key])
    try:
        f = product / sum
    except:
        f = None

    return f
