# Written by Aadit Trivedi

# Features
# 1) Sentiment analysis
# 2) Summarize email
# 3) AI classificaiton of actionable items within emails
# 4) Autocorrect email content
# 5) Generate a wordcloud



# --------------------- Dependencies --------------------- #
import os
from os import path
import smtplib
import nltk
from nltk.sentiment.vader import SentimentIntensityAnalyzer
from summarizer import summarize
from autocorrect import spell
from wordcloud import WordCloud
import matplotlib.pyplot as plt
import goslate
# ---------------------------------------------------------#



# ------------------------------------------------------#
# Returns the sentiment score of a sentence.
# Dendencies: nltk
# ------------------------------------------------------#
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
            
            
            
# ------------------------------------------------------#
# Summarizes provided text in provided number of lines
# Dependencies: summarizer
# ------------------------------------------------------#
def sum(title,text,count):
  summarize(title,text,count)
# Example input --> Martin Luther King Jr.'s "I Have A Dream" speech
# Output:
# ['It is obvious today that America has defaulted on this promissory noteinsofar as her citizens of color are concerned.', 
# 'We refuse to believe that there are insufficient funds in the great vaults of opportunity of this nation.', 
# 'This is no time to engage in the luxury of cooling off or to take the tranquilizing drug of gradualism.', 
# 'I say to you today, my friends, so even though we face the difficulties of today and tomorrow, I still have a dream.', 
# 'It is a dream deeply rooted in the American dream.']



# -------------------------------------------------------------------------------------------------#
# smart_reply() -- Function responsible for easily sending standard response based on user's choice
#--------------------------------------------------------------------------------------------------#
aff = "Thank you for the reminder. Looking forward to meeting you!"
neg = "Thanks for the invite, but I will not be able to attend due to a conflict. Would any other times work?"
med = "I will get back to you as soon as possible."
def smart_reply(email_address, user_pwd, target, response_type):
  if response_type == aff:
    smtp_send(email_address, user_pwd, target, aff)
  elif response_type == neg:
    smtp_send(email_address, user_pwd, target, neg)
  elif response_type == med:
    smtp_send(email_address, user_pwd, target, med)

    
    
# -------------------------------------------------------------------------------------------------#
# Interfacing with Lisp AI program.
# Depdencies: os, smtplib
# -------------------------------------------------------------------------------------------------#
def get_results():
    # get_results() - runs the Lisp program and returns a list of two-element lists that contain:
    # the flag string ("ACTION-ITEM" or "NOT-ACTION-ITEM") as first element and the sentence itself as the second.
    os.system('sbcl --script main.lisp') # run the Lisp file
    with open('data/RESULTS', 'r') as fin:
        return [[line.split()[0], ' '.join(line.split()[1:]).upper()] for line in fin.readlines()]
def flag(string, ident):
    # flag() - appends a string to the POSITIVES file if ident=True and the NEGATIVES file if ident=False.
    # This is for the user to be able to give data to the AI for training.
    with open(('training/POSITIVES' if ident else 'training/NEGATIVES'), 'a+') as fout:
        fout.write(string + '\n')
        

        
# ------------------------------------------------------#
# Returns corrected words in brand new dictionary
# Dependencies: autocorrect
# ------------------------------------------------------#
def correct(email_content):
  new_content = []
  for word in email_content:
    if str(word) == str(spell(word)):
        new_content.append(word)
    else:
        new_content.append(spell(word))
# Example input --> "This is teh ablum"
# Output: ['This', 'is', 'the', 'album']




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

    
    
# ------------------------------------------------------------------#
# Translates provided text into provided language
# Dependencies: goslate
# ------------------------------------------------------------------#
ctry_lan = {
    'af': 'Afrikaans', 
    'sq': 'Albanian', 
    'am': 'Amharic', 
    'ar': 'Arabic', 
    'hy': 'Armenian', 
    'az': 'Azerbaijani', 
    'eu': 'Basque', 
    'be': 'Belarusian', 
    'bn': 'Bengali', 
    'bs': 'Bosnian', 
    'bg': 'Bulgarian', 
    'ca': 'Catalan', 
    'ceb': 'Cebuano', 
    'ny': 'Chichewa', 
    'zh-CN': 'Chinese (Simplified)', 
    'co': 'Corsican', 
    'hr': 'Croatian', 
    'cs': 'Czech', 
    'da': 'Danish', 
    'nl': 'Dutch', 
    'en': 'English', 
    'eo': 'Esperanto', 
    'et': 'Estonian', 
    'tl': 'Filipino', 
    'fi': 'Finnish', 
    'fr': 'French', 
    'fy': 'Frisian', 
    'gl': 'Galician', 
    'ka': 'Georgian', 
    'de': 'German', 
    'el': 'Greek', 
    'gu': 'Gujarati', 
    'ht': 'Haitian Creole', 
    'ha': 'Hausa', 
    'haw': 'Hawaiian', 
    'iw': 'Hebrew', 
    'hi': 'Hindi', 
    'hmn': 'Hmong', 
    'hu': 'Hungarian', 
    'is': 'Icelandic', 
    'ig': 'Igbo', 
    'id': 'Indonesian', 
    'ga': 'Irish', 
    'it': 'Italian', 
    'ja': 'Japanese', 
    'jw': 'Javanese', 
    'kn': 'Kannada', 
    'kk': 'Kazakh', 
    'km': 'Khmer', 
    'ko': 'Korean', 
    'ku': 'Kurdish (Kurmanji)', 
    'ky': 'Kyrgyz', 
    'lo': 'Lao', 
    'la': 'Latin', 
    'lv': 'Latvian', 
    'lt': 'Lithuanian', 
    'lb': 'Luxembourgish', 
    'mk': 'Macedonian', 
    'mg': 'Malagasy', 
    'ms': 'Malay', 
    'ml': 'Malayalam', 
    'mt': 'Maltese', 
    'mi': 'Maori', 
    'mr': 'Marathi', 
    'mn': 'Mongolian', 
    'my': 'Myanmar (Burmese)', 
    'ne': 'Nepali', 
    'no': 'Norwegian', 
    'ps': 'Pashto', 
    'fa': 'Persian', 
    'pl': 'Polish', 
    'pt': 'Portuguese', 
    'pa': 'Punjabi', 
    'ro': 'Romanian', 
    'ru': 'Russian', 
    'sm': 'Samoan', 
    'gd': 'Scots Gaelic', 
    'sr': 'Serbian', 
    'st': 'Sesotho', 
    'sn': 'Shona', 
    'sd': 'Sindhi', 
    'si': 'Sinhala', 
    'sk': 'Slovak', 
    'sl': 'Slovenian', 
    'so': 'Somali', 
    'es': 'Spanish', 
    'su': 'Sundanese', 
    'sw': 'Swahili', 
    'sv': 'Swedish', 
    'tg': 'Tajik', 
    'ta': 'Tamil', 
    'te': 'Telugu', 
    'th': 'Thai', 
    'tr': 'Turkish', 
    'uk': 'Ukrainian', 
    'ur': 'Urdu', 
    'uz': 'Uzbek', 
    'vi': 'Vietnamese', 
    'cy': 'Welsh', 
    'xh': 'Xhosa', 
    'yi': 'Yiddish', 
    'yo': 'Yoruba', 
    'zu': 'Zulu', 
    'zh-TW': 'Chinese (Traditional)', 
    'zh': 'Chinese'
}
def translate_into_lang(text_to_tran, target_lan):
    if str(target_lan) in ctry_lan:
        _slate_ = goslate.Goslate()
        return _slate_.translate(str(text_to_tran), str(target_lan))
    else:
        return "Invalid target language"
