from codegen import *
import argparse
import os
import glob


def get_sources_names(source):
    sources_names = []
    for path, subdirs, files in os.walk(source):
        for name in files:
            new_name = name[:-2]
            sources_names.append(new_name)

    return sources_names


def get_test_names(sources_names):
    test_names = []
    for name in sources_names:
        test_names.append("test_" + name)

    print(test_names)
    return test_names


def generate_tests(source, output):
    get_sources_names(source)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('source', help='Path to the folder to test')
    parser.add_argument('output', help='Path to the folder to add tests')
    args = parser.parse_args()
    generate_tests(args.source, args.output)
