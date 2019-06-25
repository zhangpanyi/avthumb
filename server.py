#!/usr/bin/python

import os
import shutil
import argparse

def run():
    cmd = 'cd {0}{1}bin && ./server'.format(root(), os.path.sep)
    os.system(cmd)

def build():
    path = '{0}{1}build'.format(root(), os.path.sep)
    if not os.path.exists(path):
        os.makedirs(path)
    cmd = 'cd {0} && cmake .. && make -j4'.format(path)
    os.system(cmd)

def protoc():
    filenames = []
    path = '{0}{1}proto'.format(root(), os.path.sep)
    for _, _, files in os.walk(path):
        for file in files:
            _, ext = os.path.splitext(file)
            if ext.lower() == '.proto':
                filenames.append(file)
        break
    cmds = ['cd {0}'.format(root())]
    for file in filenames:
        cmds.append('protoc -I=proto --cpp_out=protocol {0}'.format(file))
        cmds.append('protoc -I=proto --grpc_out=protocol --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin {0}'.format(file))
    os.system(' && '.join(cmds))

def root():
    return os.path.split(__file__)[0]

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('command', choices=['run', 'build', 'protoc'])
    args = parser.parse_args()
    if args.command == 'run':
        run()
    elif args.command == 'build':
        build()
    else:
        protoc()

if __name__ == "__main__":
    main()