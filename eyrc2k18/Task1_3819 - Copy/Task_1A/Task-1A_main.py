#classes and subclasses to import
import cv2
import numpy as np
import os
og = cv2.imread(fp)
img = cv2.imread(fp,0)      
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
            shape ="pentagon"
            
        elif len(approx)==3:
            shape = "triangle"
        elif len(approx)==4 and (ar >= 2 and ar <= 2.55)  :
            shape= "trapezium"
        elif len(approx)==4 and (ar <= 1.7 and ar>= 1.414)  :
            shape="rhombus"
        elif len(approx) > 6:
            shape="circle"
        text= "{}".format(shape)
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(og,"blue",(cx-100,cy-90), font,1,(0,0,0),2)
        cv2.putText(og,text,(cx-35,cy), font,1,(0,0,0),2)
        cv2.putText(og,str(cx)+str(' ')+ str (cy),(cx-50,cy-50), font,1,(0,0,0),2)
        writecsv("blue",text,(cx,cy))
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
            shape ="pentagon"
        elif len(approx)==3:
            shape = "triangle"
        elif len(approx)==4 and (ar >= 2 and ar <= 2.55)  :
            shape= "trapezium"
        elif len(approx)==4 and (ar <= 1.7 and ar>= 1.414)  :
            shape="rhombus"     
        elif len(approx) > 6:
            shape="circle"
        font = cv2.FONT_HERSHEY_SIMPLEX
        text= "{}".format(shape)
        cv2.putText(og,text,(cx-100,cy-90), font,1,(0,0,0),2)
        cv2.putText(og,'green',(cx-50,cy), font,1,(0,0,0),2)
        cv2.putText(og,str(cx)+str(' ')+ str (cy),(cx-50,cy-50), font,1,(0,0,0),2)
        writecsv("blue",text,(cx,cy))
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
           shape ="pentagon"
        elif len(approx)==3:
           shape = "triangle"
        elif len(approx)==4 and (ar >= 2 and ar <= 2.55)  :
           shape= "trapezium"
        elif len(approx)==4 and (ar>= 1.414 and ar <= 1.7)  :
           shape="rhombus"
        elif len(approx) > 6:
           shape="circle"
        font = cv2.FONT_HERSHEY_SIMPLEX
        text= "{}".format(shape)
        cv2.putText(og,'red',(cx-35,cy), font,1,(0,0,0),2)
        cv2.putText(og,text,(cx-100,cy-90), font,1,(0,0,0),2)
        cv2.putText(og,str(cx)+str(' ')+ str (cy),(cx-50,cy-50), font,1,(0,0,0),2)
        p=p+1

    cv2.imshow(fp, og)
    str1 = str(fp)
    str2 = 'png'
    imgout = str1 + 'output.' + str2
    cv2.imwrite(imgout,og)

    cv2.waitKey(0)

    cv2.destroyAllWindows()
