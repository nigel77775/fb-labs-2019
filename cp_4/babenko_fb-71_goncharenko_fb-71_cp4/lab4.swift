import AppKit
import Darwin.C.math

// ------------------------------------------------ SOURCE -------------------------------------------------- //
var bigram : [String : Int] = ["00":0, "01":0, "10":0, "11":0]

var threegram : [String : Int] = ["000":0, "001":0, "010":0, "011":0, "100":0, "101":0, "110":0, "111":0]

var fourgram : [String : Int] = ["0000":0, "0001":0, "0010":0, "0011":0, "0100":0, "0101":0, "0110":0, "0111":0, "1000":0, "1001":0, "1010":0, "1011":0, "1100":0, "1101":0, "1110":0, "1111":0]

var fivegram : [String : Int] = ["00000":0, "00001":0, "00010":0, "00011":0, "00100":0, "00101":0, "00110":0, "00111":0, "01000":0, "01001":0, "01010":0, "01011":0, "01100":0, "01101":0, "01110":0, "01111":0, "10000":0, "10001":0, "10010":0,  "10011":0, "10100":0, "10101":0, "10110":0, "10111":0, "11000":0, "11001":0, "11010":0, "11011":0, "11100":0, "11101":0, "11110":0, "11111":0]

let polinom1 : [Int] = [1,1,1,1,0,1,0,1,0,1,0,0,0,0,1,1,0,1,0,0] // first polinom
let impulse1 : [Int] = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1] //impulse for first polinom
let polinom2 : [Int] = [1,1,1,0,1,0,0,0,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0] // second polinom
let impulse2 : [Int] = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1] //impulse for second polinom
var period = ""

// ----------------------------------------------- FUNCTIONS ------------------------------------------------ //
func period_count(){
    var temp = [Int]()
    for i in 0...(impulse2.count)-1{
        let a : Int = impulse2[i]
        temp.append(a)
    }
    repeat {
        var sum_array = [Int]()
        for i in 0...(impulse2.count)-1{
            let a = polinom2[i] * temp[i]
            sum_array.append(a)
        }
        let sum : Int = (sum_array.reduce(0, +))%2
        temp.append(sum)
        period = period + String(temp[0])
        temp.removeFirst()
    } while(temp != impulse2)
    print("Period = \(period.count)")
}

func ngramm_count (dict: [String:Int], n: Int) -> [String:Int] {
    var ngram = dict
    var temp_ngram = ""
    for character in period {
        temp_ngram = temp_ngram + String(character)
        if temp_ngram.count == n {
            ngram[temp_ngram]!+=1
            temp_ngram.removeAll()
        }}
    return ngram
}

func autocor (p: String, n: Int) -> Int{
    var period_int = period.compactMap{$0.wholeNumberValue}
    for i in 1...n{
        period_int.append(period_int[i-1])
    }
    var sum_array = [Int]()
    for i in 0...(period.count)-1 {
        let a = (period_int[i] + period_int[i+n])%2
        sum_array.append(a)
    }
    let sum : Int = sum_array.reduce(0, +)
    return sum
}

// ----------------------------------------------- MAIN ------------------------------------------------ //
let methodStart = Date()
period_count()
print("\n")
print("2-граммы: ")
bigram = ngramm_count(dict: bigram, n: 2)
for item in bigram {
    print("\(item.key):\(item.value)")
}
print("\n")
print("3-граммы: ")
threegram = ngramm_count(dict: threegram, n: 3)
for item in threegram {
    print("\(item.key):\(item.value)")
}
print("\n")
print("4-граммы: ")
fourgram = ngramm_count(dict: fourgram, n: 4)
for item in fourgram {
    print("\(item.key):\(item.value)")
}
print("\n")
print("5-граммы: ")
fivegram = ngramm_count(dict: fivegram, n: 5)
for item in fivegram {
    print("\(item.key):\(item.value)")
}
print("\n")
for i in 1...10{
    print("Autocor \(i): \(autocor(p: period, n: i))")
}
print("\n")
let methodFinish = Date()
let executionTime = methodFinish.timeIntervalSince(methodStart)
print("Execution time: \(executionTime)")
