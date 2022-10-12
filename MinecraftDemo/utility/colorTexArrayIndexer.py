import argparse
import os
import re

def index_file(opt):
    if (not os.path.exists(opt.input_file)):
        print(opt.input_file + ' does not exist')
        return
    f = open(opt.input_file, "r")
    try:
        lines = f.readlines()
    finally:
        f.close()
    arrayIndex = 0
    regex = opt.array_name + '\[[0-9]*\]'
    f = open(opt.input_file, "w")
    try:
        for line in lines:
            occourrence = re.search(regex, line)
            if occourrence:
                subText = opt.array_name + '[' + str(arrayIndex) + ']'
                arrayIndex = arrayIndex + 1
                newLine = re.sub(regex, subText, line, 1)
                f.write(newLine)
            else:
                f.write(line)
        print('Substituted ' + str(arrayIndex) + ' occourrences')
    finally:
        f.close()

def get_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument('--array_name', default='', help='Array to index name', required=True)
    parser.add_argument('--input_file', help='Input file to index', default='', required=True)

    return parser

if __name__ == '__main__':
    parser = get_arguments()
    opt = parser.parse_args()
    index_file(opt)

