# encoding: UTF-8

file1 = File.open("./list_config")
countFirstName = File.open("./list_config").lines.count

tmpRead = ""
file1.each {|line|
  tmpRead << line
}
fnames = tmpRead.split("\n")

fileAnsver = File.open("./out", "w")

for num in (1 .. countFirstName-1)
	#p "<field name=#{fnames[num]} type=\"text_general\" indexed=\"true\" stored=\"true\"/>"  
	fileAnsver.write("<field name=\"#{fnames[num]}\" type=\"text_general\" indexed=\"true\" stored=\"true\"/>")
	fileAnsver.write("\r")
end
fileAnsver.write("\r")
for num in (1 .. countFirstName-1)
	fileAnsver.write("<copyField source=\"#{fnames[num]}\" dest=\"text\"/>") 
	fileAnsver.write("\r")
end