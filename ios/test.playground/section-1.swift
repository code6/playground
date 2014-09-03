import Foundation

extension String {
    subscript (i: Int) -> String {
        return String(Array(self)[i])
    }
    subscript (r: Range<Int>) -> String {
        var start = advance(startIndex, r.startIndex)
        var end = advance(startIndex, r.endIndex)
        return substringWithRange(Range(start: start, end: end))
    }
    var length:Int { return (self as NSString).length }
    var strip:String {
        return self.stringByTrimmingCharactersInSet(NSCharacterSet.whitespaceAndNewlineCharacterSet())
    }
    var reversed:String {
        var result:[String] = []
        for ch in self {
                result.append(String(ch))
        }
        return "".join(result.reverse())
    }
    func slice(start:Int=0, end:Int?=nil) -> String {
        let s = self as NSString
        var new_end:Int
        if ((end) != nil) {
            new_end = min(end!, s.length)
        } else {
            new_end = s.length
        }
        return  s.substringWithRange(NSRange(location: start, length:new_end - start))
    }
    func split(sep:String = "") -> [String] {
        return self.componentsSeparatedByString(sep)
    }
    func group(var step:Int) -> [String] {
        var result:[String] = []
        var next_i:Int
        step = max(step, 1)
        for var i = 0; i < self.length; i = next_i {
            next_i = i + step
            result.append(self.slice(start: i, end: next_i))
        }
        return result
    }
}

func splitWordString(var s:String) -> [String] {
    return s.split(sep: " ").filter({w in w.strip.isEmpty }).map({w in w.strip + " "})
}

var b  = 1.712121100
var s = "123"
var c = Array(Zip2(["1", "2"].map({x in x.toInt()!}), ["3", "4"]))

c.count

var array = Array(["1", "2", "3"])
var contained = contains(c, ("1", "3"))
println(contained ? "yes" : "no")


"".join(s.split().reverse())


s.slice(start: 1, end:100)
s.group(3)


let myZip = Zip2([1, 2], ["a", "b", "c"])
let myZipArray = Array(myZip)

println(myZipArray)    // [(1, a), (2, b), (3, c)]

