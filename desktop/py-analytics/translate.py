# Written by Aadit Trivedi and Srihari Nanniyur.
import goslate
from tkinter import *
from tkinter.ttk import *
# ------------------------------------------------------------------#
# Translates provided text into provided language
# Dependencies: goslate
# ------------------------------------------------------------------#

ctry_lan = {
    'af Afrikaans', 
    'sq Albanian', 
    'am Amharic', 
    'ar Arabic', 
    'hy Armenian', 
    'az Azerbaijani', 
    'eu Basque', 
    'be Belarusian', 
    'bn Bengali', 
    'bs Bosnian', 
    'bg Bulgarian', 
    'ca Catalan', 
    'ce bCebuano', 
    'ny Chichewa', 
    'zh Chinese (Simplified)', 
    'co Corsican', 
    'hr Croatian', 
    'cs Czech', 
    'da Danish', 
    'nl Dutch', 
    'en English', 
    'eo Esperanto', 
    'et Estonian', 
    'tl Filipino', 
    'fi Finnish', 
    'fr French', 
    'fy Frisian', 
    'gl Galician', 
    'ka Georgian', 
    'de German', 
    'el Greek', 
    'gu Gujarati', 
    'ht Haitian Creole', 
    'ha Hausa', 
    'ha wHawaiian', 
    'iw Hebrew', 
    'hi Hindi', 
    'hm Hmong', 
    'hu Hungarian', 
    'is Icelandic', 
    'ig Igbo', 
    'id Indonesian', 
    'ga Irish', 
    'it Italian', 
    'ja Japanese', 
    'jw Javanese', 
    'kn Kannada', 
    'kk Kazakh', 
    'km Khmer', 
    'ko Korean', 
    'ku Kurdish (Kurmanji)', 
    'ky Kyrgyz', 
    'lo Lao', 
    'la Latin', 
    'lv Latvian', 
    'lt Lithuanian', 
    'lb Luxembourgish', 
    'mk Macedonian', 
    'mg Malagasy', 
    'ms Malay', 
    'ml Malayalam', 
    'mt Maltese', 
    'mi Maori', 
    'mr Marathi', 
    'mn Mongolian', 
    'my Myanmar (Burmese)', 
    'ne Nepali', 
    'no Norwegian', 
    'ps Pashto', 
    'fa Persian', 
    'pl Polish', 
    'pt Portuguese', 
    'pa Punjabi', 
    'ro Romanian', 
    'ru Russian', 
    'sm Samoan', 
    'gd Scots Gaelic', 
    'sr Serbian', 
    'st Sesotho', 
    'sn Shona', 
    'sd Sindhi', 
    'si Sinhala', 
    'sk Slovak', 
    'sl Slovenian', 
    'so Somali', 
    'es Spanish', 
    'su Sundanese', 
    'sw Swahili', 
    'sv Swedish', 
    'tg Tajik', 
    'ta Tamil', 
    'te Telugu', 
    'th Thai', 
    'tr Turkish', 
    'uk Ukrainian', 
    'ur Urdu', 
    'uz Uzbek', 
    'vi Vietnamese', 
    'cy Welsh', 
    'xh Xhosa', 
    'yi Yiddish', 
    'yo Yoruba', 
    'zu Zulu', 
    'zh Chinese (Traditional)', 
    'zh Chinese'
}

root = Tk()
variable = StringVar(root)
variable.set("Select Language")
menu = OptionMenu(root, variable, *ctry_lan)
lab = Label(root, text="Two-letter language code")
menu.grid(row=0, column=0)
lab.grid(row=0, column=1)

def translate_into_lang():
        _slate_ = goslate.Goslate()
        result = _slate_.translate(open('data/DATA', 'r').read(), variable.get()[:2])
        label = Label(root, text=result)
        label.grid(row=2, column=0)

button = Button(root, text="Translate", command=translate_into_lang)
button.grid(row=1, column=0)

root.mainloop()
