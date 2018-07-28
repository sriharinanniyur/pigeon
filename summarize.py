# Dependencies
# pip3 install summarizer

from summarizer import summarize

def sum(title,text,count):
  summarize(title,text,count)

# Example input (Martin Luther King Jr.'s "I Have A Dream" speech)
# Output:
# [
# 'It is obvious today that America has defaulted on this promissory noteinsofar as her citizens of color are concerned.', 
# 'We refuse to believe that there are insufficient funds in the great vaults of opportunity of this nation.', 
# 'This is no time to engage in the luxury of cooling off or to take the tranquilizing drug of gradualism.', 
# 'I say to you today, my friends, so even though we face the difficulties of today and tomorrow, I still have a dream.', 
# 'It is a dream deeply rooted in the American dream.'
# ]
