import os.path
import re

import bs4
import requests

HEADERS = {
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
    "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.105 Safari/537.36 Vivaldi/2.4.1488.40",
    "Connection": "keep-alive"
}
URL = "https://www.luogu.com.cn/problem"


def get_response(_url: str):
    return requests.get(_url, headers=HEADERS)


def get_bs_instance(_url: str):
    return bs4.BeautifulSoup(get_response(_url).content, "lxml")


# ids = []
# ids.extend([f"P{i}" for i in range(5657, 5667)])
# ids.extend([f"P{i}" for i in range(5681, 5682)])
ids = ["P4000"]
for _id in ids:
    try:
        if not os.path.exists("out"):
            os.mkdir("out")
        fout = open(f"out/{_id}.md", "w", encoding="UTF-8")
        url = f"{URL}/{_id}"
        article: bs4.BeautifulSoup = get_bs_instance(url).article

        background: bs4.BeautifulSoup = article.find(lambda tag: tag.string == "题目背景")
        if background:
            fout.write("# 题目背景")

        description: bs4.BeautifulSoup = article.find(lambda tag: tag.string == "题目描述")
        fout.write("# 题目描述\n\n")
        fout.write(description.find_next("div").string)
        fout.write("\n\n")

        informat: bs4.BeautifulSoup = article.find(lambda tag: tag.string == "输入格式")
        fout.write("# 输入格式\n\n")
        fout.write(informat.find_next("div").string)
        fout.write("\n\n")

        outformat: bs4.BeautifulSoup = article.find(lambda tag: tag.string == "输出格式")
        fout.write("# 输出格式\n\n")
        fout.write(outformat.find_next("div").string)
        fout.write("\n\n")

        example: bs4.BeautifulSoup = article.find(lambda tag: tag.string == "输入输出样例")
        fout.write("# 输入输出样例\n")
        cnt = 0
        cursor = example.find_next("h3")
        while cursor and re.match(r"输入样例 #\d", cursor.string):
            cnt += 1
            fout.write(f"```input{cnt}\n")
            fout.write(cursor.find_next("code").string)
            fout.write("\n```\n\n")
            cursor = cursor.find_next("code")

            fout.write(f"```output{cnt}\n")
            fout.write(cursor.find_next("code").string)
            fout.write("\n```\n\n")
            cursor = cursor.find_next("h3").find_next("h3")

        note: bs4.BeautifulSoup = article.find(lambda tag: str(tag.string).find("说明") != -1)
        fout.write("# 说明/提示\n\n")
        s = note.find_next("div").string
        s = re.sub(r"-(?=\040\|)", ":", s)
        s = re.sub(r"【.*(?P<f>\d).*样例.*】|【.*样例.*(?P<s>\d).*】", lambda m: f'【样例解释 #{m.group("f") or m.group("s")}】', s)
        s = re.sub(r"【数据.*】", "【数据规模】", s)
        s = s.replace("\n\n\n", "\n\n")
        fout.write(s)

        fout.close()
    except Exception as e:
        print("GG!", f"Problem{_id}")
        print(e)
        opt = input("Continue?(Y/Any)")
        if not opt == 'Y':
            exit(-1)
