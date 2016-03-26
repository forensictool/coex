import markdown2
import os
import glob

def compose_anycase(string):
	result = ""
	for letter in string:
		result += "[%s%s]" % (letter.lower(), letter.upper())
	return result
		
path = os.path.join("sources\\plugins\\*\\")
readmes = glob.glob(os.path.join(path, compose_anycase("readme.md")))

for readme in readmes:
	outpath = "%s%s%s" % (os.path.dirname(readme), os.sep, "Readme.html")
	with open(outpath, 'w') as outfile, open(readme, 'r') as infile:
		file = infile.read()
		html = markdown2.markdown(file).encode('utf-8')
		outfile.write(html)