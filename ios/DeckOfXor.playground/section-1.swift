// Playground - noun: a place where people can play

import Foundation


func gauss(var a:[[Int]], var b:[Int]) -> Int {
    var row = 0, m = a[0].count, n = a.count
    var i: Int, j: Int
    for col in 0...m - 1 {
        for i = row ;i < n; i++ {
            if a[i][col] > 0 {
                break;
            }
        }
        if i >= n {
            continue
        }
        
        if i != row {
            for j in col...m-1 {
                swap(&a[row][j], &a[i][j])
            }
            swap(&b[i], &b[row])
        }
        
        for i = row + 1; i < n; i++ {
            if a[i][col] > 0 {
                for j = col; j < m; j++ {
                    a[i][j] ^= a[row][j]
                }
                b[i] ^= b[row]
            }
        }
        row += 1
    }
    
    
    var ret = 0
    
    for i = row; i < n; i++ {
        if b[i] > 0 {
            return 0
        }
    }
    
    return 1 << (m - row)
}

func gen(var number:[Int], var limit:Int) -> Int {
    var a = [[Int]]()
    var b = [Int]()
    
    for i in 1...63 {
        b.append(limit & 1)
        limit >>= 1
    }
    
    for i in 1...63 {
        var row = [Int]()
        for i in 0...number.count - 1 {
            row.append(number[i] & 1)
            number[i] >>= 1
        }
        a.append(row)
    }
    
    var ret = gauss(a, b)
    return ret
}

func differentWays(var number: [Int], var limit: Int) -> Int {
    var ret = gen(number, limit)
    for pos in 1...63 {
        if limit & 1 > 0 {
            limit ^= 1
            ret += gen(number, limit)
        }
        limit >>= 1
        for i in 0...number.count-1 {
            number[i] >>= 1
        }
    }
    
    return ret
}
differentWays([1,2], 2)
differentWays([5,5], 3)
differentWays([1,2,3,4,5,6,7], 5)
differentWays([123, 456, 789, 147, 258, 369, 159, 357]
, 500)
differentWays([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
, 1000000000000000)
differentWays([1000000000000000, 999999999999999]
, 65535)
