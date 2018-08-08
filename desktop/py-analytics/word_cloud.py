import matplotlib.pyplot as plt
import os
from os import path
from wordcloud import WordCloud
# ------------------------------------------------------------------#
# Displays a wordcloud given a file with words
# Dependencies: os, os.path, wordcloud.WordCloud, matplotlib.pyplot
# ------------------------------------------------------------------#
def genWC(file_path_wc):
    d = path.dirname(__file__) if "__file__" in locals() else os.getcwd()
    text = open(path.join(d, str(file_path_wc))).read()
    wordcloud = WordCloud().generate(text)
    wordcloud = WordCloud(max_font_size=40).generate(text)
    plt.imshow(wordcloud, interpolation="bilinear")
    plt.axis("off")
    plt.show()
genWC('data/DATA')
