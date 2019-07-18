from fractions import Fraction
import itertools



def make_splits(number):
    """
    Splits a number into possible concatenations of digits.
    Example:
        number = '123'
        return: [['123'], ['1', '23'], ['12', '3'], ['1', '2', '3']]
    """

    n_pos = len(number) - 1

    for x in itertools.product((True, False), repeat=n_pos):
        res = [number[0]]
        for i in range(n_pos):
            if x[i]:
                res[-1] += number[i+1]
            else:
                res.append(number[i+1])
        yield res


def make_operations(split):
    """
    Assignes different operations between parts of the split number
    Example:
        split = ['1', '2', '3']
        return: [('+', '+'), ('+', '-'), ... , ('/', '/')]
        which means ['1+2+3', '1+2-3', ..., '1/2/3']
    """

    n_pos = len(split) - 1

    for x in itertools.product(('+', '-', '*', '/'), repeat=n_pos):
        yield x


def make_order(operation):
    """
    Defines various order of executing operations.
    Example:
        operation = ('+', '*', '-')
        return: (0, 1, 2),   (0, 2, 1),   (1, 0, 2),   (1, 2, 0),   (2, 0, 1),   (2, 1, 0)
        meaning ((1+2)*3)-4, (1+2)*(3-4), (1+(2*3))-4, (1+2)*(3-4), 1+((2*3)-4), 1+(2*(3-4))
    """
    n_op = len(operation)

    for x in itertools.permutations(range(n_op), n_op):
        yield x


def make_expression(split, operations, order, nofrac=False):
    """
    Makes an expression that can later be executed by python.
    """

    
    split = list(split) if nofrac else ['Fraction(%s)'%x for x in split]
    operations = list(operations)
    order = list(order)
    for i in range(len(order)):
        j = order.index(i)
        split[j] = '(%s %s %s)'%(split[j], operations[j], split[j+1])

        split.pop(j+1)
        operations.pop(j)
        order.pop(j)

    return split[-1]





number = '717528'
for split in make_splits(number):
    for operations in make_operations(split):
        for order in make_order(operations):
            expression = make_expression(split, operations, order)
            try:
                res = eval(expression)
                if res == 100:
                    print("%s = "%make_expression(split, operations, order, nofrac=True), res)
            except:
                continue            


