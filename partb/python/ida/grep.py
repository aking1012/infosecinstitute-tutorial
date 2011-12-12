import idautils

class funcRVAs():
    def __init__(self, grep = None, path = 'Y:\output.txt'):
        self.grep = grep
        self.path = path
        segs = []
        self.funcs = {}
        for base in idautils.Segments():
            segs.append(base)
        self.imgbase = segs[0]
        print 'Image Base: ' + str(hex(self.imgbase))
        for base in Segments():
            for func in Functions(base, SegEnd(base)):
                self.funcs[GetFunctionName(func)] = func
    def find(self, grep=None):
        if grep != None:
            self.grep = grep
        if self.grep == None:
            print 'No grep parameter'
            quit('No grep parameter')
        thisdict = {}
        for key, ea in self.funcs.iteritems():
            if self.grep in key:
                thisdict[key] = ea
        RVADict = {}
        for key, address in thisdict.iteritems():
            RVA = address - self.imgbase
            RVADict[key] = RVA
        with open(self.path, 'w') as out:
            for key, address in RVADict.iteritems():
                out.write(key + ':::' + str(address) + '---')
        print 'Matching functions found:' + str(len(RVADict))

if __name__ == '__main__':
    funcRVAs().find('Wlan')
