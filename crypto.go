package main

import(
    "fmt"
    "math/rand"
    "time"
    "strconv"
    "strings"
)

func randInt(count int) int {
    rand.Seed(time.Now().UTC().UnixNano() + rand.Int63n(65537))
    return 1 + rand.Intn(count)
}

func reverse_string(text string) string {
    n := len(text)
    runes := make([]rune, n)
    for _, rune := range text {
        n--
        runes[n] = rune
    }
    return string(runes[n:])
}

func encrypt_string(plaintext string) string {
    k := randInt(1024)
    n := 0
    f := ""
    for _, v := range plaintext {
        n += 1
        c := (n * n) ^ 0x3E
        t, err := strconv.Atoi(strconv.FormatInt(int64(int(v) ^ k ^ 0xAFE43 ^ 0x399AA3 ^ c), 8))
        if err != nil { return "" }
        tx := "00000" + fmt.Sprintf("%x", t)
        f += tx[len(tx)-6:len(tx)]
    }
    fy := "000" + fmt.Sprintf("%x", (k ^ 0xA9F ^ 0xE77E))
    f = reverse_string(fy[len(fy)-4:len(fy)] + f)

    return strings.ToUpper(f)
}

func decrypt_string(ciphertext string) string {
    e := reverse_string(ciphertext)
    k, err := strconv.ParseInt("0x" + e[:4], 0, 64)
    if err != nil { return "" }
    k = int64(k) ^ 0xA9F ^ 0xE77E
    t := e[4:len(e)]
    f := ""
    n := 0
    for i := 0; i < len(t); i += 6 {
        n += 1
        c := int64(n * n) ^ 0x3E
        fx, err := strconv.ParseInt("0x" + t[i:i+6], 0, 64)
            if err != nil { return "" }
        fy := "0" + strconv.FormatInt(fx, 10)
        fz, err := strconv.ParseInt(fy, 8, 64)
        if err != nil { return "" }
        fa := int(fz ^ int64(k) ^ 0xAFE43 ^ 0x399AA3 ^ c)
        f += string(fa)
    }
    return f
}

func main() {
    fmt.Println(encrypt_string("testing crypto in golang"))
}
