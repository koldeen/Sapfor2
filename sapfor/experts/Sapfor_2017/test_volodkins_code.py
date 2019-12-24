import argparse
from typing import List
import os
import time
import difflib


class bcolors:
    HEADER = '\033[95m'
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'


class TestFailed(Exception):
    ...


class Checker:
    def __init__(self, input_dir: str, output_dir: str):
        self.input_dir = input_dir
        self.output_dir = output_dir

    def preprocess_lines(self, lines: List[str]) -> List[str]:
        result = []
        for line in lines:
            if not line or line.isspace():  # filter out empty lines
                continue
            if line.startswith('! ***'):  # remove sapfor header
                continue
            
            result.append(line.strip())
        
        return result

    def load_file(self, file_path: str) -> List[str]:
        with open(file_path, 'r') as f:
            lines = f.readlines()
            return self.preprocess_lines(lines)

    def check(self, test_name: str) -> bool:
        expected = self.load_file(f'{self.input_dir}{test_name}.out')
        output = self.load_file(f'{self.output_dir}{test_name}.out')

        diff = list(difflib.unified_diff(expected, output, fromfile=f'{test_name}.in', tofile='{test_name}.out', lineterm=''))

        if not diff:
            return True

        raise TestFailed('\n'.join(diff))


class Runner:
    def __init__(self, sapfor_path: str, input_dir: str, output_dir: str):
        self.sapfor_path = sapfor_path
        self.input_dir = input_dir
        self.output_dir = output_dir

    def run(self, test_name: str):
        os.system(f'{self.sapfor_path} -parse {self.input_dir}{test_name}.in >/dev/null 2>&1')
        os.system(f'{self.sapfor_path} -t 13 -var 4 >/dev/null 2>&1')

        os.system(f'mv {self.input_dir}{test_name}_v4.for {self.output_dir}{test_name}.out')
        os.remove(f'{self.input_dir}/{test_name}.dep')


class Tester:
    def __init__(self):
        args = self.parse_args()

        self.test_dir = args.test_dir
        self.sapfor_path = args.sapfor_path
        self.keep_files = args.keep_files
        self.no_diff = args.no_diff

        self.output_dir = self.test_dir + 'outputs_' + time.strftime('%l_%M_%s') + "/"
        os.mkdir(self.output_dir)
        if self.keep_files:
            print(f'outputs will be saved to [{self.output_dir}]')

        self.test_names = self.load_test_names(self.test_dir)
        print(f'tests to run {self.test_names}')

    def parse_args(self):
        parser = argparse.ArgumentParser()

        parser.add_argument("--test_dir", help="path to directory with test files", required=True)
        parser.add_argument("--sapfor_path", help="path to sapfor executable", required=True)
        parser.add_argument("--keep_files", help="specify to keep output", type=bool, default=False, required=False)
        parser.add_argument("--no_diff", help="don't print diff for failed tests", type=bool, default=False, required=False)

        return parser.parse_args()

    def run_tests(self):
        checker = Checker(self.test_dir, self.output_dir)
        runner = Runner(self.sapfor_path, self.test_dir, self.output_dir)

        for t_name in self.test_names:
            print(bcolors.HEADER + f'running test [{t_name}]...' + bcolors.ENDC)
            runner.run(t_name)

            try:
                checker.check(t_name)
            except TestFailed as e:
                if self.no_diff:
                    print(bcolors.FAIL + "failed" + bcolors.ENDC)
                else:
                    print(bcolors.FAIL + "failed with error: " + bcolors.ENDC)
                    print(e)
                continue

            print(bcolors.OKGREEN + "ok" + bcolors.ENDC)
        
        if not self.keep_files:
            self.clean_dir()


    def load_test_names(self, test_dir: str) -> List[str]:
        f_names = os.listdir(test_dir)
        filtered = [f_name[:-3] for f_name in f_names if f_name.endswith('.in')]
        return filtered

    def clean_dir(self):
        print('removing')
        os.system(f'rm -rf {self.output_dir}')


if __name__ == "__main__":
    tester = Tester()
    tester.run_tests()


