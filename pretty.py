import os
import fileinput

def create_logs():
    logs = []
    logs_i = -1
    for line in fileinput.input():
        if line.strip() == "":
            continue
        if line[:len("Testing")] == "Testing":
            logs.append({
                "name": line[:-4],
                "ok_counter": 0,
                "ko_counter": 0,
                "ko_messages": []
            })
            logs_i += 1
        elif line.find("[OK]") != -1:
            logs[logs_i]["ok_counter"] += 1
        elif line.find("[KO]") != -1:
            logs[logs_i]["ko_counter"] += 1
            logs[logs_i]["ko_messages"].append(line[line.find("[KO]") + len("[OK]") + 4:].strip())
    return logs

if __name__ == '__main__':
    logs = create_logs()[:-1]
    if len(logs) < 5:
        print("Somthing went wrong")
        exit()
    logs.sort(key=lambda x: x["name"])
    for log in logs:
        log["ok_ko_total"] = log["ok_counter"] + log["ko_counter"]
    os.system("clear")
    print("Summary")
    print("=======")
    for log in logs:
        print("{:20}  total: {:2}\t\t\033[32m[OK]\033[0m: {:2}\t\t".format(log["name"], log["ok_ko_total"], log["ok_counter"]), end="")
        if log["ko_counter"] != 0:
            print("\033[31m[KO]\033[0m: {:2}".format(log["ko_counter"]))
        else:
            print("\033[32mgg my boy\033[0m")
    print("=======")
    for log in logs:
        if log["ko_counter"] == 0:
            continue
        print("\n\033[31m[{}] {:2} KO\033[0m".format(log["name"], log["ko_counter"]))
        for msg in log["ko_messages"]:
            print("- {}".format(msg))
    if sum([log["ko_counter"] for log in logs]) == 0:
        print("GG MY BOY")
        print("You should make cacharle_great_again")

