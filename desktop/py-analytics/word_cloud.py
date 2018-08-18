# Written by Aadit Trivedi

import matplotlib.pyplot as plt
import os
from os import path
from wordcloud import WordCloud

def genWC(file_path_wc):
    d = path.dirname(__file__) if "__file__" in locals() else os.getcwd()
    text = open(path.join(d, str(file_path_wc))).read()
    wordcloud = WordCloud().generate(text)
    wordcloud = WordCloud(max_font_size=40).generate(text)
    plt.imshow(wordcloud, interpolation="bilinear")
    plt.axis("off")
    plt.show()
genWC('data/DATA') # KEEP THIS LINE
