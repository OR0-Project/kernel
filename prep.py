# build preparation tool

import subprocess
import datetime
import os



WORK_DIR = os.path.abspath(os.path.dirname(os.path.abspath(__file__)))


def set_build_info() -> bool:
    git_command = "git log -n 1 --pretty=format:%h"
    result = subprocess.run(git_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    
    if result.returncode != 0: return False
    commit_hash = result.stdout.strip()
    dt = datetime.datetime.now()
    time_stamp = dt.strftime('%Y-%m-%d %H:%M:%S')
    
    print(f"commit hash: {commit_hash}\nwriting build.h...")
    with open(WORK_DIR + "/inc/build.h", 'w') as file:
        file.write(
            "#ifndef __BUILD_H\n"                           +\
            "#define __BUILD_H\n"                           +\
            f"#define B_GIT_HASH \"{commit_hash}\"\n"       +\
            f"#define B_COMPTIME_START \"{time_stamp}\"\n"  +\
            "#endif"
        )
        file.close()
        return True


def init_directories() -> bool:
    print(f"initializing directories...")
    directories = [
        "obj",
        "obj/util",
        "obj/kern",
        "obj/dev",
        "obj/arch",
        "obj/arch/x86",
        "obj/io",
        "build",
        "cdrom/sys"
    ]
    try:
        for dir in directories:
            if not os.path.exists(dir):
                os.mkdir(dir)
    except Exception as e:
        return False
    return True



if __name__ == "__main__":
    if not set_build_info():    print("failed to set build info")
    if not init_directories():  print("failed to init directories")
    
