from CodeGen import *
import argparse
import os

functions = [
    "Create",
    "Destroy",
    "Evaluate",
    "Equals",
    "Clone",
    "Derivative",
    "Simplified",
    "Latex",
    "Stringify",
    "Text",
    "ExplicitText"
]


def get_sources_names(source):
    sources_names = []
    for path, subdirs, files in os.walk(source):
        for name in files:
            new_name = name[:-2]
            sources_names.append(new_name)

    return sources_names


def generate_tests(source, output):
    sources_names = get_sources_names(source)
    for source in sources_names:
        test_name = source + 'NodeTest'
        test_cpp_file_name = test_name + '.cpp'

        if os.path.exists(os.path.join(output, test_cpp_file_name)):
            print('File already exists: ' + test_cpp_file_name)
            continue

        test_cpp_file_full_name = output + '/' + test_cpp_file_name
        test_cpp_file = CppFile(test_cpp_file_full_name)

        test_cpp_file('#include "cas/node/{}.h"'.format(source))
        test_cpp_file('#include "gtest/gtest.h"')

        for function in functions:
            test_cpp_file('\nTEST({}, {}{}Test) {}'.format(test_name, source, function, '{'))
            test_cpp_file('}')

        test_cpp_file.close()

        print(test_cpp_file_full_name)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('source', help='Path to the folder to test')
    parser.add_argument('output', help='Path to the folder to add tests')
    args = parser.parse_args()
    generate_tests(args.source, args.output)
