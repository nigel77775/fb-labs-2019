mas = ["а","б","в","г","д","е","ж","з","и","й","к","л","м","н","о","п","р","с","т","у","ф","х","ц","ч","ш","щ","ы","ь","э","ю","я"," "]

$i = 0

=begin
while $i < mas.length do
  puts(mas[$i])
  $i += 1
end
=end

text = File.open('text.txt', 'r'){ |file| file.read }

$i = 0
q_mas = []

while $i < mas.length do
  new_mas = text.scan(mas[$i])
  q_mas[$i] = new_mas.length
  $i += 1
end

$i = 0
while $i < mas.length do
  print mas[$i]
  print ' '
  print q_mas[$i]
  puts ''
  $i += 1
end
