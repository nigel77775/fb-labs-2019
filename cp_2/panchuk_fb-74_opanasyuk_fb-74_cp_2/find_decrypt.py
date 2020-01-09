alphabet = 'абвгдежзийклмнопрстуфхцчшщъыьэюя'

al = []

for i in alphabet:
    al.append(i)

text = 'рустщвухюпуопъцйтцсцубужржнгвшофгчюппюсфцуткрвчшчахгтлтаоуяфчзсрнрлрьбкщдлнлсцтлшлбрцеюодрмьмхбтрщзбтжтйникатъчшьактлгйжфюцаыщкоэяижзбдацяыхпвдфэхпвьтжэечъбнцуэчшзтчоъудююхжбнъацвюрйылуэгшщущоыьфюязъбрцчпеэстакечыахчлыяцмщейэтыишхаеяэяшютютцбмнтанмзюепъъвуенязучткъшобыкьядсныьавмшдеыщзщчхкуая'


def find(num, text):
    crypt_text = ''
    for i in text:
        a = al.index(i)
        a = a + num
        a = a % len(al)
        crypt_text = crypt_text + al[a]

    print('Crypted text with ' + str(num) + ' key: ' + crypt_text)
    print('----------')

for i in range(len(alphabet)):
    find(i, text)
