import AppKit

// ----------------------------------------------------- SOURCE ----------------------------------------------------- //

let alphabet_enum : [ Int : String] = [0:" ", 1:"а", 2:"б", 3:"в", 4:"г", 5:"д", 6:"е", 7:"ж", 8:"з", 9:"и", 10:"й", 11:"к", 12:"л", 13:"м", 14:"н", 15:"о", 16:"п", 17:"р", 18:"с", 19:"т", 20:"у", 21:"ф", 22:"х", 23:"ц", 24:"ч", 25:"ш", 26:"щ", 27:"ы", 28:"ь", 29:"э", 30:"ю", 31:"я"]

let alphabet = [" ", "а", "б", "в", "г", "д", "е", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ы", "ь", "э", "ю", "я"]

var invalphabet_dict : [ String : Double] = [" ":0, "а":0, "б":0, "в":0, "г":0, "д":0, "е":0, "ж":0, "з":0, "и":0, "й":0, "к":0, "л":0, "м":0, "н":0, "о":0, "п":0, "р":0, "с":0, "т":0, "у":0, "ф":0, "х":0, "ц":0, "ч":0, "ш":0, "щ":0, "ы":0, "ь":0, "э":0, "ю":0, "я":0]

let invalphabet_enum : [ String : Int] = [" ":0, "а":1, "б":2, "в":3, "г":4, "д":5, "е":6, "ж":7, "з":8, "и":9, "й":10, "к":11, "л":12, "м":13, "н":14, "о":15, "п":16, "р":17, "с":18, "т":19, "у":20, "ф":21, "х":22, "ц":23, "ч":24, "ш":25, "щ":26, "ы":27, "ь":28, "э":29, "ю":30, "я":31]

// --------------------------------------------------- TEXT EDIT --------------------------------------------------- //
let methodStart = Date()
let path = "/Users/_ria_go_/Desktop/универ/crypto1/crypto1/crypto1.txt"
var text = try String(contentsOfFile: path, encoding: String.Encoding.utf8)
text = text.lowercased()
text = text.replacingOccurrences(of: "ё", with: "е")
text = text.replacingOccurrences(of: "ъ", with: "ь")
text = text.replacingOccurrences(of: "\n", with: " ")
text = text.filter("абвгдежзийклмнопрстуфхцчшщыьэюя ".contains)
text = text.replacingOccurrences(of: "\\s+", with: " ", options: .regularExpression, range: nil)

// ------------------------------------------- WORDS & BIGRAMS COUNT --------------------------------------------- //

var matrix = [[Double]](repeating: [Double](repeating: 0, count: alphabet.count), count: alphabet.count)

var bigram = ""
for character in text {
    invalphabet_dict[String(character)] = invalphabet_dict[String(character)]! + 1
    bigram = bigram + String(character)
    if bigram.count == 2 {
        let i = invalphabet_enum[String(bigram.first!)]
        let j = invalphabet_enum[String(bigram.last!)]
        matrix[i!][j!]+=1
        bigram.remove(at: bigram.startIndex)
    }
}

var letters_sum = (invalphabet_dict.values).reduce(0, +)
var letter : String = ""
for i in 0...alphabet.count-1 {
    letter = alphabet[i]
    invalphabet_dict[letter] = invalphabet_dict[letter]!/letters_sum
}
let freqValDec = invalphabet_dict.sorted(by: { $0.value > $1.value })
for item in freqValDec {
    print("\(item.key):\(item.value)")
}
print("\n")

var bigram_sum : Int = 0
for var i : Int in 0...31{
    for var j : Int in 0...31{
        bigram_sum = bigram_sum + Int(matrix[i][j])
        j += 1
    }
    i+=1
}
for var i : Int in 0...31{
    for var j : Int in 0...31{
        matrix[i][j] = matrix[i][j]/Double(bigram_sum)
        j += 1
    }
    i+=1
}

print("      ", terminator: " ")
for var k : Int in 1...31{
    print("\(alphabet[k])", terminator: "        ")
    k+=1
}
print("\n")

for var i : Int in 1...31{
    print("\(alphabet[i])", terminator: " ")
    for var j : Int in 1...31{
        print(String(format: "%.6f", matrix[i][j]), terminator: " ")
        j+=1
    }
    i+=1
    print("\n")
}

// ------------------------------------------------- ENTROPY ------------------------------------------------- //

func log2(x: Double) -> Double{
    return log(x)/log(2.0)
}

// ------- H1 ------- //

var h_letter = [Double]()
for character in alphabet {
    if invalphabet_dict[character] != 0{
        h_letter.append(Double(invalphabet_dict[character]!)*log2(Double(1/invalphabet_dict[character]!)))
    }
}
var h1 = (h_letter.reduce(0, +))//Double(h_letter.count)
print("H1 = \(h1)")

// ------- H2 ------- //

var h_bigram = [Double]()
for var i : Int in 0...31{
    for var j : Int in 0...31{
        if matrix[i][j] != 0{
            h_bigram.append(Double((matrix[i][j]))*log2(Double(1/(matrix[i][j]))))
        }
        j += 1
    }
    i+=1
}
var h2 = h_bigram.reduce(0, +)/2
print("H2 = \(h2)")
// ----------------------------------------------------------------------------------------------------------- //

let methodFinish = Date()
let executionTime = methodFinish.timeIntervalSince(methodStart)
print("Execution time: \(executionTime)")
