
symbols = input("Input symbols (space separated): ").split()

num_states = int(input("Enter number of states: "))

start_state = int(input("Initial state: "))

num_accept = int(input("Number of accepting states: "))
accept_states = set(map(int, input("Accepting states: ").split()))

transitions = {}
print("Enter transitions:")
for _ in range(num_states * len(symbols)):
    frm, sym, to = input().split()
    transitions[(int(frm), sym)] = int(to)

string = input("Input string: ")

current_state = start_state
valid = True

for ch in string:
    if (current_state, ch) in transitions:
        current_state = transitions[(current_state, ch)]
    else:
        valid = False
        break

if valid and current_state in accept_states:
    print("Valid String")
else:
    print("Invalid String")