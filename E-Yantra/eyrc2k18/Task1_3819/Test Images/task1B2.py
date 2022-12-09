#classes and subclasses to import
import cv2
import numpy as np
import os

filename = 'results1B_3819.csv'
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

#################################################################################################
# DO NOT EDIT!!!
#################################################################################################
def blend_transparent(face_img, overlay_t_img):
    # Split out the transparency mask from the colour info
    overlay_img = overlay_t_img[:,:,:3] # Grab the BRG planes
    overlay_mask = overlay_t_img[:,:,3:]  # And the alpha plane

    # Again calculate the inverse mask
    background_mask = 255 - overlay_mask

    # Turn the masks into three channel, so we can use them as weights
    overlay_mask = cv2.cvtColor(overlay_mask, cv2.COLOR_GRAY2BGR)
    background_mask = cv2.cvtColor(background_mask, cv2.COLOR_GRAY2BGR)

    # Create a masked out face image, and masked out overlay
    # We convert the images to floating point in range 0.0 - 1.0
    face_part = (face_img * (1 / 255.0)) * (background_mask * (1 / 255.0))
    overlay_part = (overlay_img * (1 / 255.0)) * (overlay_mask * (1 / 255.0))

    # And finally just add them together, and rescale it back to an 8bit integer image    
    return np.uint8(cv2.addWeighted(face_part, 255.0, overlay_part, 255.0, 0.0))


def main(self):
    global cap
    cap = cv2.VideoCapture('./Video.mp4')
    print (cap.grab())
    image_red = cv2.imread("./yellow_flower.png",-1)
    image_blue = cv2.imread("./pink_flower.png",-1)
    image_green = cv2.imread("./red_flower.png",-1)

#####################################################################################################
    #Write your code here!!!
#####################################################################################################
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    out = cv2.VideoWriter('video_output.avi',fourcc, 16.0, (1280,720))
    while (True) :
        # Capture frame-by-frame
        ret, frame = cap.read()
        #print (cap.grab())
        img = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
        ret,thresh = cv2.threshold(img,127,255,1)
        thresh, contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
        
        if (len(contours)==1):

            
            M = cv2.moments(contours[0])
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])

            writecsv("green","circle",(cx,cy))

            x,y,w,h = cv2.boundingRect(contours[0])

            overlay_image = cv2.resize(image_green,(h,w))

            frame[y:y+w,x:x+h,:] = blend_transparent(frame[y:y+w,x:x+h,:], overlay_image)

        if (len(contours)==2):

            
            M = cv2.moments(contours[1])
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])

            writecsv("blue","hexagon",(cx,cy))


            x,y,w,h = cv2.boundingRect(contours[1])

            overlay_image = cv2.resize(image_blue,(h,w))

            frame[y:y+w,x:x+h,:] = blend_transparent(frame[y:y+w,x:x+h,:], overlay_image)

        if (len(contours)==3):

            
            M = cv2.moments(contours[0])
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])

            writecsv("blue","triangle",(cx,cy))

            x,y,w,h = cv2.boundingRect(contours[0])

            overlay_image = cv2.resize(image_blue,(h,w))

            frame[y:y+w,x:x+h,:] = blend_transparent(frame[y:y+w,x:x+h,:], overlay_image)

        if (len(contours)==4):

            

            M = cv2.moments(contours[2])
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])

            writecsv("red","rhombus",(cx,cy))
            
            x,y,w,h = cv2.boundingRect(contours[2])

            overlay_image = cv2.resize(image_red,(h,w))

            frame[y:y+w,x:x+h,:] = blend_transparent(frame[y:y+w,x:x+h,:], overlay_image)


        if (len(contours)==5):

            
            M = cv2.moments(contours[2])
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])

            writecsv("green","pentagon",(cx,cy))
            
            x,y,w,h = cv2.boundingRect(contours[2])

            overlay_image = cv2.resize(image_green,(h,w))

            frame[y:y+w,x:x+h,:] = blend_transparent(frame[y:y+w,x:x+h,:], overlay_image)


        out.write(frame)
        cv2.imshow('frame',frame)
        if cv2.waitKey(40) & 0xFF == ord('q'):
            break

    # When everything done, release the capture
    cap.release()
    out.release()
    cv2.destroyAllWindows()
        
#####################################################################################################
    #sample of overlay code for each frame
    #x,y,w,h = cv2.boundingRect(current_contour)
    #overlay_image = cv2.resize(image_red,(h,w))
    #frame[y:y+w,x:x+h,:] = blend_transparent(frame[y:y+w,x:x+h,:], overlay_image)
#######################################################################################################

#################################################################################################
# DO NOT EDIT!!!
#################################################################################################
#main where the path is set for the directory containing the test images
if __name__ == "__main__":
    main('self')

