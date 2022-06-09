from urllib.request import urlopen

import json

# url = "https://bookcoverapi.herokuapp.com/getBookCover?bookTitle=The+Pale+Blue+Dot&authorName=Carl+Sagan"

# response = urlopen(url)

# data_json = json.loads(response.read())

# print(data_json['bookCoverUrl'])


def fetchCover(title, author):
    title = title.replace(" ", "+")

    if "/" in author:
        author = author.split("/")[0]

    author = author.replace(" ", "+")
    author = author.replace(".", "")

    url = f"https://bookcoverapi.herokuapp.com/getBookCover?bookTitle={title}&authorName={author}"
    response = urlopen(url)
    data_json = json.loads(response.read())
    return data_json

print(fetchCover("The Pale Blue Dot", "Carl Sagan/J. K. Rowling"))
