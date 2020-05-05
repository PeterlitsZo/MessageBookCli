from pathlib import Path

c_header = '''\
#ifndef PETERLITS_HELP_INFO_H__
#define PETERLITS_HELP_INFO_H__

namespace HELP_DOC {{

{}

}}

#endif // for PETERLITS_HELP_INFO_H__
'''

def escape(string: str) -> str:
    result = ''
    for char in string:
        if   char == '\\':
            result += '\\\\'
        elif char == '"':
            result += '\\"'
        elif char == "'":
            result += "\\'"
        else:
            result += char
    return result

def make_cpp_str(string: str) -> str:
    result = ''
    for i in string.split('\n'):
        result += '   "' + escape(i) + r'\n"' + '\n'
    return result

def list_extern(all_file_name: list) -> str:
    result = ''
    for name in all_file_name:
        result += "extern const char* " + name + ";\n"
    return result

# ---[ main ]------------------------------------------------------------------

all_file_name = []

out_folder = Path(__file__).parent / 'inside'
in_folder  = Path(__file__).parent / '..' / 'src' / 'help'

for file_ in out_folder.iterdir():
    with    open(file_) as out_file, \
            open(in_folder / (file_.stem + '.cpp'), 'w') as in_file:
        print (f"writing to file {in_file.name}...")
        all_file_name.append(file_.stem)
        in_file.write ("namespace HELP_DOC {\n")
        in_file.write (f"const char* {file_.stem} =\n");
        in_file.write (make_cpp_str(out_file.read()))
        in_file.write (";");
        in_file.write ("}");

with open(in_folder / "help.h", 'w') as header:
    header.write(c_header.format(list_extern(all_file_name)))
