import random
import pickle

connotations = pickle.load(open(r"savefiles\connotations.pkl", "rb"))
sentencedic = pickle.load(open(r"savefiles\sentencedic.pkl", "rb")) 
sentencedict = pickle.load(open(r"savefiles\sentenceranking.pkl", "rb"))
dictionary = pickle.load(open(r"savefiles\dictionary.pkl", "rb"))
wordstuff = pickle.load(open(r"savefiles\wordstuff.pkl", "rb"))

class Utils:
    def getpattern(x = wordstuff): #get the pattern of the entire wordstuff lists or one specific word
        pattern = {}
        for key in x:
            tempnum = 0
            pattern[key] = {"commonbefore":{},"commonafter":{}}
            if x[key]["before"] != '':
                for beforewords in x[key]["before"]:
                    tempnum = x[key]["before"][beforewords] + tempnum
                for beforewords in x[key]["before"]:
                    pattern[key]["commonbefore"][beforewords] = x[key]["before"][beforewords]/tempnum
        for key in x:
            tempnum = 0
            if x[key]["after"] != '':
                for afterwords in x[key]["after"]:
                    tempnum = x[key]["after"][afterwords] + tempnum
                for afterwords in x[key]["after"]:
                    pattern[key]["commonafter"][afterwords] = x[key]["after"][afterwords]/tempnum
        return pattern

    def getallknownwords(): #gets a list of all the words in dict
        templist = []
        for key in dictionary:
            if key != "sortedlater" and key != "none":
                for word in dictionary[key]:
                    templist.append(word)
        return templist

    def placewords(word): #finds the what part of sentence a specific word is
        for key in dictionary:
            if word in dictionary[key]:
                return key

    def choosewordfromcat(pos): #gets a random word in a specific part of speech
        return random.choice(list(dictionary[pos]))

    def makereadable(item):
        for x in item:
            wordlist = []
            for y in item[x]:
                wordlist.append(f"{y} : {item[x][y]}")
            print(f"{x} = {wordlist}")

def setword(message,*client):
    msg = message.lower().split(" ")
    for key in dictionary:
        if msg[1] in dictionary[key]:
            dictionary[key].remove(msg[1])
    if msg[2] in ["greeting", "pronoun", "noun", "verb", "adverb", "question", "adjective", "preposition", "conjunction", "self", "possesive", "random", "article", "yesno", "others", "none"]:
        dictionary[msg[2]].add(msg[1]) 
        print("Assigned {} to {}".format(msg[1], msg[2]))
    else:
        print("Format is: **setword *__word__* *__part of sentence__***\nThe parts of sentence available are: greeting, pronoun, noun, verb, adverb, question, adjective, preposition, conjunction, self, possesive, random, article, yesno, others, none")


class Response:
        #greeting, pronoun, noun, verb, adverb, question, adjective, preposition, conjunction, self, possesive, random, article, yesno, others

    def checksentence(msg):
        sentencestruct = []
        for word in msg: #loops through words in the message
            if word in dictionary["pronoun"]: 
                sentencestruct.append("pronoun")
            elif word in dictionary["noun"]:
                sentencestruct.append("noun")
            elif word in dictionary["verb"]:
                sentencestruct.append("verb")
            elif word in dictionary["adverb"]:
                sentencestruct.append("adverb")
            elif word in dictionary["question"]:
                sentencestruct.append("question")
            elif word in dictionary["adjective"]:
                sentencestruct.append("adjective")
            elif word in dictionary["preposition"]:
                sentencestruct.append("preposition")
            elif word in dictionary["conjunction"]:
                sentencestruct.append("conjunction")
            elif word in dictionary["greeting"]:
                sentencestruct.append("greeting")
            elif word in dictionary["self"]:
                sentencestruct.append("self")
            elif word in dictionary["possesive"]:
                sentencestruct.append("possesive")
            elif word in dictionary["random"]:
                sentencestruct.append("random")
            elif word in dictionary["article"]:
                sentencestruct.append("article")
            elif word in dictionary["yesno"]:
                sentencestruct.append("yesno")
            elif word in dictionary["others"]:
                sentencestruct.append("others")
            elif word in dictionary["sortedlater"]:
                sentencestruct.append("sortedlater")
            elif word in dictionary["none"]:
                sentencestruct.append("none")
            else:
                sentencestruct.append("unknown")
                unknownword = word
                return unknownword
        return sentencestruct

    def sentencedeconstruct(message, sentencestuff, sentencestruct, msg):
        sentencedeconstruct = {}
        counter = 0
        for word in msg:
            sentencedeconstruct[word] = {"pos":Utils.placewords(word), "position":counter}
            counter = counter + 1

        for key in sentencedeconstruct:
            if sentencedeconstruct[key]["pos"] == "noun":
                if sentencedeconstruct[key]["position"] == 0:
                    pass
                else:
                    breaktime = False
                    counters = 1
                    while counters <= sentencedeconstruct[key]["position"]:
                        for items in sentencestuff['preposition']:
                            if (sentencedeconstruct[key]["position"]-counters) == max((i for i in items if isinstance(i, int))):
                                breaktime = True
                        if breaktime == True:
                            breaktime = False
                            break
                        elif sentencestruct[sentencedeconstruct[key]["position"]-counters] == "article":
                            print("It's an article")
                        elif sentencestruct[sentencedeconstruct[key]["position"]-counters] == "adjective":
                            print("It's an adjective")
                        elif sentencestruct[sentencedeconstruct[key]["position"]-counters] == "noun":
                            print("It's a noun")
                        else:
                            break
                        counters = counters + 1
                        sentencedeconstruct[key]["phrase"] = msg[sentencedeconstruct[key]["position"]-counters+1:sentencedeconstruct[key]["position"]+1]

            if sentencedeconstruct[key]["pos"] == "verb":
                if sentencedeconstruct[key]["position"] == 0:
                    pass
                else:
                    counters = 1
                    while counters <= sentencedeconstruct[key]["position"]:
                        if sentencestruct[sentencedeconstruct[key]["position"]-counters] == "verb":
                            print("It's a helping verb")
                        elif sentencestruct[sentencedeconstruct[key]["position"]-counters] == "adverb":
                            print("It's an adverb")

                        else:
                            break
                        counters = counters + 1
                        sentencedeconstruct[key]["phrase"] = msg[sentencedeconstruct[key]["position"]-counters+1:sentencedeconstruct[key]["position"]+1]
        
        Utils.makereadable(sentencedeconstruct)
        


    def getpreposition(message, sentencestuff, msg):
        prepositions = []
        thenoun = 0
        for prep in sentencestuff["preposition"]:
            msg2 = msg[msg.index(prep):] #shortens sentence to the preposition to the rest of the sentence
            for word in msg2:
                if word in dictionary["noun"]:
                    thenoun = word #gets the closest noun
                    break
            if thenoun != 0:
                prepositions.append([msg.index(prep), msg.index(thenoun), " ".join(msg2[:(msg2.index(thenoun)+1)]).split(" ")])
                thenoun = 0
        sentencestuff["preposition"] = prepositions
        return sentencestuff
 
    def getsubject(message, sentencestuff, msg):
        subjectloc = []
        verbloc = []
        for sub in sentencestuff["subject"]:
            subjectloc.append(msg.index(sub)) #gets the location of the potential subjects
        for verb in sentencestuff["mainverb"]:
            verbloc.append(msg.index(verb)) #gets location of potential mainverbs
        verbloc = min(verbloc)
        for nums in subjectloc:
            if nums > verbloc: #if potential subject is after verb, remove it
                subjectloc.remove(nums)
        sentencestuff["subject"] = [msg[min(subjectloc, key=lambda x:abs(x-verbloc))], min(subjectloc, key=lambda x:abs(x-verbloc))]  #gets the noun/pronoun/self closest to the verb
        sentencestuff["mainverb"] = [msg[verbloc],verbloc]
        
        return sentencestuff

    def sentencebreakdown(sentencestuff, sentencestruct, msg): #may completely delete in the future, sentencedeconstruct seems to work better
        #make a process that groups phrases/relevant parts of sentences together
        #{the pretty man} {is going} {to {the store}}
        #description of noun, helping verb + action verb, prepositional phrase/desc of noun

        if sentencestuff["subject"][1] != 0:
            counter = 1
            while counter < sentencestuff["subject"][1]:

                if sentencestuff["preposition"]:
                    for preps in sentencestuff["preposition"]:
                        if int(sentencestuff["subject"][1]) - counter == preps[1]: #This section checks if the subject breakdown is going into a preposition
                            counter = "break"
                            break
                if counter == "break":
                    break

                if sentencestruct[sentencestuff["subject"][1]-counter] == "article":
                    print("It's an article")
                elif sentencestruct[sentencestuff["subject"][1]-counter] == "adjective":
                    print("It's an adjective")
                elif sentencestruct[sentencestuff["subject"][1]-counter] == "noun":
                    print("It's a noun")
                counter = counter + 1
        
        if sentencestuff["mainverb"][1] != 0:
            counter = 1
            while counter < sentencestuff["mainverb"][1]:

                if sentencestuff["preposition"]:
                    for preps in sentencestuff["preposition"]:
                        if int(sentencestuff["mainverb"][1]) - counter == preps[1]: #This section checks if the subject breakdown is going into a preposition
                            counter = "break"
                            break
                if counter == "break":
                    break

                if sentencestruct[sentencestuff["mainverb"][1]-counter] == "adverb":
                    print("It's an adverb")
                elif sentencestruct[sentencestuff["mainverb"][1]-counter] == "verb":
                    print("It's an verb")
                counter = counter + 1

        return

    def compose(message, sentencestuff, msg): #COMPLETELY REDO, MIGHT HAVE TO HAVE MORE PATTERN INPUT? CONNECTING NOUNS AND THEIR DESCRIPTORS TOGETHER, VERBS WITH WHATS DOING ACTION
        newsentence = []
        avg = []
        for key in sentencedict:
            if "noun" in key and "verb" in key:
                avg.append(sentencedict[key])
        avg = sum(avg)/len(avg) #creates an average of sentence structure integers
        pattern = Utils.getpattern() #word patterns

        createsent = random.choice(list(sentencedic["sentences"]))
        while (sentencedict[createsent] <= avg) and (len(createsent) < 2) and (createsent[0] == "none") and ("noun" not in createsent) and ("verb" not in createsent): #checks for specific sentence paramaters
            createsent = random.choice(list(sentencedic["sentences"]))
        createsent = str(createsent).replace(" ", ",").replace("[","").replace("]","").split(",")
        
        found = []
        counter = 0
        for words in createsent: #for every part of sentence in the createsent list
            templist = []
            dontHave = False
            avg = []
            if counter > 0: #makes sure that there has been one loop before
                if (words == "noun" or words == "pronoun" or words == "self" or words == "others") and "noun" not in found:
                    newsentence.append(sentencestuff["subject"])
                    found.append("noun")
                    continue
                elif words == "verb" and "noun" not in found:
                    newsentence.append(sentencestuff["mainverb"])
                    found.append("verb")
                    continue
                if newsentence[counter-1] in wordstuff:
                    for key in wordstuff[newsentence[counter-1]]["after"]:
                        avg.append(wordstuff[newsentence[counter-1]]["after"][key])
                    try: 
                        avg = sum(avg)/len(avg) #gets the averages of the after words
                    except:
                        pass
                    for key in wordstuff[newsentence[counter-1]]["after"]: #this loop gets a list of words that have a greater average in ctx to the last word
                        if wordstuff[newsentence[counter-1]]["after"][key] >= avg:
                            templist.append(key)
                        else:
                            continue
                if not templist: #if the word has not been used around anything else
                    dontHave = True
                if (newsentence[counter-1] in wordstuff) and dontHave != True: 
                    newsentence.append(random.choice(templist)) #adds a random word from the previously made list to the sentence
            if counter == 0 or dontHave == True:
                if words == "noun" or words == "pronoun" or words == "self" or words == "others":
                    newsentence.append(sentencestuff["subject"])
                    found.append("noun")
                elif words == "verb":
                    newsentence.append(sentencestuff["mainverb"])
                    found.append("verb")
                else:
                    newsentence.append(Utils.choosewordfromcat(words)) #if the word not in wordstuff, randomly chooses from a category
            counter = counter + 1
        
        return " ".join(newsentence)
        #replace noun/pronouon/self etc with subject in a struct. Use ctx to check before and after for subject and verb. Intersect common words and choose one
        
    def response(message,*client):
    #identify subject, identify descriptive words, formulate response based on words it knows and commonly positioned words, if no commonly positioned words: use commonly positioned words for nouns. https://webapps.towson.edu/ows/modulesvagr.htm 

        sentencestuff = {"subject":[],"mainverb":[],"preposition":[]} #subject is main noun/pronoun, mainverb is the first verb after the subject, prepositions, affected is the word affected by the mainverb
        #^^^ ENDUP: {"subject":[],"mainverb":[],"preposition":[]}
        msg = str(message.lower()).replace(",","").replace(" ", ",").replace("~","").replace("$","").replace("%","").replace("^","").replace("&","").replace("*","").replace("(","").replace(")","").replace("-","").replace("_","").replace("+","").replace("=","").replace("<","").replace(">","").replace("/","").replace("{","").replace("}","").replace("[","").replace("]","").replace(":","").replace(";","").replace("|","").replace("~","").replace("`","").replace('"', "").replace("?", "").replace(".", "").replace("!","").replace("#","").split(",")

        sentencestruct = Response.checksentence(msg)
        print(sentencestruct)
        if isinstance(sentencestruct, str):
            print("I do not know the word '{}'! Please use the **setword** command to add it!".format(sentencestruct))
            return

        if (msg[0] in dictionary["question"]) or (msg[0] == "do") or (msg[0] == "does"):
            print("I am not prepared for questions yet")

        for word in msg:
            if word in dictionary["noun"]:
                sentencestuff["subject"].append(word)
            if word in dictionary["pronoun"]:
                sentencestuff["subject"].append(word)
            if word in dictionary["self"]:
                sentencestuff["subject"].append(word)
            if word in dictionary["others"]:
                sentencestuff["subject"].append(word)
            if word in dictionary["verb"]:
                sentencestuff["mainverb"].append(word)
            if word in dictionary["preposition"]:
                sentencestuff["preposition"].append(word)

        sentencestuff = Response.getpreposition(message, sentencestuff, msg)

        if sentencestuff["preposition"]: #if there is a preposition, do code
            for lists in sentencestuff["preposition"]: #if a noun/verb inside a preposition, remove it from being a potential subject or mainverb
                for theprepwords in lists[2]:
                    for potentialsubjects in sentencestuff["subject"]:
                        if potentialsubjects == theprepwords:
                            sentencestuff["subject"].remove(potentialsubjects)
                    for potentialmainverbs in sentencestuff["mainverb"]:
                        if potentialmainverbs == theprepwords:
                            sentencestuff["mainverb"].remove(potentialmainverbs)

        try:
            sentencestuff = Response.getsubject(message, sentencestuff, msg)
            print(sentencestuff)
        except Exception as e:
            print(e)
            return

        #Response.sentencebreakdown(sentencestuff, sentencestruct, msg)
        Response.sentencedeconstruct(message, sentencestuff, sentencestruct, msg)

        #SENTENCE BUILDING SECTION
        
        #compose = Response.compose(message, sentencestuff, msg) #COMPLETELY REDO :)
        #await message.channel.send(compose)

while True:
    message = input()
    if message.startswith("setword"):
        setword(message)
    else:
        Response.response(message)
        

#RUNNING LIST OF PROBLEMS TO FIX LATER
#Subject / Main verb can not be in the preposition at all. (later, make it reliant on sentence position)
#If main verb is before subject, error (add exception)