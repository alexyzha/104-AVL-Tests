# auto run all tests in in/out
import subprocess

for x in range(1,10):
    print(f'Running test {x}...')
    try:
        test = subprocess.run(["../floorplan",f'in/in{x}.txt',f'out/out{x}.txt'],
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE,
                               text=True)
        if test.returncode:
            print(test.stderr)
        else:
            print(test.stdout)
    except FileNotFoundError:
        print("../floorplan not found")
        break
    try:
        validate = subprocess.run(["./checker",f'in/in{x}.txt',f'out/out{x}.txt',f'{x}'],
                                   stdout=subprocess.PIPE,
                                   stderr=subprocess.PIPE,
                                   text=True)
        if validate.returncode:
            print(validate.stderr)
        else:
            print(validate.stdout)
    except FileNotFoundError:
        print(f'./checker not found')
        break


for x in range(10,13):
    print(f'Running test {x}...')
    try:
        test = subprocess.run(["../floorplan",f'in/in{x}.txt',f'out/out{x}.txt'],
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE,
                               text=True)
        if test.returncode:
            print(test.stderr)
        else:
            print(test.stdout)
    except FileNotFoundError:
        print("../floorplan not found")
        break
    with open(f'out/out{x}.txt','r') as file:
        for ln in file:
            if ln != "No solution found.":
                print(f'\033[31mFAILED TEST: {x}\033[0m\n')
            else:
                print(f'\033[32mPASSED TEST: {x}\033[0m\n')
