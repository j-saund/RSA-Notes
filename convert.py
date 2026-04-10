import sys

if __name__ == "__main__":
    if len(sys.argv) > 1:
        msg = sys.argv[1]
    else:
        msg = "This is a secret!"
    
    # set up w/ 2nd arg in case we need other conversions
    if len(sys.argv) > 2:   
        if sys.argv[2] == "utf_hex":
            print(msg.encode("utf-8").hex())
        elif sys.argv[2] == "from_hex":
            print(bytes.fromhex(msg).decode("utf-8"))
            
    else:
        print(msg.encode("utf-8").hex())
    