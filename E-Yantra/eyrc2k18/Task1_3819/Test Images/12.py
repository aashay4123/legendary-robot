#classes and subclasses to import
import cv2
import numpy as np
import os

c=0

filename = 'results1A_TeamId.csv'
#################################################################################################
# DO NOT EDIT!!!
#################################################################################################
#subroutine to write results to a csv
def writecsv(color,shape,(cx,cy)):
    global filename
    #open csv file in append mode
    filep = open(filename,'a')
    # create string data to write per image
    datastr = "," + color + "-" + shape + "-" + str(cx) + "-" + str(cy)
    #write to csv
    filep.write(datastr)
    filep.close()

def main(path):
#####################################################################################################
    #Write your code here!!!
#####################################################################################################
    global c
    if c==0:
        og = cv2.imread('./test1.png')
        img= cv2.imread('./test1.png',0)
    elif c==1:
        og = cv2.imread('./test2.png')
        img= cv2.imread('./test2.png',0)
    elif c==2:
        og = cv2.imread('./test3.png')
        img= cv2.imread('./test3.png',0)
    elif c==3:
        og = cv2.imread('./test4.png')
        img= cv2.imread('./test4.png',0)
    elif c==4:
        og = cv2.imread('./test5.png')
        img= cv2.imread('./test5.png',0)

    c=c+1
        
    ret,thresh = cv2.threshold(img,80,255,0)
    ret,thresh1 = cv2.threshold(img,80,255,1)

    thresh, contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    thresh = cv2.drawContours(thresh, contours, -1, (100,255,0), 3)

    lower_blue = np.array([0,0,0])
    upper_blue = np.array([255,0,0])
    mask_blue = cv2.inRange(og, lower_blue , upper_blue)
    mask_blue,contours_blue,hierarchy1 = cv2.findContours(mask_blue,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)


    lower_green = np.array([0,0,0]  )
    upper_green = np.array([0,255,0])
    mask_green = cv2.inRange(og, lower_green , upper_green)
    mask_green,contours_green,hierarchy1 = cv2.findContours(mask_green,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)


    lower_red = np.array([0,0,0])
    upper_red = np.array([0,0,255])
    mask_red = cv2.inRange(og, lower_red , upper_red)
    mask_red,contours_red,hierarchy3 = cv2.findContours(mask_red,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    i_blue = len(contours_blue)
    i_green = len(contours_green)
    i_red = len(contours_red)

    font = cv2.FONT_HERSHEY_SIMPLEX


    j=0

    while j<=i_blue - 1:
        global blue
        final_blue= cv2.bitwise_and(og, og, mask = mask_blue)
        cnt1 = contours_blue[j]
        approx = cv2.approxPolyDP(cnt1,0.01*cv2.arcLength(cnt1,True),True)
        (x, y, w, h) = cv2.boundingRect(approx)
        ar = w / float(h)
        M = cv2.moments(cnt1)
        cx = int(M['m10']/M['m00'])
        cy = int(M['m01']/M['m00'])
     
        if len(approx)==5:
            cv2.putText(og,"pentagon",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("blue","pentagon",(cx,cy))
        elif len(approx)==3:
            cv2.putText(og,"triangle",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("blue","triangle",(cx,cy))
        elif len(approx)==4 and (ar >= 2 and ar <= 2.55)  :
            cv2.putText(og,"trapezium",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv(blue,trapezium,(cx,cy))
        elif len(approx)==4 and (ar <= 1.7 and ar>= 1.414)  :
            cv2.putText(og,"rhombus",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("blue","rhombus",(cx,cy))
        elif len(approx) > 6:
            cv2.putText(og,"circle",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("blue","circle",(cx,cy))
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(og,'blue',(cx-35,cy), font,1,(0,0,0),2)
        cv2.putText(og,str(cx)+str(' ')+ str (cy),(cx-50,cy-50), font,1,(0,0,0),2)
        j=j+1

    k=0
    while k<=i_green - 1:
        global green
        final_green= cv2.bitwise_and(og, og, mask = mask_green)
        cnt2 = contours_green[k]
        approx = cv2.approxPolyDP(cnt2,0.01*cv2.arcLength(cnt2,True),True)
        (x, y, w, h) = cv2.boundingRect(approx)
        ar = w / float(h)
        M = cv2.moments(cnt2)
        cx = int(M['m10']/M['m00'])
        cy = int(M['m01']/M['m00'])
        if len(approx)==5:
            cv2.putText(og,"pentagon",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("green","pentagon",(cx,cy))
        elif len(approx)==3:
            cv2.putText(og,"triangle",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("green","triangle",(cx,cy))
        elif len(approx)==4 and (ar >= 2 and ar <= 2.55)  :
            cv2.putText(og,"trapezium",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("green","trapezium",(cx,cy))
        elif len(approx)==4 and (ar <= 1.7 and ar>= 1.414)  :
            cv2.putText(og,"rhombus",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("green","rhombus",(cx,cy))        
        elif len(approx) > 6:
            cv2.putText(og,"circle",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("green","circle",(cx,cy))
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(og,'green',(cx-50,cy), font,1,(0,0,0),2)
        cv2.putText(og,str(cx)+str(' ')+ str (cy),(cx-50,cy-50), font,1,(0,0,0),2)
        k=k+1

    p=0
    while p<=i_red - 1:
        global red
        final_red= cv2.bitwise_and(og, og, mask = mask_red)
        cnt3 = contours_red[p]
        approx = cv2.approxPolyDP(cnt3,0.01*cv2.arcLength(cnt3,True),True)
        (x, y, w, h) = cv2.boundingRect(approx)
        ar = w / float(h)
        M = cv2.moments(cnt3)
        cx = int(M['m10']/M['m00'])
        cy = int(M['m01']/M['m00'])

        if len(approx)==5:
           cv2.putText(og,"pentagon",(cx-100,cy-90), font,1,(0,0,0),2)
           writecsv("red","pentagon",(cx,cy))
        elif len(approx)==3:
            cv2.putText(og,"triangle",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("red","triangle",(cx,cy))
        elif len(approx)==4 and (ar >= 2 and ar <= 2.55)  :
            cv2.putText(og,"trapezium",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("red","trapezium",(cx,cy))
        elif len(approx)==4 and (ar>= 1.414 and ar <= 1.7)  :
            cv2.putText(og,"rhombus",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("red","rhombus",(cx,cy))
        elif len(approx) > 6:
            cv2.putText(og,"circle",(cx-100,cy-90), font,1,(0,0,0),2)
            writecsv("red","circle",(cx,cy))
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(og,'red',(cx-35,cy), font,1,(0,0,0),2)
        cv2.putText(og,str(cx)+str(' ')+ str (cy),(cx-50,cy-50), font,1,(0,0,0),2)
        p=p+1

    #cv2.imshow('imagePath', og)


    cv2.waitKey(0)

    cv2.destroyAllWindows()

#################################################################################################
# DO NOT EDIT!!!
#################################################################################################
#main where the path is set for the directory containing the test images
if __name__ == "__main__":
    mypath = '.'
    #getting all files in the directory
    onlyfiles = [mypath.join(f) for f in os.listdir(mypath) if f.endswith(".png")]
    
    #iterate over each file in the directory
    for fp in onlyfiles:
        #Open the csv to write in append mode
        filep = open(filename,'a')
        #this csv will later be used to save processed data, thus write the file name of the image 
        filep.write(fp)
        #close the file so that it can be reopened again later
        filep.close()
        #process the image
        data = main(fp)
        print data
        print f
        print fp
        print mypath.join(f)
        print os.listdir(mypath)
        #open the csv
        filep = open(filename,'a')
        #make a newline entry so that the next image data is written on a newline
        filep.write('\n')
        #close the file
        filep.close()
