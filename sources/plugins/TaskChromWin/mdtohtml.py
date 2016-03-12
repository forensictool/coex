import markdown2

with open("Readme.html", 'w') as outfile, open("Readme.md", 'r') as infile:
	file = infile.read()
	html = markdown2.markdown(file).encode('utf-8')
	print html
	outfile.write(html)