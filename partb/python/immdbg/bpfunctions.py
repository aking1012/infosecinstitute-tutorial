
from immlib import *

def main(args):
    imm = Debugger()
    base = imm.getModule('Wlanapi.dll').getCodebase() - 4096
    astring = ''
    with open('y:\output.txt', 'r') as functions:
        astring = functions.read()
    stuff = astring.split('---')
    funclist = {}
    for thing in stuff:
        items = thing.split(':::')
        try:
            funclist[items[0]] = int(items[1])
        except:
            pass
    for key, address in funclist.iteritems():
        imm.log('Image base ' + str(hex(base)))
        imm.log('Function ' + key + ' RVA: ' + str(hex(address)))    
        imm.log('Function ' + key + ' Address: ' + str(hex(base + address)))    
        imm.setBreakpoint(base + address)
    return 'Done...'