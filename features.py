# Features
# 1) Sentiment analysis
# 2) Summarize email
# Returns the sentiment score of a sentence.

import nltk
from nltk.sentiment.vader import SentimentIntensityAnalyzer

def bubbleSort(mylist):
    for num in range(len(mylist)-1,0,-1):
        for i in range(num):
            if mylist[i]>mylist[i+1]:
                temp = mylist[i]
                mylist[i] = mylist[i+1]
                mylist[i+1] = temp
    return mylist

def sentiment_analysis(sentence):
    nltk_sentiment = SentimentIntensityAnalyzer()
    score = nltk_sentiment.polarity_scores(sentence)
    emotion_val = [score['neg'], score['neu'], score['pos'], score['compound']]
    emotion_val = bubbleSort(emotion_val)
    dominant_emotion = emotion_val[3]
    for key in score.keys():
        if score[key] == dominant_emotion:
            if (key == "pos"):
                return "positive: " + str(round(100 * dominant_emotion)) + "%"
            elif (key == "neg"):
                return "negative: " + str(round(100 * dominant_emotion)) + "%"
            elif (key == "neu"):
                return "neutral: " + str(round(100 * dominant_emotion)) + "%"
            elif (key == "compound"):
                return "compound: " + str(round(100 * dominant_emotion)) + "%"
